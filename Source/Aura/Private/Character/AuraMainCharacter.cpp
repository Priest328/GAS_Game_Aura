// Copyright Maks Martyniuk Sample


#include "Character/AuraMainCharacter.h"

#include "NiagaraComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

void AAuraMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

AAuraMainCharacter::AAuraMainCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("TopDowmSpringArmComp");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->bDoCollisionTest = false;
	
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopdownCameraComp");
	TopDownCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CharacterClass = ECharacterClass::Elementalist;

	SetReplicates(true);
	
	LevelUpNagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComp");
	LevelUpNagaraComponent->SetupAttachment(GetRootComponent(), FName("LevelUpSocket"));
	LevelUpNagaraComponent->bAutoActivate = false;
}

void AAuraMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info on the server
	InitAbilityActorInfo();

	AddCharacterAbilities();
}

void AAuraMainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

int32 AAuraMainCharacter::GetPlayerLevel_Implementation()
{
	const AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);

	return AuraPS->GetPlayerLevel();
}

int32 AAuraMainCharacter::GetXP_Implementation() const
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	return AuraPS->GetPlayerXP();
}

int32 AAuraMainCharacter::FindLevelForXP_Implementation(int32 InXPAmount) const
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	return AuraPS->GetLevelUpInfo()->GetCurrentLevelByXP(InXPAmount);
}

void AAuraMainCharacter::AddToXP_Implementation(int32 InXP)
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	
	AuraPS->AddToPlayerXP(InXP);
}

void AAuraMainCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	AuraPS->AddToLevel(InPlayerLevel);
	
	UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(AuraPS->GetAbilitySystemComponent());
	if (IsValid(ASC))
	{
		ASC->UpdateAbilityStatuses(AuraPS->GetPlayerLevel());
	}
}

int32 AAuraMainCharacter::GetAttributePointsRewards_Implementation(int32 InLevel) const
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	return AuraPS->GetLevelUpInfo()->LevelUpList[InLevel].AttributePointReward;
}

int32 AAuraMainCharacter::GetSpellPointsRewards_Implementation(int32 InLevel) const
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	return AuraPS->GetLevelUpInfo()->LevelUpList[InLevel].SpellPointReward;
}

void AAuraMainCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	
	AuraPS->AddToAttributePoints(InAttributePoints);
}

void AAuraMainCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	
	AuraPS->AddToSpellPoints(InSpellPoints);
}

int32 AAuraMainCharacter::GetAttributePoints_Implementation() const
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	return AuraPS->GetAttributePoints();
}

int32 AAuraMainCharacter::GetSpellPoints_Implementation() const
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	return AuraPS->GetSpellPoints();
}

void AAuraMainCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}

void AAuraMainCharacter::MulticastLevelUpParticles_Implementation() const
{
	if (!IsValid(LevelUpNagaraComponent))
	{
		return;
	}
	
	const FVector CameraLocation = TopDownCameraComponent->GetComponentLocation();
	const FVector NiagaraLocation = LevelUpNagaraComponent->GetComponentLocation();
	const FRotator ToCameraRotation = (CameraLocation-NiagaraLocation).Rotation();
	LevelUpNagaraComponent->SetWorldRotation(ToCameraRotation);
	
	LevelUpNagaraComponent->Activate(true);
}

void AAuraMainCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	AuraPS->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPS, this);
	Cast<UAuraAbilitySystemComponent>(AuraPS->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = AuraPS->GetAbilitySystemComponent();
	AttributeSet = AuraPS->GetAttributeSet();

	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* HUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			HUD->InitOverlay(AuraPlayerController, AuraPS, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}



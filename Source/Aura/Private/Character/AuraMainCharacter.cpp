// Copyright Maks Martyniuk Sample


#include "Character/AuraMainCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

void AAuraMainCharacter::BeginPlay()
{
	Super::BeginPlay();

}

AAuraMainCharacter::AAuraMainCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f,400.0f,0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info on the server
	InitAbilityActorInfo();
}

void AAuraMainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Init ability actor info for the client
	InitAbilityActorInfo();
}

void AAuraMainCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	check(AuraPS);
	AuraPS->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPS,this);
	AbilitySystemComponent = AuraPS->GetAbilitySystemComponent();
	AttributeSet = AuraPS->GetAttributeSet();

	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		
		if (AAuraHUD* HUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
		     HUD->InitOverlay(AuraPlayerController, AuraPS, AbilitySystemComponent, AttributeSet);
		}
	}
}

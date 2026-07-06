// Copyright Maks Martyniuk Sample


#include "Character/AuraCharacter_Base.h"

#include "AuraGameplayTags.h"
#include "NiagaraComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


AAuraCharacter_Base::AAuraCharacter_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetGenerateOverlapEvents(true);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAnimMontage* AAuraCharacter_Base::GetHitReactMontage_Implementation()
{
	return HitReactAnimMontage;
}

void AAuraCharacter_Base::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

bool AAuraCharacter_Base::IsDead_Implementation() const
{
	return bIsCharacterDead;
}

AActor* AAuraCharacter_Base::GetAvatar_Implementation() 
{
	return this;
}

TArray<FTaggedMontage> AAuraCharacter_Base::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* AAuraCharacter_Base::GetBloodEffectSystem_Implementation()
{
	return BloodEffect;
}

FTaggedMontage AAuraCharacter_Base::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (const auto& TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag.MatchesTagExact(MontageTag))
		{
			return TaggedMontage;
		}
	}
	return FTaggedMontage();
}

int32 AAuraCharacter_Base::GetMinionCount_Implementation()
{
	return MinionCount;
}

void AAuraCharacter_Base::IncrementMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

ECharacterClass AAuraCharacter_Base::GetCharacterClass_Implementation() const
{
	return CharacterClass;
}

void AAuraCharacter_Base::Dissolve()
{
	if (IsValid(CharacterDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMaterialIns = UMaterialInstanceDynamic::Create(
			CharacterDissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMaterialIns);

		StartDissolveTimeline(DynamicMaterialIns);
	}
	
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicWeaponMaterialIns = UMaterialInstanceDynamic::Create(
			WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, DynamicWeaponMaterialIns);

		StartDissolveWeaponTimeline(DynamicWeaponMaterialIns);
	}
}


void AAuraCharacter_Base::MulticastHandleDeath_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
	bIsCharacterDead = true;
}


void AAuraCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* AAuraCharacter_Base::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacter_Base::InitAbilityActorInfo()
{
}

void AAuraCharacter_Base::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffect);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(
		GameplayEffect, Level, ContextHandle);

	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacter_Base::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.0f);
}

void AAuraCharacter_Base::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	AuraASC->AddCharacterAbilities(StartupAbilities);
	AuraASC->AddPassiveCharacterAbilities(StartupPassiveAbilities);
}

FVector AAuraCharacter_Base::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageAttackTag)
{

	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	if (MontageAttackTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageAttackTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageAttackTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (MontageAttackTag.MatchesTagExact(GameplayTags.CombatSocket_Tail))
	{
		return GetMesh()->GetSocketLocation(TailTipSocketName);
	}

	return FVector::ZeroVector;
}

// Copyright Maks Martyniuk Sample


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AuraAbilitySystemTypes.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Engine/OverlapResult.h"
#include "Game/AuraGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

bool UAuraAbilitySystemLibrary::MakeWidgetControllerParams(
	const UObject* WorldContextObject,
	FWidgetControllerParams& OutParams
)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!IsValid(PC))
	{
		return false;
	}

	AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if (!IsValid(AuraHUD))
	{
		return false;
	}

	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	if (!IsValid(PS))
	{
		return false;
	}

	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();

	if (!IsValid(ASC) || !IsValid(AS))
	{
		return false;
	}

	OutParams = FWidgetControllerParams(PC, PS, ASC, AS);
	return true;
}

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{	
	FWidgetControllerParams WidgetControllerParams;
	
	if (MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams))
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(WidgetControllerParams.PlayerController->GetHUD());
		if (IsValid(AuraHUD))
		{
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributesMenuWidgetController(
	const UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	
	if (MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams))
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(WidgetControllerParams.PlayerController->GetHUD());
		if (IsValid(AuraHUD))
		{
			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

USpellMenuWidgetController* UAuraAbilitySystemLibrary::GetSpellMenuWidgetController(
	const UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	
	if (MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams))
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(WidgetControllerParams.PlayerController->GetHUD());
		if (IsValid(AuraHUD))
		{
			return AuraHUD->GetSpellMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(
	const UObject* WorldContextObject,
	ECharacterClass CharacterClassType,
	float Level,
	UAbilitySystemComponent* AbilitySystemComponent)
{
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	UCharacterClassInfo* ClassInfo = GetCharacterClassInfo(WorldContextObject);

	check(ClassInfo);

	FCharacterClassDefaultInfo ClassDefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClassType);

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(AbilitySystemComponent->GetAvatarActor());

	// Primary effect
	const FGameplayEffectSpecHandle PrimaryEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(
		ClassDefaultInfo.PrimaryAttributes, Level, ContextHandle);

	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*PrimaryEffectSpec.Data.Get());

	// Secondary effect
	const FGameplayEffectSpecHandle SecondaryEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(
		ClassInfo->SecondaryAttributes, Level, ContextHandle);

	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SecondaryEffectSpec.Data.Get());

	// Vital effect
	const FGameplayEffectSpecHandle VitalEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(
		ClassInfo->VitalAttributes, Level, ContextHandle);

	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*VitalEffectSpec.Data.Get());
}

void UAuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject,
                                                     UAbilitySystemComponent* AbilitySystemComponent,
                                                     ECharacterClass CharacterClassType)
{
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	UCharacterClassInfo* ClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!IsValid(ClassInfo))
	{
		return;
	}

	for (const auto& Ability : ClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}

	const FCharacterClassDefaultInfo& DefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClassType);
	for (const auto& AbilityClass : DefaultInfo.StartupAbilities)
	{
		int32 Level = AbilitySystemComponent->GetAvatarActor()->Implements<UCombatInterface>()
			              ? ICombatInterface::Execute_GetPlayerLevel(AbilitySystemComponent->GetAvatarActor())
			              : 1;

		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, Level);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AAuraGameModeBase* GameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!IsValid(GameMode))
	{
		return nullptr;
	}

	return GameMode->CharacterClassInfo;
}

UAbilityInfo* UAuraAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	const AAuraGameModeBase* GameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!IsValid(GameMode))
	{
		return nullptr;
	}
	return GameMode->AbilityInfo;
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FAuraGameplayEffectContext* AuraContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.
		Get());
	if (AuraContext)
	{
		return AuraContext->IsBlockedHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FAuraGameplayEffectContext* AuraContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.
		Get());
	if (AuraContext)
	{
		return AuraContext->IsCriticalHit();
	}
	return false;
}

void UAuraAbilitySystemLibrary::SetBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	FAuraGameplayEffectContext* AuraContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get());
	if (AuraContext)
	{
		AuraContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UAuraAbilitySystemLibrary::SetCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	FAuraGameplayEffectContext* AuraContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get());
	if (AuraContext)
	{
		AuraContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,
                                                           TArray<AActor*>& OutOverlappingActors,
                                                           const TArray<AActor*>& ActorsToIgnore, float Radius,
                                                           const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,
	                                                             EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity,
		                                FCollisionObjectQueryParams(
			                                FCollisionObjectQueryParams::InitType::AllDynamicObjects),
		                                FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			const bool ImplementsCombatinterface = Overlap.GetActor()->Implements<UCombatInterface>();
			if (!ImplementsCombatinterface)
			{
				continue;
			}

			const bool IsAlive = !ICombatInterface::Execute_IsDead(Overlap.GetActor());
			if (IsAlive)
			{
				OutOverlappingActors.AddUnique(Overlap.GetActor());
			}
		}
	}
}

bool UAuraAbilitySystemLibrary::IsNotFriend(AActor* Actor, AActor* OtherActor)
{
	const bool bIsActorPlayer = Actor->ActorHasTag(FName("Player"));
	const bool bIsOtherActorPlayer = OtherActor->ActorHasTag(FName("Player"));

	const bool bIsActorEnemy = Actor->ActorHasTag(FName("Enemy"));
	const bool bIsOtherActorEnemy = OtherActor->ActorHasTag(FName("Enemy"));

	const bool bIsFriends = (bIsActorEnemy && bIsOtherActorEnemy) || (bIsActorPlayer && bIsOtherActorPlayer);
	return !bIsFriends;
}

int32 UAuraAbilitySystemLibrary::GetXPRewardForClassAndLevel(ECharacterClass ActorClass, int32 CharacterLevel,
                                                             const UObject* WorldContextObject)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!IsValid(CharacterClassInfo))
	{
		return 0;
	}

	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(ActorClass);
	const float XPReward = DefaultInfo.XPReward.GetValueAtLevel(CharacterLevel);

	return static_cast<int32>(XPReward);
}

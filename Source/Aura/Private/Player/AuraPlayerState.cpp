// Copyright Maks Martyniuk Sample


#include "Player/AuraPlayerState.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	SetNetUpdateFrequency(100.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAuraPlayerState, Level);
	DOREPLIFETIME(AAuraPlayerState, PlayerXP);
	DOREPLIFETIME(AAuraPlayerState, AttributePoints);
	DOREPLIFETIME(AAuraPlayerState, SpellPoints);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::SetPlayerXP(int32 XP)
{
	if (!HasAuthority())
	{
		return;
	}
	
	PlayerXP = XP;
	OnXPChangedDelegate.Broadcast(PlayerXP);
}

void AAuraPlayerState::SetPlayerLevel(int32 InLevel)
{
	if (!HasAuthority())
	{
		return;
	}
	
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::AddToPlayerXP(int32 XPToAdd)
{
	if (!HasAuthority())
	{
		return;
	}
	
	PlayerXP += XPToAdd;
	OnXPChangedDelegate.Broadcast(PlayerXP);
}

void AAuraPlayerState::AddToLevel(int32 LevelToAdd)
{
	if (!HasAuthority())
	{
		return;
	}
	
	Level += LevelToAdd;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::AddToAttributePoints(int32 AttributePointsToAdd)
{
	if (!HasAuthority())
	{
		return;
	}
	
	AttributePoints += AttributePointsToAdd;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::AddToSpellPoints(int32 SpellPointsToAdd)
{
	if (!HasAuthority())
	{
		return;
	}
	
	SpellPoints += SpellPointsToAdd;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnXPChangedDelegate.Broadcast(PlayerXP);
}

void AAuraPlayerState::OnRep_PlayerXP(int32 OldPlayerXP)
{
	OnXPChangedDelegate.Broadcast(PlayerXP);
}

void AAuraPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

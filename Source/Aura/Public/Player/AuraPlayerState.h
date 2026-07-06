// Copyright Maks Martyniuk Sample

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChangedSignature, int32 StatValue);

class ULevelUpInfo;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetPlayerXP() const { return PlayerXP; }
	
	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
	FORCEINLINE int32 GetSpellPoints() const { return SpellPoints; }

	FORCEINLINE ULevelUpInfo* GetLevelUpInfo() const { return LevelUpInfo; }

	void SetPlayerXP(int32 XP);

	void SetPlayerLevel(int32 InLevel);

	void AddToPlayerXP(int32 XPToAdd);

	void AddToLevel(int32 LevelToAdd);
	
	void AddToAttributePoints(int32 AttributePointsToAdd);
	
	void AddToSpellPoints(int32 SpellPointsToAdd);
	
private:
	UFUNCTION()
	void OnRep_PlayerXP(int32 OldPlayerXP);
	
	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);
	
	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);

public:
	FOnPlayerStateChangedSignature OnXPChangedDelegate;

	FOnPlayerStateChangedSignature OnLevelChangedDelegate;
	
	FOnPlayerStateChangedSignature OnAttributePointsChangedDelegate;
	
	FOnPlayerStateChangedSignature OnSpellPointsChangedDelegate;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_PlayerXP)
	int32 PlayerXP = 1;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_AttributePoints)
	int32 AttributePoints = 0;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_SpellPoints)
	int32 SpellPoints = 0;
};

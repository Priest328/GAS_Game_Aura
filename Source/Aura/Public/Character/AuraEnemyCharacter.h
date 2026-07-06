// Copyright Maks Martyniuk Sample

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacter_Base.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemyCharacter.generated.h"


class UStateTree;
class UBehaviorTree;
class AAuraAIController;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemyCharacter : public AAuraCharacter_Base, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemyCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void InitializeDefaultAttributes() const override;
	
	/*
	 * Enemy Interface
	 */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	virtual void SetCombatTarget_Implementation(AActor* NewCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;

public:
	/*
	 * Combat Interface
	 */
	virtual int32 GetPlayerLevel_Implementation() override;

	virtual void Die() override;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

private:
	void HitReactTagChanged(FGameplayTag Tag, int32 TagCount);

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UStateTree> StateTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsDead = false;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XPReward")
	FScalableFloat XPReward;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "AI")
	TObjectPtr<AAuraAIController> AuraAIController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float BaseWalkSpeed = 300.f;
};

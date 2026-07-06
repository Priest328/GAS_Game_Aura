// Copyright Maks Martyniuk Sample

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter_Base.h"
#include "Interaction/PlayerInterface.h"
#include "AuraMainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraMainCharacter : public AAuraCharacter_Base, public IPlayerInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	AAuraMainCharacter();

	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;

	/*
     * Combat Interface
     */
	virtual int32 GetPlayerLevel_Implementation() override;
	/*
	 * end Combat Interface
	 */
	
	/*
	 * Player Interface
	 */
	virtual int32 GetXP_Implementation() const override;
	
	virtual int32 FindLevelForXP_Implementation(int32 InXPAmount) const override;
	
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	
	virtual void LevelUp_Implementation() override;
	
	virtual int32 GetAttributePointsRewards_Implementation(int32 InLevel) const override;
	virtual int32 GetSpellPointsRewards_Implementation(int32 InLevel) const override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	
	virtual  int32 GetAttributePoints_Implementation() const override;
	virtual  int32 GetSpellPoints_Implementation() const override;
	/*
	 * end Player Interface
	 */
private:
	void InitAbilityActorInfo(); 
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpParticles() const;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LevelUp")
	TObjectPtr<UNiagaraComponent> LevelUpNagaraComponent;
};

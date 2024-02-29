// Copyright Maks Martyniuk Sample

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter_Base.h"
#include "AuraMainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraMainCharacter : public AAuraCharacter_Base
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	AAuraMainCharacter();

	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
private:
	
	void InitAbilityActorInfo(); 
	
};

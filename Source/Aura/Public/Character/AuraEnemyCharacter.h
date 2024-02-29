// Copyright Maks Martyniuk Sample

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter_Base.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemyCharacter : public AAuraCharacter_Base, public IEnemyInterface
{
	GENERATED_BODY()

	
public:
	AAuraEnemyCharacter();


	
	virtual void HighlightActor() override;

	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;
};



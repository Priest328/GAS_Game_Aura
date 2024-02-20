// Copyright Maks Martyniuk Sample

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacter_Base.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:

	AAuraCharacter_Base();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Comabat")
	TObjectPtr<USkeletalMeshComponent> Weapon = nullptr;

	
};

// Copyright Maks Martyniuk Sample

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SummonAbility")
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure, Category = "SummonAbility")
	TSubclassOf<APawn> GetRandomPawnClass();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SummonAbility")
	int32 NumMinionsToSpawn = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SummonAbility")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SummonAbility")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SummonAbility")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SummonAbility")
	float SpawnSpread = 90.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SummonAbility")
	bool bDrawDebug = false;
};

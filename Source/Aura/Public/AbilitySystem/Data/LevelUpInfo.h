// Copyright Maks Martyniuk Sample

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraLevelUpInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 LevelUpRequirement = 0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 AttributePointReward = 1;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 SpellPointReward = 1;
};

/**
 * 
 */
UCLASS()
class AURA_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	int32 GetCurrentLevelByXP(int32 XPAmount) const;

	/*
	 * LevelUpList[0] is an empty placeholder which holds nothing
	 * LevelUpList[1] == first level info
	 * LevelUpList[2] == second level info
	 * ...
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraLevelUpInfo> LevelUpList;
};

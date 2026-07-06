// Copyright Maks Martyniuk Sample


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::GetCurrentLevelByXP(int32 XPAmount) const
{
	if (LevelUpList.Num() <= 1)
	{
		return 0;
	}

	int32 CurrentLevel = 0;

	for (int32 i = 0; i < LevelUpList.Num(); ++i)
	{
		if (XPAmount < LevelUpList[i].LevelUpRequirement)
		{
			break;
		}

		CurrentLevel = i;
	}

	return CurrentLevel + 1;
}
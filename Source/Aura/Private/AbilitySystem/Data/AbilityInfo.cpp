// Copyright Maks Martyniuk Sample


#include "AbilitySystem/Data/AbilityInfo.h"

#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& GameplayTag, bool bLogNotFound)
{
	for (const auto& AbilityInfo : AbilitiesInfo)
	{
		if (AbilityInfo.AbilityTag == GameplayTag)
		{
			return AbilityInfo;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can`t find info for AbilityTag [%s] on AbilityInfo [%s]"), *GameplayTag.ToString(),
		       *GetNameSafe(this));
	}

	return FAuraAbilityInfo();
}

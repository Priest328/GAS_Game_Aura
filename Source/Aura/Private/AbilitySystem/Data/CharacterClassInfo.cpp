// Copyright Maks Martyniuk Sample


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass TargetClassType)
{
	return CharacterClassInfo.FindChecked(TargetClassType);
}

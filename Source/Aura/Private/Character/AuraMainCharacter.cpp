// Copyright Maks Martyniuk Sample


#include "Character/AuraMainCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AAuraMainCharacter::AAuraMainCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f,400.0f,0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

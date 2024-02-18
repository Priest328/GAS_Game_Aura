// Copyright Maks Martyniuk Sample


#include "AuraCharacter_Base.h"

// Sets default values
AAuraCharacter_Base::AAuraCharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAuraCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAuraCharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAuraCharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


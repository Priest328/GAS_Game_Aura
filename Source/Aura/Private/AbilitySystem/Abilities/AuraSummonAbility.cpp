// Copyright Maks Martyniuk Sample


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector ForwardVector = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();

	const FVector RightSpread = ForwardVector.RotateAngleAxis(SpawnSpread / 2.f, FVector::UpVector);
	const FVector LeftSpread = ForwardVector.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	const float DeltaSpread = SpawnSpread / NumMinionsToSpawn;

	TArray<FVector> SpawnLocations;

	for (int i = 0; i < NumMinionsToSpawn; i++)
	{
		const FVector DirectionVector = LeftSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + DirectionVector * FMath::RandRange(
			MinSpawnDistance, MaxSpawnDistance);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, ChosenSpawnLocation + FVector(0.f,0.f,400.f), ChosenSpawnLocation - FVector(0.f,0.f,400.f), ECC_Visibility);

		if (HitResult.bBlockingHit)
		{
			ChosenSpawnLocation = HitResult.ImpactPoint;
		}
		
		if (bDrawDebug)
		{
			UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location,
			                                     Location + DirectionVector * MaxSpawnDistance, 4.f, FColor::Green,
			                                     5.f);

			DrawDebugSphere(GetAvatarActorFromActorInfo()->GetWorld(), Location + DirectionVector * MinSpawnDistance,
			                10.f, 12, FColor::Red, false, 3.f);
			DrawDebugSphere(GetAvatarActorFromActorInfo()->GetWorld(), Location + DirectionVector * MaxSpawnDistance,
			                10.f, 12, FColor::Red, false, 3.f);
			
			DrawDebugSphere(GetAvatarActorFromActorInfo()->GetWorld(), ChosenSpawnLocation,
			                10.f, 12, FColor::Blue, false, 3.f);
		}

		SpawnLocations.Add(ChosenSpawnLocation);
	}
	
	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomPawnClass()
{
	TSubclassOf<APawn>* TargetItem = GetRandomArrayItem(MinionClasses);
	if (TargetItem)
	{
		return *TargetItem;
	}
	
	return nullptr;
}

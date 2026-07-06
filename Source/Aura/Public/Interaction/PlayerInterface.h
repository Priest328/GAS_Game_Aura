// Copyright Maks Martyniuk Sample

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetXP() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 FindLevelForXP(int32 InXPAmount) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetAttributePointsRewards(int32 InLevel) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetSpellPointsRewards(int32 InLevel) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetAttributePoints() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetSpellPoints() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddToPlayerLevel(int32 InPlayerLevel);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddToAttributePoints(int32 InAttributePoints);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddToSpellPoints(int32 InSpellPoints);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddToXP(int32 InXP);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LevelUp();
};

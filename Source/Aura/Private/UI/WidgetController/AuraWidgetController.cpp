// Copyright Maks Martyniuk Sample


#include "UI/WidgetController/AuraWidgetController.h"

#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}

AAuraPlayerController* UAuraWidgetController::GetAuraPlayerController()
{
	if (IsValid(AuraPlayerController))
	{
		return AuraPlayerController;
	}
	
	AuraPlayerController = Cast<AAuraPlayerController>(PlayerController);
	return AuraPlayerController;
}

AAuraPlayerState* UAuraWidgetController::GetAuraPlayerState()
{
	if (IsValid(AuraPlayerState))
	{
		return AuraPlayerState;
	}
	
	AuraPlayerState = Cast<AAuraPlayerState>(PlayerState);
	return AuraPlayerState;
}

UAuraAbilitySystemComponent* UAuraWidgetController::GetAuraAbilitySystemComponent()
{
	if (IsValid(AuraAbilitySystemComponent))
	{
		return AuraAbilitySystemComponent;
	}
	
	AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	return AuraAbilitySystemComponent;
}

UAuraAttributeSet* UAuraWidgetController::GetAuraAttributeSet()
{
	if (IsValid(AuraAttributeSet))
	{
		return AuraAttributeSet;
	}
	
	AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	return AuraAttributeSet;
}

void UAuraWidgetController::BroadcastAbiltyInfo()
{
	if (!GetAuraAbilitySystemComponent()->bStartupAbilitiesGiven)
	{
		return;
	}

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& Spec)
	{
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(UAuraAbilitySystemComponent::GetAbilityTagFromSpec(Spec));
		Info.AbilityInputTag = UAuraAbilitySystemComponent::GetInputTagFromSpec(Spec);
		Info.StatusTag = UAuraAbilitySystemComponent::GetStatusFromSpec(Spec);
		 
		AbilityInfoDelegate.Broadcast(Info);
	});
	GetAuraAbilitySystemComponent()->ForEachAbility(BroadcastDelegate);
}

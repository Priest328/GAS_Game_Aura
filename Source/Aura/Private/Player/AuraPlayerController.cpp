// Copyright Maks Martyniuk Sample


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraMappingContext,0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 * Line trace from cursor. 5 scenarious:
	 *  1. LastActor is null && CurrentActor is null
	 *		- Do nothing
	 *	2. LastActor is null && CurrentActor is valid
	 *		- Highlight CurrentActor
	 *	3. LastActor is valid && CurrentActor is null
	 *		- UnHighlight LastActor
	 *	4. Both actors are valid, but LastActor != CurrentActor
	 *		- UnHighlight LastActor, and Highlight CurrentActor
	 *	5. Both actors are valid, and are the same actor
	 *		- Do nothing**/

	if (LastActor == nullptr)
	{
		if (CurrentActor !=nullptr)
		{
			// Case 2
			CurrentActor->HighlightActor();
		}
		else
		{
			// Case 1
		}
	}
	else // LastActor is valid
	{
		if (CurrentActor == nullptr)
		{
			// Case 3
			LastActor->UnHighlightActor();
		}
		else // Both are valid
		{
			if (LastActor != CurrentActor)
			{
				// Case 4
				LastActor->UnHighlightActor();
				CurrentActor->HighlightActor();
			}
			else
			{
				// Case 5
			}
		}
	}
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation =  GetControlRotation();
	const FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

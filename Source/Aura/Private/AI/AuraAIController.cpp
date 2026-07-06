// Copyright Maks Martyniuk Sample


#include "AI/AuraAIController.h"

#include "StateTree.h"
#include "Character/AuraEnemyCharacter.h"
#include "Components/StateTreeComponent.h"

AAuraAIController::AAuraAIController()
{
	StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>("BehaviorTreeComp");
	StateTreeComponent->SetStartLogicAutomatically(false);
}

void AAuraAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (StateTreeComponent->GetStateTreeRunStatus() == EStateTreeRunStatus::Unset)
	{
		AAuraEnemyCharacter* EnemyCharacter = Cast<AAuraEnemyCharacter>(InPawn);
		if (IsValid(EnemyCharacter) && IsValid(EnemyCharacter->StateTree))
		{
			StateTreeComponent->SetStateTree(EnemyCharacter->StateTree);
			StateTreeComponent->StartLogic();
		}
	}
}

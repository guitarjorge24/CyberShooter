// Copyright of Jorge Luque

#include "CS_AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"

void ACS_AIController::BeginPlay()
{
	Super::BeginPlay();

	if(BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}

	// used to be needed before we used the Behavior Tree asset. Kept for reference.
	// PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ACS_AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// This logic below was replaced by the Behavior Tree asset. Kept for reference.
	// if(LineOfSightTo(PlayerPawn))
	// {
	// 	SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
	// 	MoveToActor(PlayerPawn, GoalRadius);		
	// }
	// else
	// {
	// 	ClearFocus(EAIFocusPriority::Gameplay);
	// 	StopMovement();
	// }
}
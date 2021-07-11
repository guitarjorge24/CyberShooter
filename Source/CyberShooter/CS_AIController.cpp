// Copyright of Jorge Luque

#include "CS_AIController.h"

#include "CS_Character.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ACS_AIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

		Cast<ACharacter>(GetPawn())->GetCharacterMovement()->MaxWalkSpeed = 400.f;
	}
}

void ACS_AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// This logic was replaced by the custom BT services like UBTService_PlayerLocation and UBTService_PlayerLocationIfSeen 
	// if(LineOfSightTo(PlayerPawn))
	// {
	// 	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	// 	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	// }
	// else
	// {
	// 	GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	// }

	// This logic below was replaced by the default tasks in Behavior Tree asset. Kept for reference.
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

bool ACS_AIController::IsDead() const
{
	ACS_Character* ControlledCharacter = Cast<ACS_Character>(GetPawn());

	if (ControlledCharacter)
	{
		return ControlledCharacter->IsDead();
	}

	// If ControlledCharacter is null, meaning the AI Controller is not controlling a pawn, then the AI must be dead
	// because we only call DetachFromControllerPendingDestroy() when a character dies.
	return true;
}

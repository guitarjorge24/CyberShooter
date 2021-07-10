// Copyright of Jorge Luque


#include "CS_PlayerController.h"

void ACS_PlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UE_LOG(LogTemp, Warning, TEXT("Game Ended. Did the player win? %s"), bIsWinner ? TEXT("true") : TEXT("false"));

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
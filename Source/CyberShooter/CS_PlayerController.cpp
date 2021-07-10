// Copyright of Jorge Luque


#include "CS_PlayerController.h"
#include "Blueprint/UserWidget.h"

void ACS_PlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UE_LOG(LogTemp, Warning, TEXT("Game Ended. Did the player win? %s"), bIsWinner ? TEXT("true") : TEXT("false"));

	UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass, TEXT("Player Lose Screen"));
	if (LoseScreen)
	{
		LoseScreen->AddToViewport();
	}
	
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
	
}

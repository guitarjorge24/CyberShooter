// Copyright of Jorge Luque

#include "CS_PlayerController.h"
#include "Blueprint/UserWidget.h"

void ACS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	HUD = CreateWidget(this, HUDClass, TEXT("Player HUD"));
	if (HUD)
	{
		HUD->AddToViewport();
	}
}

void ACS_PlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UE_LOG(LogTemp, Warning, TEXT("Game Ended. Did the player win? %s"), bIsWinner ? TEXT("true") : TEXT("false"));

	HUD->RemoveFromViewport();
	
	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass, TEXT("Game Win Screen"));
		if (WinScreen)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass, TEXT("Game Lose Screen"));
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}
	
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

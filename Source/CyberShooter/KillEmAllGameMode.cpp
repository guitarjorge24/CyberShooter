// Copyright of Jorge Luque

#include "KillEmAllGameMode.h"
#include "CS_AIController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp, Warning, TEXT(" The pawn killed was: %s"), *PawnKilled->GetName());

	// If the player pawn is the one who was killed
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		EndGame(false);
	}

	// Go through all the existing enemy AI
	for(ACS_AIController* CS_AIController : TActorRange<ACS_AIController>(GetWorld()))
	{
		if(!CS_AIController->IsDead())
		{
			// Don't end the game if there are still AI enemies living
			return;
		}
		// End game if there are no living AI
	}
	
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) const
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		const bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

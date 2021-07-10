// Copyright of Jorge Luque


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp, Warning, TEXT(" The pawn killed was: %s"), *PawnKilled->GetName());
}
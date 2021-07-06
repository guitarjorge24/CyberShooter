// Copyright of Jorge Luque

#include "CS_AIController.h"
#include "Kismet/GameplayStatics.h"

void ACS_AIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
}

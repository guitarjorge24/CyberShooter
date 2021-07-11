// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "CyberShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CYBERSHOOTER_API AKillEmAllGameMode : public ACyberShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

	private:
	void EndGame(bool bIsPlayerWinner) const;
};

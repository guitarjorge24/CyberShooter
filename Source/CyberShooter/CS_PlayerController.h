// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CS_PlayerController.generated.h"

/** Custom PlayerController class */
UCLASS()
class CYBERSHOOTER_API ACS_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void GameHasEnded(AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	FTimerHandle RestartTimer;
};
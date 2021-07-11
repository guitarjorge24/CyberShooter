// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CS_AIController.generated.h"

UCLASS()
class CYBERSHOOTER_API ACS_AIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY()
	APawn* PlayerPawn;

	// Used to be needed before we used the Behavior Tree asset. Kept for reference.
	/** @brief How close to the player the AI needs to be before it stops moving towards the player. */
	// UPROPERTY(EditAnywhere)
	// float GoalRadius = 200.f;
};

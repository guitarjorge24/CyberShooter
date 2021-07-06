// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CS_AIController.generated.h"

UCLASS()
class CYBERSHOOTER_API ACS_AIController : public AAIController
{
	GENERATED_BODY()

	protected:
	virtual void BeginPlay() override;
	
};

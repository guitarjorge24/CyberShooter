// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocation.generated.h"

/** Set  BB key to Player's Location. */
UCLASS()
class CYBERSHOOTER_API UBTService_PlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerLocation();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

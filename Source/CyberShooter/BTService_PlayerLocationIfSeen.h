// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocationIfSeen.generated.h"

/** If Player is seen, set  BB key to Player's Location. Else, clear BB key value. */
UCLASS()
class CYBERSHOOTER_API UBTService_PlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	public:
	UBTService_PlayerLocationIfSeen();

	protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};

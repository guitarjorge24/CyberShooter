// Copyright of Jorge Luque

#include "BTTask_Shoot.h"
#include "AIController.h"
#include "CS_Character.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner()) { return EBTNodeResult::Failed; }
	
	ACS_Character* Character =  Cast<ACS_Character>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (!Character) { return EBTNodeResult::Failed; }

	Character->Shoot();
	return EBTNodeResult::Succeeded;
}

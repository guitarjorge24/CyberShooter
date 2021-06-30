// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CS_Character.generated.h"

UCLASS()
class CYBERSHOOTER_API ACS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ACS_Character();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
};

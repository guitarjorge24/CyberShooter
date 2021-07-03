// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class CYBERSHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* GunRoot;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;
};

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
	void PullTrigger();
	void AutoSetOwnerController();

protected:
	virtual void BeginPlay() override;

private:
	AController* OwnerController;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* GunRoot;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* ImpactParticle;
	UPROPERTY(EditAnywhere, Category="Effects")
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere, Category="Effects")
	USoundBase* ImpactSound;
	
	
	UPROPERTY(EditAnywhere)
	float FiringRange = 3000.f;
	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	void ShootLineTrace(FHitResult& OutHit, FVector& ShotDirection, bool bDrawDebug) const;
};

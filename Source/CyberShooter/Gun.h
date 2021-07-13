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

	/**
 	* @brief 
 	* @param OutHit The HitResult containing the impact location and whether there was an impact or not
 	* @param OutShotDirection The direction opposite to the direction of the bullet's velocity. The direction to the location
 	* where the gun was fired, from the perspective of the impact location.
 	* @param bDrawDebug Whether the bullet line trace should be drawn to the screen or not. Also draws camera and impact point.
 	*/

	void ShootLineTrace(FHitResult& OutHit, FVector& OutShotDirection, bool bDrawDebug) const;
};

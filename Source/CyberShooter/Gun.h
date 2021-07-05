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

protected:
	virtual void BeginPlay() override;

private:
	void ShootLineTrace(FHitResult& OutHit, FVector ViewPointLocation, FRotator ViewPointRotation,
	                    FVector TraceEndLocation, bool bDrawDebug) const;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* GunRoot;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="VFX")
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category="VFX")
	UParticleSystem* ImpactParticle;

	UPROPERTY(EditAnywhere)
	float FiringRange = 3000.f;
};

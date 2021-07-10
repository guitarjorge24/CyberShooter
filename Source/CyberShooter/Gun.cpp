// Copyright of Jorge Luque

#include "Gun.h"

#include "CS_Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	GunRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Root"));
	SetRootComponent(GunRoot);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	Mesh->SetupAttachment(GunRoot);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	// Use SpawnEmitterAttached instead of SpawnEmitterAtLocation because in case there's smoke coming out of the gun
	// muzzle, we want that smoke trail to follow the weapon's location.
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return;

	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	// calls APlayerController::GetPlayerViewPoint and not AController::GetPlayerViewPoint
	// since the OwnerPawn is an ACS_Character which uses APlayerController instead of AController
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

	FVector TraceEndLocation = ViewPointLocation + (ViewPointRotation.Vector() * FiringRange);

	FHitResult HitResult;
	ShootLineTrace(HitResult, ViewPointLocation, ViewPointRotation, TraceEndLocation, true);

	// Alternate way to trace & draw line + impact point using the BP Kismet node LineTraceByChannel.
	// UKismetSystemLibrary::LineTraceSingle(
	// 	GetWorld(), ViewPointLocation, TraceEndLocation,
	// 	UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false,
	// 	TArray<AActor*>(), EDrawDebugTrace::Type::Persistent, HitResult, true,
	// 	FLinearColor::Red);

	if (HitResult.bBlockingHit)
	{
		// #ToDoJ: Does the particle effect look better if shoots towards the player camera or the wall's normal?
		// We can set the particle rotation to PlayerViewOppositeDirection.Rotation() or HitResult.Normal.Rotation()
		// Using the normal looks more realistic, the VFX is more noticeable when emitting towards the player.
		FVector BulletViewOppositeDirection = -ViewPointRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, HitResult.Location, HitResult.Normal.Rotation());

		if (HitResult.GetActor())
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, BulletViewOppositeDirection, nullptr);
			HitResult.GetActor()->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}



void AGun::ShootLineTrace(FHitResult& OutHit, FVector ViewPointLocation, FRotator ViewPointRotation,
                          FVector TraceEndLocation, bool bDrawDebug = false) const
{
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(this->GetOwner());
	GetWorld()->LineTraceSingleByChannel(OutHit, ViewPointLocation, TraceEndLocation, ECC_GameTraceChannel1, Params);

	if (!bDrawDebug) { return; }

	// Draws the location and rotation of the player's camera which is where the linetrace is shooting from
	DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90.f,
	                2.f, FColor::Cyan, true);

	// Draw the line of the bullet and the impact point the old school way:
	DrawDebugLine(GetWorld(), ViewPointLocation, TraceEndLocation, FColor::Blue, true);
	if (OutHit.bBlockingHit)
	{
		DrawDebugPoint(GetWorld(), OutHit.Location, 20.f, FColor::Red, true);
	}
}

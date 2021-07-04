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
	if(!OwnerPawn) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return;

	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	// calls APlayerController::GetPlayerViewPoint and not AController::GetPlayerViewPoint since the OwnerPawn is an ACS_Character which uses APlayerController instead of AController
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	
	DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90.f,
	                2.f, FColor::Red, true);
}

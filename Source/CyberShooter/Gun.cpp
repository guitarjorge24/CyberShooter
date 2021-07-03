// Copyright of Jorge Luque

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"

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
// Copyright of Jorge Luque

#include "CS_Character.h"
#include "Gun.h"

ACS_Character::ACS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACS_Character::BeginPlay()
{
	Super::BeginPlay();
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	// Hide the gun that comes with the Wraith skeletal mesh so we can spawn our own gun.
	GetMesh()->HideBoneByName(TEXT("weapon_r"), PBO_None);
	// Attack our own gun to the socket we created that is under the weapon_r bone.
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

void ACS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}	

void ACS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACS_Character::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ACS_Character::LookUpRate);
	
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACS_Character::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ACS_Character::LookRightRate);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &ACS_Character::Shoot);
}

void ACS_Character::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ACS_Character::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ACS_Character::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(LookUpRotationRate * AxisValue * GetWorld()->GetDeltaSeconds());
}

void ACS_Character::LookRightRate(float AxisValue)
{
	AddControllerYawInput(LookRightRotationRate * AxisValue * GetWorld()->GetDeltaSeconds());
}

void ACS_Character::Shoot()
{
	if(ensure(Gun))
	{
		Gun->PullTrigger();
	}
}





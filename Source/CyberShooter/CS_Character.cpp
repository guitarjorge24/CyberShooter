// Copyright of Jorge Luque

#include "CS_Character.h"

#include "CyberShooterGameModeBase.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"


ACS_Character::ACS_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACS_Character::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

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

float ACS_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(CurrentHealth, DamageToApply); // the most damage we can apply should be the remaining HP.
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth: %f"), CurrentHealth);

	if (IsDead())
	{
		ACyberShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ACyberShooterGameModeBase>();
		if (GameMode) { GameMode->PawnKilled(this); }

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// SetActorEnableCollision(false); // turns off all collisions from all components in the actor
	}

	return DamageToApply;
}

bool ACS_Character::IsDead() const
{
	return CurrentHealth <= 0;
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
	if (ensure(Gun))
	{
		Gun->PullTrigger();
	}
}

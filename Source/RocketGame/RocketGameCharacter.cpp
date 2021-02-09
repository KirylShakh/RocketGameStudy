// Copyright Epic Games, Inc. All Rights Reserved.

#include "RocketGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ARocketGameCharacter::ARocketGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void ARocketGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	Rockets = StartingRockets;
	Health = StartingHealth;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARocketGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARocketGameCharacter::LaunchRocket);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ARocketGameCharacter::LaunchRocketReleased);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ARocketGameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ARocketGameCharacter::TouchStopped);
}

void ARocketGameCharacter::LaunchRocket()
{
	bTapActive = true;
	if (TapTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(TapTimerHandle);
	}
	GetWorldTimerManager().SetTimer(TapTimerHandle, this, &ARocketGameCharacter::OnTapTimerTick, CorrectionTickDuration, true);

	if (!GetMovementComponent()->IsFalling())
	{
		LaunchCharacter(FVector(0, ImpulseY, ImpulseZ), false, false);
		Rockets--;
		Health--;
	}
}

void ARocketGameCharacter::LaunchRocketReleased()
{
	bTapActive = false;
	if (TapTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(TapTimerHandle);
	}
}

void ARocketGameCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	LaunchRocket();
}

void ARocketGameCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	LaunchRocketReleased();
}

//////////////////////////////////////////////////////////////////////////
// Movement Logic

void ARocketGameCharacter::OnTapTimerTick()
{
	if (bTapActive && GetMovementComponent()->IsFalling())
	{
		LaunchCharacter(FVector(0.f, CorrectY, CorrectZ), false, false);
	}
}

void ARocketGameCharacter::Die()
{
	DisableInput(Cast<APlayerController>(GetController()));
	OnCrash();
}

void ARocketGameCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (Rockets <= 0 || Health <= 0)
	{
		Die();
	}
}

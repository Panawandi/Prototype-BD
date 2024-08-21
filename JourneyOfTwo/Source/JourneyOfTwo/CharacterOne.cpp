// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterOne.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"

// Sets default values
ACharacterOne::ACharacterOne()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Disable character rotation with the camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Allow the character to orient its rotation to movement direction
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("FreeCamera"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;

	// Initialize sliding properties
	bIsSliding = false;
	DefaultCapsuleHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

}

// Called when the game starts or when spawned
void ACharacterOne::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterOne::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Create inputs
	PlayerInputComponent->BindAction("Space", IE_Pressed, this, &ACharacterOne::Jump);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacterOne::StartSlide);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACharacterOne::EndSlide);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterOne::MoveForward);
	PlayerInputComponent->BindAxis("MoveSides", this, &ACharacterOne::MoveSides);

	PlayerInputComponent->BindAxis("TurnCamera", this, &ACharacterOne::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterOne::LookUp);

}

// Move methods

void ACharacterOne::MoveForward(float InputValue)
{
	if (Controller && InputValue != 0.0f)
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, InputValue);
	}
}

void ACharacterOne::MoveSides(float InputValue)
{
	if (Controller && InputValue != 0.0f)
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, InputValue);
	};
}

// Camera turn methods

void ACharacterOne::Turn(float InputValue)
{
	AddControllerYawInput(InputValue);
}

void ACharacterOne::LookUp(float InputValue)
{
	AddControllerPitchInput(InputValue);
}

// Sliding methods

void ACharacterOne::StartSlide()
{
	if (IsRunning() && !bIsSliding)  // Ensure sliding only starts if character is running and not already sliding
	{
		bIsSliding = true;
		GetCharacterMovement()->MaxWalkSpeed *= SlideSpeedMultiplier;
		GetCapsuleComponent()->SetCapsuleHalfHeight(SlideCapsuleHalfHeight);

		// Optional: Start a timer to auto-end the slide after SlideDuration
		GetWorldTimerManager().SetTimer(SlideTimerHandle, this, &ACharacterOne::EndSlide, SlideDuration, false);
	}
}

void ACharacterOne::EndSlide()
{
	UnCrouch();
	if (bIsSliding)
	{
		GetCharacterMovement()->MaxWalkSpeed /= SlideSpeedMultiplier;
		GetCapsuleComponent()->SetCapsuleHalfHeight(DefaultCapsuleHalfHeight);
		bIsSliding = false;
	}
}

bool ACharacterOne::IsRunning()
{
	return GetVelocity().Size() > 475.0f;
}
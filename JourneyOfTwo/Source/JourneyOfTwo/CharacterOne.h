// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterOne.generated.h"

UCLASS()
class JOURNEYOFTWO_API ACharacterOne : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterOne();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Components
	UPROPERTY(EditAnywhere)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* FollowCamera;

	// Movement functions
	void MoveForward(float InputValue);
	void MoveSides(float InputValue);

	// Camera functions
	void Turn(float InputValue);
	void LookUp(float InputValue);

	// Sliding functions
	void StartSlide();
	void EndSlide();
	bool IsRunning();

	// Sliding properties
	bool bIsSliding;
	FTimerHandle SlideTimerHandle;

	// Configurable slide parameters
	UPROPERTY(EditAnywhere, Category = "Slide")
		float SlideDuration = 0.5f; // Slide lasts half a second

	UPROPERTY(EditAnywhere, Category = "Slide")
		float SlideSpeedMultiplier = 1.5f; // Increase speed by 50% during slide

	UPROPERTY(EditAnywhere, Category = "Slide")
		float SlideCapsuleHalfHeight = 42.0f; // Capsule height during slide
		float DefaultCapsuleHalfHeight; // Default capsule height to revert after slide

};

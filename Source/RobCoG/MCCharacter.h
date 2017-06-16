// Copyright 2017, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Animation/SkeletalMeshActor.h"
#include "MotionControllerComponent.h"
#include "PIDController3D.h"
#include "MCHand.h"
#include "MCCharacter.generated.h"

UCLASS()
class ROBCOG_API AMCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCCharacter(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Left hand skeletal mesh
	UPROPERTY(EditAnywhere, Category = "MC|Hands")
	ASkeletalMeshActor* LeftHand;

	// Right hand skeletal mesh
	UPROPERTY(EditAnywhere, Category = "MC|Hands")
	ASkeletalMeshActor* RightHand;

	// Show motion controller pose arrows
	UPROPERTY(EditAnywhere, Category = "MC|Hands")
	bool bShowTargetArrows;

	// PID controller proportional argument
	UPROPERTY(EditAnywhere, Category = "MC|Control")
	float PGain;
	
	// PID controller integral argument
	UPROPERTY(EditAnywhere, Category = "MC|Control")
	float IGain;
	
	// PID controller derivative argument
	UPROPERTY(EditAnywhere, Category = "MC|Control")
	float DGain;
	
	// PID controller maximum output (absolute value)
	UPROPERTY(EditAnywhere, Category = "MC|Control")
	float PIDMaxAbsOutput;

	// Hand rotation controller boost
	UPROPERTY(EditAnywhere, Category = "MC|Control")
	float RotationBoost;
	
	// Handles moving forward/backward
	void MoveForward(const float Val);

	// Handles strafing Left/Right
	void MoveRight(const float Val);

	// Update hand positions
	FORCEINLINE void UpdateHandLocationAndRotation(
		UMotionControllerComponent* MC,
		USkeletalMeshComponent* SkelMesh,
		PIDController3D& PIDController,
		const float DeltaTime);

	// Update left hand grasp
	void GraspWithLeftHand(const float Val);

	// Update right hand grasp
	void GraspWithRightHand(const float Val);

	// Attach to left hand
	void AttachToLeftHand();

	// Attach to right hand
	void AttachToRightHand();

	// Character camera
	UCameraComponent* CharCamera;

	// Motion controller origin parent
	USceneComponent* MCOriginComponent;

	// Left hand motion controller
	UMotionControllerComponent* MCLeft;

	// Right hand motion controller
	UMotionControllerComponent* MCRight;

	// Left target arrow visual
	UArrowComponent* LeftTargetArrow;

	// Right target arrow visual
	UArrowComponent* RightTargetArrow;

	// Left hand controller
	PIDController3D LeftPIDController;

	// Right hand controller
	PIDController3D RightPIDController;

	// Left hand control body
	FBodyInstance* LeftControlBody;

	// Right hand control body
	FBodyInstance* RightControlBody;

	// Left MC hand // TODO look into delegates to avoid dynamic casting
	AMCHand* MCLeftHand;

	// Right MC hand
	AMCHand* MCRightHand;

};

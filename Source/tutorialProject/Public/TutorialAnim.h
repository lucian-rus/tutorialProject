// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TutorialAnim.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIALPROJECT_API UTutorialAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;

	/* make these variables accessible through blueprints */
	UPROPERTY(BlueprintReadOnly)
	class AModelCharacter* ModelCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* ModelCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float groundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float previousGroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool isFalling;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool isAccelerating;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool isDecelerating;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool isAttacking;
};

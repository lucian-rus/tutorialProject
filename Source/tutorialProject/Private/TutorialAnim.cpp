// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialAnim.h"
#include "ModelCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UTutorialAnim::NativeInitializeAnimation() {
    Super::NativeInitializeAnimation();

    /* do casting - Cast in unreal engine is different from normal c++ cast */
    ModelCharacter = Cast<AModelCharacter>(TryGetPawnOwner());

    /* basically do what we were doing in the blueprint */
    if(nullptr != ModelCharacter) {
        ModelCharacterMovement = ModelCharacter->GetCharacterMovement();
    }
}

void UTutorialAnim::NativeUpdateAnimation(float deltaTime) {
    Super::NativeUpdateAnimation(deltaTime);

    /* check for movement */
    if(nullptr != ModelCharacterMovement) {
        groundSpeed = UKismetMathLibrary::VSizeXY(ModelCharacterMovement->Velocity);

        if(groundSpeed > previousGroundSpeed) {
            isAccelerating = true;
            isDecelerating = false;
        }

        if(groundSpeed < previousGroundSpeed) {
            isAccelerating = false;
            isDecelerating = true;
        }

        if(groundSpeed == previousGroundSpeed) {
            isAccelerating = false;
            isDecelerating = false;
        }

        UE_LOG(LogTemp, Warning, TEXT("moving at %f, previous %f, attacking %d"), groundSpeed, previousGroundSpeed, isAttacking);

        previousGroundSpeed = groundSpeed;
        isFalling = ModelCharacterMovement->IsFalling();
    }
}

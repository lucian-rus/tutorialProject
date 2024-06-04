// Fill out your copyright notice in the Description page of Project Settings.


#include "ModelCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AModelCharacter::AModelCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.0f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AModelCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AModelCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AModelCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AModelCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AModelCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("UpDown"), this, &AModelCharacter::UpDown);

	PlayerInputComponent->BindAction(FName("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}


void AModelCharacter::MoveForward(float value) 
{
	/* explicit checks. this differs from the bird as it allows backwards movement */
	if((nullptr != Controller) && (0.0f != value)) {
		const FRotator control = GetControlRotation();
		const FRotator yaw(0.0f, control.Yaw, 0.0f);

		/* CHECK THE MATHS !!! */
		const FVector direction = FRotationMatrix(yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}

void AModelCharacter::MoveRight(float value) 
{
	/* explicit checks. this differs from the bird as it allows backwards movement */
	if((nullptr != Controller) && (0.0f != value)) {
		const FRotator control = GetControlRotation();
		const FRotator yaw(0.0f, control.Yaw, 0.0f);

		/* CHECK THE MATHS !!! */
		const FVector direction = FRotationMatrix(yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, value);
	}
}

void AModelCharacter::Turn(float value) {
	AddControllerYawInput(value);
}

void AModelCharacter::UpDown(float value) {
	AddControllerPitchInput(value);
}

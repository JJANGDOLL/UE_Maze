// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharcater.h"
#include "GameFramework/PlayerInput.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"

// Sets default values
AMainCharcater::AMainCharcater()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    _mainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    _mainCamera->SetupAttachment(GetCapsuleComponent());
    _mainCamera->SetRelativeLocation(FVector(0, 0, 64.f)); // Position the camera
    _mainCamera->bUsePawnControlRotation = true;

    _flashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
    _flashLight->SetupAttachment(_mainCamera);
    _flashLight->SetRelativeLocation(FVector(0, 0, -40.f));
    _flashLight->Intensity = 10000.0f;
    _flashLight->InnerConeAngle = 15.0f;
    _flashLight->OuterConeAngle = 22.0f;
    _flashLight->AttenuationRadius = 3500.f;
}

// Called when the game starts or when spawned
void AMainCharcater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharcater::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

//     if (!MovementInput.IsZero())
//     {
//         MovementInput *= 100;
// 
//         FVector InputVector = FVector(0, 0, 0);
//         InputVector += GetActorForwardVector() * MovementInput.X * DeltaTime;
//         InputVector += GetActorRightVector() * MovementInput.Y * DeltaTime;
// 
//         GetCharacterMovement()->AddInputVector(InputVector);
// 
//         GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("x- %f, y - %f, z - %f"), InputVector.X, InputVector.Y, InputVector.Z));
//     }
// 
//     if (!CameraInput.IsNearlyZero())
//     {
//         FRotator NewRotation = GetActorRotation();
// 
//         NewRotation.Yaw += CameraInput.X;
//         NewRotation.Pitch += CameraInput.Y;
// 
//         APlayerController* MyPlayerController = Cast<APlayerController>(GetController());
//         if (MyPlayerController != nullptr)
//         {
//             MyPlayerController->AddYawInput(CameraInput.X);
//             MyPlayerController->AddPitchInput(CameraInput.Y);
//         }
//         SetActorRotation(NewRotation);
// 
//         GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Pitch - %f, Yaw - %f"), NewRotation.Pitch, NewRotation.Yaw));
// 
//     }
}

// Called to bind functionality to input
void AMainCharcater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Forward", this, &AMainCharcater::MoveForward);
    PlayerInputComponent->BindAxis("Back", this, &AMainCharcater::MoveForward);
    PlayerInputComponent->BindAxis("Left", this, &AMainCharcater::MoveRight);
    PlayerInputComponent->BindAxis("Right", this, &AMainCharcater::MoveRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharcater::Jump);

    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);


    FInputAxisKeyMapping forwardKey("Forward", EKeys::W, 1.f);
    FInputAxisKeyMapping backKey("Back", EKeys::S, -1.f);
    FInputAxisKeyMapping rightKey("Right", EKeys::D, 1.f);
    FInputAxisKeyMapping leftKey("Left", EKeys::A, -1.f);

    FInputAxisKeyMapping lookUpKey("LookUp", EKeys::MouseY, -1.f);
    FInputAxisKeyMapping turnKey("Turn", EKeys::MouseX, 1.f);

    FInputActionKeyMapping jumpKey("Jump", EKeys::SpaceBar, 0, 0, 0, 0);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(forwardKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(backKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(rightKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(leftKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(lookUpKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(turnKey);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(jumpKey);
}

void AMainCharcater::MoveForward(float AxisValue)
{
    AddMovementInput(GetActorForwardVector(), AxisValue);
}

void AMainCharcater::MoveRight(float AxisValue)
{
    AddMovementInput(GetActorRightVector(), AxisValue);
}
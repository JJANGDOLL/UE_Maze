// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharcater.h"
#include "GameFramework/PlayerInput.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include <Components/SceneComponent.h>
#include <Components/ChildActorComponent.h>
#include <Curves/CurveFloat.h>
#include "FlashLightBase.h"

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

    _flashLight = CreateDefaultSubobject<UChildActorComponent>(TEXT("FlashLight"));
    _flashLight->SetRelativeRotation(FQuat(0.f, 0.f, -90.f, 0.f));
    _flashLight->SetupAttachment(_mainCamera);

    TSubclassOf<AFlashLightBase> flashLight;
    Helpers::GetClass<AFlashLightBase>(&flashLight, TEXT("Blueprint'/Game/Actors/BP_FlashLight.BP_FlashLight_C'"));
    _flashLight->SetChildActorClass(flashLight);

    GetCharacterMovement()->MaxWalkSpeed = 400.0f;

    SmoothCrouchingCurveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CrouchTimeline"));
    SmoothCrouchInterpFunction.BindUFunction(this, FName("SmoothCrouchIterRet"));
    SmoothCrouchTimelineFinish.BindUFunction(this, FName("SmoothCrouchOnFinish"));

    Helpers::GetAsset<UCurveFloat>(&SmoothCrouchingCurveFloat, TEXT("CurveFloat'/Game/TImeline/CourchCurve.CourchCurve'"));
}



// Called when the game starts or when spawned
void AMainCharcater::BeginPlay()
{
	Super::BeginPlay();
	
    SmoothCrouchTimelineSetting();
    _flashLight->CreateChildActor();
    _flashActor = Cast<AFlashLightBase>(_flashLight->GetChildActor());
}

// Called every frame
void AMainCharcater::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharcater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Forward", this, &AMainCharcater::MoveForward);
    PlayerInputComponent->BindAxis("Back", this, &AMainCharcater::MoveForward);
    PlayerInputComponent->BindAxis("Left", this, &AMainCharcater::MoveRight);
    PlayerInputComponent->BindAxis("Right", this, &AMainCharcater::MoveRight);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMainCharcater::Run);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AMainCharcater::Walk);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharcater::Jump);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharcater::Crouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainCharcater::Stand);
    PlayerInputComponent->BindAction("Flash", IE_Pressed, this, &AMainCharcater::CmdFlash);
    PlayerInputComponent->BindAction("Use", IE_Pressed, this, &AMainCharcater::Use);

    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

    FInputAxisKeyMapping forwardKey("Forward", EKeys::W, 1.f);
    FInputAxisKeyMapping backKey("Back", EKeys::S, -1.f);
    FInputAxisKeyMapping rightKey("Right", EKeys::D, 1.f);
    FInputAxisKeyMapping leftKey("Left", EKeys::A, -1.f);

    FInputAxisKeyMapping lookUpKey("LookUp", EKeys::MouseY, -1.f);
    FInputAxisKeyMapping turnKey("Turn", EKeys::MouseX, 1.f);

    FInputActionKeyMapping jumpKey("Jump", EKeys::SpaceBar, 0, 0, 0, 0);
    FInputActionKeyMapping runKey("Run", EKeys::LeftShift, 0, 0, 0, 0);
    FInputActionKeyMapping crouchKey("Crouch", EKeys::LeftControl, 0, 0, 0, 0);
    FInputActionKeyMapping flashKey("Flash", EKeys::F, 0, 0, 0, 0);
    FInputActionKeyMapping useKey("Use", EKeys::Q, 0, 0, 0, 0);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(forwardKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(backKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(rightKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(leftKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(lookUpKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(turnKey);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(jumpKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(runKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(crouchKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(flashKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(useKey);
}

void AMainCharcater::MoveForward(float AxisValue)
{
    AddMovementInput(GetActorForwardVector(), AxisValue);
}

void AMainCharcater::MoveRight(float AxisValue)
{
    AddMovementInput(GetActorRightVector(), AxisValue);
}

void AMainCharcater::Walk()
{
    GetCharacterMovement()->MaxWalkSpeed = 400;
}

void AMainCharcater::Run()
{
    if(!_bCrouched)
        GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AMainCharcater::Crouch()
{
    SmoothCrouchingCurveTimeline->Play();
    _bCrouched = true;
}

void AMainCharcater::Stand()
{
    SmoothCrouchingCurveTimeline->Reverse();
    _bCrouched = false;
}

void AMainCharcater::Use()
{

}

void AMainCharcater::SmoothCrouchIterRet(float value)
{
    GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::Lerp(96.0f, 48.0f, value));
}

void AMainCharcater::SmoothCrouchOnFinish()
{
    if (_bCrouched)
    {
        GetCharacterMovement()->MaxWalkSpeed = 250.f;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = 400.f;
    }
}

void AMainCharcater::CmdFlash()
{
    _flashActor->PressSwitch();

    PrintLine();
}

void AMainCharcater::StartCrouch()
{
    SmoothCrouchingCurveTimeline->Play();
}

void AMainCharcater::SmoothCrouchTimelineSetting()
{
    if (SmoothCrouchingCurveFloat)
    {
        SmoothCrouchingCurveTimeline->AddInterpFloat(SmoothCrouchingCurveFloat, SmoothCrouchInterpFunction);
        SmoothCrouchingCurveTimeline->SetTimelineFinishedFunc(SmoothCrouchTimelineFinish);
        SmoothCrouchingCurveTimeline->SetLooping(false);
    }
}
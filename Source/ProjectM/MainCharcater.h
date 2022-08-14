// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Components/TimelineComponent.h>
#include "MainCharcater.generated.h"

class UCameraComponent;
class USpotLightComponent;

UENUM()
enum class ECharacterState : uint8
{
	STAND,
	CROUCH,
};

UCLASS()
class PROJECTM_API AMainCharcater : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharcater();

private:
    UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* _mainCamera;

    UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UChildActorComponent* _flashLight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float amount);
    void MoveRight(float amount);
	void Walk();
	void Run();
	void Crouch();
	void Stand();
	void Use();

private:
    FVector _movementInput;
    FVector _cameraInput;

	float _flashlightIntensity;

private:
	FOnTimelineFloat SmoothCrouchInterpFunction;
	FOnTimelineEvent SmoothCrouchTimelineFinish;

private:
	void StartCrouch();
	void SmoothCrouchTimelineSetting();

	UFUNCTION() 
	void SmoothCrouchIterRet(float value);

	UFUNCTION()
	void SmoothCrouchOnFinish();

	UPROPERTY()
	class UTimelineComponent* SmoothCrouchingCurveTimeline;

	UPROPERTY(EditAnywhere, Category="Timeline")
	class UCurveFloat* SmoothCrouchingCurveFloat;

	bool _bCrouched = false; 

private:
	class AFlashLightBase* _flashActor;

	void CmdFlash();

private:
	class IItem* _equipedItem;
};

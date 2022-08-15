// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashLightBase.h"
#include <Components/StaticMeshComponent.h>
#include <Engine/StaticMesh.h>
#include "Global.h"
#include <Components/SpotLightComponent.h>


// Sets default values
AFlashLightBase::AFlashLightBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

//     USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
//     SetRootComponent(root);

	UStaticMesh* flashMesh;
	Helpers::GetAsset<UStaticMesh>(&flashMesh, "StaticMesh'/Game/Flashlight/tourch_light_Cylinder.tourch_light_Cylinder'");

    UStaticMeshComponent* mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
//     mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	mesh->SetupAttachment(GetRootComponent());
    mesh->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
	mesh->SetStaticMesh(flashMesh);
    mesh->SetRelativeRotation(FQuat(0.f, 0.f, 0.f, 0.f));

    _flashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
    _flashLight->SetupAttachment(mesh);
    _flashLight->SetRelativeLocation(FVector(0.f, -11.f, 125.f));
    _flashLight->AddRelativeRotation(FRotator(0.f ,-90.f, 0.f));
    _flashLight->Intensity = 15000.f;
    _flashLight->InnerConeAngle = 18.0f;
    _flashLight->OuterConeAngle = 25.0f;
    _flashLight->AttenuationRadius = 5000.f;
}

void AFlashLightBase::PressSwitch()
{
    bOn = !bOn;
    _flashLight->ToggleVisibility(bOn);
}

// Called when the game starts or when spawned
void AFlashLightBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlashLightBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


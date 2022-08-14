// Fill out your copyright notice in the Description page of Project Settings.


#include "Stone.h"
#include "Utilities/Helpers.h"
#include <Components/StaticMeshComponent.h>
#include <Engine/StaticMesh.h>
#include <Components/SpotLightComponent.h>

// Sets default values
AStone::AStone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

//     USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
//     SetRootComponent(root);

	UStaticMesh* mesh;
	Helpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Engine/BasicShapes/Sphere.Sphere'");

	UStaticMeshComponent* _mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	_mesh->SetStaticMesh(mesh);
	_mesh->SetSimulatePhysics(true);
	_mesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	_mesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AStone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


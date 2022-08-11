// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBase.h"
#include "Global.h"
#include <Engine/Blueprint.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AMazeBase::AMazeBase()
    : _mazeBuilder(new MazeBuilder), _mazeGenerator(new MazeGenerator)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

//     TSubclassOf<AActor> mazeMesh;
//     Helpers::GetClass<AActor>(&mazeMesh, "Blueprint'/Game/Meshes/BP_Maze_E.BP_Maze_E_C'");
// 
    USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    root->SetupAttachment(GetRootComponent());

//     UChildActorComponent* child = CreateDefaultSubobject<UChildActorComponent>(TEXT("TEST"));
//     child->SetupAttachment(root);
//     child->SetChildActorClass(mazeMesh);

}

// Called when the game starts or when spawned
void AMazeBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMazeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMazeBase::RerunConstructionScripts()
{
    Super::RerunConstructionScripts();
}

void AMazeBase::PostActorCreated()
{
    Super::PostActorCreated();

    makeMap();
}

void AMazeBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    makeMap();
}

void AMazeBase::makeMap()
{
    _mazeGenerator->init(_mazeSize);
    _mazeGenerator->generate();
    _mazeBuilder->build(_mazeGenerator.Get(), this);
}

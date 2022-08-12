// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBase.h"
#include "Global.h"
#include <Engine/Blueprint.h>
#include <Components/StaticMeshComponent.h>

AMazeBase::AMazeBase()
    : _mazeBuilder(new MazeBuilder), _mazeGenerator(new MazeGenerator)
{
	PrimaryActorTick.bCanEverTick = true;

    USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(root);


    _goalLoc = CreateDefaultSubobject<USceneComponent>(TEXT("GoalLoc"));
    _goalLoc->SetupAttachment(GetRootComponent());
}

void AMazeBase::NewMaze()
{
    Logger::Log(_goalLoc);

    makeMap();
}

// Called when the game starts or when spawned
void AMazeBase::BeginPlay()
{
    PrintLine();
	Super::BeginPlay();
    bPlaying = true;
}

void AMazeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    PrintLine();
    Super::EndPlay(EndPlayReason);
    bPlaying = false;
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

    Logger::Log(_goalLoc);

    makeMap();
}

void AMazeBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
}

void AMazeBase::makeMap()
{
    _mazeGenerator->init(_mazeSize);
    _mazeGenerator->generate();
    _mazeBuilder->build(_mazeGenerator.Get(), this);
    _goalLoc->SetRelativeLocation(_mazeBuilder->getGoalLoc());
}

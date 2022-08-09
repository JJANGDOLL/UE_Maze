// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldBuilder.h"

#include "Global.h"
#include "MazeGenerator.h"
#include <Engine/StaticMesh.h>
#include <Engine/StaticMeshActor.h>
#include <Engine/Blueprint.h>

// Sets default values
AWorldBuilder::AWorldBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    _mazeMeshNames.Add(Direction::NONE, "BP_Maze_NoWall");

    _mazeMeshNames.Add(Direction::EAST, "BP_Maze_E");
    _mazeMeshNames.Add(Direction::WEST, "BP_Maze_W");
    _mazeMeshNames.Add(Direction::SOUTH, "BP_Maze_S");
    _mazeMeshNames.Add(Direction::NORTH , "BP_Maze_N");

    _mazeMeshNames.Add(Direction::EAST + Direction::WEST, "BP_Maze_EW");
    _mazeMeshNames.Add(Direction::EAST + Direction::SOUTH, "BP_Maze_ES");
    _mazeMeshNames.Add(Direction::EAST + Direction::NORTH, "BP_Maze_EN");
    _mazeMeshNames.Add(Direction::WEST + Direction::SOUTH, "BP_Maze_WS");
    _mazeMeshNames.Add(Direction::WEST + Direction::NORTH, "BP_Maze_WN");
    _mazeMeshNames.Add(Direction::SOUTH + Direction::NORTH, "BP_Maze_SN");

    _mazeMeshNames.Add(Direction::EAST + Direction::WEST + Direction::SOUTH, "BP_Maze_EWS");
    _mazeMeshNames.Add(Direction::EAST + Direction::WEST + Direction::NORTH, "BP_Maze_EWN");
    _mazeMeshNames.Add(Direction::EAST + Direction::SOUTH + Direction::NORTH, "BP_Maze_ESN");
    _mazeMeshNames.Add(Direction::WEST + Direction::SOUTH + Direction::NORTH, "BP_Maze_WSN");

    FString pathName = "Blueprint'/Game/Meshes/";
    for (auto& Elem : _mazeMeshNames)
    {
        Logger::Log(Elem.Value);

        UBlueprint* mazeMesh;
        Helpers::GetAsset<UBlueprint>(&mazeMesh, pathName + Elem.Value + "." + Elem.Value + "'");

        _mazeMeshes.Add(Elem.Key, mazeMesh);
    }
}

AWorldBuilder::~AWorldBuilder()
{

}

// Called when the game starts or when spawned
void AWorldBuilder::BeginPlay()
{
	Super::BeginPlay();

    FTransform transform;
    uint8 ccount = 0;
    uint8 rcount = 0;
    uint8 counter = 0;

//     for (auto& Elem : _mazeMeshes)
//     {
//         transform = GetActorTransform();
//         transform.SetLocation(transform.GetLocation() + FVector(-300 * (counter >> 2), 300 * (counter % 4), 0));
// 
//         AActor* mazeActor = GetWorld()->SpawnActor<AActor>(Elem.Value->GeneratedClass, transform);
//         counter++;
//     }
}

// Called every frame
void AWorldBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldBuilder::build(std::map<Position, MazeNode*> mazes)
{
    for (const auto& maze : mazes)
    {
        Position pos = maze.first;
        MazeNode* mazeNode = maze.second;
        FTransform transform;
        transform.SetLocation(transform.GetLocation() + FVector(-300 * pos.Col, 300 * pos.Row, 0));
        GetWorld()->SpawnActor<AActor>(_mazeMeshes[mazeNode->GetWall()]->GeneratedClass, transform);
    }
}


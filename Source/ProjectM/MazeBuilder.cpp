// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBuilder.h"

#include "Global.h"
#include "Datas/Structures.h"
#include "MazeGenerator.h"
#include <UObject/NoExportTypes.h>
#include <map>
#include <Components/ActorComponent.h>
#include <GameFramework/Actor.h>

MazeBuilder::MazeBuilder()
{
    _mazeMeshNames.Add(Direction::NONE, "BP_Maze_NoWall");

    _mazeMeshNames.Add(Direction::EAST, "BP_Maze_E");
    _mazeMeshNames.Add(Direction::WEST, "BP_Maze_W");
    _mazeMeshNames.Add(Direction::SOUTH, "BP_Maze_S");
    _mazeMeshNames.Add(Direction::NORTH, "BP_Maze_N");

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

        TSubclassOf<AActor> mazeMesh;
        Helpers::GetClass<AActor>(&mazeMesh, pathName + Elem.Value + "." + Elem.Value + "_C'");

        _mazeMeshes.Add(Elem.Key, mazeMesh);
    }
}

MazeBuilder::~MazeBuilder()
{
}

void MazeBuilder::build(MazeGenerator* const generatedMaze, AActor* const parent)
{

    uint8 idx = 0;
    for (const auto& mazeCell : generatedMaze->getMaze())
    {
        FString label = "Maze_";
        label += FString::FromInt(idx++);
     
        Position pos = mazeCell.first;
        MazeNode* mazeNode = mazeCell.second;

        UChildActorComponent* mazeComp = NewObject<UChildActorComponent>(parent, UChildActorComponent::StaticClass(), FName(*label));
        mazeComp->SetChildActorClass(_mazeMeshes[mazeNode->GetWall()]);
        mazeComp->CreateChildActor();

        FVector loc = FVector(-599 * pos.Col, 599 * pos.Row, 0);
        FVector scale = FVector(2.0f, 2.0f, 2.0f);

        mazeComp->SetupAttachment(parent->GetRootComponent());
        mazeComp->SetRelativeLocation(loc);
        mazeComp->SetRelativeScale3D(scale);
        mazeComp->RegisterComponent();

//        parent->AddInstanceComponent(mazeComp);

        Logger::Log(parent->GetWorld());    
        Logger::Log(mazeComp->GetOwner());
        Logger::Log(mazeComp);
        PrintLine();

        //FTransform transform;
        //Position pos = maze.first;
        //MazeNode* mazeNode = maze.second;
        //transform.SetLocation(transform.GetLocation() + FVector(-599 * pos.Col, 599 * pos.Row, 0));
        //transform.SetScale3D(FVector(2.0f, 2.0f, 2.0f));
        ////GetWorld()->SpawnActor<AActor>(_mazeMeshes[mazeNode->GetWall()]->GeneratedClass, transform);
        //AActor* defferedActor = GetWorld()->SpawnActorDeferred<AActor>(_mazeMeshes[mazeNode->GetWall()]->GeneratedClass, transform);

        //UGameplayStatics::FinishSpawningActor(defferedActor, transform);
        //defferedActor->GetRootComponent()->SetMobility(EComponentMobility::Static);
    }

//     USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
//     root->SetupAttachment(GetRootComponent());

//     UChildActorComponent* child = CreateDefaultSubobject<UChildActorComponent>(TEXT("TEST"));
//     child->SetupAttachment(root);
//     child->SetChildActorClass(mazeMesh);
}

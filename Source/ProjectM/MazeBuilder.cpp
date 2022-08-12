// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBuilder.h"

#include "Global.h"
#include "Datas/Structures.h"
#include "MazeGenerator.h"
#include <UObject/NoExportTypes.h>
#include <map>
#include <Components/ActorComponent.h>
#include <GameFramework/Actor.h>
#include <Materials/MaterialInstanceConstant.h>
#include <Components/StaticMeshComponent.h>

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

    _material;
    Helpers::GetAsset<UMaterialInstanceConstant>(&_material, "MaterialInstanceConstant'/Game/EF_Barbra/Common/Materials/Concrete/WM_ConcreteBare_b_mat_Inst.WM_ConcreteBare_b_mat_Inst'");


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
    for (const auto& cellComp : _mazeChildComponents)
    {
        cellComp->DestroyChildActor();
        cellComp->UnregisterComponent();
        cellComp->DestroyComponent();
    }

    _mazeChildComponents.Reset();

    Position goalPos = generatedMaze->getGoalPos();

    for (const auto& mazeCell : generatedMaze->getMaze())
    {     
        Position pos = mazeCell.first;
        
        MazeNode* mazeNode = mazeCell.second;

        UChildActorComponent* mazeComp = NewObject<UChildActorComponent>(parent, UChildActorComponent::StaticClass());
        _mazeChildComponents.Emplace(mazeComp);
        mazeComp->SetChildActorClass(_mazeMeshes[mazeNode->GetWall()]);
        mazeComp->CreateChildActor();
        
        for (auto& mazeCompCell : mazeComp->GetChildActor()->GetComponentsByClass(UStaticMeshComponent::StaticClass()))
        {
            UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(mazeCompCell);
            for (int idx = 0; idx < mesh->GetNumMaterials(); idx++)
            {
                mesh->SetMaterial(idx, _material);
            }
        }

        FVector loc = FVector(-599 * pos.Col, 599 * pos.Row, 0);
        if (pos == goalPos)
        {
            _goalLoc = loc;
        }

        FVector scale = FVector(2.0f, 2.0f, 2.0f);

        mazeComp->SetupAttachment(parent->GetRootComponent());
        mazeComp->SetRelativeLocation(loc);
        mazeComp->SetRelativeScale3D(scale);
        mazeComp->RegisterComponent();
    }
}

FVector MazeBuilder::getGoalLoc()
{
    Logger::Log(_goalLoc);
    return _goalLoc;
}

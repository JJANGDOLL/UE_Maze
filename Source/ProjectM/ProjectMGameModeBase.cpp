// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectMGameModeBase.h"

#include "Global.h"
#include "WorldBuilder.h"

AProjectMGameModeBase::AProjectMGameModeBase()
{
    _mazeGenerator = MakeUnique<MazeGenerator>();
}

AProjectMGameModeBase::~AProjectMGameModeBase()
{

}

void AProjectMGameModeBase::BeginPlay()
{
    Super::BeginPlay();


    // -----------------------------------------
    _mazeGenerator->init(50, GetWorld());
    _mazeGenerator->generate();
    _mazeGenerator->build();
    PrintInfo();
}

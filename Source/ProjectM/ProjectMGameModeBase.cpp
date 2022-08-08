// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectMGameModeBase.h"

#include "Global.h"
#include "MazeGenerator.h"

AProjectMGameModeBase::AProjectMGameModeBase()
{
    PrintInfo();
}

AProjectMGameModeBase::~AProjectMGameModeBase()
{

}

void AProjectMGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    _mazeGenerator = MakeUnique<MazeGenerator>();

    // -----------------------------------------
    _mazeGenerator->init(2);
    _mazeGenerator->generate();
    PrintInfo();
}

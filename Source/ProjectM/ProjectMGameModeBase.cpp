// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectMGameModeBase.h"

#include "Global.h"
#include "WorldBuilder.h"
#include "MainCharcater.h"

AProjectMGameModeBase::AProjectMGameModeBase()
{
    _mazeGenerator = MakeUnique<MazeGenerator>();

    DefaultPawnClass = AMainCharcater::StaticClass();
}

AProjectMGameModeBase::~AProjectMGameModeBase()
{

}

void AProjectMGameModeBase::BeginPlay()
{
    Super::BeginPlay();


    // -----------------------------------------
    _mazeGenerator->init(15, GetWorld());
    _mazeGenerator->generate();
    _mazeGenerator->build();
    PrintLine();
}

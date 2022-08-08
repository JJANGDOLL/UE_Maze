// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MazeGenerator.h"
#include "ProjectMGameModeBase.generated.h"

/**
 * 
 */
class MazeGenerator;

UCLASS()
class PROJECTM_API AProjectMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectMGameModeBase();
	~AProjectMGameModeBase();
	
private:
	TUniquePtr<class MazeGenerator> _mazeGenerator;

protected:
	void BeginPlay() override;
};

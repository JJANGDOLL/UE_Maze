// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class PROJECTM_API MazeBuilder
{
public:
	MazeBuilder();
	~MazeBuilder();

public:
    void build(class MazeGenerator* const generatedMaze, class AActor* const parent);
    FVector getGoalLoc();

private:
    TMap<uint8, TSubclassOf<AActor>> _mazeMeshes;
    TMap<uint8, FString> _mazeMeshNames;
    TArray<class UChildActorComponent*> _mazeChildComponents;
    FVector _startLoc;
    FVector _goalLoc;
};

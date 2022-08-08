// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.h"
#include "WorldBuilder.generated.h"

UCLASS()
class PROJECTM_API AWorldBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldBuilder();
	~AWorldBuilder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void build(std::map<Position, MazeNode*> maze);

private:
	UPROPERTY(EditInstanceOnly, Category=MapPos)
	AActor* _mapStartPosition;

	TMap<uint8, class UBlueprint*> _mazeMeshes;
	TMap<uint8, FString> _mazeMeshNames;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeBuilder.h"
#include "MazeGenerator.h"
#include "MazeBase.generated.h"

UCLASS()
class PROJECTM_API AMazeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeBase();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MazeProp, meta=(AllowPrivateAccess = "true", ClampMin = "4", ClampMax="10"))
	uint8 _mazeSize = 3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void RerunConstructionScripts() override;
	void PostActorCreated() override;
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	void makeMap();

private:
	TUniquePtr<class MazeBuilder> _mazeBuilder;
	TUniquePtr<class MazeGenerator> _mazeGenerator;
};

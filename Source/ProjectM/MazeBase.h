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
	UPROPERTY(VisibleInstanceOnly, Category = "MazeProp")
    bool bPlaying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MazeProp", meta = (AllowPrivateAccess = "true", ClampMin = "4", ClampMax = "15", EditCondition = "bPlaying == false", EditConditionHides))
	uint8 _mazeSize = 3;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UChildActorComponent* _goalLoc;

protected:
	UFUNCTION(BlueprintCallable, CallInEditor, Category="MazeProp")
	void NewMaze();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RerunConstructionScripts() override;
	void PostActorCreated() override;
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	void makeMap();

private:
	TUniquePtr<class MazeBuilder> _mazeBuilder;
	TUniquePtr<class MazeGenerator> _mazeGenerator;
};

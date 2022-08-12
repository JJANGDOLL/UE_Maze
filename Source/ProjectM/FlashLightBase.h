// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlashLightBase.generated.h"

UCLASS()
class PROJECTM_API AFlashLightBase : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AFlashLightBase();

private:
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* _mesh;

    UPROPERTY(VisibleAnywhere, Category = Items, meta = (AllowPrivateAccess = "true"))
    class USpotLightComponent* _flashLight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

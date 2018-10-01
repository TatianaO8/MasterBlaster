// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

#include "PaperSpriteComponent.h"
#include "BaseTile.h"


#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class MASTERBLASTER_API ALevelGenerator : public AActor{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

private:
	void GetTileSpawnLocation(const ABaseTile* previousTile, FVector &location, bool &canChangeDirection);
	void GetTileSpawnRotation(const ABaseTile* previousTile, FRotator &rotation, bool canChangeDirection);
	void GenerateFloor();
	void GenerateCeiling();
	void GenerateMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	TArray<ABaseTile*> floor;
	TArray<ABaseTile*> ceiling;

	UPROPERTY(EditAnywhere, Category = LevelGeneration)
	int mapWidth;

	UPROPERTY(EditAnywhere, Category = LevelGeneration)
	int ceilingHeight;

	UPROPERTY(EditAnywhere, Category = LevelGeneration)
	int tileSize;
	
	UPROPERTY(EditAnywhere, Category = LevelGeneration)
	int slope;
	
	UPROPERTY(EditAnywhere, Category = LevelGeneration)
	TSubclassOf<ABaseTile> tile;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	const float pi = 3.141592;
	
};

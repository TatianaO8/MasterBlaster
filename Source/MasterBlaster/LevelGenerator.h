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
	void GenerateMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	TArray<ABaseTile*> map;


	UPROPERTY(EditAnywhere, Category = LevelGeneration)
	int mapWidth;

	UPROPERTY(EditAnywhere, Category = LevelGeneration)
	int ceilingHeight;
	
	UPROPERTY(EditAnywhere, Category = LevelGeneration)
	TSubclassOf<ABaseTile> tile;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

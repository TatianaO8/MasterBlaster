// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ARoom;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class MASTERBLASTER_API ALevelGenerator : public AActor{
	GENERATED_BODY()
	
private:
	TArray<ARoom*> map;

public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

	//Array of rooms the level generator can use
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ARoom>> rooms;

	UPROPERTY(EditAnywhere)
	int numRooms;

protected:
	void GenerateLevel();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

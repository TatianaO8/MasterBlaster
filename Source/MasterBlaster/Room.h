// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ABaseUnit;
class ABasicEnemyUnit;
class ACoverBlock;

#include "CoreMinimal.h"
#include "PaperTileMapActor.h"
#include "Room.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDoor {
	GENERATED_USTRUCT_BODY()

	FDoor(){}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Doors)
	int base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Doors)
	int height;

	//Equality Comparison overload
	bool operator==(const FDoor &other) {
		return (base == other.base && height == other.height);
	}

};
UCLASS()
class MASTERBLASTER_API ARoom : public APaperTileMapActor
{
	GENERATED_BODY()

private:

	//Private Variables
	UPROPERTY(EditAnywhere, Category = Doors)
	FDoor leftEntrance;

	UPROPERTY(EditAnywhere, Category = Doors)
	FDoor rightEntrance;
	
	bool isEntered;

	//Private Functions

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	//Public Variables
	void EnterRoom();

	void SpawnEnemies(TSubclassOf<ABasicEnemyUnit> EnemyUnitBP);
	void SpawnCoverElements(TSubclassOf<ACoverBlock> CoverBlockBP);
	
	FTransform GetSpawnLocation(int x, int y);
	void SpawnEnemyUnit(int x, int y, TSubclassOf<ABasicEnemyUnit> &EnemyUnitBP);
	void SpawnCoverBlock(int x, int y, TSubclassOf<ACoverBlock> &CoverBlockBP);
	void Populate(TSubclassOf<ABasicEnemyUnit> EnemyUnitBP, TSubclassOf<ACoverBlock> CoverBlockBP);

	

	//Public Functions
	UFUNCTION(BlueprintCallable)
	int GetRoomWidthTiles();

	UFUNCTION(BlueprintCallable)
	int GetRoomWidthPixels();

	UFUNCTION(BlueprintCallable)
	int GetRoomHeightTiles();

	UFUNCTION(BlueprintCallable)
	int GetRoomHeightPixels();

	bool CanConnectTo(ARoom* other);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
		return (
			base == other.base 
			&& height == other.height
		);
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
	
	//Private Functions

protected:
	//Protected Variables

	//Protected Functions

public:
	//Public Variables
	
	//Public Functions
	int GetRoomWidthTiles();
	int GetRoomWidthPixels();

	int GetRoomHeightTiles();
	int GetRoomHeightPixels();
};

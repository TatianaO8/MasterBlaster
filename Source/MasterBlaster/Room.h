// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapActor.h"
#include "Room.generated.h"

/**
 * 
 */
UCLASS()
class MASTERBLASTER_API ARoom : public APaperTileMapActor
{
	GENERATED_BODY()

public:
	int GetRoomWidthTiles();
	int GetRoomWidthPixels();

	int GetRoomHeightTiles();
	int GetRoomHeightPixels();
};

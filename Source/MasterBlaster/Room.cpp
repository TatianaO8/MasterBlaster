// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"
#include "BaseUnit.h"

#include "PaperTileMapComponent.h"
#include "PaperTileMap.h"
#include "PaperTileSet.h"


void ARoom::BeginPlay() {

}

void ARoom::EnterRoom(){
	isEntered = true;
	//When a room is entered

	//Remove Fog of war

	//Activate Enemy Units in the room

	return;
}

void ARoom::SpawnEnemies(TSubclassOf<ABaseUnit> EnemyUnitBP){
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Spawn Room Contents")));
	auto TileMap = this->GetRenderComponent();

	int rows, cols, layers;
	TileMap->GetMapSize(rows, cols, layers);

	if (layers < 2) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("No Spawn Layer")));
		return;
	}

	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < rows; y++) {
			auto tile = TileMap->GetTile(x, y, 0);
			auto tileIndex = tile.PackedTileIndex;
			auto tileData = tile.TileSet->GetTileUserData(tileIndex);

			/*if (tileIndex != -1) {
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("%d"), tileIndex));
			}*/

			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, tileData.ToString());
			
			FName spawnFlag(TEXT("EnemySpawn"));
			if (spawnFlag == tileData) {
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Spawn")));
				
				FVector rootLocation = this->GetActorLocation();

				FVector location(rootLocation.X + x * 128, rootLocation.Y, rootLocation.Z - (128 * y));
				FRotator rotation(0, 0, 0);
				ABaseUnit* unit = GetWorld()->SpawnActor<ABaseUnit>(EnemyUnitBP, location, rotation);

			}
		}
	}
}

int ARoom::GetRoomWidthTiles() {
	return GetRenderComponent()->TileMap->MapWidth;
}

int ARoom::GetRoomWidthPixels() {
	int width = GetRoomWidthTiles();
	int tileSize = GetRenderComponent()->TileMap->TileWidth;
	return width * tileSize;
}

int ARoom::GetRoomHeightTiles() {
	return GetRenderComponent()->TileMap->MapHeight; 
}

int ARoom::GetRoomHeightPixels() {
	int width = GetRoomHeightTiles();
	int tileSize = GetRenderComponent()->TileMap->TileHeight;
	return width * tileSize;
}

bool ARoom::CanConnectTo(ARoom* other){
	return rightEntrance == other->leftEntrance;
}

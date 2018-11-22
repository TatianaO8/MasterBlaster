// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"
#include "BaseUnit.h"
#include "BasicEnemyUnit.h"
#include "CoverBlock.h"
#include "DynamicLevelElement.h"

#include "PaperTileMapComponent.h"
#include "PaperTileMap.h"
#include "PaperTileSet.h"


void ARoom::BeginPlay() {
	bCanBeDamaged = false;
}

void ARoom::EnterRoom(){
	isEntered = true;
	//When a room is entered

	//Remove Fog of war

	//Activate Enemy Units in the room

	return;
}

FTransform ARoom::GetSpawnLocation(int x, int y){
	FTransform temp = this->GetActorTransform();
	
	FVector rootLocation = temp.GetLocation();
	FVector location(rootLocation.X + x * 128, rootLocation.Y, rootLocation.Z - (128 * y));
	temp.SetLocation(location);
		
	return temp;
}

void ARoom::SpawnEnemyUnit(int x, int y, TSubclassOf<ABasicEnemyUnit> &EnemyUnitBP){
	FTransform transform = GetSpawnLocation(x, y);
	FVector location = transform.GetLocation();
	FRotator rotation = transform.GetRotation().Rotator();
	
	//Modify spawn location to prevent units falling through world.
	location.Z += 128;

	//Flip Facing Direction
	rotation.Yaw += 180;

	//Update transform
	transform.SetLocation(location);
	transform.SetRotation(FQuat(rotation));

	//Spawn
	auto enemyUnit = GetWorld()->SpawnActor<ABasicEnemyUnit>(EnemyUnitBP, transform);
}

void ARoom::SpawnCoverBlock(int x, int y, TSubclassOf<ACoverBlock> &CoverBlockBP){
	FTransform transform = GetSpawnLocation(x, y);
	auto block = GetWorld()->SpawnActor<ACoverBlock>(CoverBlockBP, transform);
}

void ARoom::SpawnDynamicElement(int x, int y, FName tileData, TArray<TSubclassOf<ADynamicLevelElement>> Elements){
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Spawn dynamic elements")));
	FVector tempLoc(0, -1000, 0);
	FRotator tempRot(0, 0, 0);

	for (auto element : Elements) {
		auto temp = GetWorld()->SpawnActor<ADynamicLevelElement>(element, tempLoc, tempRot);
		if (temp->GetElementId() == tileData) {
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Pass")));
			temp->SetActorTransform(GetSpawnLocation(x, y));
			break;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Fail")));
		temp->Destroy();
	}

}

void ARoom::Populate(TSubclassOf<ABasicEnemyUnit> EnemyUnitBP, TSubclassOf<ACoverBlock> CoverBlockBP, TArray<TSubclassOf<ADynamicLevelElement>> DynamicLevelElements){
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

			FName unitSpawnFlag(TEXT("EnemySpawn"));
			FName coverSpawnFlag(TEXT("Cover"));
			
			if (tileData == "") {
				continue;
			}

			if (tileData == unitSpawnFlag) {
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("SpawnEnemy")));
				SpawnEnemyUnit(x, y, EnemyUnitBP);
			}
			else if (tileData == coverSpawnFlag) {
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("SpawnCover")));
				SpawnCoverBlock(x, y, CoverBlockBP);
			}
			else {
				SpawnDynamicElement(x, y, tileData, DynamicLevelElements);
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

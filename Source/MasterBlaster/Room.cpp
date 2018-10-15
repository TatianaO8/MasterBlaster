// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"
#include "PaperTileMapComponent.h"
#include "PaperTileMap.h"

void ARoom::EnterRoom(){
	isEntered = true;
	//When a room is entered

	//Remove Fog of war

	//Activate Enemy Units in the room

	return;
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

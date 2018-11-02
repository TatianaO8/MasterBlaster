// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
class ARoom;
class ABaseUnit;
class ABasicEnemyUnit;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatMap.generated.h"

UCLASS()
class MASTERBLASTER_API ACombatMap : public AActor
{
	GENERATED_BODY()

private:
	TArray<ARoom*> rooms;
	
	//APlayerSquad object reference
	//EnemyForce object reference


public:	
	// Sets default values for this actor's properties
	ACombatMap();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	ARoom* GetSpawnRoom();

	UFUNCTION(BlueprintCallable)
	ARoom* GetLastRoom();
	
	void AddRoom(ARoom* room);

	void SpawnEnemies(TSubclassOf<ABasicEnemyUnit> EnemyUnitBP);
	
	
};

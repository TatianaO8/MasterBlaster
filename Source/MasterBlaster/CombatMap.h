// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
class ARoom;
class ABaseUnit;
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatMap.generated.h"

UCLASS()
class MASTERBLASTER_API ACombatMap : public AActor
{
	GENERATED_BODY()

private:
	TArray<ARoom*> map;
	
	//APlayerSquad object reference
	//EnemyForce object reference


public:	
	// Sets default values for this actor's properties
	ACombatMap();
	void AddRoom(ARoom* room);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

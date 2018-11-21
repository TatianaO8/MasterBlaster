// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "BasicEnemyUnit.generated.h"

/**
 * 
 */
UCLASS()
class MASTERBLASTER_API ABasicEnemyUnit : public ABaseUnit
{
	GENERATED_BODY()


protected:
	FVector dest;
	FTimerHandle FireShotTimeHandler;

private:
	AMasterBlasterGameState *gameState;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<ABaseUnit*> PlayerTeam;

	int repeatingCallsRemaining;
	
protected:
	// Called when the game starts or when spawned
	void BeginPlay();

public:
	
	//override
	void BeginTurn() override;
	
	//override
	// Fire a shot in the specified direction 
	void FireShot() override;
	
	void Die() override;
};

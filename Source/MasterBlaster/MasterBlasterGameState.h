// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ABaseUnit;

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MasterBlasterGameState.generated.h"

/**
 * 
 */
UCLASS()
class MASTERBLASTER_API AMasterBlasterGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	ABaseUnit* ActiveUnit;
	TArray<ABaseUnit*> PlayerTeam;

public:
	void AddUnit(ABaseUnit* unit);
	ABaseUnit* SelectUnit(int index);
	ABaseUnit* SetActiveUnit();
	
};

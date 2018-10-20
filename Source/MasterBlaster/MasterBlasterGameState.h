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
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int activeUnit;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<ABaseUnit*> PlayerTeam;

public:
	//ctors
	AMasterBlasterGameState();

	//public functions
	void AddUnit(ABaseUnit* unit);

	UFUNCTION(BlueprintCallable)
	void CycleUnit();

	UFUNCTION(BlueprintCallable)
	ABaseUnit* GetActiveUnit();


};

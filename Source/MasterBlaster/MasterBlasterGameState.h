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

	//determine who's turn it is
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsPlayerTurn;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool GameOver;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int activeUnit;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<ABaseUnit*> PlayerTeam;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<ABaseUnit*> EnemyTeam;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool combatStarted;
	
	int count;

public:

	//ctors
	AMasterBlasterGameState();

	//public functions
	int RegisterPlayerUnit(ABaseUnit* unit);
	int RegisterEnemyUnit(ABaseUnit* unit);
	void UnregisterPlayerUnit(int index);
	void UnregisterEnemyUnit(int index);

	UFUNCTION(BlueprintCallable)
	void SetActiveUnit(int index);

	UFUNCTION(BlueprintCallable)
	void CycleUnit();

	UFUNCTION(BlueprintCallable)
	ABaseUnit* GetActiveUnit();

	UFUNCTION(BlueprintCallable)
	int SearchForUnitIndex(ABaseUnit* unit);

	int GetPlayerTeamSize();

	UFUNCTION(BlueprintCallable)
	bool GetIsPlayerTurn();

	UFUNCTION(BlueprintCallable)
	TArray<ABaseUnit*> GetPlayerTeam();

	void BeginEnemyTurn();
	void BeginPlayerTurn();

	void PlayerTurnUpdate();
	void EnemyTurnUpdate();

	UFUNCTION(BlueprintCallable)
	void UpdateGameState();

	UFUNCTION(BlueprintCallable)
	void StartCombat();

	UFUNCTION(BlueprintCallable)
	bool GetCombatStarted();

};

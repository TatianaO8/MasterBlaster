// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerUnit.h"
#include "BaseUnit.h"
#include "BasicEnemyUnit.generated.h"


/**
 * 
 */
UCLASS()
class MASTERBLASTER_API ABasicEnemyUnit : public ABaseUnit
{
	GENERATED_BODY()

private:
	AMasterBlasterGameState *gameState;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<ABaseUnit*> PlayerTeam;


	float ClosestTargetDistance();

	
protected:
	// Called when the game starts or when spawned
	void BeginPlay();

public:
	UPROPERTY(BlueprintReadWrite)
		bool Activated;

	UFUNCTION(BlueprintCallable)
		APlayerUnit* AquireTarget();

	UFUNCTION(BlueprintCallable)
		bool IsActivated();

	UFUNCTION(BlueprintCallable)
		bool CheckActivation();

	//override
	void BeginTurn() override;
	
	UFUNCTION(BlueprintCallable)
	bool ShouldMove();

	UFUNCTION(BlueprintCallable)
	FVector PickMoveDestination();

	
	void Die() override;
};

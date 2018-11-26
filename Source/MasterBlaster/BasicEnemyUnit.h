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

	int repeatingCallsRemaining;
	FTimerHandle FireShotTimeHandler;
	
protected:
	// Called when the game starts or when spawned
	void BeginPlay();

public:
	UPROPERTY(BlueprintReadWrite)
		bool Activated;

	UFUNCTION(BlueprintCallable)
		APlayerUnit* AquireTarget();

	UFUNCTION(BlueprintCallable)
		bool PlayerWithinRangeOfEnemy();

	UFUNCTION(BlueprintCallable)
		bool IsActivated();


	FVector dest;
	//override
	void BeginTurn() override;
	
	//override
	// Fire a shot in the specified direction 

	void OnFireShot();

	UFUNCTION(BlueprintCallable)
		virtual void FireShot2(FVector dest);
	
	void Die() override;
};

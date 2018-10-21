// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AMasterBlasterGameState;

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "PlayerUnit.generated.h"

/**
 * 
 */
UCLASS()
class MASTERBLASTER_API APlayerUnit : public ABaseUnit
{
	GENERATED_BODY()
private:
	AMasterBlasterGameState *gameState;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MyTeamIndex;
protected:
	// Called when the game starts or when spawned
	void BeginPlay();
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AMasterBlasterGameState;
class APlayerUnit;
#include "CoreMinimal.h"
#include "DynamicLevelElement.h"
#include "MrBoom.generated.h"

/**
 * 
 */
UCLASS()
class MASTERBLASTER_API AMrBoom : public ADynamicLevelElement
{
	GENERATED_BODY()

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float FullHealth;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth();

	AMasterBlasterGameState* GameState;
	
	UPROPERTY(BlueprintReadWrite)
	bool hasFired;

	UPROPERTY(BlueprintReadWrite)
	float visionRange;
	
	AMrBoom();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	APlayerUnit* AquireTarget();

	UFUNCTION(BlueprintCallable)
	bool IsActivated();
	
};

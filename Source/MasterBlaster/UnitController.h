// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
class ABaseUnit;

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitController.generated.h"

/**
 * 
 */
UCLASS()
class MASTERBLASTER_API AUnitController : public AAIController
{
	GENERATED_BODY()

	TArray<TSubclassOf<ABaseUnit>> team;
	
	
};

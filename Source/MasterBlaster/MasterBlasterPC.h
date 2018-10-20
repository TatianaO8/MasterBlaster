// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AUnitController;
class ABaseUnit;

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MasterBlasterPC.generated.h"

/**
 * 
 */
UCLASS()
class MASTERBLASTER_API AMasterBlasterPC : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ABaseUnit*> PlayerTeam;
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interface.h"

#include "CoreMinimal.h"
#include "DynamicLevelElementInterface.generated.h"

/**
 * 
 */


UINTERFACE(Blueprintable, BlueprintType)
class UDynamicLevelElementInterface : public UInterface {
	GENERATED_BODY()
};

class  IDynamicLevelElementInterface{
	GENERATED_BODY()

public:
	virtual FName GetElementId() = 0;
};

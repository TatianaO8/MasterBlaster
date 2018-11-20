// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DynamicLevelElementInterface.h"

#include "DynamicLevelElement.generated.h"

UCLASS()
class MASTERBLASTER_API ADynamicLevelElement : public AActor, public IDynamicLevelElementInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicLevelElement();
	FName ElementID;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FName GetElementId() override;
	
};

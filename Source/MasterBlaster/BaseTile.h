// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "ConstructorHelpers.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTile.generated.h"

UCLASS()
class MASTERBLASTER_API ABaseTile : public AActor
{
	GENERATED_BODY()

private:
	//UPaperSpriteComponent* tileSpriteComponent;
	

public:	
	// Sets default values for this actor's properties
	ABaseTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

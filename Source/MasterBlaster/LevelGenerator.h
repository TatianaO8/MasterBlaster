// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSPriteComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class MASTERBLASTER_API ALevelGenerator : public AActor{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	TArray<UPaperSpriteComponent *> map;
	
	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* basicTile;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

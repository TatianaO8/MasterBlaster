// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

#include "PaperSpriteComponent.h"
#include "BaseTile.h"


#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class MASTERBLASTER_API ALevelGenerator : public AActor{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	TArray<ABaseTile*> floor;
	TArray<ABaseTile*> ceiling;

	UPROPERTY(EditAnywhere, Category = Rooms)
	TArray<ABaseTile*> test;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};

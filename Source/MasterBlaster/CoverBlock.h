// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "CoverBlock.generated.h"

/**
 * 
 */
UCLASS()
class MASTERBLASTER_API ACoverBlock : public APaperSpriteActor
{
	GENERATED_BODY()
	
private:
	int Health;
	void Die();
	
public:
	ACoverBlock();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

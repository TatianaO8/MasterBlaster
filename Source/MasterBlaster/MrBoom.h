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
	void Die();
	
	

public:
	AMasterBlasterGameState* GameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthPercentage;
	
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

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
		float GetHealthPercentage();

	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();

	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateHealth(float HealthChange);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);
};

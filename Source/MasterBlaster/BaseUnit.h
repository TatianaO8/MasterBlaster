// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "MasterBlasterGameState.h"
#include "BaseUnit.generated.h"

/**
 * 
 */
UCLASS()
class MASTERBLASTER_API ABaseUnit : public APaperCharacter{
	
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* UnitSpriteComponent;

	// The camera 
	//UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* CameraComponent;

	// Camera boom positioning the camera above the character
	//UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

private:
	bool IsMoving;
	FVector MoveDestination;
	bool InWalkRange(FVector dest);
	bool InSprintRange(FVector dest);
	AMasterBlasterGameState *gameState;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPercentage;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Movement")
		int MaxActionPoints;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Movement")
		int ActionPoints;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		float MoveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		float MoveRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
		FVector UnitLocation;

	// Offset from the unit location to spawn projectiles 
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	// How fast the weapon will fire 
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	// Sets default values for this character's properties
	ABaseUnit();

	// Static names for axis bindings
	static const FName FireRightBinding;
	static const FName FireForwardBinding;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Flag to control firing  
	uint32 bCanFire : 1;

	// Handle for efficient management of ShotTimerExpired timer 
	FTimerHandle TimerHandle_ShotTimerExpired;

	UFUNCTION(BlueprintCallable)
	void BeginMove(FVector dest);

	void Move(float DeltaTime);

	void FinishMove();

	void Raycast();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	
	
	void UseActionPoint();
	void EmptyActionPoints();
	void RefreshActionPoints();

public:


	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	UFUNCTION(BlueprintCallable)
		float GetHealthPercentage();

	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();

	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateHealth(float HealthChange);

	UFUNCTION()
		void SetDamageState();

	UFUNCTION(BlueprintCallable)
		int GetActionPoints();

	UFUNCTION(BlueprintCallable)
		void BeginTurn();

	UFUNCTION(BlueprintCallable)
		bool GetIsMoving();

	// void ReceivePointDamage(float Damage, const UDamageType * DamageType, FVector HitLocation, FVector HitNormal, UPrimitiveComponent * Hit Component, FName BoneName, FVector ShotFromDirection, AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo);


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Fire a shot in the specified direction 
	UFUNCTION(BlueprintCallable)
	void FireShot(FVector FireDirection);

	// Handler for the fire timer expiry 
	void ShotTimerExpired();

	


};

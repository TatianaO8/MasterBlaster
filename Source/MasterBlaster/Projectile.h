// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Projectile.generated.h"

UCLASS(config=Game)
class MASTERBLASTER_API AProjectile : public AActor
{
	GENERATED_BODY()

	// Collision component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UPaperSpriteComponent* ProjectileSprite;
	
	// Projectile movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;
public:	
	// Sets default values for this actor's properties
	AProjectile();
	
	// Returns ProjectileMesh subobject 
	FORCEINLINE UPaperSpriteComponent* GetProjectileSprite() const { return ProjectileSprite; }

	// Returns ProjectileMovement subobject
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

};

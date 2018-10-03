// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blaster.generated.h"

UENUM(BlueprintType)
namespace EWeaponProjectile
{
	enum ProjectileType
	{
		EBullet			UMETA(DisplayName = "Bullet"),
		ESpread			UMETA(DisplayName = "Spread"),
		EProjectile		UMETA(DisplayName = "Projectile"),

	};
}


USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
		float TimeBetweenShots;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		int32 ShotCost;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
		float WeaponRange;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
		float WeaponSpread;
};

UCLASS()
class MASTERBLASTER_API ABlaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

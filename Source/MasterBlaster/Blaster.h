// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blaster.generated.h"
#include "Components/BoxComponent.h"

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
	GENERATED_UCLASS_BODY()

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void Instant_Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	FWeaponData WeaponConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	TEnumAsByte<EWeaponProjectile::ProjectileType> ProjectileType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent *CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		USkeletalMeshComponent *WeaponMesh;
	
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

// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UPaperSprite> ProjectileSpriteAsset(TEXT("/Game/Sprites/ProjectileSprite.ProjectileSprite"));

	// Create mesh component for the projectile sphere
	ProjectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ProjectileMesh0"));
	ProjectileSprite->SetSprite(ProjectileSpriteAsset.Object);
	ProjectileSprite->SetupAttachment(RootComponent);
	ProjectileSprite->BodyInstance.SetCollisionProfileName("Projectile");
	//ProjectileSprite->OnComponentHit.AddDynamic(this, &AshootHelpProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileSprite;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileSprite;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

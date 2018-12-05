// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileEvil.h"


// Sets default values
AProjectileEvil::AProjectileEvil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	static ConstructorHelpers::FObjectFinder<UPaperSprite> ProjectileSpriteAsset(TEXT("/Game/Sprites/ProjectileEvilSprite.ProjectileEvilSprite"));

	// Create mesh component for the projectile sphere
	ProjectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ProjectileMesh0"));
	ProjectileSprite->SetSprite(ProjectileSpriteAsset.Object);
	ProjectileSprite->SetupAttachment(RootComponent);
	ProjectileSprite->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileSprite->SetSimulatePhysics(false);
	ProjectileSprite->SetNotifyRigidBodyCollision(true);
	ProjectileSprite->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileSprite;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileSprite;
	ProjectileMovement->InitialSpeed = 2500.f;
	ProjectileMovement->MaxSpeed = 2500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.0f;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
	ProjectileMovement->bBounceAngleAffectsFriction = false;
	ProjectileMovement->Friction = 0.f;

}

// Called when the game starts or when spawned
void AProjectileEvil::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileEvil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UPaperSprite> ProjectileSpriteAsset(TEXT("/Game/Sprites/ProjectileGoodSprite.ProjectileGoodSprite"));

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
	
	SetActorScale3D(FVector(2, 2, 2));

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, GetActorLocation().ToString());
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComponent != NULL))
	{
		//if (GEngine)
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, OtherActor->GetClass()->GetName());

		UnitCharacter = Cast<AActor>(OtherActor);

		//Destroy();
		//Destroy(OtherActor);

		if (OtherActor->bCanBeDamaged)
		{
			Destroy();
			UGameplayStatics::ApplyDamage(UnitCharacter, 50.f, nullptr, this, DamageType);

			//if (GEngine)
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, FString::Printf(TEXT("HERE")));
		}
			

		

		NormalImpulse = GetVelocity() * 100;



		/*if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("I Just Hit: %s"), *OtherActor->GetName()));
		}
		
		if (OtherActor->GetName().Compare("SpawnRoom_C_0") == 0)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, GetActorLocation().ToString());
			}
		}
		if (OtherActor->GetName().Compare("SpawnRoom_C_0") == 0)
		{

		}*/

	}
}

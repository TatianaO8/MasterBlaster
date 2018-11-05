// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemyUnit.h"
#include "GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Engine.h"


void ABasicEnemyUnit::BeginPlay() {
	Super::BeginPlay();

	gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();
	gameState->RegisterEnemyUnit(this);
}

//override from BaseUnit
void ABasicEnemyUnit::BeginTurn() 
{
	Super::BeginTurn();

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("BasicEnemyUnit turn")));

	//if there is any players within range, shoot at it
	//if not, skip turn for now
	//PlayerTeam = gameState->GetPlayerTeam();
	//
	//if(gameState->GetPlayerTeamSize() > 0)
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("There are players on the team")));

	//for (auto x : PlayerTeam)
	//{
	//	//check if the player is within range
	//	if (InSprintRange(x->GetActorLocation()))
	//	{
	//		//if there's enough action points or the player hasn't died yet
	//		while (GetActionPoints() > 0 || x->GetHealth() != 0)
	//		{
	//			target = x->GetActorLocation();
	//			FireShot();
	//		}
	//	}

	//}

}

void ABasicEnemyUnit::FireShot()
{

	// If it's ok to fire again
	if (bCanFire == true)
	{

		if (ActionPoints < 1) {
			return;
		}
		if (IsMoving) {
			return;
		}

		EmptyActionPoints();

		FVector start = GetActorLocation();
		start += GunOffset;

		//enemy knows its target, doesn't have to pick it
		/*FHitResult result;
		GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, result);
		FVector target = result.Location; */


		//GetWorld()->GetFirstPlayerController()->GetMousePosition(target.X, target.Z);

		FRotator direction = UKismetMathLibrary::FindLookAtRotation(start, target);


		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			bAllowRaycast = false;

			// spawn the projectile
			AProjectile *proj = World->SpawnActor<AProjectile>(start, direction);

		}

		//bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ABaseUnit::ShotTimerExpired, FireRate);

		//bCanFire = false;
	}
}


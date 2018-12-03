// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemyUnit.h"
#include "GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectileEvil.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Engine.h"
#include "PlayerUnit.h"


void ABasicEnemyUnit::BeginPlay() {
	Super::BeginPlay();

	gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();
	teamIndex = gameState->RegisterEnemyUnit(this);

	Activated = false;
}
//override from BaseUnit
void ABasicEnemyUnit::BeginTurn() 
{
	Super::BeginTurn();
	RefreshActionPoints();
	bCanBeDamaged = false;
}

APlayerUnit* ABasicEnemyUnit::AquireTarget() {

	float minDistance = 2560;
	APlayerUnit* closestUnit = nullptr;

	for (auto playerUnit : gameState->GetPlayerTeam()) {

		if (playerUnit == nullptr)
			continue;

		auto unitLocation = playerUnit->GetActorLocation();
		auto distance = (this->GetActorLocation() - unitLocation).Size();

		if (distance <= minDistance) {
			minDistance = distance;
			closestUnit = Cast<APlayerUnit>(playerUnit);
		}

	}

	return closestUnit;
}

bool ABasicEnemyUnit::IsActivated()
{
	return Activated;

}

bool ABasicEnemyUnit::PlayerWithinRangeOfEnemy()
{
	PlayerTeam = gameState->GetPlayerTeam();
	for (int x = 0; x < PlayerTeam.Num(); x++)
	{
		if (PlayerTeam[x] == nullptr)
			continue;

		FVector dest = PlayerTeam[x]->GetActorLocation();

		if (InWalkRange(dest))
		{
			Activated = true;
			return true;
		}
	}
	return false;
}

void ABasicEnemyUnit::OnFireShot()
{
	if(--repeatingCallsRemaining <= 0)
		GetWorldTimerManager().ClearTimer(FireShotTimeHandler);
}

void ABasicEnemyUnit::FireShot2(FVector dest){

	bCanBeDamaged = false;
	// If it's ok to fire again
	if (bCanFire == true)
	{

		if (ActionPoints < 1) {
			return;
		}
		if (IsMoving) {
			return;
		}

		UseActionPoint();

		FVector start = GetActorLocation();
		start += GunOffset;
		start.Y = 0.f;

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, start.ToString());

		//has to be a way to do this
		FVector target = dest;
		target.Y = 0.f;
		
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, target.ToString());
		
		//GetWorld()->GetFirstPlayerController()->GetMousePosition(target.X, target.Z);

		FRotator direction = UKismetMathLibrary::FindLookAtRotation(start, target);

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, direction.ToString());

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			bAllowRaycast = false;

			// spawn the projectile
			AProjectile *proj = World->SpawnActor<AProjectileEvil>(start, direction);

		}

		//bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ABaseUnit::ShotTimerExpired, FireRate);

		//bCanFire = false;
		return;
	}
	return;
}

void ABasicEnemyUnit::Die(){
	Super::Die();
	gameState->UnregisterEnemyUnit(teamIndex);
	Destroy();
}


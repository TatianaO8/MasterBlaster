// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemyUnit.h"
#include "GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
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
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Am I ever in here?")));

	Super::BeginTurn();

	repeatingCallsRemaining = 2;

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("BasicEnemyUnit turn")));

	//if there is any players within range, shoot at it
	//if not, skip turn for now
	PlayerTeam = gameState->GetPlayerTeam();
	//
	
	//if(gameState->GetPlayerTeamSize() > 0)
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("There are players on the team")));


	for (int x = 0; x < PlayerTeam.Num(); x++)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("In the for loop")));

		if (ActionPoints == 0)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Out of action points")));
			Activated = false;
			break;
		}

		FVector dest = PlayerTeam[x]->GetActorLocation();
		
		if (InWalkRange(dest)) {
			Activated = true;
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Player within range")));
			GetWorldTimerManager().SetTimer(FireShotTimeHandler, this, &ABasicEnemyUnit::OnFireShot, 1.f, false, 5.0f);
			FireShot2(dest);
			GetWorldTimerManager().SetTimer(FireShotTimeHandler, this, &ABasicEnemyUnit::OnFireShot, 1.f, false, 5.0f);
		}
	}

	EmptyActionPoints();
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
			AProjectile *proj = World->SpawnActor<AProjectile>(start, direction);

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


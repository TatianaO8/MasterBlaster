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
	teamIndex = gameState->RegisterEnemyUnit(this);
	
}

//override from BaseUnit
void ABasicEnemyUnit::BeginTurn() 
{
	Super::BeginTurn();

	repeatingCallsRemaining = 2;

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("BasicEnemyUnit turn")));

	//if there is any players within range, shoot at it
	//if not, skip turn for now
	PlayerTeam = gameState->GetPlayerTeam();
	//or move positions...come back to later


	
	//if(gameState->GetPlayerTeamSize() > 0)
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("There are players on the team")));


	for (int x = 0; x < PlayerTeam.Num(); x++)
	{

		if (ActionPoints == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Out of action points")));
			break;
		}

		dest = PlayerTeam[x]->GetActorLocation();
		if (InWalkRange(dest)) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Player %d within range"), x));
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("P pos: %f, %f"), dest.X, dest.Y));
			//GetWorld()->GetTimerManager().SetTimer(FireShotTimeHandler, this, &ABasicEnemyUnit::OnFireShot, 5.f, false);
			FireShot();
			repeatingCallsRemaining = 2;
			//GetWorldTimerManager().SetTimer(FireShotTimeHandler, this, &ABasicEnemyUnit::OnFireShot, 5.f, false);
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Done firing shot")));
		}


		/*
		//else
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Player not within range")));
		//check if the player is within range
		if (InSprintRange(PlayerTeam[x]->GetActorLocation()))
		{
			ActionPoints--;
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Player is within range")));

			//if there's enough action points or the player hasn't died yet
			while (GetActionPoints() > 0 || PlayerTeam[x]->GetHealth() != 0)
			{
				target = PlayerTeam[x]->GetActorLocation();
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Enemy has ability to shoot")));
			}
		} */
	   	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Enemy is done with turn")));
	}

	EmptyActionPoints();

}

void ABasicEnemyUnit::OnFireShot()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("We need some time")));
	if (--repeatingCallsRemaining <= 0)
		GetWorldTimerManager().ClearTimer(FireShotTimeHandler);
	else
		OnFireShot();
}

void ABasicEnemyUnit::FireShot(){

	if (!CanFireShot()) return;


	EmptyActionPoints();

	FVector start = GetActorLocation();
	start += GunOffset;
	start.Y = 0.f;

	//FRotator enemyRot = GetActorRotation();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, start.ToString());

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, start.ToString());

	//has to be a way to do this

	FVector target = dest;
	target.Y = 0.f;
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Target: %f, %f"), target.X, target.Y));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Start: %f, %f"), start.X, start.Y));


	//GetWorld()->GetFirstPlayerController()->GetMousePosition(target.X, target.Z);

	FRotator direction = UKismetMathLibrary::FindLookAtRotation(start, target);
	direction.Yaw = 0.f;
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Dir: %f, %f, %f"), direction.Pitch, direction.Roll, direction.Yaw));


	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		bAllowRaycast = false;

		// spawn the projectile
		AProjectile *proj = World->SpawnActor<AProjectile>(start, direction);


	}

	//bCanFire = false;
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ABaseUnit::ShotTimerExpired, 5.0f);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Fire shot")));
}

void ABasicEnemyUnit::Die(){
	Super::Die();
	gameState->UnregisterEnemyUnit(teamIndex);
	Destroy();
}


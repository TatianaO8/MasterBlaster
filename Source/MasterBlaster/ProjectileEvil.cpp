// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileEvil.h"


// Sets default values
AProjectileEvil::AProjectileEvil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	static ConstructorHelpers::FObjectFinder<UPaperSprite> ProjectileSpriteAsset(TEXT("/Game/Sprites/ProjectileEvilSprite.ProjectileEvilSprite"));

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


// Fill out your copyright notice in the Description page of Project Settings.

#include "DynamicLevelElement.h"


// Sets default values
ADynamicLevelElement::ADynamicLevelElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementID = "null";
}

// Called when the game starts or when spawned
void ADynamicLevelElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADynamicLevelElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName ADynamicLevelElement::GetElementId(){
	return ElementID;
}


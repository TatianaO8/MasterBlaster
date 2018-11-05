// Fill out your copyright notice in the Description page of Project Settings.

#include "CoverBlock.h"

void ACoverBlock::Die(){
	Destroy();
}

ACoverBlock::ACoverBlock(){
	Health = 100;
}

void ACoverBlock::Tick(float DeltaTime){
	if (Health <= 0) {
		Die();
	}
}


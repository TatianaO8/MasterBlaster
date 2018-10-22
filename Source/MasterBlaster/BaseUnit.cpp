#include "BaseUnit.h"
#include "GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Engine.h"

const FName ABaseUnit::FireRightBinding("FireRight");
const FName ABaseUnit::FireForwardBinding("FireForward");

bool ABaseUnit::InWalkRange(FVector dest){
	FVector loc = GetActorLocation();
	float distance = FGenericPlatformMath::Abs(loc.X - dest.X);
	//GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::Red, FString::Printf(TEXT("MoveDistance: %f."), distance));
	return distance <= MoveRange;
}

bool ABaseUnit::InSprintRange(FVector dest){
	FVector loc = GetActorLocation();
	return FGenericPlatformMath::Abs(loc.X - dest.X) <= 2 * MoveRange;
}

// Sets default values
ABaseUnit::ABaseUnit()
{
	bAllowRaycast = true;
	IsMoving = false;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;

	FullHealth = 100.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;

	MaxActionPoints = ActionPoints = 2;

	MoveSpeed = 200;
	MoveRange = 1280;
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();

	//Maybe this doesn't go here but testing because doesn't work
	FullHealth = 100.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;

	bCanBeDamaged = true;

}

float ABaseUnit::GetHealth()
{
	return HealthPercentage;
}

float ABaseUnit::GetHealthPercentage(){
	return Health / FullHealth;
}

FText ABaseUnit::GetHealthIntText()
{
	int32 hp = FMath::RoundHalfFromZero(HealthPercentage * 100);
	FString hps = FString::FromInt(hp);
	FString healthHUD = hps + FString(TEXT("%"));
	FText hpText = FText::FromString(healthHUD);
	return hpText;
}

void ABaseUnit::SetDamageState()
{
	bCanBeDamaged = true;
}

void ABaseUnit::BeginMove(FVector dest){
	if (IsMoving) {
		//One movement at a time, please
		return;
	}
	if (ActionPoints < 1) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("This unit is out of action points"));
		}
		return;
	}

	if (InWalkRange(dest)) {
		if (GEngine) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Walking"));
		}
		IsMoving = true;
		UseActionPoint();
		MoveDestination = dest;
	}
	else if (InSprintRange(dest) && ActionPoints > 1) {
		if (GEngine) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Running"));
		}
		IsMoving = true;
		EmptyActionPoints();
		MoveDestination = dest;
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("That's too far pal"));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("AP: %d"), ActionPoints));
		}
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, UnitLocation.ToString());
}

void ABaseUnit::Move(float DeltaTime){
	FVector loc = GetActorLocation();
	if (FGenericPlatformMath::Abs(loc.X - MoveDestination.X) <= 1) {
		FinishMove();
	}
	FVector moveDirection = MoveDestination - loc;
	moveDirection.Normalize();
	AddMovementInput(moveDirection * MoveSpeed * DeltaTime);

}

void ABaseUnit::FinishMove() {
	IsMoving = false;
}

float ABaseUnit::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	bCanBeDamaged = false;
	UpdateHealth(-DamageAmount);
	return DamageAmount;
}

int ABaseUnit::GetActionPoints(){
	return ActionPoints;
}

void ABaseUnit::BeginTurn(){
	RefreshActionPoints();
}

bool ABaseUnit::GetIsMoving(){
	return IsMoving;
}

void ABaseUnit::UseActionPoint(){
	ActionPoints--;
}

void ABaseUnit::EmptyActionPoints(){
	ActionPoints = 0;
}

void ABaseUnit::RefreshActionPoints(){
	ActionPoints = MaxActionPoints;
}

void ABaseUnit::UpdateHealth(float HealthChange)
{ 
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, FullHealth);
	HealthPercentage = Health / FullHealth;
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UnitLocation = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, UnitLocation.ToString());

	// Create fire direction vector
	//const float FireRightValue = GetInputAxisValue(FireRightBinding);
	//const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	FVector FireDirection;
	
	gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();

	if (gameState->GetActiveUnit() == this)
	{
		Raycast();
		//FireShot();
	}
	

	if (IsMoving) {
		Move(DeltaTime);
	}

	
}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Set up gameplay key bindings
	//PlayerInputComponent->BindAxis(FireRightBinding);
	//PlayerInputComponent->BindAxis(FireForwardBinding);

}

void ABaseUnit::FireShot()
{

	// If it's ok to fire again
	if (bCanFire == true)
	{
		/*gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();
		UGameViewportClient *GameViewport = GEngine->GameViewport;
		FVector2D MousePosition;
		GameViewport->GetMousePosition(MousePosition);
		FVector WorldPosition, WorldDirection;
		FHitResult *HitResult = new FHitResult();
		FVector StartTrace = gameState->GetActiveUnit()->UnitLocation;
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldPosition, WorldDirection);
		FVector FireDirection = FVector(WorldPosition.X, 0.f, WorldPosition.Y);
		*///GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, WorldPosition.ToString());
		
		

		// If we are pressing fire stick in a direction
		if (true)
		{
			//const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			//const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
			
			
			FVector start = GetActorLocation();
			start += GunOffset;

			FHitResult result;
			GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, result);
			FVector target = result.Location;


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
}

void ABaseUnit::ShotTimerExpired()
{
	bCanFire = true;
}

void ABaseUnit::Raycast()
{
	gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();
	UGameViewportClient *GameViewport = GEngine->GameViewport;
	FVector2D MousePosition;
	GameViewport->GetMousePosition(MousePosition);
	FVector WorldPosition, WorldDirection;
	FHitResult *HitResult = new FHitResult();
	FVector StartTrace = gameState->GetActiveUnit()->UnitLocation;
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldPosition, WorldDirection);
	FVector ForwardVector = WorldPosition;
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, WorldPosition.ToString());
	FVector EndTrace = ForwardVector;
	FCollisionQueryParams *TraceParams = new FCollisionQueryParams();

	if (!bAllowRaycast)
		return;

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(12, 12, 12), false, 0.f, 50.f);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("You hit: %s"), *HitResult->Actor->GetName()));
	}
}
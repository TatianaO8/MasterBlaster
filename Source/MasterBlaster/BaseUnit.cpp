#include "BaseUnit.h"
#include "GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "string.h"

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

	//static ConstructorHelpers::FObjectFinder<UPaperSprite> UnitSpriteAsset(TEXT("/Game/Sprites/UnitPlaceholderSprite.UnitPlaceholderSprite"));

	bRayCastActive = false;
	bAllowRaycast = false;
	bCanMove = true;
	IsMoving = false;
	// Weapon
	GunOffset = FVector(45.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;

	FullHealth = 100.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;

	MaxActionPoints = ActionPoints = 2;

	MoveSpeed = 300;
	MoveRange = 2560;

	isActive = false;

}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();

	//Maybe this doesn't go here but testing because doesn't work
	FullHealth = 100.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;

	bCanBeDamaged = true;

}

/*float ABaseUnit::GetHealth()
{
	return Health;
} */

float ABaseUnit::GetHealthPercentage(){
	return HealthPercentage;
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
	if (IsMoving || !bCanMove) {
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
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("AP: %d"), ActionPoints));
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, GetActorLocation().ToString());
}

float ABaseUnit::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	//bCanBeDamaged = false;
	UpdateHealth(-DamageAmount);
	return DamageAmount;
}

int ABaseUnit::GetActionPoints(){
	return ActionPoints;
}

void ABaseUnit::BeginTurn(){
	bCanBeDamaged = false;
	RefreshActionPoints();
	bCanBeDamaged = true;
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

	//UnitLocation = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, UnitLocation.ToString());

	// Create fire direction vector
	//const float FireRightValue = GetInputAxisValue(FireRightBinding);
	//const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	FVector FireDirection;
	
	if (Health <= 0) {
		Die();
	}

	if (bAllowRaycast)
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

bool ABaseUnit::CanFireShot(){
	if (ActionPoints < 1) {
		return false;
	}
	if (IsMoving) {
		return false;
	}
	return true;
}

void ABaseUnit::FireShot(){
		
	if(!CanFireShot()) return;
		

	EmptyActionPoints();

	FVector start = GetActorLocation();
	start += GunOffset;
	start.Y = 0.f;

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, start.ToString());

	FHitResult result;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, result);
	FVector target = result.Location;
	target.Y = 0.f;
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Target: %f, %f"), target.X, target.Y));
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Start: %f, %f"), start.X, start.Y));



	//GetWorld()->GetFirstPlayerController()->GetMousePosition(target.X, target.Z);

	FRotator direction = UKismetMathLibrary::FindLookAtRotation(start, target);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Dir: %f, %f, %f"), direction.Pitch, direction.Roll, direction.Yaw));


			

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

void ABaseUnit::ShotTimerExpired()
{
	bCanFire = true;
}

void ABaseUnit::EnableRaycast()
{
	bAllowRaycast = true;
}

void ABaseUnit::DisableRaycast()
{
	bAllowRaycast = false;
}

void ABaseUnit::Raycast()
{
	FHitResult result;
	FVector NewVelocity;
	//gameState = GetWorld()->GetGameState<AMasterBlasterGameState>();
	UGameViewportClient *GameViewport = GEngine->GameViewport;
	FVector2D MousePosition;
	GameViewport->GetMousePosition(MousePosition);
	FVector WorldPosition, WorldDirection;
	FHitResult *HitResult = new FHitResult();
	FVector StartTrace = gameState->GetActiveUnit()->GetActorLocation();
	StartTrace += GunOffset;
	StartTrace.Y = 0.f;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, StartTrace.ToString());

	//GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldPosition, WorldDirection);
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, result);
	FVector ForwardVector = result.Location;
	ForwardVector.Y = 0.f;
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Orange, ForwardVector.ToString());
	FVector EndTrace = ForwardVector;
	
	FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
	FPredictProjectilePathParams *ProjParams = new FPredictProjectilePathParams();
	FPredictProjectilePathParams *ProjParams2 = new FPredictProjectilePathParams();
	FPredictProjectilePathResult PathResult;
	FPredictProjectilePathResult PathResult2;
	UGameplayStatics *GameplayStatics;

	ProjParams->bTraceWithChannel = true;
	ProjParams->bTraceWithCollision = true;
	ProjParams->bTraceComplex = true;
	ProjParams->StartLocation = StartTrace;
	ProjParams->LaunchVelocity = ForwardVector;
	ProjParams->DrawDebugTime = .05f;
	ProjParams->DrawDebugType = EDrawDebugTrace::Type::ForDuration;
	ProjParams->SimFrequency = 5;
	ProjParams->MaxSimTime = 2;
	ProjParams->OverrideGravityZ = 1.f;
	ProjParams->ProjectileRadius = 10;
	ProjParams->ActorsToIgnore = (TArray<AActor*>)gameState->GetPlayerTeam(); //{ gameState->GetPlayerTeam()[0],  gameState->GetPlayerTeam()[1], gameState->GetPlayerTeam()[2] };

	GameplayStatics->PredictProjectilePath(GetWorld(),  *ProjParams, PathResult);

	*HitResult = PathResult.HitResult;

	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, HitResult->ImpactPoint.ToString());
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, UKismetMathLibrary::MirrorVectorByNormal(ForwardVector, HitResult->ImpactNormal).ToString());

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, ForwardVector.ToString());*/

	

	UGameplayStatics::SuggestProjectileVelocity(GetWorld(), NewVelocity, HitResult->ImpactPoint + HitResult->Normal, UKismetMathLibrary::MirrorVectorByNormal(ForwardVector, HitResult->ImpactNormal) + HitResult->ImpactPoint, 1000.f);
	
	ProjParams2->bTraceWithChannel = true;
	ProjParams2->bTraceWithCollision = true;
	ProjParams2->bTraceComplex = true;
	ProjParams2->StartLocation = HitResult->ImpactPoint + (HitResult->Normal * 8);
	ProjParams2->LaunchVelocity = NewVelocity;
	ProjParams2->DrawDebugTime = .05f;
	ProjParams2->DrawDebugType = EDrawDebugTrace::Type::ForDuration;
	ProjParams2->SimFrequency = 5;
	ProjParams2->MaxSimTime = 2;
	ProjParams2->OverrideGravityZ = 1.f;
	ProjParams2->ProjectileRadius = 7;
	ProjParams2->ActorsToIgnore = (TArray<AActor*>)gameState->GetPlayerTeam(); //{ gameState->GetPlayerTeam()[0],  gameState->GetPlayerTeam()[1], gameState->GetPlayerTeam()[2] };
	//if (GEngine)
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, ProjParams2->StartLocation.ToString());
	//if (GEngine)
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, ProjParams2->LaunchVelocity.ToString());
	GameplayStatics->PredictProjectilePath(GetWorld(), *ProjParams2, PathResult2);

	if (!bAllowRaycast)
		return;

	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(12, 12, 12), false, 0.f, 50.f);

	//if(GEngine)
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("You hit: %s"), *HitResult->Actor->GetName()));
	
	
}

void ABaseUnit::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComponent != NULL))
	{
		//if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("I Just Hit: %s"), *OtherActor->GetName()));
		

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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("I was just hit")));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Oh, the pain")));
	}
}

void ABaseUnit::Die(){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Oh death"));
}

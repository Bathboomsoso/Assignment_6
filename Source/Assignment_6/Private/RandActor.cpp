#include "RandActor.h"
#include "Components/BoxComponent.h"
#include "SpartaPlatform.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

ARandActor::ARandActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;
}
void ARandActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle, 
		this, 
		&ARandActor::SpawnActor, 
		EachSpawnTime, 
		true,
		0.0f
	);
}
void ARandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARandActor::SpawnActor()
{
	if (SpawnedActorCount >= MaxSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}
	SpawnedActorCount++;

	if (!GetWorld() || !SpawnVolume)
	{
		return;
	}
	
	const FBox BoundingBox = SpawnVolume->CalcBounds(GetActorTransform()).GetBox();
	const FVector SpawnLocation = FMath::RandPointInBox(BoundingBox);
	const FRotator SpawnRotation = UKismetMathLibrary::RandomRotator(true);
	
	ASpartaPlatform* SpawnedPlatform = GetWorld()->SpawnActor<ASpartaPlatform>(SpawnLocation, SpawnRotation);

	if (SpawnedPlatform)
	{
		SpawnedPlatform->MoveEnable = FMath::RandBool();
		if (SpawnedPlatform->MoveEnable)
		{
			SpawnedPlatform->Direction = FMath::VRand().GetSafeNormal();
			SpawnedPlatform->Movespeed = FMath::RandRange(100.0f, 300.0f);
			SpawnedPlatform->MaxRage = FMath::RandRange(300.0f, 600.0f);
		}
		SpawnedPlatform->RoationEnable = FMath::RandBool();
		if (SpawnedPlatform->RoationEnable)
		{
			SpawnedPlatform->RoationSpeed = FMath::RandRange(10.0f, 90.0f);
		}
		SpawnedPlatform->DestroyEnable = FMath::RandBool();
		SpawnedPlatform->MoveTimerEnable = FMath::RandBool();
		
		if (SpawnedPlatform->DestroyEnable || SpawnedPlatform->MoveTimerEnable)
		{
			SpawnedPlatform->TimerEnable = true;
			SpawnedPlatform->TimerOfPlatform = FMath::RandRange(3.0f, 6.0f);
		}
		else
		{
			SpawnedPlatform->TimerEnable = false;
		}
	}
}
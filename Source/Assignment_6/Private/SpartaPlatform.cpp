#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Engine/StaticMesh.h"
#include "SpartaPlatform.h"
#include "GameFramework/Actor.h"

ASpartaPlatform::ASpartaPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(RootComp);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_AssetPlatform.SM_AssetPlatform"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Rock_Basalt.M_Rock_Basalt"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
}

void ASpartaPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	if (TimerEnable)
	GetWorld()->GetTimerManager().SetTimer(
		MySingleShotTimerHandle,
		this,
		&ASpartaPlatform::OnSingleShotTimerElapsed, 
		TimerOfPlatform,
		false
	);

}

void ASpartaPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RoationSpeed) && RoationEnable) // Roation @@
	{
		AddActorLocalRotation(FRotator(0.0f, RoationSpeed * DeltaTime, 0.0f));
	}

	if (MoveEnable) // Move @@
	{
		TargetMove = Movespeed * DeltaTime * Direction; // 이동량
		CurrentLocation = GetActorLocation();
		TargetLocation = CurrentLocation + TargetMove; // 예상위치
		
		MoveDistance = FVector::Dist(StartLocation, TargetLocation); // 거리
		OverValue = 0.0f;
		
		if (MoveDistance > MaxRage)
		{
			OverValue = MoveDistance - MaxRage; // 초과거리
			Direction *= -1.0f;
		}
		if (FVector::DotProduct(CurrentLocation - StartLocation, TargetLocation - StartLocation) < 0)
		{
			OverValue = FVector::Dist(StartLocation, TargetLocation); // 초과거리
			Direction *= -1.0f;
			
		}

		
		FixRage = Direction * OverValue;
		SetActorLocation(TargetLocation + FixRage);
	}

}

void ASpartaPlatform::OnSingleShotTimerElapsed() // 타이머로 삭제, 정지함수
{
	if (DestroyEnable)
	{
		Destroy();
	}
	if (MoveTimerEnable)
	{
		MoveEnable = false;
		GetWorld()->GetTimerManager().SetTimer(
		MySingleShotTimerHandle,
		this,
		&ASpartaPlatform::PlatformTimerMove, 
		TimerOfPlatform,
		false
	);
	}
}

void ASpartaPlatform::PlatformTimerMove() // 다시 움직이는 함수
{
	MoveEnable = true;
	if (MoveTimerEnable)
		GetWorld()->GetTimerManager().SetTimer(
			MySingleShotTimerHandle,
			this,
			&ASpartaPlatform::OnSingleShotTimerElapsed, 
			TimerOfPlatform,
			LoopPlatform
		);
}


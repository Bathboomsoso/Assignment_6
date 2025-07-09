#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpartaPlatform.generated.h"

UCLASS()
class ASSIGNMENT_6_API ASpartaPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpartaPlatform();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements|Roation")
	float RoationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements|Roation")
	bool RoationEnable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements|Move")
	bool MoveEnable = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements|Move")
	FVector Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements|Move")
	float MaxRage = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements|Move")
	float Movespeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements|Timer")
	bool TimerEnable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements|Timer")
	float TimerOfPlatform = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements|Timer")
	bool DestroyEnable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements|Timer")
	bool MoveTimerEnable = false;

protected:
	USceneComponent* RootComp;
	UStaticMeshComponent* StaticMeshComp;
	
	virtual void BeginPlay() override;
	
	FVector CurrentLocation;
	FVector TargetLocation;
	FVector StartLocation;
	FVector FixRage;
	FVector TargetMove;
	float MoveDistance;
	float OverValue;
	bool LoopPlatform = false;

	FTimerHandle MySingleShotTimerHandle;
	void OnSingleShotTimerElapsed();
	void PlatformTimerMove();
	
	virtual void Tick(float DeltaTime) override;
};
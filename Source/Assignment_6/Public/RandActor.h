// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandActor.generated.h"

UCLASS()
class ASSIGNMENT_6_API ARandActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandActor();

	UFUNCTION()
	void SpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UBoxComponent* SpawnVolume;

	FVector RandDirection;
	FVector RandLocation;
	int32 RandRange;
	int32 RandTimes;
	int32 RandSpeed;
	bool RandRoation;
	bool RandMove;
	bool RandRemove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandRange/Range")
	int32 RandNumForRandRangeMin = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandRange/Range")
	int32 RandNumForRandRangeMax = 400;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandRange/Times")
	int32 RandNumForTimesMin = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandRange/Times")
	int32 RandNumForTimesMax = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandRange/Speed")
	int32 RandNumForSpeedMin = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandRange/Speed")
	int32 RandNumForSpeedMax = 300;
	
	FTimerHandle SpawnTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 SpawnedActorCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 MaxSpawnCount = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float EachSpawnTime = 1.0f;

public:	
	virtual void Tick(float DeltaTime) override;

};

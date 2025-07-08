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

protected:
	USceneComponent* RootComp;
	UStaticMeshComponent* StaticMeshComp;
	
	virtual void BeginPlay() override;
	
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
	
	FVector CurrentLocation;
	FVector TargetLocation;
	FVector StartLocation;
	FVector FixRage;
	FVector TargetMove;
	float MoveDistance;
	float OverValue;
	int a;
	
	virtual void Tick(float DeltaTime) override;
public:	
	

};

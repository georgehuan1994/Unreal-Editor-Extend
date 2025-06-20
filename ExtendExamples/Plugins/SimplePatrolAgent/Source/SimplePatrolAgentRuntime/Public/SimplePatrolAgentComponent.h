// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SimplePatrolAgentComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEPATROLAGENTRUNTIME_API USimplePatrolAgentComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	USimplePatrolAgentComponent();

	UPROPERTY(EditInstanceOnly, Category = "Patrol Agent Settings")
	TArray<AActor*> PatrolPoints;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Patrol Agent Settings")
	int32 CurrentPatrolPointIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Patrol Agent Settings")
	float PatrolSpeed = 230.0f;

	UPROPERTY(EditAnywhere, Category = "Patrol Agent Settings")
	float DistanceThreshold = 150.0f;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

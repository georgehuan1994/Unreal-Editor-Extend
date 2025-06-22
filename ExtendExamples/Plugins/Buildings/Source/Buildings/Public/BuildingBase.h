// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingBase.generated.h"

class UBuildingStylePreset;
class UHierarchicalInstancedStaticMeshComponent;
class UStaticMesh;

UCLASS()
class BUILDINGS_API ABuildingBase : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBuildingStylePreset* BuildingStyle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Levels = 3;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHierarchicalInstancedStaticMeshComponent* HISMCornerGround;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHierarchicalInstancedStaticMeshComponent* HISMCorner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHierarchicalInstancedStaticMeshComponent* HISMWallGround;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHierarchicalInstancedStaticMeshComponent* HISMWall;

protected:

	ABuildingBase();
	
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Destroyed() override;


};

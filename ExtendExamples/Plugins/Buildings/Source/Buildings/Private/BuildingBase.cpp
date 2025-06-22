// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBase.h"
#include "BuildingStylePreset.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

ABuildingBase::ABuildingBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	HISMCornerGround = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Corner Ground Meshes"));
	HISMCornerGround->SetupAttachment(RootComponent);
		
	HISMCorner = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Corner Regular Meshes"));
	HISMCorner->SetupAttachment(RootComponent);

	HISMWallGround = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Wall Ground Meshes"));
	HISMWallGround->SetupAttachment(RootComponent);

	HISMWall= CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Wall Regular Meshes"));
	HISMWall->SetupAttachment(RootComponent);
}

void ABuildingBase::BeginPlay()
{	
	Super::BeginPlay();
	
	HISMCornerGround->SetMobility(EComponentMobility::Static);
    HISMCorner->SetMobility(EComponentMobility::Static);
	HISMWallGround->SetMobility(EComponentMobility::Static);
	HISMWall->SetMobility(EComponentMobility::Static);
}

void ABuildingBase::OnConstruction(const FTransform& Transform)
{
	if (!IsValid(HISMCornerGround) || !IsValid(HISMCorner))
	{
		UE_LOG(LogTemp,Warning,TEXT("HISM not valid"));
		return;
	}
	
	HISMCornerGround->ClearInstances();
	HISMCorner->ClearInstances();
	HISMWallGround->ClearInstances();
	HISMWall->ClearInstances();

	if (!BuildingStyle)
	{
		UE_LOG(LogTemp,Warning,TEXT("No style selected. Skipping..."));
		return;
	}

#if WITH_EDITOR
	if (!BuildingStyle->OnObjectChanged.IsBoundToObject(this))
	{
		BuildingStyle->OnObjectChanged.AddUObject(this, &ABuildingBase::RerunConstructionScripts);
	}
#endif
	
	HISMCornerGround->SetStaticMesh(BuildingStyle->GroundFloor.CornerMesh);
	HISMWallGround->SetStaticMesh(BuildingStyle->GroundFloor.WallMesh);

	HISMCorner->SetStaticMesh(BuildingStyle->RegularFloor.CornerMesh);
	HISMWall->SetStaticMesh(BuildingStyle->RegularFloor.WallMesh);

	
	if (IsValid(BuildingStyle->GroundFloor.MaterialOverride))
	{
		if (IsValid(BuildingStyle->GroundFloor.CornerMesh))
		{
			HISMCornerGround->SetMaterial(0,BuildingStyle->GroundFloor.MaterialOverride);
		}

		if (IsValid(BuildingStyle->GroundFloor.WallMesh))
		{
			HISMWallGround->SetMaterial(0,BuildingStyle->GroundFloor.MaterialOverride);
		}
	}

	if (IsValid(BuildingStyle->RegularFloor.MaterialOverride))
	{
		if (IsValid(BuildingStyle->RegularFloor.CornerMesh))
		{
			HISMCorner->SetMaterial(0,BuildingStyle->RegularFloor.MaterialOverride);
		}

		if (IsValid(BuildingStyle->GroundFloor.WallMesh))
		{
			HISMWall->SetMaterial(0,BuildingStyle->RegularFloor.MaterialOverride);
		}
	}

	if(!IsValid(BuildingStyle->GroundFloor.CornerMesh) || !IsValid(BuildingStyle->GroundFloor.WallMesh) || !IsValid(BuildingStyle->RegularFloor.CornerMesh) || !IsValid(BuildingStyle->RegularFloor.WallMesh))
	{
		UE_LOG(LogTemp,Warning,TEXT("Meshes not valid. Skipping..."));
		return;
	}
	
	if (Levels>0)
	{
		for (int i = 0; i < Levels; ++i)
		{
			UHierarchicalInstancedStaticMeshComponent* Corner = i == 0 ? HISMCornerGround : HISMCorner;
			UHierarchicalInstancedStaticMeshComponent* Wall = i == 0 ? HISMWallGround : HISMWall;
			const FModuleDefinition& Style = i == 0 ? BuildingStyle->GroundFloor : BuildingStyle->RegularFloor;

			float WallLength = 2.f * Style.WallMesh->GetBounds().BoxExtent.X;
			float CornerLength = 2.f * Style.WallMesh->GetBounds().BoxExtent.X;
			float Height = 2.f * Style.WallMesh->GetBounds().BoxExtent.Z;
			
			FTransform TransformWallA = FTransform(FRotator(0.f,0.f,0.f),FVector(-0.5f * WallLength,0.5f * CornerLength - 10.f,i * Height));
			FTransform TransformWallB = FTransform(FRotator(0.f,180.f,0.f),FVector(0.5f * WallLength,-0.5f * CornerLength + 10.f,i * Height));

			Wall->AddInstances({TransformWallA,TransformWallB},false,false,false);

			FTransform TransformCornerA = FTransform(FRotator(0.f,180.f,0.f),FVector(-0.5f * WallLength,-0.5f * CornerLength + 10.f,i * Height));
			FTransform TransformCornerB = FTransform(FRotator(0.f,0.f,0.f),FVector(0.5f * WallLength,0.5f * CornerLength - 10.f,i * Height));
			FTransform TransformCornerC = FTransform(FRotator(0.f,-90.f,0.f),FVector(0.5f * WallLength + 0.5f * CornerLength -10.f,0.f,i * Height));
			FTransform TransformCornerD = FTransform(FRotator(0.f,90.f,0.f),FVector(-0.5f * WallLength - 0.5f * CornerLength + 10.f,0.f,i * Height));

			Corner->AddInstances({TransformCornerA,TransformCornerB,TransformCornerC,TransformCornerD},false,false,false);
		}		
	}
}

void ABuildingBase::Destroyed()
{
	if (BuildingStyle && BuildingStyle->OnObjectChanged.IsBoundToObject(this))
	{
		BuildingStyle->OnObjectChanged.RemoveAll(this);
	}
	
	Super::Destroyed();
}
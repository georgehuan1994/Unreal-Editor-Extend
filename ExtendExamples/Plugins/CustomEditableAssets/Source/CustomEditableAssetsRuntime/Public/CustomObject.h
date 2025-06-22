// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CustomObject.generated.h" 

DECLARE_MULTICAST_DELEGATE(FOnAssetChanged);

UCLASS()
class CUSTOMEDITABLEASSETSRUNTIME_API UCustomObject : public UObject
{
	GENERATED_BODY()

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Object")
	TSubclassOf<AActor> RepresentingActorClass = nullptr;
	
	FOnAssetChanged OnObjectChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Object")
	float Radius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Object")
	float Speed = 1.f;
};

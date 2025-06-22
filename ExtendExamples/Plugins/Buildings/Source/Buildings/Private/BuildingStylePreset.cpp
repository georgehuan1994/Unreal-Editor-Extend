// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingStylePreset.h"

#if WITH_EDITOR
void UBuildingStylePreset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
	OnObjectChanged.Broadcast();
}
#endif

// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomObject.h"

#if WITH_EDITOR
void UCustomObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);

	OnObjectChanged.Broadcast();
}
#endif
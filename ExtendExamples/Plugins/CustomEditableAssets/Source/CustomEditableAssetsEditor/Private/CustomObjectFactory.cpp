// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomObjectFactory.h"

#include "CustomObject.h"

UCustomObjectFactory::UCustomObjectFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UCustomObject::StaticClass();

	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = false;
}

UObject* UCustomObjectFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
                                                UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UCustomObject>(InParent, Class, Name, Flags | RF_Transactional);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomObjectFactory.h"

#include "CustomObject.h"
#include "CustomObjectToolkit.h"

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

EAssetCommandResult UAssetDefinition_CustomObject::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	for (UCustomObject* EditingAsset : OpenArgs.LoadObjects<UCustomObject>())
	{
		const TSharedRef<FCustomObjectToolkit> Toolkit = MakeShared<FCustomObjectToolkit>();
		Toolkit->InitEditor(OpenArgs.ToolkitHost, EditingAsset);
	}
	return EAssetCommandResult::Handled;
}

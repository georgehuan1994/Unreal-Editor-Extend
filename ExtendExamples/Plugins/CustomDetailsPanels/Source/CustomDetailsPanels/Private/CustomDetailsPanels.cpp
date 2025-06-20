// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomDetailsPanels.h"

#include "DirectionalLightCustomDetails.h"
#include "Engine/DirectionalLight.h"

#define LOCTEXT_NAMESPACE "FCustomDetailsPanelsModule"

void FCustomDetailsPanelsModule::StartupModule()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyEditorModule.RegisterCustomClassLayout(ADirectionalLight::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FDirectionalLightCustomDetails::MakeInstance));
}

void FCustomDetailsPanelsModule::ShutdownModule()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyEditorModule.UnregisterCustomClassLayout(ADirectionalLight::StaticClass()->GetFName());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomDetailsPanelsModule, CustomDetailsPanels)

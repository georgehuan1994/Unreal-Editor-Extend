#include "BuildingsEditor.h"

#define LOCTEXT_NAMESPACE "FBuildingsEditorModule"

DEFINE_LOG_CATEGORY(LogTlBuildingsEditor);

void FBuildingsEditorModule::StartupModule()
{
	UE_LOG(LogTlBuildingsEditor, Log, TEXT("BuildingsEditor module has been loaded"));
}

void FBuildingsEditorModule::ShutdownModule()
{
	UE_LOG(LogTlBuildingsEditor, Log, TEXT("BuildingsEditor module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FBuildingsEditorModule, BuildingsEditor)

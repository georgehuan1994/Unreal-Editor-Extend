#include "CustomEditableAssetsEditor.h"
#include "AssetToolsModule.h"
#include "CustomObject.h"
#include "IAssetTools.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FCustomEditableAssetsEditorModule"

EAssetTypeCategories::Type FCustomEditableAssetsEditorModule::CustomAssetCategory;
TSharedPtr<FSlateStyleSet> FCustomEditableAssetsEditorModule::CustomAssetsEditorSlateStyle;

void FCustomEditableAssetsEditorModule::StartupModule()
{
	const FString ProjectResourceDir = FPaths::ProjectPluginsDir() / TEXT("CustomEditableAssets/Resources");

	CustomAssetsEditorSlateStyle = MakeShareable(new FSlateStyleSet("CustomEditableAssetsEditor"));
	CustomAssetsEditorSlateStyle->Set("CustomAsset.Thumbnail",
		new FSlateImageBrush(FString(ProjectResourceDir / "Icon128.png"), FVector2D(128.0f, 128.0f)));
	
	CustomAssetsEditorSlateStyle->Set("ClassIcon.CustomActor",
		new FSlateImageBrush(FString(ProjectResourceDir / "Icon128.png"), FVector2D(32.0f, 32.0f)));
	
	CustomAssetsEditorSlateStyle->Set("ClassIcon.UAssetDefinition_CustomObject",
		new FSlateImageBrush(FString(ProjectResourceDir / "Icon128.png"), FVector2D(32.0f, 32.0f)));

	FSlateStyleRegistry::RegisterSlateStyle(*CustomAssetsEditorSlateStyle.Get());
}

void FCustomEditableAssetsEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomEditableAssetsEditorModule, CustomEditableAssetsEditor)

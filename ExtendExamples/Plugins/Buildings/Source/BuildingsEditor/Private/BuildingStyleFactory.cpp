
#include "BuildingStyleFactory.h"
#include "BuildingStylePreset.h"
#include "BuildingStyleToolkit.h"
#include "Styling/SlateStyle.h"

UBuildingStyleFactory::UBuildingStyleFactory(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	SupportedClass = UBuildingStylePreset::StaticClass();
	
	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}

UObject* UBuildingStyleFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UBuildingStylePreset>(InParent, Class, Name, Flags | RF_Transactional);
}

EAssetCommandResult UAssetDefinition_BuildingStylePreset::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	return Super::OpenAssets(OpenArgs);
	for (UBuildingStylePreset* EditingAsset : OpenArgs.LoadObjects<UBuildingStylePreset>())
	{
		const TSharedRef<FBuildingStyleToolkit> CustomObjectToolkit(new FBuildingStyleToolkit());
		CustomObjectToolkit->Initialize(OpenArgs.ToolkitHost, EditingAsset);
	}

	return EAssetCommandResult::Handled;
}


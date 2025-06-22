#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "Modules/ModuleManager.h"

class FCustomEditableAssetsEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    static EAssetTypeCategories::Type CustomAssetCategory;
    static TSharedPtr<FSlateStyleSet> CustomAssetsEditorSlateStyle;
};

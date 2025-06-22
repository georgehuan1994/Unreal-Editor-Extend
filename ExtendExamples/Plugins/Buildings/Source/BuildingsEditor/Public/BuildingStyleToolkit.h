#pragma once

class UBuildingStylePreset;
class UCustomObject;
class FTabManager;

class BUILDINGSEDITOR_API FBuildingStyleToolkit : public FAssetEditorToolkit
{
public:
	void Initialize(const TSharedPtr<IToolkitHost>& InitToolkitHost, UBuildingStylePreset* StylePreset);
	
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	virtual FName GetToolkitFName() const override { return FName("CustomObjectEditor"); }
	virtual FText GetBaseToolkitName() const override { return INVTEXT("Custom Object Editor"); }
	virtual FString GetWorldCentricTabPrefix() const override { return "CustomObjectEditor"; }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::White; }
	
private:
	TObjectPtr<UBuildingStylePreset> BuildingStylePreset = nullptr;
};

#pragma once

class UCustomObject;
class FTabManager;

class CUSTOMEDITABLEASSETSEDITOR_API FCustomObjectToolkit : public FAssetEditorToolkit
{
public:
	void InitEditor(const TSharedPtr<IToolkitHost>& InitToolkitHost, UCustomObject* Object);
	
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	virtual FName GetToolkitFName() const override { return FName("CustomObjectEditor"); }
	virtual FText GetBaseToolkitName() const override { return INVTEXT("Custom Object Editor"); }
	virtual FString GetWorldCentricTabPrefix() const override { return "CustomObjectEditor"; }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::White; }
	
private:
	TWeakObjectPtr<UCustomObject> CustomObject = nullptr;
};

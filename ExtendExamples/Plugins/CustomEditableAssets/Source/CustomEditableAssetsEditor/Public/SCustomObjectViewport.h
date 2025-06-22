#pragma once
#include "SCommonEditorViewportToolbarBase.h"
#include "SEditorViewport.h"

class FAdvancedPreviewScene;
class UCustomObject;

class SCustomObjectViewport: public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider
{
public:
	SLATE_BEGIN_ARGS(SCustomObjectViewport) : _EditingObject(nullptr) {}

		SLATE_ARGUMENT(UCustomObject*, EditingObject )
	
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);
	void UpdatePreviewActor();

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	
	//Toolbar interface
	virtual TSharedRef<SEditorViewport> GetViewportWidget() override {return SharedThis(this);}
	virtual TSharedPtr<FExtender> GetExtenders() const override {return MakeShareable(new FExtender);}
	virtual void OnFloatingButtonClicked() override {}
	
	TSharedPtr<FAdvancedPreviewScene> AdvancedPreviewScene = nullptr;
	TSoftObjectPtr<UCustomObject> CustomObject = nullptr;
	AActor* PreviewActor = nullptr;

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	
private:
	TSharedPtr<FEditorViewportClient> LevelViewportClient;
};

#pragma once

#include "SCommonEditorViewportToolbarBase.h"
#include "SEditorViewport.h"

class ABuildingBase;
class UBuildingStylePreset;
class FAdvancedPreviewScene;

class SBuildingStyleViewport: public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider
{
public:
	SLATE_BEGIN_ARGS(SBuildingStyleViewport) : _EditingObject(nullptr) {}
		SLATE_ARGUMENT(UBuildingStylePreset*, EditingObject )
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

	virtual TSharedRef<SEditorViewport> GetViewportWidget() override { return SharedThis(this); }
	virtual TSharedPtr<FExtender> GetExtenders() const override { return MakeShareable(new FExtender); }

	virtual void OnFloatingButtonClicked() override
	{
	}
	
	TSharedPtr<FAdvancedPreviewScene> AdvancedPreviewScene = nullptr;
	TSoftObjectPtr<UBuildingStylePreset> StylePreset = nullptr;

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	TSharedPtr<FEditorViewportClient> LevelViewportClient;
};

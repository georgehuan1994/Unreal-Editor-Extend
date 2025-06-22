#include "SBuildingStyleViewport.h"
#include "AdvancedPreviewScene.h"
#include "BuildingBase.h"
#include "BuildingStylePreset.h"

void SBuildingStyleViewport::Construct(const FArguments& InArgs)
{
	// 在构造之前，先创建一个新的预览场景，否则会默认获取编辑器的主世界的场景
	AdvancedPreviewScene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));

	SEditorViewport::Construct(SEditorViewport::FArguments());
	
	StylePreset = InArgs._EditingObject;
	if (!StylePreset.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Editing asset is not valid"));
		return;
	}

	ABuildingBase* PreviewBuilding = GetWorld()->SpawnActor<ABuildingBase>();
	PreviewBuilding->BuildingStyle = StylePreset.Get();
	PreviewBuilding->RerunConstructionScripts();
}


TSharedRef<FEditorViewportClient> SBuildingStyleViewport::MakeEditorViewportClient()
{
	LevelViewportClient = MakeShareable(new FEditorViewportClient(
		nullptr, AdvancedPreviewScene.Get(), SharedThis(this)));
	
	LevelViewportClient->ViewportType = LVT_Perspective;
	LevelViewportClient->bSetListenerPosition = false;
	LevelViewportClient->SetRealtime(true);
	
	LevelViewportClient->SetViewLocation( FVector(-50000.f,0.f,5000));
	LevelViewportClient->SetViewRotation( FRotator(-30.0f, -90.0f, 0.0f) );
	LevelViewportClient->SetViewLocationForOrbiting( FVector::ZeroVector );
	
	return LevelViewportClient.ToSharedRef();
}
#include "SCustomObjectViewport.h"
#include "AdvancedPreviewScene.h"
#include "CustomObject.h"
#include "CustomEditableAssetsEditor.h"
#include "Engine/PointLight.h"

void SCustomObjectViewport::Construct(const FArguments& InArgs)
{
	// We need to create a new Scene before constructing this viewport. Otherwise, it will default to grabbing the one from the main World in the Editor
	AdvancedPreviewScene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));

	SEditorViewport::Construct(SEditorViewport::FArguments());
	
	CustomObject = InArgs._EditingObject;

	if (!CustomObject.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("SCustomObjectViewport: CustomObject is not valid!"));
		return;
	}

	CustomObject->OnObjectChanged.AddSP(this, &SCustomObjectViewport::UpdatePreviewActor);
	UpdatePreviewActor();
}

void SCustomObjectViewport::UpdatePreviewActor()
{
	if (PreviewActor)
	{
		PreviewActor->Destroy();
		PreviewActor = nullptr;
	}
}

void SCustomObjectViewport::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SEditorViewport::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	
	if (PreviewActor)
	{
		float X = CustomObject->Radius * FMath::Cos(FPlatformTime::Seconds() * 0.1f * CustomObject->Speed);
		float Y = CustomObject->Radius * FMath::Sin(FPlatformTime::Seconds() * 0.1f * CustomObject->Speed);
		PreviewActor->SetActorLocation(FVector(X,Y,0));
	}
}

TSharedRef<FEditorViewportClient> SCustomObjectViewport::MakeEditorViewportClient()
{
	LevelViewportClient = MakeShareable(new FEditorViewportClient(nullptr, AdvancedPreviewScene.Get(), SharedThis(this)));
	
	LevelViewportClient->ViewportType = LVT_Perspective;
	LevelViewportClient->bSetListenerPosition = false;
	LevelViewportClient->SetRealtime(true);
	
	LevelViewportClient->SetViewLocation( FVector(-25000.f,0.f,500));
	LevelViewportClient->SetViewRotation( FRotator(-30.0f, -90.0f, 0.0f) );
	LevelViewportClient->SetViewLocationForOrbiting( FVector::ZeroVector );
	
	return LevelViewportClient.ToSharedRef();
}
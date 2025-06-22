
#include "SimplePatrolAgentVisualizer.h"
#include "SimplePatrolAgentComponent.h"
#include "Engine/Canvas.h"

IMPLEMENT_HIT_PROXY(HPatrolPointProxy, HComponentVisProxy);

void FSimplePatrolAgentVisualizer::DrawVisualization(const UActorComponent* Component,
	const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	PatrolAgentComponent = Cast<USimplePatrolAgentComponent>(Component);
	
	if(!PatrolAgentComponent.IsValid())
	{
		return;
	}
	
	TArray<AActor*> PatrolPoints = PatrolAgentComponent->PatrolPoints;
	if (PatrolPoints.IsEmpty())
	{
		return;
	}

	FVector StartLocation = PatrolAgentComponent->GetOwner()->GetActorLocation();
	for (int i = 0; i < PatrolPoints.Num(); ++i)
	{
		if (IsValid(PatrolPoints[i]))
		{
			const FLinearColor Color = FColor::MakeRedToGreenColorFromScalar(
				static_cast<float>(i) / (PatrolPoints.Num() + 1));

			FVector EndLocation = PatrolPoints[i]->GetActorLocation();

			PDI->DrawLine(StartLocation, EndLocation, Color, SDPG_Foreground, 5.f, 0.0f, false);

			PDI->SetHitProxy(new HPatrolPointProxy(Component, i));
			PDI->DrawPoint(EndLocation, Color, 30.f, SDPG_Foreground);
			PDI->SetHitProxy(nullptr);

			StartLocation = EndLocation;
		}
	}

	if (IsValid(PatrolPoints[0]))
	{
		const FLinearColor Color = FColor::MakeRedToGreenColorFromScalar(1.f).ReinterpretAsLinear();
		PDI->DrawLine(StartLocation, PatrolPoints[0]->GetActorLocation(), Color, SDPG_Foreground, 2.f, 0.0f, true);
	}
}

void FSimplePatrolAgentVisualizer::DrawVisualizationHUD(const UActorComponent* Component,
	const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas)
{
	if (!IsValid(PatrolAgentComponent.Get()))
	{
		return;
	}

	for (int i = 0; i < PatrolAgentComponent.Get()->PatrolPoints.Num(); ++i)
	{
		if (IsValid(PatrolAgentComponent.Get()->PatrolPoints[i]))
		{
			FVector Location = PatrolAgentComponent.Get()->PatrolPoints[i]->GetActorLocation() + FVector(0, 0, 0.f);

			const FPlane ProjectionPlane = View->Project(Location);

			const float NormalizedProjectionX = 0.5f * (ProjectionPlane.X + 1);
			const float NormalizedProjectionY = 1.f - 0.5f * (ProjectionPlane.Y + 1);

			const double PosX = NormalizedProjectionX * Viewport->GetSizeXY().X / Canvas->GetDPIScale();
			const double PosY = NormalizedProjectionY * Viewport->GetSizeXY().Y / Canvas->GetDPIScale();

			FCanvasTextItem TextItem(FVector2D(PosX, PosY), FText::FromString(FString::FromInt(i)),
			                         GEngine->GetSubtitleFont(), FLinearColor::White);
			TextItem.EnableShadow(FLinearColor::Black);
			Canvas->DrawItem(TextItem);
		}
	}
} 

bool FSimplePatrolAgentVisualizer::VisProxyHandleClick(FEditorViewportClient* InViewportClient,
	HComponentVisProxy* VisProxy, const FViewportClick& Click)
{
	if (VisProxy && VisProxy->Component.IsValid())
	{
		const HPatrolPointProxy* PatrolPointProxy = static_cast<HPatrolPointProxy*>(VisProxy);
		SelectedProxyId = PatrolPointProxy->Id;
		
		return true;
	}

	SelectedProxyId = -1;
	return false;
}

bool FSimplePatrolAgentVisualizer::GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const
{
	if (IsValid(PatrolAgentComponent.Get()) && SelectedProxyId >= 0)
	{
		if(const AActor* PatrolPointActor = PatrolAgentComponent->PatrolPoints[SelectedProxyId]; IsValid(PatrolPointActor))
		{
			OutLocation = PatrolPointActor->GetActorLocation();
			return true;
		}
	}

	return false;
}

bool FSimplePatrolAgentVisualizer::HandleInputDelta(FEditorViewportClient* ViewportClient,
	FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale)
{
	if (IsValid(PatrolAgentComponent.Get()) && SelectedProxyId > -1)
	{
		if(AActor* PatrolPointActor = PatrolAgentComponent->PatrolPoints[SelectedProxyId]; IsValid(PatrolPointActor))
		{
			PatrolPointActor->SetActorLocation(PatrolPointActor->GetActorLocation() + DeltaTranslate);
			return true;
		}
	}

	return false;
}


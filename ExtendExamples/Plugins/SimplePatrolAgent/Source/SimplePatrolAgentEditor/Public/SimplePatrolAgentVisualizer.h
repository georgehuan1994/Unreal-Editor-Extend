// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ComponentVisualizer.h"

class USimplePatrolAgentComponent;

struct HPatrolPointProxy : public HComponentVisProxy
{
	DECLARE_HIT_PROXY();

	int32 Id;

	HPatrolPointProxy(const UActorComponent* InComponent, const int32 PatrolPointId):
		HComponentVisProxy(InComponent, HPP_Wireframe), Id(PatrolPointId)
	{
	}
};

class SIMPLEPATROLAGENTEDITOR_API FSimplePatrolAgentVisualizer : public FComponentVisualizer
{
public:
	virtual void DrawVisualization(const UActorComponent* Component,
		const FSceneView* View, FPrimitiveDrawInterface* PDI) override;

	virtual void DrawVisualizationHUD(const UActorComponent* Component,
		const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;

	virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient,
		HComponentVisProxy* VisProxy, const FViewportClick& Click) override;

	virtual bool GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const override;
	
	virtual bool HandleInputDelta(FEditorViewportClient* ViewportClient,
		FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale) override;

	TWeakObjectPtr<const USimplePatrolAgentComponent> PatrolAgentComponent;

	int32 SelectedProxyId;
};

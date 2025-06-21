#include "SimplePatrolAgentEditor.h"

#include "SimplePatrolAgentComponent.h"
#include "SimplePatrolAgentVisualizer.h"
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"

#define LOCTEXT_NAMESPACE "FSimplePatrolAgentEditorModule"

void FSimplePatrolAgentEditorModule::StartupModule()
{
	if (GUnrealEd)
	{
		const TSharedPtr<FSimplePatrolAgentVisualizer> Visualizer = MakeShareable(new FSimplePatrolAgentVisualizer());
		GUnrealEd->RegisterComponentVisualizer(USimplePatrolAgentComponent::StaticClass()->GetFName(), Visualizer);
	}
}

void FSimplePatrolAgentEditorModule::ShutdownModule()
{
	if (GUnrealEd)
	{
		GUnrealEd->UnregisterComponentVisualizer(USimplePatrolAgentComponent::StaticClass()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSimplePatrolAgentEditorModule, SimplePatrolAgentEditor)
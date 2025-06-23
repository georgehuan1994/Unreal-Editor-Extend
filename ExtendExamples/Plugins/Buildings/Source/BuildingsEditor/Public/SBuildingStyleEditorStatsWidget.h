// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class BUILDINGSEDITOR_API SBuildingStyleEditorStatsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBuildingStyleEditorStatsWidget)
		{
		}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void AddMessage(const FString& Message, const bool bIsError);
	void ClearMessages();

protected:
	TSharedPtr<SVerticalBox> MessageBoxWidget;
};

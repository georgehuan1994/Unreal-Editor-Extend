// Fill out your copyright notice in the Description page of Project Settings.


#include "SBuildingStyleEditorStatsWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SBuildingStyleEditorStatsWidget::Construct(const FArguments& InArgs)
{
	const auto VerticalScrollbar = SNew(SScrollBar)
		.Orientation(Orient_Vertical)
		.Thickness(FVector2D(11.0f, 11.0f));

	MessageBoxWidget = SNew(SVerticalBox)
	+ SVerticalBox::Slot()
	.AutoHeight();

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush(TEXT("Brushes.Recessed")))
		.Padding(0.0f)
		.HAlign(HAlign_Fill)
		[
			SNew(SScrollBox)
			.Orientation(Orient_Vertical)
			.ExternalScrollbar(VerticalScrollbar)
			+ SScrollBox::Slot()
			[
				SNew(SBorder)
				.Padding(0.0f)
				.HAlign(HAlign_Fill)
				.BorderImage(FAppStyle::Get().GetBrush(TEXT("Brushes.Recessed")))
				[
					MessageBoxWidget.ToSharedRef()
				]
			]
		]
	];
}

void SBuildingStyleEditorStatsWidget::AddMessage(const FString& Message, const bool bIsError)
{
	MessageBoxWidget->AddSlot()
	                .AutoHeight()
	                .Padding(2.5, 2.5)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush(TEXT("Brushes.Recessed")))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(FAppStyle::GetBrush(bIsError ? "MessageLog.Error" : "MessageLog.Warning"))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(FAppStyle::Get(), TEXT("DataTableEditor.CellText"))
				.ColorAndOpacity(bIsError ? FStyleColors::Error : FStyleColors::Warning)
				.Text(FText::FromString(Message))
				.ToolTipText(FText::FromString(Message))
			]
		]
	];
}

void SBuildingStyleEditorStatsWidget::ClearMessages()
{
	MessageBoxWidget->ClearChildren();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

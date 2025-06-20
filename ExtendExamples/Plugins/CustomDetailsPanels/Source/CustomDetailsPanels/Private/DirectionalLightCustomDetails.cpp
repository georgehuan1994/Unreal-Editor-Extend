#include "DirectionalLightCustomDetails.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"

void FDirectionalLightCustomDetails::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	// 隐藏默认分类
	DetailLayout.HideCategory("Light");
	DetailLayout.HideCategory("Rendering");

	DetailLayout.GetObjectsBeingCustomized(SelectedObjects);

	// 创建强度分类
	IDetailCategoryBuilder& IntensityCategory = DetailLayout.EditCategory(
		"Intensity",
		FText::FromString("Sun Intensity"),
		ECategoryPriority::Important);
	
	IntensityCategory.SetSortOrder(0);
	IntensityCategory.AddCustomRow(FText::FromString("Intensity"))
	                 .NameContent()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Sun Intensity"))
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
		.ValueContent()
		.VAlign(VAlign_Center)
		.MaxDesiredWidth(125.0f)
		[
			SNew(SBox)
			.WidthOverride(125.0f)
			[
				SNew(SSpinBox<float>)
				.MinValue(0.f)
				.MaxValue(10.f)
				.Delta(0.1f)
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
				.Value(this, &FDirectionalLightCustomDetails::GetCurrentIntensity)
				.OnValueChanged(this, &FDirectionalLightCustomDetails::OnIntensityValueChanged)
			]
		];

	// 创建方向分类
	IDetailCategoryBuilder& DirectionCategory = DetailLayout.EditCategory(
		"Direction",
		FText::FromString("Light Direction"),
		ECategoryPriority::Important);
	
	DirectionCategory.SetSortOrder(1);
	DirectionCategory.AddCustomRow(FText::FromString("Pitch"))
	                 .NameContent()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Pitch (Up/Down)"))
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
		.ValueContent()
		.VAlign(VAlign_Center)
		.MaxDesiredWidth(125.0f)
		[
			SNew(SBox)
			.WidthOverride(125.0f)
			[
				SNew(SSpinBox<float>)
				.MinValue(-90.f)
				.MaxValue(90.f)
				.Delta(1.0f)
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
				.Value(this, &FDirectionalLightCustomDetails::GetCurrentPitch)
				.OnValueChanged(this, &FDirectionalLightCustomDetails::OnPitchValueChanged)
			]
		];
}

float FDirectionalLightCustomDetails::GetCurrentIntensity() const
{
	if (SelectedObjects.Num() > 0)
	{
		if (const ADirectionalLight* Light = Cast<ADirectionalLight>(SelectedObjects[0].Get()))
		{
			return Light->GetLightComponent()->Intensity;
		}
	}
	return 0.f;
}

void FDirectionalLightCustomDetails::OnIntensityValueChanged(const float NewValue) const
{
	for (TWeakObjectPtr Object : SelectedObjects)
	{
		if (const ADirectionalLight* Light = Cast<ADirectionalLight>(Object.Get()))
		{
			Light->GetLightComponent()->SetIntensity(NewValue);
		}
	}
}

float FDirectionalLightCustomDetails::GetCurrentPitch() const
{
	if (SelectedObjects.Num() > 0)
	{
		if (const ADirectionalLight* Light = Cast<ADirectionalLight>(SelectedObjects[0].Get()))
		{
			return Light->GetActorRotation().Pitch;
		}
	}
	return 0.f;
}

void FDirectionalLightCustomDetails::OnPitchValueChanged(const float NewValue) const
{
	for (TWeakObjectPtr Object : SelectedObjects)
	{
		if (ADirectionalLight* Light = Cast<ADirectionalLight>(Object.Get()))
		{
			FRotator CurrentRotation = Light->GetActorRotation();
			CurrentRotation.Pitch = FMath::Clamp(NewValue, -90.f, 90.f);
			Light->SetActorRotation(CurrentRotation);
		}
	}
}

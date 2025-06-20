#include "DirectionalLightCustomDetails.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Widgets/Input/SSpinBox.h"

void FDirectionalLightCustomDetails::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	DetailLayout.HideCategory("Light");
	DetailLayout.HideCategory("Rendering");

	DetailLayout.GetObjectsBeingCustomized(SelectedObjects);

	IDetailCategoryBuilder& CustomCategory = DetailLayout.EditCategory("Intensity", FText::FromString("Sun Intensity"),
	                                                                   ECategoryPriority::Important);
	CustomCategory.SetSortOrder(0);
	CustomCategory.AddCustomRow(FText::FromString("Intensity"))
	              .ValueContent()
	              .VAlign(VAlign_Center)
	              .HAlign(HAlign_Fill)
	[
		SNew(SSpinBox<float>)
		.MinValue(0.f)
		.MaxValue(10.f)
		.OnValueChanged(this, &FDirectionalLightCustomDetails::OnValueChanged)
	];
}

void FDirectionalLightCustomDetails::OnValueChanged(const float NewValue) const
{
	for (TWeakObjectPtr Object : SelectedObjects)
	{
		if (const ADirectionalLight* Light = Cast<ADirectionalLight>(Object.Get()))
		{
			Light->GetLightComponent()->SetIntensity(NewValue);
		}
	}
}

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class IPropertyHandle;

class FDirectionalLightCustomDetails final : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance() { return MakeShareable(new FDirectionalLightCustomDetails); }

protected:
	TArray<TWeakObjectPtr<UObject>> SelectedObjects;

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

	float GetCurrentIntensity() const;
	float GetCurrentPitch() const;

	void OnIntensityValueChanged(float NewValue) const;
	void OnPitchValueChanged(float NewValue) const;
	
};

#pragma once

#include "AssetDefinitionDefault.h"
#include "BuildingStylePreset.h"
#include "Factories/Factory.h"
#include "UObject/NameTypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectGlobals.h"
#include "BuildingStyleFactory.generated.h"

UCLASS(MinimalAPI, hidecategories=Object)
class UBuildingStyleFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class UAssetDefinition_BuildingStylePreset : public UAssetDefinitionDefault
{
	GENERATED_BODY()

public:
	
	virtual FText GetAssetDisplayName() const override { return FText::FromString("BuildingStylePreset"); }
	virtual FLinearColor GetAssetColor() const override { return FLinearColor(FColor(148, 65, 71)); }
	virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UBuildingStylePreset::StaticClass(); }

	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override
	{
		static const FAssetCategoryPath Categories[] = {FText::FromString("Unreal Fest")};
		return Categories;
	}

	virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
};

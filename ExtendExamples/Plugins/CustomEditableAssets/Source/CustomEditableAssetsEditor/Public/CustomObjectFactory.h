// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"
#include "CustomEditableAssetsEditor.h"
#include "CustomObject.h"
#include "Factories/Factory.h"
#include "CustomObjectFactory.generated.h"

UCLASS(MinimalAPI, hidecategories=Object)
class UCustomObjectFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
		UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class UAssetDefinition_CustomObject : public UAssetDefinitionDefault
{
	GENERATED_BODY()

public:
	
	virtual FText GetAssetDisplayName() const override { return FText::FromString("CustomObject"); }
	virtual FLinearColor GetAssetColor() const override { return FLinearColor(FColor(48, 165, 171)); }
	virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UCustomObject::StaticClass(); }

	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override
	{
		static const FAssetCategoryPath Categories[] = {FText::FromString("Custom Objects")};
		return Categories;
	}

	virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override
	{
		return FCustomEditableAssetsEditorModule::CustomAssetsEditorSlateStyle->GetBrush(FName("CustomAsset.Thumbnail"));
	}

	virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "CustomNotificationsBPLibrary.generated.h"

UCLASS()
class CUSTOMNOTIFICATIONS_API UCustomNotificationsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Custom Notifications")
	static void ShowNotification(const FString& Title, const FString& Message, float Duration = 5.0f)
	{
		FNotificationInfo Info(FText::FromString(Message));
		Info.Image = FCoreStyle::Get().GetBrush("Icons.SuccessWithColor");
		Info.ExpireDuration = Duration;
		Info.FadeInDuration = 1.f;
		Info.FadeOutDuration = 1.f;
		Info.bUseSuccessFailIcons = true;
		Info.bUseLargeFont = true;

		FSlateNotificationManager::Get().AddNotification(Info)->SetText(FText::FromString(Title));
	}

	UFUNCTION(BlueprintCallable, Category = "Custom Notifications")
	static void ShowNotificationWithLink(const FString& Title, const FString& Message, const FString& LinkText,
	                              const FString& LinkUrl, float Duration = 5.0f)
	{
		FNotificationInfo Info(FText::FromString(Message));
		Info.Image = FCoreStyle::Get().GetBrush("Icons.SuccessWithColor");
		Info.bUseLargeFont = true;
		Info.ExpireDuration = Duration;
		Info.FadeInDuration = 1.f;
		Info.FadeOutDuration = 1.f;
		Info.bUseSuccessFailIcons = true;

		Info.HyperlinkText = FText::FromString(LinkText);
		Info.Hyperlink = FSimpleDelegate::CreateLambda([LinkUrl]()
		{
			FPlatformProcess::LaunchURL(*LinkUrl, nullptr, nullptr);
		});

		FSlateNotificationManager::Get().AddNotification(Info)->SetText(FText::FromString(Title));
	}
};

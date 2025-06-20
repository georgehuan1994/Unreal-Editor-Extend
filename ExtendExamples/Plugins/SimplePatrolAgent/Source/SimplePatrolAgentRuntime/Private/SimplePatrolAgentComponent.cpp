// Fill out your copyright notice in the Description page of Project Settings.

#include "SimplePatrolAgentComponent.h"

#include "Misc/DataValidation.h"

USimplePatrolAgentComponent::USimplePatrolAgentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USimplePatrolAgentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USimplePatrolAgentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PatrolPoints.Num() > 0)
	{
		const AActor* CurrentPatrolPoint = PatrolPoints[CurrentPatrolPointIndex];
		if (const float Distance = GetOwner()->GetDistanceTo(CurrentPatrolPoint); Distance > DistanceThreshold)
		{
			// 匀速移动
			const FVector Direction = (CurrentPatrolPoint->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();
			GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + Direction * PatrolSpeed * DeltaTime);

			// 设置朝向
			FRotator NewRotation = FMath::RInterpTo(GetOwner()->GetActorRotation(), Direction.Rotation(), DeltaTime, 2.0f);
			NewRotation.Pitch = 0.0f;
			GetOwner()->SetActorRotation(NewRotation);
		}
		else
		{
			CurrentPatrolPointIndex = (CurrentPatrolPointIndex + 1) % PatrolPoints.Num();
		}
	}
}

#if WITH_EDITOR
EDataValidationResult USimplePatrolAgentComponent::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult ValidationResult = Super::IsDataValid(Context);

	for (int i = 0; i < PatrolPoints.Num(); ++i)
	{
		if (!PatrolPoints[i])
		{
			Context.AddError(FText::Format(FText::FromString("Patrol Point number in index {0} is not valid"), FText::AsNumber(i)));
			ValidationResult = EDataValidationResult::Invalid;
		}
	}

	return ValidationResult;
}
#endif
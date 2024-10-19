
#include "Characters/StatsComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UStatsComponent::ReduceHealth(float Amount)
{
	if (Stats[EStat::Health] <= 0) { return; }

	Stats[EStat::Health] -= Amount;
	Stats[EStat::Health] = UKismetMathLibrary::FClamp(
		Stats[EStat::Health],
		0,
		Stats[EStat::MaxHealth]
	);
	
	OnHealthPercentUpdateDelegate.Broadcast(GetStatPercentage(EStat::Health, EStat::MaxHealth));
	if (Stats[EStat::Health] == 0)
	{
		OnZeroHealthDelegate.Broadcast();
	}

}

void UStatsComponent::ReduceStamina(float Amount)
{
	Stats[EStat::Stamina] -= Amount;

	Stats[EStat::Stamina] = UKismetMathLibrary::FClamp(
		Stats[EStat::Stamina],
		0,
		Stats[EStat::MaxStamina]
	);
	bCanRegen = false;

	FLatentActionInfo FunctionInfo{
		0,
		100,
		TEXT("EnableRegen"),
		this
	};

	UKismetSystemLibrary::RetriggerableDelay(
		GetWorld(),
		StaminaDelayDuration,
		FunctionInfo
	);

	OnStaminaPercentUpdateDelegate.Broadcast(GetStatPercentage(EStat::Stamina, EStat::MaxStamina));
	
}

void UStatsComponent::RegenStamina()
{
	if (!bCanRegen) { return; }

	Stats[EStat::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[EStat::Stamina],
		Stats[EStat::MaxStamina],
		GetWorld()->DeltaTimeSeconds,
		StaminaRegenRate
	);

	OnStaminaPercentUpdateDelegate.Broadcast(GetStatPercentage(EStat::Stamina, EStat::MaxStamina));

}

void UStatsComponent::EnableRegen()
{
	bCanRegen = true;
}

float UStatsComponent::GetStatPercentage(EStat Current, EStat Max)
{
	return Stats[Current] / Stats[Max];
}


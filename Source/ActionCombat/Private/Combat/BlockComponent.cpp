
#include "Combat/BlockComponent.h"

UBlockComponent::UBlockComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBlockComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBlockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


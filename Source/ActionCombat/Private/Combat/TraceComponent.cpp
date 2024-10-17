
#include "Combat/TraceComponent.h"

#include "Engine/DamageEvents.h"
#include "Interface/Fighter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UTraceComponent::UTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	SkeletalCom=GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}

void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsAttacking){return;}
	
	FVector StartSocketLocation=SkeletalCom->GetSocketLocation(Start);
	FVector EndSocketLocation=SkeletalCom->GetSocketLocation(End);
	FQuat ShapeRotation=SkeletalCom->GetSocketQuaternion(Rotation);

	TArray<FHitResult> OutResults;
	
	double WeaponDistance=FVector::Distance(StartSocketLocation,EndSocketLocation);
	FVector BoxHalfExtent=FVector(BoxCollisionLength,BoxCollisionLength,WeaponDistance);
	BoxHalfExtent/=2;
	FCollisionShape Box=FCollisionShape::MakeBox(BoxHalfExtent);
	FCollisionQueryParams IgnoreParams(
	FName(TEXT("Ignore Params")),
		false,
		GetOwner()
		);
	
	
	bool bHasFoundTargets{ GetWorld()->SweepMultiByChannel(
		OutResults,
		StartSocketLocation,
		EndSocketLocation,
		ShapeRotation,
		ECollisionChannel::ECC_GameTraceChannel1,
		Box,
		IgnoreParams
	) };

	if (bDebugMode)
	{
		FVector CenterPoint=UKismetMathLibrary::VLerp(StartSocketLocation,EndSocketLocation,0.5f);
		UKismetSystemLibrary::DrawDebugBox(
			GetWorld(),
			CenterPoint,
			Box.GetExtent(),
			bHasFoundTargets?FLinearColor::Green:FLinearColor::Red,
			ShapeRotation.Rotator(),
			1.0f,
			2.0f
		);
	}
	if (OutResults.Num()==0){return;}
	float CharacterDamage=0.f;
	IFighter* FighterRef=Cast<IFighter>(GetOwner());
	if (FighterRef)
	{
		CharacterDamage=FighterRef->GetDamage();
	}
	FDamageEvent TargetAttackedEvent;
	for(const FHitResult& Hit : OutResults)
	{
		AActor*TargetActor=Hit.GetActor();
		if (TargetsToIgnore.Contains(TargetActor)){continue;}
		TargetActor->TakeDamage(
			CharacterDamage,
			TargetAttackedEvent,
			GetOwner()->GetInstigatorController(),
			GetOwner()
			);
		TargetsToIgnore.AddUnique(TargetActor);
	}
}

void UTraceComponent::HandleResetAttack()
{
	TargetsToIgnore.Empty();
}


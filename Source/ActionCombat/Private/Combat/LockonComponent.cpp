
#include "Combat/LockonComponent.h"

#include "ShaderPrintParameters.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ULockonComponent::ULockonComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();

	OwenRef=GetOwner<ACharacter>();
	Controller=GetWorld()->GetFirstPlayerController();
	MovementComp=OwenRef->GetCharacterMovement();
	SpringArmComp=OwenRef->FindComponentByClass<USpringArmComponent>();
	
}

void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!IsValid(CurrentTargetActor))return;
	FVector CurrentLoaction={OwenRef->GetActorLocation()};
	FVector TargetLocation={CurrentTargetActor->GetActorLocation()};
	double TargetDistance=FVector::Distance(CurrentLoaction,TargetLocation);
	if (TargetDistance>BreakDistance)
	{
		EndLockon();
		return;
	}
	TargetLocation.Z-=125.f;
	FRotator NewRotation{UKismetMathLibrary::FindLookAtRotation(
		CurrentLoaction,
		TargetLocation
		)};

	Controller->SetControlRotation(NewRotation);
}
void ULockonComponent::StartLockon(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation{ OwenRef->GetActorLocation() };
	FCollisionShape Sphere{ FCollisionShape::MakeSphere(Radius) };
	FCollisionQueryParams IgnorePrams{ 
		FName(TEXT("Ignore Query Params")),
		false,
		OwenRef
	};

	bool bHasFoundTarget{ GetWorld()->SweepSingleByChannel(
		OutResult,
		CurrentLocation,
		CurrentLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		Sphere,
		IgnorePrams
	) };

	if (!bHasFoundTarget) { return; }
	if (!OutResult.GetActor()->Implements<UEnemy>()){ return;}
	{
		CurrentTargetActor=OutResult.GetActor();
		Controller->SetIgnoreLookInput(true);
		MovementComp->bOrientRotationToMovement=false;
		MovementComp->bUseControllerDesiredRotation=true;

		SpringArmComp->TargetOffset=FVector(0,0,100.f);
		IEnemy::Execute_OnSelect(CurrentTargetActor);
		OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
	}
}

void ULockonComponent::ToggleLockon(float Radius)
{
	if (IsValid((CurrentTargetActor)))
	{
		EndLockon();
	}
	else
	{
		StartLockon();
	}
}

void ULockonComponent::EndLockon()
{
	IEnemy::Execute_OnDeselect(CurrentTargetActor);
	CurrentTargetActor=nullptr;
	MovementComp->bOrientRotationToMovement=true;
	MovementComp->bUseControllerDesiredRotation=false;

	SpringArmComp->TargetOffset=FVector::ZeroVector;
	Controller->ResetIgnoreLookInput();
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}


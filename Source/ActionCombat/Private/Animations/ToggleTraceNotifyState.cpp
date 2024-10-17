// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/ToggleTraceNotifyState.h"

#include "ShaderPrintParameters.h"
#include "Combat/TraceComponent.h"

void UToggleTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	UTraceComponent* TraceComp=
		MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>();
	if (!IsValid(TraceComp)){return;}
	
}

void UToggleTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	 const FAnimNotifyEventReference& EventReference)
{
	UTraceComponent* TraceComp=
		MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>();
	if (!IsValid(TraceComp)){return;}
	TraceComp->bIsAttacking = false;
}

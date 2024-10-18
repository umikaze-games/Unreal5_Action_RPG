// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_PlayerDistance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UBTS_PlayerDistance : public UBTService
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds
	) override;

};

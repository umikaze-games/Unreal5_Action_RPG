
#include "Characters/AI/BTT_RangeAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EEnemyState.h"
#include "Characters/EStat.h"
#include "GameFramework/Character.h"
#include "Interfaces/Fighter.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* CharacterRef=OwnerComp.GetAIOwner()->GetPawn<ACharacter>();
	if (!IsValid(CharacterRef)) { return EBTNodeResult::Failed; }

	float Distance=OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"));

	IFighter* FighterRef{ Cast<IFighter>(CharacterRef) };

	if (Distance < FighterRef->GetMeleeRange())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Melee);

		AbortTask(OwnerComp, NodeMemory);

		return EBTNodeResult::Aborted;
	}

	CharacterRef->PlayAnimMontage(AnimMontage);

	double RandomValue{ UKismetMathLibrary::RandomFloat() };

	if (RandomValue > Threshold)
	{
		Threshold = 0.9;
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"),EEnemyState::Charge);

	}
	else
	{
		Threshold -= 0.1;
	}

	
	return EBTNodeResult::Succeeded;
}

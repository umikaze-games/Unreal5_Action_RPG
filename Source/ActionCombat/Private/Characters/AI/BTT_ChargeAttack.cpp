
#include "Characters/AI/BTT_ChargeAttack.h"
#include "AIController.h"
#include "Animations/BossAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"

void UBTT_ChargeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool bIsReadyToCharge=OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsReadyToCharge"));

	if (bIsReadyToCharge) 
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsReadyToCharge"), false);

		ChargeAtPlayer();
	}
}

UBTT_ChargeAttack::UBTT_ChargeAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ControllerRef = OwnerComp.GetAIOwner();
	CharacterRef = ControllerRef->GetCharacter();
	BossAnim = Cast<UBossAnimInstance>(CharacterRef->GetMesh()->GetAnimInstance());

	BossAnim->bIsCharging = true;

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsReadyToCharge"), false);

	return EBTNodeResult::InProgress;
}

void UBTT_ChargeAttack::ChargeAtPlayer()
{
	APawn* PlayerRef=GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector PlayerLocation=PlayerRef->GetActorLocation() ;

	FAIMoveRequest MoveRequest{ PlayerLocation };
	MoveRequest.SetUsePathfinding(true);
	MoveRequest.SetAcceptanceRadius(AcceptableRadius);

	ControllerRef->MoveTo(MoveRequest);
	ControllerRef->SetFocus(PlayerRef);
}
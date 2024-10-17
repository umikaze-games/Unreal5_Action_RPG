
#include "Characters/AI/BossAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ABossAIController::ABossAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/Characters/Characters/Boss/AI/BT_Boss"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
		UE_LOG(LogTemp, Log, TEXT("Successfully loaded BehaviorTree: %s"), *BehaviorTree->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find BehaviorTree asset in ABossAIController. Path: /Game/Characters/Characters/Boss/AI/BT_Boss"));
	}
}

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeBlackboardAndBehaviorTree();
}

void ABossAIController::InitializeBlackboardAndBehaviorTree()
{
	if (BehaviorTree && BehaviorTree->BlackboardAsset)
	{
		UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);
		RunBehaviorTree(BehaviorTree);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BehaviorTree or BlackboardAsset is missing in %s"), *GetName());
	}
}

void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABossAIController::SetTargetLocation(const FVector& Location)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsVector(TEXT("TargetLocation"), Location);
	}
}
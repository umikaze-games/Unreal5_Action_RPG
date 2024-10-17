
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

UCLASS()
class ACTIONCOMBAT_API ABossAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABossAIController();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	void SetTargetLocation(const FVector& Location);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UBlackboardComponent* BlackboardComponent;

private:
	void InitializeBlackboardAndBehaviorTree();
};
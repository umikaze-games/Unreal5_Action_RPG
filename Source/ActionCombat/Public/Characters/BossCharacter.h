
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Enemy.h"
#include "Characters/EEnemyState.h"
#include "BossCharacter.generated.h"

UCLASS()
class ACTIONCOMBAT_API ABossCharacter : public ACharacter, public IEnemy
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	class UBlackboardComponent* BlackboardComp;

public:
	ABossCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStatsComponent* StatsComp;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect);
};

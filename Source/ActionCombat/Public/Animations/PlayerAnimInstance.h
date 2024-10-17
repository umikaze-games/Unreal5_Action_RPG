
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class ACTIONCOMBAT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentSpeed{ 0.0f };

	UFUNCTION(BlueprintCallable)
	void UpdateSpeed();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInCombat{ false };
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentDirection{0.f};

public:

	UFUNCTION(BlueprintCallable)
	void HandleUpdatedTarget(AActor*NewTargetActorRef);
	
	UFUNCTION(BlueprintCallable)
	void UpdateDirection();
};

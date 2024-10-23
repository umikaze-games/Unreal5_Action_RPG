
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnSprintSignature,
	UPlayerActionsComponent, OnSprintDelegate,
	float, Cost
);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnRollSignature,
	UPlayerActionsComponent, OnRollDelegate,
	float, Cost
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* CharacterRef;

	class IMainPlayer* IPlayerRef;

	class UCharacterMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere)
	float SprintCost{ 0.1f };

	UPROPERTY(EditAnywhere)
	float SprintSpeed{ 1000.0f };

	UPROPERTY(EditAnywhere)
	float WalkSpeed{ 500.0f };
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* RollAnimMontage;

	UPROPERTY(EditAnywhere)
	float RollCost{ 5.0f };

public:	
	// Sets default values for this component's properties
	UPlayerActionsComponent();

	UPROPERTY(BlueprintAssignable)
	FOnSprintSignature OnSprintDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnRollSignature OnRollDelegate;

	bool bIsRollActive{ false };
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Sprint();

	UFUNCTION(BlueprintCallable)
	void Walk();
	
	UFUNCTION(BlueprintCallable)
	void Roll();

	UFUNCTION()
	void FinishRollAnim();

};


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LockonComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockonComponent,OnUpdatedTargetDelegate,
	AActor*,NewTargetActorRef
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API ULockonComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* OwenRef;
	APlayerController* Controller;
	class UCharacterMovementComponent* MovementComp;
	AActor* CurrentTargetActor;
	class USpringArmComponent* SpringArmComp;
	
public:	
	ULockonComponent();

	UPROPERTY(BlueprintAssignable)
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;
	
	UFUNCTION(BlueprintCallable)
	void StartLockon(float Radius=750.f);
	UFUNCTION(BlueprintCallable)
	void ToggleLockon(float Radius=750.f);
	void EndLockon();

	UPROPERTY(EditAnywhere)
	double BreakDistance=1000;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlockComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnBlockSignature,
	UBlockComponent, OnBlockDelegate,
	float, Cost
);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UBlockComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float StaminaCost{ 10.0f };

	UPROPERTY(EditAnywhere)
	UAnimMontage* BlockAnimMontage;

public:	
	// Sets default values for this component's properties
	UBlockComponent();

	UPROPERTY(BlueprintAssignable)
	FOnBlockSignature OnBlockDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool Check(AActor* Opponent);
};

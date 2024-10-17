
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/EStat.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	double StaminaRegenRate{ 10.0 };

	UPROPERTY(VisibleAnywhere)
	bool bCanRegen{ true };

	UPROPERTY(EditAnywhere)
	float StaminaDelayDuration{ 2.0f };

public:	
	UStatsComponent();

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStat>, float> Stats;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float Amount);
	
	UFUNCTION(BlueprintCallable)
	void ReduceStamina (float Amount);

	UFUNCTION(BlueprintCallable)
	void RegenStamina();

	UFUNCTION()
	void EnableRegen();

};

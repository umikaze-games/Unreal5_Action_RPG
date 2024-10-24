
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat/FTraceSockets.h"
#include "TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

	USkeletalMeshComponent* SkeletalComp;

	UPROPERTY(EditAnywhere)
	TArray<FTraceSockets> Sockets;

	UPROPERTY(EditAnywhere)
	double BoxCollisionLength{ 30.0 };

	UPROPERTY(EditAnywhere)
	bool bDebugMode{ false };

	TArray<AActor*> TargetsToIgnore;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitParticleTemplate;

public:	
	// Sets default values for this component's properties
	UTraceComponent();

	UPROPERTY(VisibleAnywhere)
	bool bIsAttacking{ false };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();
};


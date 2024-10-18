
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
	double BoxCollisionLength=30.0;

	UPROPERTY(EditAnywhere)
	bool bDebugMode=false;

	TArray<AActor*> TargetsToIgnore;
public:	
	UTraceComponent();
	UPROPERTY(visibleAnywhere)
	bool bIsAttacking=false;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();	
};

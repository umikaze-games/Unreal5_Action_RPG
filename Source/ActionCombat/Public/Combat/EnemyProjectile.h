
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class ACTIONCOMBAT_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void HandleBeginOverlap(AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitTemplate;

	UFUNCTION()
	void DestroyProjectile();

	UPROPERTY(EditAnywhere)
	float Damage{ 10.0f };


};

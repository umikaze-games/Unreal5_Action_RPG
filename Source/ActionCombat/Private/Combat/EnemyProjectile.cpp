
#include "Combat/EnemyProjectile.h"

#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyProjectile::HandleBeginOverlap(AActor* OtherActor)
{
	APawn* PawnRef{ Cast<APawn>(OtherActor) };

	if (!PawnRef->IsPlayerControlled()) { return; }

	FindComponentByClass<UParticleSystemComponent>()->SetTemplate(HitTemplate);

	FindComponentByClass<UProjectileMovementComponent>()->StopMovementImmediately();
	FTimerHandle DeathTimerHandle{};

	GetWorldTimerManager().SetTimer(
		DeathTimerHandle,
		this,
		&AEnemyProjectile::DestroyProjectile,
		0.5f
	);
	
	FindComponentByClass<USphereComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FDamageEvent ProjectileAttackEvent{};
	PawnRef->TakeDamage(
		Damage,
		ProjectileAttackEvent,
		PawnRef->GetController(),
		this
	);
}
void AEnemyProjectile::DestroyProjectile()
{
	Destroy();
}


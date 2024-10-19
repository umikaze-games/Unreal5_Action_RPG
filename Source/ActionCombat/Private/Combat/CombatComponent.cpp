
#include "Combat/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "Kismet/KismetMathLibrary.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterRef=GetOwner<ACharacter>();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UCombatComponent::ComboAttack()
{
	if (CharacterRef->Implements<UMainPlayer>()) 
	{
		IMainPlayer* IPlayerRef{ Cast<IMainPlayer>(CharacterRef) };
		if (IPlayerRef && !IPlayerRef->HasEnoughStamina(StaminaCost)) 
		{

			return;
		}
	}

	if (!bCanAttack) { return; }

	bCanAttack = false;

	CharacterRef->PlayAnimMontage(AttackAnimations[ComboCounter]);

	ComboCounter++;

	int MaxCombo{ AttackAnimations.Num() };

	ComboCounter = UKismetMathLibrary::Wrap(
		ComboCounter,
		-1,
		(MaxCombo - 1)
	);
	OnAttackPerformedDelegate.Broadcast(StaminaCost);
	
}

void UCombatComponent::HandleResetAttack()
{
	bCanAttack = true;
}

void UCombatComponent::RandomAttack()
{
	int RandomIndex{ 
		FMath::RandRange(0, AttackAnimations.Num() - 1)
	};

	AnimDuration = CharacterRef->PlayAnimMontage(AttackAnimations[RandomIndex]);

}




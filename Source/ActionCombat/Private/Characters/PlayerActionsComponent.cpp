
#include "Characters/PlayerActionsComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/MainPlayer.h"

UPlayerActionsComponent::UPlayerActionsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UPlayerActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetOwner<ACharacter>();
	MovementComp = CharacterRef->GetCharacterMovement();

	if (!CharacterRef->Implements<UMainPlayer>()) { return; }

	IPlayerRef = Cast<IMainPlayer>(CharacterRef);
}

void UPlayerActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UPlayerActionsComponent::Sprint()
{
	if (!IPlayerRef->HasEnoughStamina(SprintCost)) 
	{ 
		Walk();
		return; 
	}

	if (MovementComp->Velocity.Equals(FVector::ZeroVector, 1)) { return; }

	MovementComp->MaxWalkSpeed = SprintSpeed;

	OnSprintDelegate.Broadcast(SprintCost);
}

void UPlayerActionsComponent::Walk()
{
	MovementComp->MaxWalkSpeed = WalkSpeed;
}




#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EStat
{
	None UMETA(DisplayName = "None Selected"),
	Health UMETA(DisplayName = "Health"),
	MaxHealth UMETA(DisplayName = "Max Health"),
	Strength UMETA(DisplayName = "Strength"),
	Stamina UMETA(DisplayName = "Stamina"),
	MaxStamina UMETA(DisplayName = "Max Stamina"),
	MeleeRange UMETA(DisplayName = "Melee Range")
};

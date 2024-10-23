
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EEnemyState
{
	Idle UMETA(DisplayName="Idle"),
		Range UMETA(DisplayName="Range"),
		Charge UMETA(DisplayName="Charge"),
		Melee UMETA(DisplayName="Melee"),
		GameOver UMETA(DisplayName="Game Over")

};
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enemy.generated.h"

UINTERFACE(MinimalAPI)
class UEnemy : public UInterface
{
	GENERATED_BODY()
};


class ACTIONCOMBAT_API IEnemy
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnSelect();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnDeselect();
	
};

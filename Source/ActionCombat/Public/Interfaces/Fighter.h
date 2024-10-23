
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fighter.generated.h"

UINTERFACE(MinimalAPI)
class UFighter : public UInterface
{
	GENERATED_BODY()
};

class ACTIONCOMBAT_API IFighter
{
	GENERATED_BODY()

public:
	virtual  float GetDamage() { return 0; }

	virtual void Attack() {}
	virtual float GetAnimDuration() { return 0.0f; }
	virtual float GetMeleeRange() { return 0.0f; }

	virtual bool CanTakeDamage(AActor* Opponent) { return true; }
};

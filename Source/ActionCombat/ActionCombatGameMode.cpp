
#include "ActionCombatGameMode.h"
#include "ActionCombatCharacter.h"
#include "UObject/ConstructorHelpers.h"

AActionCombatGameMode::AActionCombatGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

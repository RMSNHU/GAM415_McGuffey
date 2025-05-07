// Copyright Epic Games, Inc. All Rights Reserved.

#include "FP_GAM415_McGuffeyGameMode.h"
#include "FP_GAM415_McGuffeyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFP_GAM415_McGuffeyGameMode::AFP_GAM415_McGuffeyGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "JourneyOfTwoGameMode.h"
#include "JourneyOfTwoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJourneyOfTwoGameMode::AJourneyOfTwoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

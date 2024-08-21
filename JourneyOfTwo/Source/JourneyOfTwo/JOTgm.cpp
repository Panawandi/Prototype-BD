// Fill out your copyright notice in the Description page of Project Settings.


#include "JOTgm.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void AJOTgm::PostLogin(APlayerController* NewPlayer) {

	Super::PostLogin(NewPlayer);

	int32 NumPlayers = GetNumPlayers();

	if (NumPlayers < 2) {
		// Create a second player controller for split screen
		UGameplayStatics::CreatePlayer(GetWorld(), NumPlayers, true);
	}

}
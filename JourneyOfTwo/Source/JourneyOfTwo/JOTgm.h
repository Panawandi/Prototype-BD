// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JOTgm.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEYOFTWO_API AJOTgm : public AGameModeBase
{
	GENERATED_BODY()
	

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;


};

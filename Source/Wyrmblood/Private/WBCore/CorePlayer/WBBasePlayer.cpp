// © 2025 Hephaestus Studios. All rights reserved.

#include "WBCore/CorePlayer/WBBasePlayer.h"

AWBBasePlayer::AWBBasePlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWBBasePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AWBBasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWBBasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

AWBBasePlayer* AWBBasePlayer::GetPlayerCharacterRef()
{
	return this;
}



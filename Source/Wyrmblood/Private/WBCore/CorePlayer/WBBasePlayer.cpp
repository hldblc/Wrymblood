// © 2025 Hephaestus Studios. All rights reserved.


#include "WBCore/CorePlayer/WBBasePlayer.h"


// Sets default values
AWBBasePlayer::AWBBasePlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWBBasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWBBasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWBBasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


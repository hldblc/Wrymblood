// © 2025 Hephaestus Studios. All rights reserved.

#include "WBCore/CorePlayer/WBBasePlayer.h"
#include "WBCore/CoreGame/WBPlayerController.h"
#include "Components/InputComponent.h"

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

void AWBBasePlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate CharacterInputState to all clients
	DOREPLIFETIME(AWBBasePlayer, CharacterInputState);
}

void AWBBasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

AWBBasePlayer* AWBBasePlayer::GetPlayerCharacterRef_Implementation() const
{
	return const_cast<AWBBasePlayer*>(this);
}

AWBPlayerController* AWBBasePlayer::GetPlayerControllerRef_Implementation() const
{
	return PlayerController;
}

void AWBBasePlayer::GetPropertiesForCamera_Implementation(FCharacterCamera& OutCameraProperties) const
{
	// Select Node 
	if (CanAim())
	{
		OutCameraProperties.CameraMode = E_CameraMode::Aim;
	}
	else
	{
		OutCameraProperties.CameraMode = E_CameraMode::StrafeCam;
	}

	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement && CharMovement->IsCrouching())
	{
		OutCameraProperties.Stance = E_MovementStance::Crouch;
	}
	else
	{
		OutCameraProperties.Stance = E_MovementStance::Stand;
	}
    
	
}


bool AWBBasePlayer::CanAim() const
{
	const bool bIsAiming       = CharacterInputState.bWantsToAim;
	const bool bNotSprinting   = !CharacterInputState.bWantsToSprint;
	const bool bIsCrouching    = GetCharacterMovement()
								   ? GetCharacterMovement()->IsCrouching()
								   : false;

	return bIsAiming && ( bNotSprinting || bIsCrouching );
}



void AWBBasePlayer::OnRep_CharacterInputState()
{
	
}





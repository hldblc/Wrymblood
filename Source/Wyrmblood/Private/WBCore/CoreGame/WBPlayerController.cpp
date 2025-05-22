// © 2025 Hephaestus Studios. All rights reserved.

#include "WBCore/CoreGame/WBPlayerController.h"
#include "WBCore/CorePlayer/WBBasePlayer.h"
#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AWBPlayerController::AWBPlayerController()
{
	// PlayerController is already replicated by default
	bReplicates = true;
	
	// Initialize variables
	PlayerReference = nullptr;
	IsControllerReady = false;
	IMC_Default = nullptr;
	IMC_HolBar = nullptr;
}

void AWBPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Client_OnPossess();
}

void AWBPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Replicate IsControllerReady to all clients
	DOREPLIFETIME(AWBPlayerController, IsControllerReady);
}

void AWBPlayerController::OnRep_IsControllerReady()
{
	// This function is called on clients when IsControllerReady changes
	UE_LOG(LogTemp, Log, TEXT("IsControllerReady changed to: %s"), IsControllerReady ? TEXT("true") : TEXT("false"));
	
	// Broadcast the event dispatcher when controller becomes ready
	if (IsControllerReady)
	{
		OnPlayerControllerReady.Broadcast(this);
	}
}

void AWBPlayerController::Server_SetPlayerControllerReady_Implementation()
{
	SetIsControllerReady(true);
}

void AWBPlayerController::Client_OnPossess_Implementation()
{
	// Set up default input mappings
	SetGameDefaultInputMapping(true);
	
	// Notify server that controller is ready
	Server_SetPlayerControllerReady();
}

void AWBPlayerController::SetInputMapping(bool bEnabled, UInputMappingContext* MappingContext, int32 Priority)
{
	// Validate input mapping context
	if (!MappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetInputMapping: MappingContext is null"));
		return;
	}

	// Get the Enhanced Input Local Player Subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (bEnabled)
		{
			// Add mapping context if not already present
			if (!Subsystem->HasMappingContext(MappingContext))
			{
				Subsystem->AddMappingContext(MappingContext, Priority);
				UE_LOG(LogTemp, Log, TEXT("Added Input Mapping Context: %s with Priority: %d"), 
					*MappingContext->GetName(), Priority);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Input Mapping Context already exists: %s"), *MappingContext->GetName());
			}
		}
		else
		{
			// Remove mapping context if present
			if (Subsystem->HasMappingContext(MappingContext))
			{
				Subsystem->RemoveMappingContext(MappingContext);
				UE_LOG(LogTemp, Log, TEXT("Removed Input Mapping Context: %s"), *MappingContext->GetName());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SetInputMapping: Could not get Enhanced Input Local Player Subsystem"));
	}
}

void AWBPlayerController::SetGameDefaultInputMapping(bool bEnabled)
{
	// Add default input mapping if available
	if (IMC_Default)
	{
		SetInputMapping(bEnabled, IMC_Default, 0);
	}
	
	// Add HolBar input mapping if available
	if (IMC_HolBar)
	{
		SetInputMapping(bEnabled, IMC_HolBar, 1);
	}

	// Process any additional default mappings from array
	for (int32 i = 0; i < DefaultInputMappings.Num(); i++)
	{
		if (UInputMappingContext* LoadedContext = DefaultInputMappings[i].LoadSynchronous())
		{
			SetInputMapping(bEnabled, LoadedContext, i + 2); // Start priority at 2
		}
	}
}

void AWBPlayerController::AddInputMappingContext(UInputMappingContext* MappingContext, int32 Priority)
{
	SetInputMapping(true, MappingContext, Priority);
}

void AWBPlayerController::RemoveInputMappingContext(UInputMappingContext* MappingContext)
{
	SetInputMapping(false, MappingContext, 0);
}

void AWBPlayerController::ClearAllInputMappings()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		UE_LOG(LogTemp, Log, TEXT("Cleared all input mapping contexts"));
	}
}
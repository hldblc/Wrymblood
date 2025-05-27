// © 2025 Hephaestus Studios. All rights reserved.

#include "WBCore/CoreGame/WBPlayerController.h"
#include "WBCore/CorePlayer/WBBasePlayer.h"
#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// ================================ Core C++ Functions ================================ //

AWBPlayerController::AWBPlayerController()
{
    // PlayerController is already replicated by default
    bReplicates = true;
    
    // Initialize variables
    PlayerReference = nullptr;
    IsControllerReady = false;
    IMC_Default = nullptr;
    IMC_HotBar = nullptr;
    IMC_Camera = nullptr;
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

AWBBasePlayer* AWBPlayerController::GetPlayerReference() const
{
    return PlayerReference;
}

void AWBPlayerController::SetPlayerReference(AWBBasePlayer* BasePlayerReference)
{
    PlayerReference = BasePlayerReference;
}

bool AWBPlayerController::GetIsControllerReady() const
{
    return IsControllerReady;
}

void AWBPlayerController::SetIsControllerReady(bool bIsControllerReady)
{
    IsControllerReady = bIsControllerReady;
}

void AWBPlayerController::OnRep_IsControllerReady()
{
    // Called on clients when IsControllerReady changes
    UE_LOG(LogTemp, Log, TEXT("IsControllerReady changed to: %s"), IsControllerReady ? TEXT("true") : TEXT("false"));
    
    if (IsControllerReady)
    {
        OnPlayerControllerReady.Broadcast(this);
    }
}


void AWBPlayerController::SetInputMapping(bool bEnabled, UInputMappingContext* MappingContext, int32 Priority)
{
    if (!MappingContext)
    {
        UE_LOG(LogTemp, Warning, TEXT("SetInputMapping: MappingContext is null"));
        return;
    }

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if (bEnabled)
        {
            if (!Subsystem->HasMappingContext(MappingContext))
            {
                Subsystem->AddMappingContext(MappingContext, Priority);
                UE_LOG(LogTemp, Log, TEXT("Added Input Mapping Context: %s with Priority: %d"), *MappingContext->GetName(), Priority);
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("Input Mapping Context already exists: %s"), *MappingContext->GetName());
            }
        }
        else if (Subsystem->HasMappingContext(MappingContext))
        {
            Subsystem->RemoveMappingContext(MappingContext);
            UE_LOG(LogTemp, Log, TEXT("Removed Input Mapping Context: %s"), *MappingContext->GetName());
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SetInputMapping: Could not get Enhanced Input Local Player Subsystem"));
    }
}

void AWBPlayerController::SetUIInputMappingUI(bool bEnabled)
{
    // Don't disable IMC_UI_InGame - it contains UI opening inputs
    if (IMC_Default)
        SetInputMapping(!bEnabled, IMC_Default, 0);
    if (IMC_HotBar)
        SetInputMapping(!bEnabled, IMC_HotBar, 0);
    if (IMC_Camera)
        SetInputMapping(!bEnabled, IMC_Camera, 0);
    // Keep IMC_UI_InGame always enabled
    
    if (IMC_UI_Generic)
        SetInputMapping(bEnabled, IMC_UI_Generic, 5);
}

void AWBPlayerController::SetGameDefaultInputMapping(bool bEnabled)
{
    if (IMC_Default)
    {
        SetInputMapping(bEnabled, IMC_Default, 0);
    }
    if (IMC_HotBar)
    {
        SetInputMapping(bEnabled, IMC_HotBar, 0);
    }
    if (IMC_Camera)
    {
        SetInputMapping(bEnabled, IMC_Camera, 0);
    }
    if (IMC_UI_InGame)
    {
        SetInputMapping(bEnabled, IMC_UI_InGame, 0);
    }

    for (int32 i = 0; i < DefaultInputMappings.Num(); ++i)
    {
        if (UInputMappingContext* LoadedContext = DefaultInputMappings[i].LoadSynchronous())
        {
            SetInputMapping(bEnabled, LoadedContext, i + 1);
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


//================================ Core C++ Interface Functions ================================ //
void AWBPlayerController::CloseInGameMenu_Implementation()
{
    UIManager->SetInGameMenuVisibility(false);
}

void AWBPlayerController::DisableUIMode_Implementation()
{
    SetInputMode(FInputModeGameOnly());
    
    FlushPressedKeys();
    
    SetUIInputMappingUI(false);
    
    SetShowMouseCursor(false);
}

void AWBPlayerController::EnableUIMode_Implementation(UUserWidget* FocusedWidget)
{
    FInputModeGameAndUI InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock)
             .SetHideCursorDuringCapture(false);
    
    if (FocusedWidget)
    {
        InputMode.SetWidgetToFocus(FocusedWidget->TakeWidget());
    }
    
    SetInputMode(InputMode);
    FlushPressedKeys();
    SetUIInputMappingUI(true);
    SetShowMouseCursor(true);
}

// ================================ Core C++ SERVER Functions ================================ //

void AWBPlayerController::Server_SetPlayerControllerReady_Implementation()
{
    SetIsControllerReady(true);
}

// ================================ Core C++ CLIENT Functions ================================ //

void AWBPlayerController::Client_OnPossess_Implementation()
{
    // Set up default input mappings
    SetGameDefaultInputMapping(true);

    // Add UIManager Component
    UIManager = NewObject<UWBUIManager>(this);

    if (UIManager)
    {
        UIManager->PlayerControllerRef = this;
        UIManager->PlayerCharacterRef = Cast<AWBBasePlayer>(GetPawn());
        
        // Set the blueprint classes
        UIManager->RootUIClass = LoadClass<UWBRootUI>(nullptr, TEXT("/Game/_GAME/Blueprints/UI/Common/Widgets/WBP_RooUI.WBP_RooUI_C"));
        UIManager->GameMenuWidgetClass = LoadClass<UWBGameMenu>(nullptr, TEXT("/Game/_GAME/Blueprints/UI/Common/Widgets/Menus/WBP_GameMenu.WBP_GameMenu_C"));

        UIManager->OnUIReady.AddDynamic(this, &AWBPlayerController::OnUIReadyEvent);
        UIManager->InitiliazeFullUI();
    }

    // Notify server that controller is ready
    Server_SetPlayerControllerReady();
}

//================================ Core c++ Dispatchers ================================ //
void AWBPlayerController::OnUIReadyEvent(UWBUIManager* UIManagerRef)
{
    // Handle UI ready event - call server function or other logic
    UE_LOG(LogTemp, Log, TEXT("UI is ready!"));
}

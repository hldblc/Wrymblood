// © 2025 Hephaestus Studios. All rights reserved.

#include "WBCore/CoreUI/UComponents/WBUIManager.h"

#include "Components/NamedSlot.h"
#include "WBCore/CoreGame/WBPlayerController.h"
#include "WBCore/CorePlayer/WBBasePlayer.h"


// Sets default values for this component's properties
UWBUIManager::UWBUIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWBUIManager::InitiliazeFullUI()
{
	UE_LOG(LogTemp, Warning, TEXT("InitializeFullUI called"));
    
	if (!PlayerControllerRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing PlayerController ref"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("RootUIClass: %s"), RootUIClass ? TEXT("Valid") : TEXT("NULL"));
    
	if (RootUIClass)
	{
		RootUI = CreateWidget<UWBRootUI>(PlayerControllerRef->GetWorld(), RootUIClass);

		if (RootUI)
		{
			RootUI->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("RootUI created and added to viewport"));

			FTimerHandle TimerHandle;
			PlayerControllerRef->GetWorldTimerManager().SetTimer(TimerHandle,[this](){OnUIReady.Broadcast(this);},0.2f,false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to create RootUI"));
		}
	}
}

void UWBUIManager::SetInGameMenuVisibility(bool CloseMenu)
{
	UWBGameMenu* MenuWidget = nullptr;
	GetInGameMenuWidget(MenuWidget);
    
	if (MenuWidget)
	{
		if (CloseMenu) // Opening
		{
			// Always add to slot when opening
			if (RootUI && RootUI->SlotInGameMenu)
			{
				RootUI->SlotInGameMenu->SetContent(MenuWidget);
			}
            
			MenuWidget->ActivateWidget();
			MenuWidget->SetVisibility(ESlateVisibility::Visible);
            
			if (PlayerControllerRef)
			{
				PlayerControllerRef->Execute_EnableUIMode(PlayerControllerRef, MenuWidget);
			}
		}
		else // Closing
		{
			MenuWidget->DeactivateWidget();
			MenuWidget->SetVisibility(ESlateVisibility::Hidden);
            
			if (PlayerControllerRef)
			{
				PlayerControllerRef->Execute_DisableUIMode(PlayerControllerRef);
			}
		}
	}
}

void UWBUIManager::GetInGameMenuWidget(UWBGameMenu*& ReturnValue)
{
	if (IsValid(GameMenuWidget))
	{
		ReturnValue = GameMenuWidget;
	}
	else
	{
		if (GameMenuWidgetClass && PlayerControllerRef)
		{
			GameMenuWidget = CreateWidget<UWBGameMenu>(PlayerControllerRef, GameMenuWidgetClass);
			ReturnValue = GameMenuWidget;
		}
		else
		{
			ReturnValue = nullptr;
		}
	}
}



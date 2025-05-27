// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WBControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class UWBControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for a controller-based UI Manager in the Wyrmblood game.
 * Classes implementing this interface are intended to handle UI-specific
 * functionalities such as enabling UI mode, disabling UI mode, and closing in-game menus.
 */
class WYRMBLOOD_API IWBControllerInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ControllerInterface|UIManager")
	void EnableUIMode(UUserWidget* FocusedWidget);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Controller Interface|UIManager")
	void DisableUIMode();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Controller Interface|UIManager")
	void CloseInGameMenu();
};

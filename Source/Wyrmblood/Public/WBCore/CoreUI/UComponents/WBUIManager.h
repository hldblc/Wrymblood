// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WBCore/CoreUI/WBRootUI.h"
#include "WBCore/CoreUI/UMenu/WBGameMenu.h"
#include "WBUIManager.generated.h"

class AWBPlayerController;
class AWBBasePlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIReady, UWBUIManager*, UIManager);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WYRMBLOOD_API UWBUIManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWBUIManager();

	// ================================== Core Properties ================================== //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UWBRootUI> RootUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UWBGameMenu> GameMenuWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI Manager")
	UWBRootUI* RootUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI Manager")
	AWBPlayerController* PlayerControllerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI Manager")
	AWBBasePlayer* PlayerCharacterRef;


	
	// ================================== Core Functions ================================== //
	UFUNCTION(BlueprintCallable, Category="UI Manager")
	void InitiliazeFullUI();

	UFUNCTION(BlueprintCallable, Category="UI Manager")
	void SetInGameMenuVisibility(bool CloseMenu);

	// ================================== Core Dispatchers ================================== //
	UPROPERTY(BlueprintAssignable, Category="UI Event Dispatchers")
	FOnUIReady OnUIReady;

private:
	// ================================== Core Functions ================================== //
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI Manager")
	void GetInGameMenuWidget(UWBGameMenu*& ReturnValue);

	UPROPERTY(EditDefaultsOnly, Category="UI Manager")
	UWBGameMenu* GameMenuWidget;
};

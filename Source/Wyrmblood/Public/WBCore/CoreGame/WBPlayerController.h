// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "WBCore/CoreUI/UComponents/WBUIManager.h"
#include "WBCore/CoreInterface/IController/WBControllerInterface.h"
#include "WBPlayerController.generated.h"

// Forward declarations
class AWBBasePlayer;
class UInputMappingContext;


// Delegate for when the player controller is fully ready
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerControllerReady, AWBPlayerController*, GamePlayerController);

UCLASS(BlueprintType, Blueprintable, meta=(Category="Player Controller"))
class WYRMBLOOD_API AWBPlayerController : public APlayerController, public IWBControllerInterface
{
    GENERATED_BODY()

public:
    // ================================ Core Properties ================================ //
    /** Reference to the possessed player pawn */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controller")
    AWBBasePlayer* PlayerReference;

    /** Flag indicating whether controller initialization is complete */
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_IsControllerReady, Category = "Player Controller")
    bool IsControllerReady;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controller")
    UWBUIManager* UIManager;

    // ================================ Core Functions ================================ //
    /** Constructor */
    AWBPlayerController();

    /** Called when this controller possesses a pawn */
    virtual void OnPossess(APawn* InPawn) override;

    /** Set up replication for properties */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    /** Get the stored player reference */
    UFUNCTION(BlueprintCallable, Category = "Player Controller")
    AWBBasePlayer* GetPlayerReference() const;

    /** Set the stored player reference */
    UFUNCTION(BlueprintCallable, Category = "Player Controller")
    void SetPlayerReference(AWBBasePlayer* BasePlayerReference);

    /** Check if the controller is ready */
    UFUNCTION(BlueprintCallable, Category = "Player Controller")
    bool GetIsControllerReady() const;

    /** Mark the controller as ready or not */
    UFUNCTION(BlueprintCallable, Category = "Player Controller")
    void SetIsControllerReady(bool bIsControllerReady);

    /** Broadcast when controller setup is finished */
    UPROPERTY(BlueprintAssignable, Category = "Player Controller Events")
    FOnPlayerControllerReady OnPlayerControllerReady;

    /** Activate/Deactivate the UI Input Mappings */
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetUIInputMappingUI(bool bEnabled);
    
    /** Enable or disable a specific input mapping context */
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetInputMapping(bool bEnabled, UInputMappingContext* MappingContext, int32 Priority = 0);

    /** Enable or disable the default game input mapping */
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetGameDefaultInputMapping(bool bEnabled);

    /** Add an input mapping context at a given priority */
    UFUNCTION(BlueprintCallable, Category = "Input")
    void AddInputMappingContext(UInputMappingContext* MappingContext, int32 Priority = 0);

    /** Remove an input mapping context */
    UFUNCTION(BlueprintCallable, Category = "Input")
    void RemoveInputMappingContext(UInputMappingContext* MappingContext);

    /** Clear all added input mapping contexts */
    UFUNCTION(BlueprintCallable, Category = "Input")
    void ClearAllInputMappings();
    
    //================================ Core Interface Functions ================================ //
    virtual void CloseInGameMenu_Implementation() override;
    virtual void DisableUIMode_Implementation() override;
    virtual void EnableUIMode_Implementation(UUserWidget* FocusedWidget) override;
protected:
    // ================================ Core Properties ================================ //
    /** Default input mapping context */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (DisplayName = "Default Input Mapping"))
    UInputMappingContext* IMC_Default;

    /** Hotbar input mapping context */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (DisplayName = "HotBar Input Mapping"))
    UInputMappingContext* IMC_HotBar;

    /** Camera input mapping context */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (DisplayName = "Camera Input Mapping"))
    UInputMappingContext* IMC_Camera;

    /** UI InGame Mapping Context */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (DisplayName = "UI In Game Mapping"))
    UInputMappingContext* IMC_UI_InGame;

    /** UI Generic Mapping Context */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (DisplayName = "UI Generic Mapping"))
    UInputMappingContext* IMC_UI_Generic;
    
    /** List of additional default input mappings with priorities */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TArray<TSoftObjectPtr<UInputMappingContext>> DefaultInputMappings;

private:
    // ================================ Core SERVER Functions ================================ //
    /** Notify the server that the controller is ready */
    UFUNCTION(Server, Reliable, Category = "Player Controller")
    void Server_SetPlayerControllerReady();

    // ================================ Core CLIENT Functions ================================ //
    /** Client-side handling when possession occurs */
    UFUNCTION(Client, Reliable, Category = "Player Controller")
    void Client_OnPossess();

    // ================================ Core Functions ================================ //
    /** Called when IsControllerReady is replicated */
    UFUNCTION()
    void OnRep_IsControllerReady();

    /**
     * Event triggered when the UI manager signals that the UI is fully initialized.
     * @param UIManagerRef A reference to the UI manager instance responsible for managing the user interface.
     */
    UFUNCTION()
    void OnUIReadyEvent(UWBUIManager* UIManagerRef);
};

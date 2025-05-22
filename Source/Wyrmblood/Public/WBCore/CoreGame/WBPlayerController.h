// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "WBPlayerController.generated.h"

// Forward declaration
class AWBBasePlayer;
class UInputMappingContext;

// Declare the delegate type for the event dispatcher
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerControllerReady, AWBPlayerController*, GamePlayerController);

UCLASS(BlueprintType, Blueprintable, meta=(Category="Player Controller"))
class WYRMBLOOD_API AWBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Constructor
	AWBPlayerController();

	virtual void OnPossess(APawn* InPawn) override;

	// Replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Getter for PlayerReference
	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	AWBBasePlayer* GetPlayerReference() const { return PlayerReference; }

	// Setter for PlayerReference
	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	void SetPlayerReference(AWBBasePlayer* NewPlayerReference) { PlayerReference = NewPlayerReference; }

	// Getter for IsControllerReady
	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	bool GetIsControllerReady() const { return IsControllerReady; }

	// Setter for IsControllerReady
	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	void SetIsControllerReady(bool bNewIsReady) { IsControllerReady = bNewIsReady; }

	// Event Dispatcher
	UPROPERTY(BlueprintAssignable, Category = "Player Controller Events")
	FOnPlayerControllerReady OnPlayerControllerReady;

	// Input Mapping Management
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetInputMapping(bool bEnabled, UInputMappingContext* MappingContext, int32 Priority = 0);

	// Set default game input mapping - now supports multiple contexts
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetGameDefaultInputMapping(bool bEnabled);

	// Add specific input mapping context
	UFUNCTION(BlueprintCallable, Category = "Input")
	void AddInputMappingContext(UInputMappingContext* MappingContext, int32 Priority = 0);

	// Remove specific input mapping context
	UFUNCTION(BlueprintCallable, Category = "Input")
	void RemoveInputMappingContext(UInputMappingContext* MappingContext);

	// Clear all input mapping contexts
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ClearAllInputMappings();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controller")
	AWBBasePlayer* PlayerReference;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_IsControllerReady, Category = "Player Controller")
	bool IsControllerReady;

	// Default Input Mapping Contexts - Multiple contexts support
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (DisplayName = "Default Input Mapping"))
	UInputMappingContext* IMC_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (DisplayName = "HolBar Input Mapping"))
	UInputMappingContext* IMC_HolBar;

	// Array of default input contexts with priorities
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<TSoftObjectPtr<UInputMappingContext>> DefaultInputMappings;
	
private:
	// RepNotify function
	UFUNCTION()
	void OnRep_IsControllerReady();

	UFUNCTION(Client, Reliable, Category = "Player Controller")
	void Client_OnPossess();

	UFUNCTION(Server, Reliable, Category = "Player Controller")
	void Server_SetPlayerControllerReady();
};
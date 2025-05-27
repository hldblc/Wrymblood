// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WBCore/CoreGame/CoreComponents/CInventory/CPrimaryComponent/WBInventoryBase.h"
#include "WBInventoryPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotChanged, FUWBInventorySlot, Slot);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WYRMBLOOD_API UWBInventoryPlayer : public UWBInventoryBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWBInventoryPlayer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	// ================================ Core Properties ================================ //

	// ================================ Core Functions ================================ //
	UFUNCTION(BlueprintCallable, Category="InventoryItem|Add")
	void AddItemToInventory(FUWBInventorySlot ItemToAdd, bool& Successfull);

	UFUNCTION(BlueprintCallable, Category="InventoryItem|Find")
	void FindEmptySlot(bool& Result, FUWBInventorySlot& Slot);

	UFUNCTION(BlueprintCallable, Category="InventoryItem|Remove")
	void SetItem(FUWBInventorySlot TargetSlot, FUWBInventorySlot Item, bool Silent);

	
	// ================================ Core SERVER Functions ================================ //
	UFUNCTION(BlueprintCallable, Reliable, Server)
	void SERVER_SetupSlots(int32 InMaxSlotCount);

	UFUNCTION(BlueprintCallable, Reliable, Server)
	void SERVER_AddItemToInventory(FUWBInventorySlot Item);

	// ================================ Core Dispatchers ================================ //
	UPROPERTY(BlueprintAssignable, Category="Inventory Event Dispatchers")
	FOnSlotChanged OnSlotChanged;
	
};

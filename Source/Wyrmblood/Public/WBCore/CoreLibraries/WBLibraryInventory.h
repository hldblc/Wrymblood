// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WBCore/CoreGame/CoreData/DDataAsset/PrimaryAssets/WBItemData.h"
#include "WBCore/CoreLibraries/WBLibraryItem.h"
#include "WBLibraryInventory.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="Inventory Library"))
class WYRMBLOOD_API UWBLibraryInventory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// ===================================== Core Utility Functions ===================================== //
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="InventoryUtilityLibrary")
	static void IsSlotEmpty(const FUWBInventorySlot Slot, bool& Empty);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="InventoryUtilityLibrary")
	static void IsSlotNotEmpty(const FUWBInventorySlot Slot, bool& NotEmpty);

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintPure, Category="InventoryUtilityLibrary")
	static UWBItemData* MakeItemToAdd(TSoftObjectPtr<UWBItemData> ItemDataSoftObject, int32 Quatity, FUWBInventorySlot& Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="InventoryUtilityLibrary")
	static void GetSlotWeight(FUWBInventorySlot Slot, float& Weight);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="InventoryUtilityLibrary")
	static void HasSlotContainedItem(FUWBInventorySlot Slot, bool& HasContainedItem);
	
};

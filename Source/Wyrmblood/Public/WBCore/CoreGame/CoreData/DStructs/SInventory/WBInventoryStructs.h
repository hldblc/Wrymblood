// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WBSlotContainedItem.h"
#include "WBCore/CoreGame/CoreData/DDataAsset/PrimaryAssets/WBItemData.h"
#include "WBInventoryStructs.generated.h"

class UWBInventoryBase;
/**
 * 
 */
USTRUCT(BlueprintType)
struct WYRMBLOOD_API FUWBInventorySlot 
{
	GENERATED_BODY()

public:
	FUWBInventorySlot();
	
	// ================================= Core Properties =================================
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Inventory Slot")
	FName ItemID;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Inventory Slot")
	int32 ItemQuatity;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Inventory Slot")
	int32 SlotIndex;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Inventory Slot")
	TSoftObjectPtr<UWBItemData> ItemDataAsset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Inventory Slot")
	float CurrentDurability;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Inventory Slot")
	float MaxDurability;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Inventory Slot")
	float ItemWeight;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Inventory Slot")
	FWBSlotContainedItem ContainedItem;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Inventory Slot")
	TObjectPtr<UWBInventoryBase> InventoryRef;



	
};

// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WBCore/CoreGame/CoreData/DDataAsset/PrimaryAssets/WBItemData.h"
#include "WBSlotContainedItem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct WYRMBLOOD_API FWBSlotContainedItem 
{
	GENERATED_BODY()

	// Initialize properties inline - this is the correct way for USTRUCT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySlotData")
	float CurrentAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySlotData")
	float MaxCapacity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySlotData")
	TSoftObjectPtr<UWBItemData> ContainedItemDataAsset = nullptr;
};

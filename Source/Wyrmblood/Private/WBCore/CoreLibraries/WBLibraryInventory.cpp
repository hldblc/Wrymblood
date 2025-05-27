// © 2025 Hephaestus Studios. All rights reserved.


#include "WBCore/CoreLibraries/WBLibraryInventory.h"

#include "WBCore/CoreLibraries/WBLibraryItem.h"
#include "WBCore/CoreGame/CoreData/DStructs/SInventory/WBInventoryStructs.h"



void UWBLibraryInventory::IsSlotEmpty(const FUWBInventorySlot Slot, bool& Empty)
{
	Empty = !Slot.ItemDataAsset.IsValid();
}

void UWBLibraryInventory::IsSlotNotEmpty(const FUWBInventorySlot Slot, bool& NotEmpty)
{
	NotEmpty = Slot.ItemDataAsset.IsValid();
}

UWBItemData* UWBLibraryInventory::MakeItemToAdd(TSoftObjectPtr<UWBItemData> ItemDataSoftObject, int32 Quatity,
	FUWBInventorySlot& Item)
{
	UWBItemData* ResolvedItemData = UWBLibraryItem::ResolveSoftItemDataRef(ItemDataSoftObject);

	if (IsValid(ResolvedItemData))
	{
		// Make S Inventory Slot
		Item.ItemID = ResolvedItemData->ItemID;
		Item.ItemQuatity = Quatity;
		Item.SlotIndex = 0;
		Item.ItemDataAsset = ResolvedItemData;
		Item.CurrentDurability = ResolvedItemData->GetItemDefaultDurability();
		Item.MaxDurability = ResolvedItemData->GetItemDefaultDurability();
		Item.ItemWeight = ResolvedItemData->ItemWeight;
		Item.InventoryRef = nullptr;
        
		return ResolvedItemData;
	}
	else
	{
		// Print String - Can't resolve ItemDataAsset
		UE_LOG(LogTemp, Warning, TEXT("Can't resolve ItemDataAsset"));
        
		// Return null/empty item
		Item = FUWBInventorySlot();
		return nullptr;
	}
}


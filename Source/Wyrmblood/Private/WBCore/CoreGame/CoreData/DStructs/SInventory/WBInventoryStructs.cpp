// © 2025 Hephaestus Studios. All rights reserved.

#include "WBCore/CoreGame/CoreData/DStructs/SInventory/WBInventoryStructs.h"

FUWBInventorySlot::FUWBInventorySlot()
	: ItemID(NAME_None)
	, ItemQuatity(0)  // Note: You have a typo here - should be "ItemQuantity"
	, SlotIndex(-1)
	, ItemDataAsset(nullptr)
	, CurrentDurability(0.0f)
	, MaxDurability(0.0f)
	, ItemWeight(0.0f)
	, InventoryRef(nullptr)
{
	// Constructor body can remain empty since we're using member initializer list
}
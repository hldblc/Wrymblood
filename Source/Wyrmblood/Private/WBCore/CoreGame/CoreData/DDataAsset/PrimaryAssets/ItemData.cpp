// © 2025 Hephaestus Studios. All rights reserved.


#include "WBCore/CoreGame/CoreData/DDataAsset/PrimaryAssets/ItemData.h"
#include "WBCore/CoreInterface/IAssets/WBAssetsInterface.h"
#include "WBCore/CoreInterface/IItem/WBItemDataInterface.h"


#include "Engine/Texture2D.h"

// ============================== C++ Core Properties ============================== //
UItemData::UItemData()
{
	ItemID = FName("ItemID");
	ItemIcon = nullptr;
	ItemName = FText::FromString("ItemName");
	ItemDescription = FText::FromString("ItemDescription");
	ItemType = E_ItemType::None;
	ItemRarity = E_ItemRarity::None;
	StackSize = 1;
	ItemWeight = 1.0f;
	ActorSpawnClass = nullptr;
}

TSoftObjectPtr<UTexture2D> UItemData::ItemIcon_Implementation() const
{
	return ItemIcon;
}

void UItemData::IsItemStackable_Implementation(bool& bIsStackable, int32& OutStackSize) const
{
	
	bool bStackable = false;
	bIsStackable = const_cast<UItemData*>(this)->IsStackable(bStackable);
	OutStackSize = StackSize;
}

// ============================== C++ Core Functions ============================== //
bool UItemData::IsStackable(bool& bStackable)
{
	bStackable = (StackSize > 1);
	return bStackable;
}

float UItemData::GetItemDefaultDurability() const
{
	// Override Function - used by children
	return 0.0f;
}

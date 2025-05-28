// © 2025 Hephaestus Studios. All rights reserved.


#include "WBCore/CoreGame/CoreData/DDataAsset/PrimaryAssets/WBItemData.h"
#include "WBCore/CoreInterface/IAssets/WBAssetsInterface.h"
#include "WBCore/CoreInterface/IItem/WBItemDataInterface.h"


#include "Engine/Texture2D.h"

// ============================== C++ Core Properties ============================== //
UWBItemData::UWBItemData()
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

TSoftObjectPtr<UTexture2D> UWBItemData::GetItemIcon_Implementation() const
{
	return ItemIcon;
}

// ============================== C++ Core Interface Functions ============================== //
void UWBItemData::IsItemStackable_Implementation(bool& bIsStackable, int32& OutStackSize) const
{
	
	bool bStackable = false;
	bIsStackable = const_cast<UWBItemData*>(this)->IsStackable(bStackable);
	OutStackSize = StackSize;
}

UWBItemData* UWBItemData::GetItemDataAsset_Implementation() const
{
	return const_cast<UWBItemData*>(this);
}

// ============================== C++ Core Functions ============================== //
bool UWBItemData::IsStackable(bool& bStackable)
{
	bStackable = (StackSize > 1);
	return bStackable;
}

float UWBItemData::GetItemDefaultDurability() const
{
	// Override Function - used by children
	return 0.0f;
}

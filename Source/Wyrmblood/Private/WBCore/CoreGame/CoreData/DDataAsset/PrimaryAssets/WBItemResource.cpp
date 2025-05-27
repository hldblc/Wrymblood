// © 2025 Hephaestus Studios. All rights reserved.


#include "WBCore/CoreGame/CoreData/DDataAsset/PrimaryAssets/WBItemResource.h"

UWBItemResource::UWBItemResource()
{
	FuelTime = 0.0f;
}

UWBItemResource* UWBItemResource::GetItemResourceAsset_Implementation() const
{
	return const_cast<UWBItemResource*>(this);
}

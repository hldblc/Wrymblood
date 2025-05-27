// © 2025 Hephaestus Studios. All rights reserved.


#include "WBCore/CoreLibraries/WBLibraryItem.h"

UWBItemData* UWBLibraryItem::ResolveSoftItemDataRef(TSoftObjectPtr<UWBItemData> ItemDataSoftObject)
{
	if (UWBItemData* LoadedAsset = ItemDataSoftObject.LoadSynchronous())
	{
		if (IWBAssetsInterface* AssetsInterface = Cast<IWBAssetsInterface>(LoadedAsset))
		{
			return AssetsInterface->Execute_GetItemDataAsset(LoadedAsset);
		}

		return LoadedAsset;
	}

	return nullptr;
}

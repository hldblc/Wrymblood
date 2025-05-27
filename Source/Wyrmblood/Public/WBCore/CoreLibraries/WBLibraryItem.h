// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WBCore/CoreGame/CoreData/DDataAsset/PrimaryAssets/WBItemData.h"
#include "WBCore/CoreInterface/IAssets/WBAssetsInterface.h"
#include "WBLibraryItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="Item Library"))
class WYRMBLOOD_API UWBLibraryItem : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="ItemUtility")
	static UWBItemData* ResolveSoftItemDataRef(TSoftObjectPtr<UWBItemData> ItemDataSoftObject);
};

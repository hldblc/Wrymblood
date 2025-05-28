// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WBItemDataInterface.generated.h"

class UTexture2D;

UINTERFACE(BlueprintType, MinimalAPI)
class UWBItemDataInterface : public UInterface
{
	GENERATED_BODY()
};


class WYRMBLOOD_API IWBItemDataInterface
{
	GENERATED_BODY()

public:

	/**  
	 *  Does this item stack?  
	 *  Returns via two out‐params so Blueprint sees both as outputs.  
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ItemDataInterface")
	void IsItemStackable(bool& bIsStackable, int32& OutStackSize) const;

	/**
	 *  Returns the icon texture for this item.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ItemDataInterface")
	TSoftObjectPtr<UTexture2D> GetItemIcon() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ItemDataInterface")
	void IsItemDurabilityBased(bool& bIsDurabilityBased) const;
};

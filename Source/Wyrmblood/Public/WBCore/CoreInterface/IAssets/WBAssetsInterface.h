// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WBAssetsInterface.generated.h"

class UWBItemData;
class UWBItemResource;
// This class does not need to be modified.
UINTERFACE(NotBlueprintType, meta=(DisplayName="Assets Interface"))
class UWBAssetsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WYRMBLOOD_API IWBAssetsInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Assets Interface", meta=(ReturnDisplayName="Item Data Asset"))
	UWBItemData* GetItemDataAsset() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Assets Interface", meta=(ReturnDisplayName="Item Resource Asset"))
	UWBItemResource* GetItemResourceAsset() const;
};

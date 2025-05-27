// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WBItemData.h"
#include "WBItemResource.generated.h"

/**
 * 
 */
UCLASS(blueprintable, BlueprintType, meta=(DisplayName="Item Resource Primary Data Asset"))
class WYRMBLOOD_API UWBItemResource : public UWBItemData
{
	GENERATED_BODY()

public:

	UWBItemResource();

	virtual UWBItemResource* GetItemResourceAsset_Implementation() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Resource Settings")
	float FuelTime;
};

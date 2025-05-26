// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WBCore/CoreGame/CoreActors/AItem/WBItemMaster.h"
#include "WBCore/CoreGame/CoreEnums/EItem/WBItemEnums.h"
#include "WBCore/CoreInterface/IAssets/WBAssetsInterface.h"
#include "WBCore/CoreInterface/IItem/WBItemDataInterface.h"
#include "ItemData.generated.h"




/**
 * 
 */
UCLASS()
class WYRMBLOOD_API UItemData : public UPrimaryDataAsset, public IWBItemDataInterface, public IWBAssetsInterface
{
	GENERATED_BODY()

public:
	UItemData();

	// ============================== Core Interface Functions ==============================//
	virtual TSoftObjectPtr<UTexture2D> ItemIcon_Implementation() const override;

	virtual void IsItemStackable_Implementation(bool& bIsStackable, int32& OutStackSize) const override;


	
	// ============================== Core Functions ============================== //
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Item Data|Functions", meta=(ReturnDisplayName="Stackable"))
	bool IsStackable(bool& bStackable);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Item Data|Functions")
	float GetItemDefaultDurability() const;


	
	// ============================== Core Properties ============================== //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	E_ItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	E_ItemRarity ItemRarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	int32 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	float ItemWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data")
	TSoftClassPtr<AWBItemMaster> ActorSpawnClass;


	
};

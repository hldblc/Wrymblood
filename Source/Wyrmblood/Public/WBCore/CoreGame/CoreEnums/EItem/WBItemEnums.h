// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WBItemEnums.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class E_ItemType : uint8
{
	None		   UMETA(DisplayName = "None"),
	Resource       UMETA(DisplayName = "Resource"),
	Consumable     UMETA(DisplayName = "Consumable"),
	Buildable      UMETA(DisplayName = "Buildable"),
	Equipable      UMETA(DisplayName = "Equipable"),
	Armor          UMETA(DisplayName = "Armor"),
};

UENUM(BlueprintType)
enum class E_ItemRarity : uint8
{
	None           UMETA(DisplayName = "None"),
	Common         UMETA(DisplayName = "Common"),
	Uncommon       UMETA(DisplayName = "Uncommon"),
	Rare           UMETA(DisplayName = "Rare"),
	Epic           UMETA(DisplayName = "Epic"),
	Legendary      UMETA(DisplayName = "Legendary"),
	Dark           UMETA(DisplayName = "Dark"),
};

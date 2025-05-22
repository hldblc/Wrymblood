// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WBCharacterInterface.generated.h"

class AWBBasePlayer; // Forward declaration

// This interface cannot be implemented in Blueprints, only used (called) from them
UINTERFACE(NotBlueprintable)
class WYRMBLOOD_API UWBCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for Wyrmblood character interactions
 * Provides access to the owning player character
 */
class WYRMBLOOD_API IWBCharacterInterface
{
	GENERATED_BODY()

public:
	/** 
	 * Returns the player character reference (AWBBasePlayer).
	 * Blueprint-callable, but only implemented in C++.
	 */
	UFUNCTION(BlueprintCallable, Category = "Character Interface", DisplayName = "Get Player Character Ref", meta = (ReturnDisplayName = "Player Character"))
	virtual AWBBasePlayer* GetPlayerCharacterRef() = 0;
};

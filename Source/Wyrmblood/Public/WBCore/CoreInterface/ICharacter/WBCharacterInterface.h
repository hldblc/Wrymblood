// WBCharacterInterface.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WBCore/CoreGame/CoreData/DStructs/SCharacter/WBCharacterStructs.h"
#include "WBCharacterInterface.generated.h"

class AWBBasePlayer;
class AWBPlayerController;

/*  Exposed as a type in BP, and BP classes are allowed to implement it       */
UINTERFACE(BlueprintType, Blueprintable)          //  ← was NotBlueprintable
class WYRMBLOOD_API UWBCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for Wyrmblood characters.
 * NOTE: only declarations go here; no bodies.
 */
class WYRMBLOOD_API IWBCharacterInterface
{
	GENERATED_BODY()

public:

	/* -------- Player Character getter ---------------------------------- */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,
			  Category="Character Interface",
			  meta=(DisplayName="Get Player Character Ref",
					ReturnDisplayName="Player Character"))
	AWBBasePlayer* GetPlayerCharacterRef() const;

	/* -------- Player Controller getter ---------------------------------- */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,
			  Category="Character Interface",
			  meta=(DisplayName="Get Player Controller Ref",
					ReturnDisplayName="Player Controller"))
	AWBPlayerController* GetPlayerControllerRef() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Character Camera", 
			  meta=(DisplayName="Get Properties For Camera"))
	void GetPropertiesForCamera(FCharacterCamera& OutCameraProperties) const;
};

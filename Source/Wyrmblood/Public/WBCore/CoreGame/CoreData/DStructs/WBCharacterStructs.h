// © 2025 Hephaestus Studios. All rights reserved.
// WBCharacterStructs.h
#pragma once

#include "CoreMinimal.h"
#include "WBCore/CoreGame/CoreEnums/ECharacter/WBCharacterEnums.h"
#include "WBCore/CoreGame/CoreEnums/ECharacter/WBMovementEnums.h"
#include "WBCharacterStructs.generated.h"

/**
 * Movement–intent flags that Blueprint or C++ can read / write.
 * Add new fields (or entirely new structs) here as you expand the
 * character feature-set.
 */
USTRUCT(BlueprintType)
struct WYRMBLOOD_API FCharacterInputState
{
	GENERATED_BODY()

	/** True on the frame the player last chose to Walk. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementInputStateStruct")
	bool bLastWalk = false;

	/** Player is holding the Sprint modifier. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementInputStateStruct")
	bool bWantsToSprint = false;

	/** Player actively wants to Walk (vs. Idle / Crouch). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementInputStateStruct")
	bool bWantsToWalk = false;

	/** Player is pressing Strafe (left / right). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementInputStateStruct")
	bool bWantsToStrafe = true;

	/** Player wants to Aim-Down-Sights or similar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementInputStateStruct")
	bool bWantsToAim = false;
};

USTRUCT(BlueprintType)
struct WYRMBLOOD_API FCharacterCamera
{
	GENERATED_BODY()

	// Default constructor 
	FCharacterCamera()
	{
		CameraMode = E_CameraMode::StrafeCam; 
		Stance = E_MovementStance::Stand;     
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Camera")
	E_CameraMode CameraMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Camera")
	E_MovementStance Stance;
};
// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WBMovementEnums.generated.h"

UENUM(BlueprintType)
enum class E_MovementState : uint8
{
	Moving	UMETA(DisplayName = "Moving"),
	Idle    UMETA(DisplayName = "Idle"),
};

UENUM(BlueprintType)
enum class E_MovementStance : uint8
{
	Stand	UMETA(DisplayName = "Stand"),
	Crouch	UMETA(DisplayName = "Crouch"),
};

UENUM(BlueprintType)
enum class E_MovementMode : uint8
{
	OnGround  UMETA(DisplayName = "OnGround"),
	InAir     UMETA(DisplayName = "InAir"),
};

UENUM(BlueprintType)
enum class E_MovementGait : uint8
{
	Walk	UMETA(DisplayName = "Walk"),
	Run		UMETA(DisplayName = "Run"),
	Sprint	UMETA(DisplayName = "Sprint"),
	Swim	UMETA(DisplayName = "Swim"),
	Fly		UMETA(DisplayName = "Fly"),
	Jump	UMETA(DisplayName = "Jump"),
	Fall	UMETA(DisplayName = "Fall"),
	Ladder	UMETA(DisplayName = "Ladder"),
};

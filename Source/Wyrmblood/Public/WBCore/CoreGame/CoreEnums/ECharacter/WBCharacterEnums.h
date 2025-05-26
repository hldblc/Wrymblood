// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WBCharacterEnums.generated.h"

UENUM(BlueprintType)
enum class E_CameraMode : uint8
{
	StrafeCam    UMETA(DisplayName = "StrafeCam"),
	Aim		     UMETA(DisplayName = "Aim"), 
};

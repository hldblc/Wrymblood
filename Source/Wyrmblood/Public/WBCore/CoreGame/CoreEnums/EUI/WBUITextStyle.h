// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "WBUITextStyle.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class E_UI_TextStyle : uint8
{
	TEMP                UMETA(DisplayName = "TEMP"),
	UI_Body_Text        UMETA(DisplayName = "UI_Body_Text"),
	UI_Body_Text_XS     UMETA(DisplayName = "UI_Body_Text_XS"),
	UI_Body_Subtext     UMETA(DisplayName = "UI_Body_Subtext"),
	UI_Body_Label       UMETA(DisplayName = "UI_Body_Label"),
	UI_Body_Label_Value UMETA(DisplayName = "UI_Body_Label_Value"),
	UI_Body_Label_XS    UMETA(DisplayName = "UI_Body_Label_XS"),
	UI_H1               UMETA(DisplayName = "UI_H1"),
	UI_H2               UMETA(DisplayName = "UI_H2"),
	UI_H3               UMETA(DisplayName = "UI_H3"),
	UI_H4               UMETA(DisplayName = "UI_H4"),
	UI_H1_Dark          UMETA(DisplayName = "UI_H1_Dark"),
	UI_H2_Dark          UMETA(DisplayName = "UI_H2_Dark"),
	UI_H3_Dark          UMETA(DisplayName = "UI_H3_Dark"),
	UI_H4_Dark          UMETA(DisplayName = "UI_H4_Dark"),
	UI_Slot			    UMETA(DisplayName = "UI_Slot"),
};
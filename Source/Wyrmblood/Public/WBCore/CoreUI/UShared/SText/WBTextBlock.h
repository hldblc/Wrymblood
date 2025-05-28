// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommonTextBlock.h"
#include "WBCore/CoreGame/CoreEnums/EUI/WBUITextStyle.h"
#include "WBTextBlock.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="Text Block Widget"))
class WYRMBLOOD_API UWBTextBlock : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> TextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InstanceEditable, ExposeOnSpawn))
	FText TextValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InstanceEditable, ExposeOnSpawn))
	E_UI_TextStyle TextStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TMap<E_UI_TextStyle, TSoftClassPtr<UCommonTextStyle>> StyleSet;
};

// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CommonActivatableWidget.h"
#include "WBRootUI.generated.h"

/**
 * 
 */
UCLASS()
class WYRMBLOOD_API UWBRootUI : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UNamedSlot> SlotInGameMenu;

protected:
	virtual void NativeConstruct() override;
};

// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "WBText_WithValue.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="Text Value Widget"))
class WYRMBLOOD_API UWBText_WithValue : public UUserWidget
{
	GENERATED_BODY()

protected:
	UWBText_WithValue(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InstanceEditable, ExposeOnSpawn))
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InstanceEditable, ExposeOnSpawn))
	FText StatValue;
	
};

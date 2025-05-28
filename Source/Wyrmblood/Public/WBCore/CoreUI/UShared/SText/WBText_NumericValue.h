// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommonNumericTextBlock.h"
#include "WBText_NumericValue.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="Text Numeric Value Widget"))
class WYRMBLOOD_API UWBText_NumericValue : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Constructor
	UWBText_NumericValue(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InstanceEditable, ExposeOnSpawn))
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InstanceEditable, ExposeOnSpawn))
	float StatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (InstanceEditable, ExposeOnSpawn))
	ECommonNumericType NumericType;
};

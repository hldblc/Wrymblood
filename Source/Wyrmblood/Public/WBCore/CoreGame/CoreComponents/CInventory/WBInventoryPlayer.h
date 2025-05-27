// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CPrimaryComponent/WBInventoryBase.h"
#include "WBInventoryPlayer.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WYRMBLOOD_API UWBInventoryPlayer : public UWBInventoryBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWBInventoryPlayer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

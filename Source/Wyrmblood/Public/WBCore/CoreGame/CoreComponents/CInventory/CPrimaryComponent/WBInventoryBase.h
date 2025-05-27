// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "WBCore/CoreGame/CoreData/DStructs/SInventory/WBInventoryStructs.h"
#include "WBInventoryBase.generated.h"




UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WYRMBLOOD_API UWBInventoryBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UWBInventoryBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Inventory Slots")
	TArray<FUWBInventorySlot> InventorySlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Settings")
	int32 MaxSlotcount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Settings")
	bool bEnabledWeightSystem;

protected:
	virtual void BeginPlay() override;
};
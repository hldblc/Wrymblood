// © 2025 Hephaestus Studios. All rights reserved.


#include "WBCore/CoreGame/CoreComponents/CInventory/CPrimaryComponent/WBInventoryBase.h"
#include "WBCore/CoreGame/CoreData/DStructs/SInventory/WBInventoryStructs.h"


// Sets default values for this component's properties
UWBInventoryBase::UWBInventoryBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWBInventoryBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UWBInventoryBase, InventorySlots, COND_InitialOrOwner);
}


// Called when the game starts
void UWBInventoryBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWBInventoryBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


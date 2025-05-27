// © 2025 Hephaestus Studios. All rights reserved.


#include "WBCore/CoreGame/CoreComponents/CInventory/WBInventoryPlayer.h"

#include "Kismet/KismetSystemLibrary.h"
#include "WBCore/CoreGame/CoreComponents/CInventory/CPrimaryComponent/WBInventoryBase.h"
#include "Net/UnrealNetwork.h"    
#include "WBCore/CoreGame/CoreData/DStructs/SInventory/WBInventoryStructs.h"
#include "WBCore/CoreLibraries/WBLibraryInventory.h"

// Sets default values for this component's properties
UWBInventoryPlayer::UWBInventoryPlayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWBInventoryPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority())
	{
		SERVER_SetupSlots(MaxSlotCount);
	}
	
}


// ================================ Core C++ Functions ================================ //

void UWBInventoryPlayer::AddItemToInventory(FUWBInventorySlot ItemToAdd, bool& Successfull)
{
	bool Result = false;
	FUWBInventorySlot EmptySlot;
    
	FindEmptySlot(Result, EmptySlot);
    
	if (Result)
	{
		SetItem(EmptySlot, ItemToAdd, false);
		Successfull = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TODO: Inventory is Full"));
		Successfull = false;
	}
}

void UWBInventoryPlayer::FindEmptySlot(bool& Result, FUWBInventorySlot& Slot)
{
	for (const FUWBInventorySlot& CurrentSlot : InventorySlots)
	{
		bool bIsEmpty = false;
		UWBLibraryInventory::IsSlotEmpty(CurrentSlot, bIsEmpty);

		if (bIsEmpty)
		{
			Result = true;
			Slot = CurrentSlot;
			return;
		}
	}

	Result = false;
	Slot = FUWBInventorySlot();
	
}

void UWBInventoryPlayer::SetItem(FUWBInventorySlot TargetSlot, FUWBInventorySlot Item, bool Silent)
{
	// 1) Break TargetSlot → SlotIndex
	const int32 SlotIndex = TargetSlot.SlotIndex;

	// 2) SizeToFit unchecked → bail if out-of-range
	if (!InventorySlots.IsValidIndex(SlotIndex))
	{
		return;
	}

	// 3) Set Array Elem: InventorySlots[SlotIndex] = Item
	InventorySlots[SlotIndex] = Item;

	// 4) Get (Array Element as Ref) & Set Members
	FUWBInventorySlot& SlotRef = InventorySlots[SlotIndex];
	SlotRef.SlotIndex    = SlotIndex;
	SlotRef.InventoryRef = this;

	// 5) Branch on Silent → Notify Slot Changed
	if (!Silent)
	{
		OnSlotChanged.Broadcast(SlotRef);
	}
}


// ================================ Core C++ SERVER Functions ================================ //
void UWBInventoryPlayer::SERVER_SetupSlots_Implementation(int32 InMaxSlotCount)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	MaxSlotCount = InMaxSlotCount;

	InventorySlots.Empty();

	InventorySlots.Reserve(MaxSlotCount);

	for (int32 Index = 0; Index < MaxSlotCount; ++Index)
	{
		FUWBInventorySlot NewSlot;
		NewSlot.SlotIndex = Index;
		NewSlot.InventoryRef = this;

		InventorySlots.Add(MoveTemp(NewSlot));
	}
}


void UWBInventoryPlayer::SERVER_AddItemToInventory_Implementation(FUWBInventorySlot Item)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	bool bSuccessfull = false;
	AddItemToInventory(Item, bSuccessfull);
}




// ================================ Core C++ Dispatchers ================================ //


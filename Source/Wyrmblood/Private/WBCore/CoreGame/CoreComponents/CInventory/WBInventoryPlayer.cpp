// © 2025 Hephaestus Studios. All rights reserved.


#include "WBCore/CoreGame/CoreComponents/CInventory/WBInventoryPlayer.h"


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

	// ...
	
}


// Called every frame
void UWBInventoryPlayer::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


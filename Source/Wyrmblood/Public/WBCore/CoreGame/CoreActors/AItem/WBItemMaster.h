// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WBItemMaster.generated.h"

UCLASS()
class WYRMBLOOD_API AWBItemMaster : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWBItemMaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

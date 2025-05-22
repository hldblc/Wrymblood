// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WBCore/CoreInterface/WBCharacterInterface.h"
#include "WBBasePlayer.generated.h"

UCLASS(BlueprintType, meta=(Category="Base Player Character"))
class WYRMBLOOD_API AWBBasePlayer : public ACharacter, public IWBCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWBBasePlayer();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ============================ Interface implementation ============================
	virtual AWBBasePlayer* GetPlayerCharacterRef() override;
	


};
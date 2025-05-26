// © 2025 Hephaestus Studios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WBCore/CoreInterface/ICharacter/WBCharacterInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WBBasePlayer.generated.h"

class AWBPlayerController;
class AWBPlayerController;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UCharacterMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controller")
	AWBPlayerController* PlayerController;

	UPROPERTY(ReplicatedUsing=OnRep_CharacterInputState, EditAnywhere, BlueprintReadWrite, Category="Character Input State")
	FCharacterInputState CharacterInputState;

	UFUNCTION()
	void OnRep_CharacterInputState();

	// ============================ Interface implementation ============================
	virtual AWBBasePlayer* GetPlayerCharacterRef_Implementation() const override;
	virtual AWBPlayerController* GetPlayerControllerRef_Implementation() const override;
	virtual void GetPropertiesForCamera_Implementation(FCharacterCamera& OutCameraProperties) const override;

private:

	UFUNCTION(BlueprintPure)
	bool CanAim() const;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
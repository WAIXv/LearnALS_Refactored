// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "State/AlsLocomotionState.h"
#include "State/AlsRagdollingState.h"
#include "State/AlsRollingState.h"
#include "State/AlsViewState.h"
#include "Utility/AlsGameplayTags.h"
#include "AlsCharacter.generated.h"

class UAlsMovementSettings;
class UAlsCharacterSettings;

UCLASS()
class ALS_API AAlsCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Als Character")
	TObjectPtr<UCharacterMovementComponent> AlsCharacterMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character")
	TObjectPtr<UAlsCharacterSettings> Settings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character")
	TObjectPtr<UAlsMovementSettings> MovementSettings;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State")
	bool bDesiredAiming;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State")
	FGameplayTag DesiredRotationMode{AlsRotationModeTags::LookingDirection};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State")
	FGameplayTag DesiredStance{AlsStanceTags::Standing};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State")
	FGameplayTag DesiredGait{AlsGaitTags::Running};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State")
	FGameplayTag ViewMode{AlsViewModeTags::ThirdPerson};

	//TODO:Replicated to ReplicatedUsing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State")
	FGameplayTag OverlayMode{AlsOverlayModeTags::Default};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FAlsViewState ViewState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FVector_NetQuantizeNormal InputDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FAlsLocomotionState LocomotionState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FGameplayTag LocomotionMode{AlsLocomotionModeTags::Grounded};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FGameplayTag RotationMode{AlsRotationModeTags::LookingDirection};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FGameplayTag Stance{AlsStanceTags::Standing};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FGameplayTag Gait{AlsGaitTags::Walking};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FGameplayTag LocomotionAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FVector_NetQuantize100 RagdollTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FAlsRagdollingState RagdollingState;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FAlsRollingState RollingState;

public:
	// Sets default values for this character's properties
	AAlsCharacter();

	// View Mode
public:
	const FGameplayTag& GetViewMode() const;

	// Locomotion Mode
public:
	const FGameplayTag& GetLocomotionMode() const;


	// Desired Aiming
public:
	bool IsDesiredAiming() const;

	// Desired Rotation Mode
public:
	const FGameplayTag& GetDesiredRotationMode() const;

	// Rotation Mode
public:
	const FGameplayTag& GetRotationMode() const;

	// Desired Stance
public:
	const FGameplayTag& GetDesiredStance() const;

	// Stance
public:
	const FGameplayTag& GetStance() const;

	// Desired Gait
public:
	const FGameplayTag& GetDesiredGait() const;

	// Gait
public:
	const FGameplayTag& GetGait() const;

	// OverlayMode
public:
	const FGameplayTag& GetOverlayMode() const;

	// Locomotion Action
public:
	const FGameplayTag& GetLocomotionAction() const;

	// View
public:
	const FAlsViewState& GetViewState() const;

	// Locomotion
public:
	const FVector& GetInputDirection() const;
public:
	const FAlsLocomotionState& GetLocomotionState() const;

	
};


	
inline const FGameplayTag& AAlsCharacter::GetViewMode() const
{
	return ViewMode;
}

inline const FGameplayTag& AAlsCharacter::GetLocomotionMode() const
{
	return LocomotionMode;
}

inline bool AAlsCharacter::IsDesiredAiming() const
{
	return bDesiredAiming;
}

inline const FGameplayTag& AAlsCharacter::GetDesiredRotationMode() const
{
	return DesiredRotationMode;
}

inline const FGameplayTag& AAlsCharacter::GetRotationMode() const
{
	return RotationMode;
}

inline const FGameplayTag& AAlsCharacter::GetDesiredStance() const
{
	return DesiredStance;
}

inline const FGameplayTag& AAlsCharacter::GetStance() const
{
	return Stance;
}

inline const FGameplayTag& AAlsCharacter::GetDesiredGait() const
{
	return DesiredGait;
}

inline const FGameplayTag& AAlsCharacter::GetGait() const
{
	return Gait;
}

inline const FGameplayTag& AAlsCharacter::GetOverlayMode() const
{
	return OverlayMode;
}

inline const FGameplayTag& AAlsCharacter::GetLocomotionAction() const
{
	return LocomotionAction;
}

inline const FVector& AAlsCharacter::GetInputDirection() const
{
	return InputDirection;
}

inline const FAlsViewState& AAlsCharacter::GetViewState() const
{
	return ViewState;
}

inline const FAlsLocomotionState& AAlsCharacter::GetLocomotionState() const
{
	return LocomotionState;
}

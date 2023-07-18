// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "State/AlsLocomotionState.h"
#include "State/AlsViewState.h"
#include "Utility/AlsGameplayTags.h"
#include "AlsCharacter.generated.h"

UCLASS()
class ALS_API AAlsCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State", Replicated)
	FGameplayTag DesiredRotationMode{AlsRotationModeTags::LookingDirection};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State", Replicated)
	FGameplayTag DesiredStance{AlsStanceTags::Standing};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State", Replicated)
	FGameplayTag DesiredGait{AlsGaitTags::Running};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State", Replicated)
	FGameplayTag ViewMode{AlsViewModeTags::ThirdPerson};

	//TODO:Replicated to ReplicatedUsing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State", Replicated)
	FGameplayTag OverlayMode{AlsOverlayModeTags::Default};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient)
	FAlsViewState ViewState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Replicated)
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

public:
	// Sets default values for this character's properties
	AAlsCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	inline const FGameplayTag& AAlsCharacter::GetViewMode() const
	{
		return ViewMode;
	}

	inline const FGameplayTag& AAlsCharacter::GetLocomotionMode() const
	{
		return LocomotionMode;
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
};

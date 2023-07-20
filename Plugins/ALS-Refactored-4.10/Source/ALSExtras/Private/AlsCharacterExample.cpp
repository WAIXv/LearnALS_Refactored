#include "ALSExtras/Public/AlsCharacterExample.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
AAlsCharacterExample::AAlsCharacterExample()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAlsCharacterExample::NotifyControllerChanged()
{
	auto* PreviousPlayer{Cast<APlayerController>(PreviousController)};
	if(IsValid(PreviousController))
	{
		auto* EnhanceInputSubsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PreviousPlayer->GetLocalPlayer())};
		if(IsValid(EnhanceInputSubsystem))
		{
			EnhanceInputSubsystem->RemoveMappingContext(InputMappingContext);
		}
	}

	auto* NewPlayer{Cast<APlayerController>(Controller)};
	if(IsValid(NewPlayer))
	{
		NewPlayer->InputPitchScale_DEPRECATED = 1.0f;
		NewPlayer->InputRollScale_DEPRECATED = 1.0f;
		NewPlayer->InputYawScale_DEPRECATED = 1.0f;
		
		auto* EnhancedInputSubsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(NewPlayer->GetLocalPlayer())};
		if(IsValid(EnhancedInputSubsystem))
		{
			EnhancedInputSubsystem->AddMappingContext(InputMappingContext,0);
		}
	}

	Super::NotifyControllerChanged();
}

void AAlsCharacterExample::SetupPlayerInputComponent(UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);

	auto* EnhancedInput{Cast<UEnhancedInputComponent>(Input)};
	if (IsValid(EnhancedInput))
	{
		EnhancedInput->BindAction(LookMouseAction, ETriggerEvent::Triggered, this, &ThisClass::InputLookMouse);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::InputSprint);
		EnhancedInput->BindAction(WalkAction, ETriggerEvent::Triggered, this, &ThisClass::InputWalk);
		EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ThisClass::InputCrouch);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::InputJump);
		EnhancedInput->BindAction(AimAction, ETriggerEvent::Triggered, this, &ThisClass::InputAim);
		EnhancedInput->BindAction(RagdollAction, ETriggerEvent::Triggered, this, &ThisClass::InputRagdoll);
		EnhancedInput->BindAction(RollAction, ETriggerEvent::Triggered, this, &ThisClass::InputRoll);
		EnhancedInput->BindAction(RotationModeAction, ETriggerEvent::Triggered, this, &ThisClass::InputRotationMode);
		EnhancedInput->BindAction(ViewModeAction, ETriggerEvent::Triggered, this, &ThisClass::InputViewMode);
		EnhancedInput->BindAction(SwitchShoulderAction, ETriggerEvent::Triggered, this, &ThisClass::InputSwitchShoulder);

	}
}

void AAlsCharacterExample::InputLookMouse(const FInputActionValue& ActionValue)
{
	const auto Value{ActionValue.Get<FVector2D>()};
	
	AddControllerYawInput(Value.X * LookRightMouseSensitivity);
	AddControllerPitchInput(Value.Y * LookUpMouseSensitivity);
}

void AAlsCharacterExample::InputLook(const FInputActionValue& ActionValue)
{
	const auto Value{ActionValue.Get<FVector2D>()};
	
	AddControllerYawInput(Value.X * LookRightRate * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput(Value.Y * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAlsCharacterExample::InputMove(const FInputActionValue& ActionValue)
{
	const auto Value{ActionValue.Get<FVector2D>()};

	//TODO: 用 ViewInfo.Yaw 计算方向
	const auto ForwardDirection{GetActorForwardVector()};
	const auto RightDirection{GetActorRightVector()};
	
	AddMovementInput(ForwardDirection * Value.Y + RightDirection * Value.X);
}

void AAlsCharacterExample::InputSprint(const FInputActionValue& ActionValue)
{
	
}

void AAlsCharacterExample::InputWalk()
{
}

void AAlsCharacterExample::InputCrouch()
{
}

void AAlsCharacterExample::InputJump(const FInputActionValue& ActionValue)
{
}

void AAlsCharacterExample::InputAim(const FInputActionValue& ActionValue)
{
}

void AAlsCharacterExample::InputRagdoll()
{
	UE_LOG(LogTemp,Log,TEXT("Ragdoll Action"));
}

void AAlsCharacterExample::InputRoll()
{
}

void AAlsCharacterExample::InputRotationMode()
{
}

void AAlsCharacterExample::InputViewMode()
{
}

void AAlsCharacterExample::InputSwitchShoulder()
{
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ALSCamera/Public/AlsCameraComponent.h"

#include "GameFramework/Character.h"

UAlsCameraComponent::UAlsCameraComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;

	bTickInEditor = false;
	bHiddenInGame = true;
}

void UAlsCameraComponent::OnRegister()
{
	Character = Cast<ACharacter>(GetOwner());

	Super::OnRegister();
}

void UAlsCameraComponent::Activate(bool bReset)
{
	if(!bReset && !ShouldActivate())
	{
		Super::Activate(bReset);
		return;
	}
	Super::Activate(bReset);

	TickCamera(0.0f,false);
}

void UAlsCameraComponent::InitAnim(const bool bForceReinit)
{
	Super::InitAnim(bForceReinit);

	AnimInstance = GetAnimInstance();
}

void UAlsCameraComponent::BeginPlay()
{
	ensure(IsValid(GetAnimInstance()));
	ensure(IsValid(Settings));
	ensure(IsValid(Character));
	
	Super::BeginPlay();
}

void UAlsCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	if(IsValid(Settings) && Settings->bIgnoreTimeDilation)
	{
		const auto TimeDilation{PreviousGlobalTimeDilation * GetOwner()->CustomTimeDilation};

		DeltaTime = TimeDilation <= SMALL_NUMBER ? DeltaTime : DeltaTime / TimeDilation;
	}

	PreviousGlobalTimeDilation = GetWorld()->GetWorldSettings()->GetEffectiveTimeDilation();
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickCamera(DeltaTime);
}

FTransform UAlsCameraComponent::GetThirdPersonPivotTransform() const
{
	return {
		GetComponentRotation(),
		(Character->GetMesh()->GetSocketLocation(Settings->ThirdPerson.FirstPivotSocketName) +
		 Character->GetMesh()->GetSocketLocation(Settings->ThirdPerson.SecondPivotSocketName)) * 0.5f
	};
}

void UAlsCameraComponent::TickCamera(float DeltaTime, bool bAllowLag)
{
	if(!IsValid(GetAnimInstance()) || !IsValid(Settings) || !IsValid(Character))
	{
		return;
	}

	// Step1: Calculate camera rotation

	const auto CameraTargetRotation{Character->GetViewRotation()};
	const auto PivotTargetTransform{GetThirdPersonPivotTransform()};
	PivotTargetLocation = PivotTargetTransform.GetLocation();

	CameraRotation = CalculateCameraRotation(CameraTargetRotation, DeltaTime, bAllowLag);
	const FRotator CameraYawRotation{CameraRotation.Yaw};
	
	// Step2: Calculate pivot lag location. 先获取 pivot target location 再根据曲线对每个轴进行单独插值，以达到最大控制

	PivotLagLocation = CalculatePivotLagLocation(CameraYawRotation.Quaternion(),DeltaTime, bAllowLag);

	// Step3: Calculate pivot location

	const auto PivotOffset{CalculatePivotOffset(PivotTargetTransform.GetRotation())};
	PivotLocation = PivotLagLocation + PivotOffset;
	
	// Step4 :Calculate target camera location

	const auto CameraTargetLocation{PivotLocation + CalculatePivotOffset(PivotTargetTransform.GetRotation())};

	// Step5 :Trace collision to apply a corrective offset

	const auto CameraResultLocation{CalculateCameraTrace(CameraTargetLocation,PivotOffset,DeltaTime,bAllowLag,TraceDistanceRatio)};

	// Apply result to camera
	//TODO: 添加第一人称逻辑
	CameraLocation = CameraResultLocation;
	CameraFov = Settings->ThirdPerson.Fov;
}

FRotator UAlsCameraComponent::CalculateCameraRotation(const FRotator& CameraTargetRotation, float Deltatime,
	bool bAllowLag) const
{
	return {};
}

FVector UAlsCameraComponent::CalculatePivotLagLocation(const FQuat& CameraYawRotation, float Deltatime,
                                                       bool bAllowLag) const
{
	return {};
}

FVector UAlsCameraComponent::CalculatePivotOffset(const FQuat& PivotTargetRotation) const
{
	return {};
}

FVector UAlsCameraComponent::CalculateCameraTrace(const FVector& CameraTargetLocation, const FVector& PivotOffset,
                                                  float DeltaTime, bool bAllowLag, float& NewTraceDistanceRatio) const
{
	return {};
}

bool UAlsCameraComponent::TryFindBlockingGeometryAdjustedLocation(FVector& Location) const
{
	return false;
}

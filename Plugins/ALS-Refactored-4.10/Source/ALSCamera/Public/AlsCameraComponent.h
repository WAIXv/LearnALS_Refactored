#pragma once

#include "CoreMinimal.h"
#include "AlsCameraSettings.h"
#include "Components/SkeletalMeshComponent.h"
#include "AlsCameraComponent.generated.h"


UCLASS(HideCategories = ("ComponentTick", "Clothing", "Physics", "MasterPoseComponent", "Collision",
	"AnimationRig", "Lighting", "Deformer", "Rendering", "HLOD", "Navigation", "VirtualTexture", "SkeletalMesh",
	"Optimization", "LOD", "MaterialParameters", "TextureStreaming", "Mobile", "RayTracing"))
class ALSCAMERA_API UAlsCameraComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	TObjectPtr<UAlsCameraSettings> Settings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	TObjectPtr<ACharacter> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Meta = (ShowOnlyInnerProperties))
	TWeakObjectPtr<UAnimInstance> AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	float PreviousGlobalTimeDilation{1.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FVector PivotTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FVector PivotLagLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FVector PivotLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FVector CameraLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FRotator CameraRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Meta = (ClampMin = 0, ClampMax = 1))
	float TraceDistanceRatio{1.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Meta = (ClampMin = 5, ClampMax = 360, ForceUnits = "deg"))
	float CameraFov{90.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	bool bRightShoulder{true};

public:
	UAlsCameraComponent();

	virtual void OnRegister() override;

	virtual void Activate(bool bReset) override;

	virtual void InitAnim(bool bForceReinit) override;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//TODO: everything about PostProcessing

	//TODO: public functions to get camera information

	FTransform GetThirdPersonPivotTransform() const;

	bool IsRightShoulder() const;
	
	void SetRightShoulder(bool bNewRightShoulder);

private:
	void TickCamera(float DeltaTime, bool bAllowLag = true);

	FRotator CalculateCameraRotation(const FRotator& CameraTargetRotation,float Deltatime, bool bAllowLag) const;

	FVector CalculatePivotLagLocation(const FQuat& CameraYawRotation, float Deltatime, bool bAllowLag) const;

	FVector CalculatePivotOffset(const FQuat& PivotTargetRotation) const;

	FVector CalculateCameraTrace(const FVector& CameraTargetLocation, const FVector& PivotOffset,
								 float DeltaTime, bool bAllowLag, float& NewTraceDistanceRatio) const;

	bool TryFindBlockingGeometryAdjustedLocation(FVector& Location) const;
};

inline bool UAlsCameraComponent::IsRightShoulder() const
{
	return bRightShoulder;
}

inline void UAlsCameraComponent::SetRightShoulder(const bool bNewRightShoulder)
{
	bRightShoulder = bNewRightShoulder;
}

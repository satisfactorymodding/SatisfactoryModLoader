// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "VehicleAnimationInstance.h"
#include "FGWheeledVehicleAnimationInstance.generated.h"

class AFGWheeledVehicle;

USTRUCT()
struct FACTORYGAME_API FFGVehicleAnimationInstanceProxy : public FVehicleAnimationInstanceProxy
{
	GENERATED_BODY()
public:
	FFGVehicleAnimationInstanceProxy();

	void InitializeWithVehicle( AFGWheeledVehicle* ownerWheeledVehicle );

	// Begin FVehicleAnimationInstanceProxy interface
	virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;
	// End FVehicleAnimationInstanceProxy interface
protected:
	UPROPERTY()
	TObjectPtr<AFGWheeledVehicle> OwnerWheeledVehicle;
};

UCLASS( Transient )
class FACTORYGAME_API UFGWheeledVehicleAnimationInstance : public UVehicleAnimationInstance
{
	GENERATED_BODY()
public:
	UFGWheeledVehicleAnimationInstance();

	// Begin UVehicleAnimationInstance interface
	virtual void NativeInitializeAnimation() override;
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override;
	// End UVehicleAnimationInstance interface
protected:
	UPROPERTY()
	FFGVehicleAnimationInstanceProxy mVehicleAnimInstanceProxy;
};

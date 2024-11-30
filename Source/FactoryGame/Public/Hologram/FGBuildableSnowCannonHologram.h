// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGGenericBuildableHologram.h"
#include "FGBuildableSnowCannonHologram.generated.h"

UENUM()
enum class ESnowCannonHologramBuildStep : uint8
{
	PlacementAndRotation,
	AdjustAngle
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSnowCannonHologram : public AFGGenericBuildableHologram
{
	GENERATED_BODY()

public:
	AFGBuildableSnowCannonHologram();

	virtual void BeginPlay() override;

	virtual int32 GetRotationStep() const override;
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual void ConfigureActor( AFGBuildable* inBuildable ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "JumpPad" )
	void OnCannonAngleAdjusted();
	
private:
	UPROPERTY()
	class UStaticMeshComponent* mCannonHeadMeshComponent;

	FInt32Interval mAngleLimit;
	float mAngleOffset;
	
	ESnowCannonHologramBuildStep mBuildStep;
};

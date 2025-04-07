// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGSplineBuildableSnapHologram.generated.h"

class IFGSplineBuildableInterface;
/**
 * Hologram for snapping to spline based buildables (this is a generic version as is not meant to split or modify the buildable its attaching to)
 */
UCLASS()
class FACTORYGAME_API AFGSplineBuildableSnapHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
public:
	AFGSplineBuildableSnapHologram();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void ConfigureActor( AFGBuildable* inBuildable ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual float GetHologramHoverHeight() const override;
	virtual void GetIgnoredClearanceActors( TSet< AActor* >& ignoredActors ) const override;
	virtual bool CanNudgeHologram() const override;
	// End AFGHologram Interface

	// Begin AFGBuildableHologram Interface
	virtual bool ShouldActorBeConsideredForGuidelines( class AActor* actor ) const override;
	// End AFGBuildableHologram Interface

protected:
	// Begin AFGHologram interface
	virtual int32 GetRotationStep() const override;
	// End of AFGHologram interface

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidPlacement() override;
	// End AFGBuildableHologram Interface
	
public:


private:
	/** Used to limit the placement in turns. What's the maximum offset to check from center to detect the curve. */
	UPROPERTY( EditDefaultsOnly, Category = "SplineSnapBuildable" )
	float mMaxValidTurnOffset;
	/** Used to limit the placement in turns. What's the maximum angle. */
	UPROPERTY( EditDefaultsOnly, Category = "SplineSnapBuildable" )
	float mMaxValidTurnAngle;

	/** The spline buildable we snapped to. */
	UPROPERTY( Replicated, CustomSerialization )
	class AFGBuildable* mSnappedSplineBuildable;

	UPROPERTY()
	TScriptInterface<IFGSplineBuildableInterface> mSplineInterface;

	/** The offset we snapped on the spline */
	UPROPERTY( Replicated, CustomSerialization )
	float mSnappedOffset;

	/** This will be used to fill the valid HitClass Array as the other array is transient so there is difficulty limiting the valid hitclasses */
	UPROPERTY(EditDefaultsOnly, Category="SplineSnapBuildable")
	TArray< TSubclassOf< AFGBuildable > > mValidSplineBuildableClasses;
};

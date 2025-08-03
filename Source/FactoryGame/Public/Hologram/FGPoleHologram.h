// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGFactoryHologram.h"
#include "FGPoleHologram.generated.h"


UENUM()
enum class EPoleHologramBuildStep : uint8
{
	PHBS_PlacementAndRotation,
	PHBS_AdjustHeight
};

/**
 * Base for holograms that can be raised/lowered, e.g. conveyor poles.
 */
UCLASS()
class FACTORYGAME_API AFGPoleHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
public:
	AFGPoleHologram();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void ReplaceHologram( AFGHologram* hologram, bool snapTransform ) override;
	virtual void GetClearanceData( TArray< const FFGClearanceData* >& out_ClearanceData ) const override;
	virtual bool ShouldAutomaticallySpawnLightWeightInstances() const override;

	virtual void ResetBuildSteps();
	// End AFGHologram interface

	/** Set the height of the pole, useful for parent holograms. */
	void SetPoleHeight( float height );

	virtual bool CanAdjustHeight() const { return mCanAdjustHeight; }
	
	// Returns the Height for the currently active mesh
	FORCEINLINE float GetPoleHeight() const { return mCurrentVariationHeight; }
	
protected:
	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface

	virtual void UpdatePoleMesh();
	
private:	
	UFUNCTION()
	void OnRep_PoleVariationIndex();
	
protected:
	FFGClearanceData mClearance;

	bool mCanAdjustHeight;

	UPROPERTY( CustomSerialization )
	EPoleHologramBuildStep mBuildStep;

	/** The pole mesh. */
	UPROPERTY()
	class UStaticMeshComponent* mPoleMeshComponent;
	
private:
	UPROPERTY( ReplicatedUsing = OnRep_PoleVariationIndex, CustomSerialization )
	int32 mPoleVariationIndex;

	float mCurrentVariationHeight;
};

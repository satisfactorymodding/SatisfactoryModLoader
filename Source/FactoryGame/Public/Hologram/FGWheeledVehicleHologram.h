// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGVehicleHologram.h"
#include "FGWheeledVehicleHologram.generated.h"

class AFGVehiclePathNode;
class AFGVehiclePathSegment;
struct FVehiclePathVisualizationHandle;

/**
 * The base class for wheeled vehicle holograms.
 */
UCLASS()
class FACTORYGAME_API AFGWheeledVehicleHologram : public AFGVehicleHologram
{
	GENERATED_BODY()
public:
	AFGWheeledVehicleHologram();

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin AFGVehicleHologram interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void GetIgnoredClearanceActors(TSet<AActor*>& ignoredActors) const override;
	virtual void ScrollRotate(int32 delta, int32 step) override;
	// End AFGVehicleHologram interface
protected:
	// Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
	virtual FTransform GetVehicleSpawnTransform() const override;
	virtual bool ShouldBuildGunHitVehiclePaths() const override;
	// End of AFGHologram interface

	/** Active handle to the path visualization, valid only for locally instigated holograms */
	TSharedPtr<FVehiclePathVisualizationHandle> mActivePathVisualizationHandle;

	UPROPERTY( CustomSerialization, Replicated )
	TObjectPtr<AFGVehiclePathSegment> mSnappedPathSegment;

	UPROPERTY( CustomSerialization, Replicated )
	TObjectPtr<AFGVehiclePathNode> mSnappedPathNode;

	int32 mSelectedPathNodeOrientation{0};
};

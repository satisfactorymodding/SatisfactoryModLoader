// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
#include "FGRailroadSignalHologram.generated.h"

/**
 * Hologram for placing railroad signals.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadSignalHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGRailroadSignalHologram();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual void PreHologramPlacement( const FHitResult& hitResult, bool callForChildren ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual bool CanNudgeHologram() const override;
	virtual void GetSupportedBuildModes_Implementation( TArray< TSubclassOf<UFGBuildGunModeDescriptor> >& out_buildmodes ) const override;
	virtual void OnBuildModeChanged( TSubclassOf<UFGHologramBuildModeDescriptor> buildMode ) override;
	virtual int32 GetRotationStep() const override;
	// End AFGHologram Interface

protected:
	bool IsLocallyOwnedHologram() const;

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidPlacement() override;
	// End AFGBuildableHologram Interface

	/** Updates the meshes and other properties as appropriate. */
	void SetLeftHanded( bool isLeftHanded );

private:
	UFUNCTION()
	void OnRep_IsLeftHanded();
	
	void UpdateSignalSide();

	bool ShouldBeRotatedToOtherSide() const;

protected:
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< class UFGHologramBuildModeDescriptor > mBuildModeRightHanded;
	
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< class UFGHologramBuildModeDescriptor > mBuildModeLeftHanded;
	
private:
	UPROPERTY()
	const class UFGBuildableRailroadSignalSparseData* mSparseData;
	
	UPROPERTY()
	class UStaticMeshComponent* mSignalComponent;
	
	/** The track connection we snapped to. */
	UPROPERTY( Replicated, CustomSerialization )
	class UFGRailroadTrackConnectionComponent* mSnappedConnection;

	/** The track we snapped to. */
	UPROPERTY( Replicated, CustomSerialization )
	class AFGBuildableRailroadTrack* mSnappedRailroadTrack;

	/** The distance at which we snapped to the railroad track. */
	float mSnappedDistance;

	/** Do not set this directly, go through the setter so the mesh updates also. */
	UPROPERTY( ReplicatedUsing = OnRep_IsLeftHanded )
	bool mIsLeftHanded;

	/** If we upgrade a signal to another type of signal, this is the signal we are replacing. */
	UPROPERTY( Replicated, CustomSerialization )
	class AFGBuildableRailroadSignal* mUpgradeTarget;
};

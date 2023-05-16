// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGFactoryBlueprintTypes.h"
#include "FGBlueprintHologram.generated.h"

/**
 * 
 */
UCLASS()
class AFGBlueprintHologram : public AFGFactoryHologram
{
	GENERATED_BODY()

public:
	AFGBlueprintHologram();
	
	void BeginPlay() override; 

	/// Begin Hologram Interface
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID NetConstructionID );
	virtual void PreHologramPlacement() override;
	virtual void PostHologramPlacement() override;
	virtual int32 GetRotationStep() const override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void CheckCanAfford(UFGInventoryComponent* inventory) override;
	virtual TArray< FItemAmount > GetCost(bool includeChildren) const override;
	virtual void GetSupportedBuildModes_Implementation( TArray< TSubclassOf< UFGHologramBuildModeDescriptor > >& out_buildmodes) const override;
	/// End Hologram Interface

	// Begin AFGBuildableHologram Interface
	virtual bool ShouldActorBeConsideredForGuidelines( class AActor* actor ) const override;
	// End AFGBuildableHologram Interface

	// Function called by buildgun in order to check whether or not it should hit blueprint proxies
	bool ShouldBuildGunHitProxies() const;

	void LoadBlueprintToOtherWorld();
	void DuplicateMeshComponentsFromBuildableArray( const TArray< AFGBuildable* >& buildables );
	void GenerateCollisionObjects( const TArray< AFGBuildable* >& buildables );
	void SetBlueprintDescriptor( class UFGBlueprintDescriptor* blueprintDesc ) { mBlueprintDescriptor = blueprintDesc; }
	
	USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName );

	// For use in the component duplicator for spline comp duplication when we need to have access the other components on the actor
	UPROPERTY()
	class AFGBuildable* mCurrentDuplicatingBuildable;

	// An array of all FGClearanceComponents that are created to act as cleareance objects
	UPROPERTY()
	TArray< UFGClearanceComponent* > mClearanceComponents;

	// A map containing the buildable (which is instantiated in the blueprint world) to the new root component that represents it visually
	// in the game world. This is used so we can place our collision components at a separate time onto the correct local space
	UPROPERTY()
	TMap< class AFGBuildable*, USceneComponent* > mBuildableToNewRoot;

	// Maps the BlueprintWorld buildable to an a corresponding "visual only" spline created for displaying the spline in the game world
	UPROPERTY()
	TMap< class AFGBuildable*, class USplineComponent* > mBlueprintWorldSplineToHoloSpline;

	UPROPERTY()
	UFGBlueprintDescriptor* mBlueprintDescriptor;

protected:
	/** Build mode for snapping to blueprint proxies. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< UFGHologramBuildModeDescriptor > mBlueprintSnapBuildMode;

	/** In case we snapped to a blueprint proxy, this is it. */
	UPROPERTY()
	class AFGBlueprintProxy* mSnappedProxy;

	/** Mesh representing the bounds of our blueprint. */
	UPROPERTY()
	class UStaticMeshComponent* mBlueprintBoundsMesh;

	FBox mLocalBounds;
};

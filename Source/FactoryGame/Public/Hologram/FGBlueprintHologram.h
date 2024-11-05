// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGFactoryBlueprintTypes.h"
#include "FGBlueprintHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBlueprintHologram : public AFGFactoryHologram
{
	GENERATED_BODY()

public:
	AFGBlueprintHologram();
	
	void BeginPlay() override;
	
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/// Begin Hologram Interface
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID NetConstructionID );
	virtual void PreHologramPlacement( const FHitResult& hitResult ) override;
	virtual void PostHologramPlacement( const FHitResult& hitResult ) override;
	virtual int32 GetRotationStep() const override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void CheckCanAfford(UFGInventoryComponent* inventory) override;
	virtual TArray< FItemAmount > GetCost(bool includeChildren) const override;
	virtual void GetSupportedBuildModes_Implementation( TArray< TSubclassOf< UFGBuildGunModeDescriptor > >& out_buildmodes) const override;
	virtual bool ShouldSetupPendingConstructionHologram() const override { return false; }
	/// End Hologram Interface

	// Begin AFGBuildableHologram Interface
	virtual bool ShouldActorBeConsideredForGuidelines( class AActor* actor ) const override;
	// End AFGBuildableHologram Interface

	// Function called by buildgun in order to check whether or not it should hit blueprint proxies
	bool ShouldBuildGunHitProxies() const;

	void LoadBlueprintToOtherWorld();
	void DuplicateMeshComponentsFromBuildableArray( const TArray< AFGBuildable* >& buildables );
	void CreateConnectionRepresentations( const TArray<AFGBuildable*>& buildables );
	void AlignBuildableRootWithBounds();
	
	void SetBlueprintDescriptor( class UFGBlueprintDescriptor* blueprintDesc );

	UFUNCTION()
	void OnRep_BlueprintDescName();
	
	USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName );

	// For use in the component duplicator for spline comp duplication when we need to have access the other components on the actor
	UPROPERTY()
	class AFGBuildable* mCurrentDuplicatingBuildable;

	// A map containing the buildable (which is instantiated in the blueprint world) to the new root component that represents it visually
	// in the game world. This is used so we can place our collision components at a separate time onto the correct local space
	UPROPERTY()
	TMap< class AFGBuildable*, USceneComponent* > mBuildableToNewRoot;

	// Maps the BlueprintWorld buildable to an a corresponding "visual only" spline created for displaying the spline in the game world
	UPROPERTY()
	TMap< class AFGBuildable*, class USplineComponent* > mBlueprintWorldSplineToHoloSpline;

	UPROPERTY()
	UFGBlueprintDescriptor* mBlueprintDescriptor;

	UPROPERTY( ReplicatedUsing=OnRep_BlueprintDescName )
	FString mBlueprintDescName;
	
	DECLARE_DELEGATE_ThreeParams( FCreateBuildableVisualizationDelegate, AFGBlueprintHologram* /* blueprintHologram */, AFGBuildable* /* buildable */, USceneComponent* /* buildableRootComponent */ );

	/**
	 * Registers a custom visualizer for this buildable's hologram inside of the blueprint
	 * The default behavior is that your buildable will get all of the relevant components copied and attached to the root component,
	 * but if your hologram has some advanced logic it might need to do more setup based on the already built buildable
	 */
	static void RegisterCustomBuildableVisualization( TSubclassOf<AFGBuildable> inBuildable, const FCreateBuildableVisualizationDelegate& inDelegate );
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

	/** Mesh representing the forward direction of our blueprint. */
	UPROPERTY()
	class UStaticMeshComponent* mBlueprintDirectionMesh;

	FBox mLocalBounds;
	
	FVector mLocalBoundsOffset;

	static TMap<FTopLevelAssetPath, FCreateBuildableVisualizationDelegate> RegisteredCustomVisualizers;

	static bool FindCustomVisualizer( TSubclassOf<AFGBuildable> buildableClass, FCreateBuildableVisualizationDelegate& outVisualizer );
};

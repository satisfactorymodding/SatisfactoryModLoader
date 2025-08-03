// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGFactoryBlueprintTypes.h"
#include "Components/SplineComponent.h"
#include "FGBlueprintOpenConnectionManager.h"
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
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID NetConstructionID ) override;
	virtual void PreHologramPlacement( const FHitResult& hitResult, bool callForChildren ) override;
	virtual void PostHologramPlacement( const FHitResult& hitResult, bool callForChildren ) override;
	virtual int32 GetRotationStep() const override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual TArray< FItemAmount > GetBaseCost() const override;
	virtual void GetSupportedBuildModes_Implementation( TArray< TSubclassOf< UFGBuildGunModeDescriptor > >& out_buildmodes) const override;
	virtual bool ShouldSetupPendingConstructionHologram() const override { return false; }
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual bool CanTakeNextBuildStep() const override;
	virtual bool ShouldUnlockHologramOnBuildStep() const override;
	virtual void GetHologramsToShareMaterialStateWith( TArray< AFGHologram* >& out_holograms ) const override;
	virtual void OnNearbyBuildableOverlapBegin( class AFGBuildable* buildable ) override;
	virtual void OnNearbyBuildableOverlapEnd( class AFGBuildable* buildable ) override;
	virtual void OnBuildModeChanged( TSubclassOf<UFGHologramBuildModeDescriptor> buildMode ) override;
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	virtual void PostConstructMessageDeserialization() override;
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

	TSubclassOf< UFGHologramBuildModeDescriptor > GetBridgeHologramBuildModeOverride() const { return mBridgeHologramBuildModeOverride; }
	TSubclassOf<class UFGRecipe> GetAutomaticConnectionSwitchControlRecipe() const { return mAutomaticConnectionSwitchControlRecipe; }

	UFUNCTION()
	void OnRep_BlueprintDescName();
	
	USceneComponent* SetupBuildableComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName );
	USceneComponent* SetInstanceDataBuildableComponent( USceneComponent* attachParent, const FInstanceData& instanceData );

	template< class ConnectionClass >
	ConnectionClass* DuplicateConnectionComponent( class AFGBuildable* parentBuildable, ConnectionClass* connectionComponent );

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
	template< class ManagerClass >
	void RegisterOpenConnectionManager();

	bool AreAutomaticConnectionsEnabled() const;

	virtual void ApplyCustomizationData() override;

private:
	UFUNCTION()
	void OnOpenConnectionStateChanged( const TArray< class UFGConnectionComponent* >& connections, class UFGConnectionComponent* previousTargetConnection, class UFGConnectionComponent* newTargetConnection, bool isValid );
	
protected:	
	/** Build mode for snapping to blueprint proxies. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< UFGHologramBuildModeDescriptor > mBlueprintSnapBuildMode;

	/** Build mode for enabling automatic connections. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< UFGHologramBuildModeDescriptor > mBlueprintAutoConnectBuildMode;

	/** Build mode for snapping to blueprint proxies and enabling automatic connections. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< UFGHologramBuildModeDescriptor > mBlueprintSnapAutoConnectBuildMode;

	/** Build mode to use on bridge holograms. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< UFGHologramBuildModeDescriptor > mBridgeHologramBuildModeOverride;

	/** Switch control recipe to use when automatically connecting open ended railroad tracks in the blueprint. */
	UPROPERTY( EditDefaultsOnly, Category = "Tracks" )
	TSubclassOf<class UFGRecipe> mAutomaticConnectionSwitchControlRecipe;

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

private:
	TArray< TUniquePtr< FGBlueprintOpenConnectionManagerBase > > mOpenConnectionManagers;

	TMap< class UFGConnectionComponent*, TArray< class UStaticMeshComponent* > > mConnectionRepresentationMeshes;

	UPROPERTY()
	TMap< class UFGConnectionComponent*, class UStaticMeshComponent* > mAutomaticConnectionRepresentationMap;

	UPROPERTY()
	TMap< class UFGConnectionComponent*, class UFGConnectionComponent* > mDuplicateConnectionToOriginalMap;
};

template<class ConnectionClass>
ConnectionClass* AFGBlueprintHologram::DuplicateConnectionComponent( AFGBuildable* parentBuildable, ConnectionClass* connectionComponent )
{
	ConnectionClass* duplicatedConnection = Cast< ConnectionClass >( SetupComponent( mBuildableToNewRoot[ parentBuildable ], connectionComponent, FName( FString::Printf(TEXT("%s_%s"), *parentBuildable->GetName(), *connectionComponent->GetName() ) ), NAME_None ) );

	mDuplicateConnectionToOriginalMap.Add( duplicatedConnection, connectionComponent );
	
	return duplicatedConnection;
}

template<class ManagerClass>
void AFGBlueprintHologram::RegisterOpenConnectionManager()
{
	static_assert( std::is_base_of_v< FGBlueprintOpenConnectionManagerBase, ManagerClass > && !std::is_same_v< FGBlueprintOpenConnectionManagerBase, ManagerClass >, "ManagerClass must inherit from FGBlueprintOpenConnectionManagerBase.");

	TUniquePtr<FGBlueprintOpenConnectionManagerBase> newManager( reinterpret_cast< FGBlueprintOpenConnectionManagerBase* >( new ManagerClass( this ) ) );
	newManager->mOnConnectionStateChanged.AddUObject( this, &AFGBlueprintHologram::OnOpenConnectionStateChanged );
	
	mOpenConnectionManagers.Emplace( MoveTemp( newManager ) );
}
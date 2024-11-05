// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildable.h"
#include "FGCircuit.h"
#include "FGBuildableWire.generated.h"

// This struct represents a single wire between connections. One connection can be connected with multiple wires.
USTRUCT()
struct FWireInstance
{
	GENERATED_BODY()

	FWireInstance()
		: WireMesh( nullptr )
	{}
	
	UPROPERTY()
	UStaticMeshComponent* WireMesh;

	UPROPERTY( SaveGame )
	FVector Locations[2];

	UPROPERTY( SaveGame )
	FVector CachedRelativeLocations[2];
};

/**
 * A wire that connects to wire connection components.
 * This is an edge in a circuit graph.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableWire : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableWire();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Serialize( FArchive& ar ) override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface

	// Begin Buildable interface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	virtual bool ShouldBeConsideredForBase_Implementation() override;
	virtual void StartIsLookedAtForDismantle_Implementation(AFGCharacterPlayer* byCharacter) override;

	virtual TSoftClassPtr<UFGMaterialEffect_Build> GetBuildEffectTemplate_Implementation() const override;
	virtual TSoftClassPtr<UFGMaterialEffect_Build> GetDismantleEffectTemplate_Implementation() const override;
	// End Buildable interface

	/** @return The distance between the points the wire connects. */
	UFUNCTION( BlueprintPure, Category = "Buildable|Wire" )
	FORCEINLINE float GetLength() const { return mCachedLength; }

	/** @return The connection connected at the end of the wire. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Buildable|Wire" )
	FORCEINLINE class UFGCircuitConnectionComponent* GetConnection( int32 index ) const { return index == 0 || index == 1 ? mConnections[ index ].Get() : nullptr; }

	/** @return The cached and replicated location of the connection at the end of the wire. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Buildable|Wire" )
	FORCEINLINE FVector GetConnectionLocation( int32 index ) const { return index == 0 || index == 1 ? mConnectionLocations[ index ] : GetActorLocation(); }
	
	/**
	 * Get connection at the other end of the wire.
	 * @param connection Connection at our end of the wire.
	 * @return The connection at the other end of the wire, may be nullptr for dangling wires.
	 */
	class UFGCircuitConnectionComponent* GetOppositeConnection( const class UFGCircuitConnectionComponent* connection ) const;

	/**
	 * Helper function to disconnect this wire.
	 * Note: This only disconnects the wire but do not destroy it, call TurnOffAndDestroy to disconnect and remove a wire.
	 */
	void Disconnect();

	/** Debug */
	void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos );

	/** Read only access to the tag of the wire mesh */
	FORCEINLINE static const FName& GetWireMeshTag(){ return AFGBuildableWire::mWireMeshTag; }

	/** Internal helper function to connect this wire. */ //[DavalliusA:Sun/16-02-2020] moved this out as it was needed for upgrades. If there is a reason to hide it, please make that clear, or I won't know why not to expose it.
	bool Connect( class UFGCircuitConnectionComponent* first, class UFGCircuitConnectionComponent* second );

	/** Gets the wire instances of this wire. */
	FORCEINLINE const TArray< FWireInstance >& GetWireInstances() const { return mWireInstances; }

	FORCEINLINE UStaticMesh* GetWireMesh() const { return mWireMesh; }

	/** Returns the wire instance this mesh component belongs to. Returns nullptr if none was found. */
	const FWireInstance* GetWireInstanceForMeshComponent( const UStaticMeshComponent* meshComponent ) const;

	UFUNCTION( BlueprintPure, Category = "Buildable|Wire")
	TArray< UStaticMeshComponent* > GetWireInstanceMeshes() const;

	static void CreateWireInstancesBetweenConnections( TArray< FWireInstance >& out_instances, class UFGCircuitConnectionComponent* first, class UFGCircuitConnectionComponent* second, const FTransform& WireTransform );

	static FWireInstance CreateWireInstance( const FVector& FirstLocation, const FVector& SecondLocation, const FTransform& WireTransform );

	static void UpdateWireInstanceMesh( const FWireInstance& WireInstance );
	
private:

	/**
	 * Internal helper function to see if this wire is connected.
	 * @return true if either side of the wire is connected; false if no side is connected.
	 */
	bool IsConnected() const;

	UFUNCTION()
	void OnRep_Connections();

	UStaticMeshComponent* CreateNewWireMesh();

	void DestroyWireInstances();

	void UpdateWireMeshes();
public:
	/** Maximum length a wire may be. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Wire" )
	float mMaxLength;

	/** Maximum length a wire may be when using power tower connections. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Wire" )
	float mMaxPowerTowerLength;

	/** How much length we get per unit cost, 0 to disable per length cost. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Wire" )
	float mLengthPerCost;

protected:
	/** Circuit type this wire is used for. Can only be one, e.g. power or logic. */
	UPROPERTY( EditDefaultsOnly, Category = "Wire" )
	TSubclassOf< UFGCircuit > mCircuitType;

	/** Mesh used to visualize the power line */
	UPROPERTY( EditDefaultsOnly, Category = "Wire" )
	UStaticMesh* mWireMesh;

private:
	friend class AFGWireHologram;

	/** The tag used to identify the wire mesh. */
	static FName mWireMeshTag;

	/**
	 * The connections made by this wire.
	 * Weak references as buildings can be removed and leave the cables hanging.
	 * This is for mod stability or just different lifespan when dismantling building and wires.
	 */
	UPROPERTY( ReplicatedUsing = OnRep_Connections )
	TWeakObjectPtr< class UFGCircuitConnectionComponent > mConnections[ 2 ];

	/** The cached end locations of this wire. */
	UPROPERTY( Replicated )
	FVector mConnectionLocations[ 2 ];

	/** The wires between the two connections. */
	UPROPERTY( SaveGame )
	TArray< FWireInstance > mWireInstances;

	/** Cached length of the wire, distance between connections. */
	UPROPERTY( SaveGame )
	float mCachedLength;
};

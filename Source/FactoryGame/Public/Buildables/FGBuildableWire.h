// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildable.h"
#include "FGCircuit.h"
#include "FGBuildableWire.generated.h"

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
	// End Buildable interface

	/** @return The distance between the points the wire connects. */
	UFUNCTION( BlueprintPure, Category = "Buildable|Wire" )
	FORCEINLINE float GetLength() const { return FVector::Distance( mLocations[ 0 ], mLocations[ 1 ] ); }

	/** Location of point 0 or 1 */
	FORCEINLINE FVector GetLocation( int32 index ) const { return mLocations[ FMath::Min( index, 1  ) ]; }

	/** @return The connection connected at the end of the wire. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Buildable|Wire" )
	FORCEINLINE class UFGCircuitConnectionComponent* GetConnection( int32 index ) const { return index == 0 || index == 1 ? mConnections[ index ].Get() : nullptr; }

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

	void UpdateWireMesh();

	/** Internal helper function to connect this wire. */ //[DavalliusA:Sun/16-02-2020] moved this out as it was needed for upgrades. If there is a reason to hide it, please make that clear, or I won't know why not to expose it.
	bool Connect( class UFGCircuitConnectionComponent* first, class UFGCircuitConnectionComponent* second );

private:

	/**
	 * Internal helper function to see if this wire is connected.
	 * @return true if either side of the wire is connected; false if no side is connected.
	 */
	bool IsConnected() const;

	UFUNCTION()
	void OnRep_Locations();
public:
	/** Maximum length a wire may be. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Wire" )
	float mMaxLength;

	/** How much length we get per unit cost, 0 to disable per length cost. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Wire" )
	float mLengthPerCost;

protected:
	/** Circuit type this wire is used for. Can only be one, e.g. power or logic. */
	UPROPERTY( EditDefaultsOnly, Category = "Wire" )
	TSubclassOf< UFGCircuit > mCircuitType;

	/** Mesh used to visualize the power line */
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = "Wire" )
	UStaticMeshComponent* mWireMesh;

private:
	friend class AFGWireHologram;

	/** The tag used to identify the wire mesh. */
	static FName mWireMeshTag;

	/**
	 * The connections made by this wire.
	 * Weak references as buildings can be removed and leave the cables hanging.
	 * This is for mod stability or just different lifespan when dismantling building and wires.
	 */
	UPROPERTY( Replicated )
	TWeakObjectPtr< class UFGCircuitConnectionComponent > mConnections[ 2 ];

	/** The two locations this wire span. */
	UPROPERTY( ReplicatedUsing = OnRep_Locations, Meta = (NoAutoJson = true))
	FVector mLocations[ 2 ];
};

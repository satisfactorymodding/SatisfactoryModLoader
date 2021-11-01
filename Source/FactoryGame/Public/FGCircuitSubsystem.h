// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "Buildables/FGBuildableCircuitBridge.h"
#include "UI/Message/FGMessageBase.h"
#include "FGCircuitSubsystem.generated.h"

/**
 * Message to be displayed when the sum stored battery power of a circuit has had a certain share depleted
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGCriticalBatteryDepletionMessage : public UFGMessageBase
{
	GENERATED_BODY()
public:
	UFGCriticalBatteryDepletionMessage();

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Power" )
	float GetCriticalBatteryDepletionPercent() const { return mCriticalBatteryDepletionPercent; }

private:
	float mCriticalBatteryDepletionPercent = 0.0f;
};

/**
 * Subsystem to handle all circuits, connects, disconnects.
 */
UCLASS( Blueprintable, abstract, hidecategories = ( Actor, Input, Replication, Rendering, "Actor Tick" ) )
class FACTORYGAME_API AFGCircuitSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
	
public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual bool ReplicateSubobjects( class UActorChannel* channel, class FOutBunch* bunch, FReplicationFlags* repFlags ) override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;
	virtual void CallPreReplication(UNetDriver* NetDriver) override;

	/** Get the circuit subsystem. */
	static AFGCircuitSubsystem* Get( UWorld* world );

	/** Get the circuit subsystem */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGCircuitSubsystem* GetCircuitSubsystem( UObject* worldContext );

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	AFGCircuitSubsystem();

	// Begin AActor interface
	virtual void Serialize( FArchive& ar ) override;
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	// End AActor interface

	/** Debug function to trigger a rebuild on all circuits. */
	void DebugRebuildAll();

	/**
	 * ShowDebug POWER
	 * @see Super
	 */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

	/**
	 * Find the circuit with the given circuit ID.
	 * @return - The circuit if found; nullptr if no circuit exists with that id.
	 *
	 * @note The returned pointer is only valid this tick or until a change is made to the circuitry by calling CreateCircuit, RemoveCircuit, ConnectComponents.
	 */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Circuits" )
	FORCEINLINE class UFGCircuit* FindCircuit( int32 circuitID ) const { return mCircuits.FindRef( circuitID ); }

	/** Template version of find circuit. */
	template< class T >
	FORCEINLINE T* FindCircuit( int32 circuitID ) const { return Cast< T >( FindCircuit( circuitID ) ); }

	/**
	 * Make a connection between two connection components.
	 * Forming or merging circuits as needed.
	 *
	 * @param first - First connection component.
	 * @param second - Second connection component.
	 *
	 * @note This invalidates any pointers to a circuit.
	 */
	void ConnectComponents( class UFGCircuitConnectionComponent* first, class UFGCircuitConnectionComponent* second );

	/**
	 * Break a connection between two connection components.
	 *
	 * @param first - First connection component.
	 * @param second - Second connection component.
	 *
	 * @note Multiple calls to this functions the same frame only triggers one rebuild.
	 */
	void DisconnectComponents( class UFGCircuitConnectionComponent* first, class UFGCircuitConnectionComponent* second );

	/**
	 * Removes a connection component from it's circuit. E.g. when the connection component is destroyed.
	 *
	 * @param connection - Connection component to remove.
	 *
	 * @note If the connection component does not have a valid circuit ID this does nothing.
	 */
	void RemoveComponent( class UFGCircuitConnectionComponent* component );

	void SetCircuitBridgesModified();
	void AddCircuitBridge( TWeakObjectPtr< AFGBuildableCircuitBridge > circuitBridge );
	void RemoveCircuitBridge( TWeakObjectPtr< AFGBuildableCircuitBridge > circuitBridge );

	class UFGCircuitGroup* GetCircuitGroup( int32 circuitGroupId ) { return mCircuitGroups[ circuitGroupId ]; }

	/** Called when a power circuit lost power. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Circuits|Power" )
	void PowerCircuit_OnFuseSet();

	/** Called when a power circuit had it's power restored. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Circuits|Power" )
	void PowerCircuit_OnFuseReset();

	/** Called when the batteries have depleted a certain share of their capacity. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Circuits|Power" )
	void PowerCircuit_OnCriticalBatteryDepletion( float depletionPercent );

	/** Debugging function to dump stats of all circuits to the log */
	void Debug_DumpCircuitsToLog();

	/** Event that will fire whenever one or more circuits have changed */
	DECLARE_EVENT( AFGCircuitSubsystem, FOnCircuitsChanged )
	FOnCircuitsChanged OnCircuitsChangedEvent;
	
private:
	/** Let the clients know about changes in the circuits. */
	UFUNCTION()
	void OnRep_ReplicatedCircuits();

	/** Get a new unique ID. */
	int32 GenerateUniqueCircuitID();

	/** Internal helpers to manage circuits. */
	void MergeCircuits( int32 first, int32 second );
	int32 CreateCircuit( TSubclassOf< class UFGCircuit > circuitClass );
	int32 SplitCircuit( const UFGCircuit* circuit );
	void RemoveCircuit( int32 circuitID );

	void RebuildCircuitGroups();

	/**
	 * Internal helper to rebuild a circuit.
	 * Note: This function might split, remove or otherwise change the circuit so it is not safe to assume anything about the circuit afterwards.
	 */
	void RebuildCircuit( int32 circuitID );

	/** Adds a connection component to a circuit, performs a circuit merge if the component is already connected to another circuit. */
	void AddComponentToCircuit( class UFGCircuitConnectionComponent* component, int32 circuitID, bool rebuildTrivialCircuits );
	/** Removes a connection component from it's circuit. If the connection component does not have a valid circuit ID this does nothing. */
	void RemoveComponentFromCircuit( class UFGCircuitConnectionComponent* component );

public:
	/**
	* Power circuits: the share of the battery capacity that can be depleted before a warning is raised, in the interval [0.0, 1.0].
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Power Circuit")
	float mCriticalBatteryDepletionPercent = 0.25f;

	/**
	* Power circuits: the minimum time that has to pass between battery warnings, in minutes.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Power Circuit")
	float mMinimumBatteryWarningInterval = 10.0f;

private:
	/** Map with all circuits and the circuit ID as the key. */
	UPROPERTY()
	TMap< int32, class UFGCircuit* > mCircuits;

	/** @todo There is no support for TMap replication, fix something better than this. */
	UPROPERTY( ReplicatedUsing = OnRep_ReplicatedCircuits )
	TArray< class UFGCircuit* > mReplicatedCircuits;

	/** Counter for generating new circuit ids. */
	int32 IDCounter;

	TSet< TWeakObjectPtr< AFGBuildableCircuitBridge > > mCircuitBridges;
	bool mIsCircuitGroupsDirty;

	UPROPERTY()
	TArray< class UFGCircuitGroup* > mCircuitGroups;
};

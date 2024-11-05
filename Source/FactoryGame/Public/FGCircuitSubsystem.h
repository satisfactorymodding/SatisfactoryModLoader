// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGPowerCircuit.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "Buildables/FGBuildableCircuitBridge.h"
#include "UI/Message/FGMessageBase.h"
#include "FGCircuitSubsystem.generated.h"

DECLARE_STATS_GROUP( TEXT( "CircuitSubsystem" ), STATGROUP_CircuitSubsystem, STATCAT_Advanced );

USTRUCT()
struct FPowerCircuitFuseStabilityData
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr< AFGPlayerController > FuseResetInstigator = nullptr;
	
	int32 CircuitID;
		
	FTimerHandle TimerHandle;
};

/**
 * Subsystem to handle all circuits, connects, disconnects.
 */
UCLASS( Blueprintable, abstract, hidecategories = ( Actor, Input, Replication, Rendering, "Actor Tick" ) )
class FACTORYGAME_API AFGCircuitSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGCircuitSubsystem();
	
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;

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

	// Begin AActor interface
	virtual void Serialize( FArchive& ar ) override;
	static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);
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

	/**
	 * Schedule a rebuild of the circuit-groups structure
	 */
	void SetCircuitBridgesModified();

	/**
	 * Add a bridge that will act as a delimiter of circuits (and optionally a delimiter of circuit groups)
	 */
	void AddCircuitBridge( TWeakObjectPtr< AFGBuildableCircuitBridge > circuitBridge );

	/**
	 * Remove a circuit bridge
	 */
	void RemoveCircuitBridge( TWeakObjectPtr< AFGBuildableCircuitBridge > circuitBridge );

	/**
	 * @param circuitGroupId Must be a valid circuit group id.
	 * @return the circuit group with the given id.
	 */
	class UFGCircuitGroup* GetCircuitGroup( int32 circuitGroupId ) { return mCircuitGroups[ circuitGroupId ]; }

	/** Called when a power circuit lost power. */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Circuits|Power" )
	void PowerCircuit_OnFuseSet( const TArray< class UFGPowerCircuit* >& circuits );

	/** Called when a power circuit had it's power restored. */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Circuits|Power" )
	void PowerCircuit_OnFuseReset( const TArray< class UFGPowerCircuit* >& circuits, class AFGPlayerController* fuseResetInstigator = nullptr );

	/** Called when a power circuit had it's power restored. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Circuits|Power" )
	void PowerCircuit_OnPrioritySwitchesTurnedOff( int32 priority );

	/** Called when the batteries have depleted a certain share of their capacity. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Circuits|Power" )
	void PowerCircuit_OnCriticalBatteryDepletion( float depletionPercent );

	/** Allow power circuits to keep track of all the */
	void PowerCircuit_RegisterPriorityPowerSwitchInfo( class AFGPriorityPowerSwitchInfo* info );
	void PowerCircuit_UnregisterPriorityPowerSwitchInfo( class AFGPriorityPowerSwitchInfo* info );
	
	/** Get all the other power switch infos. Not only the ones belonging to this circuit. Can be called on Client and Server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|Power" )
	TArray< AFGPriorityPowerSwitchInfo* > PowerCircuit_GetPriorityPowerSwitchInfos() const;
	
	/** Helper to sort a list of infos by their given name in ascending order. Can be called on Client and Server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|Power" )
	void PowerCircuit_SortPriorityPowerSwitchInfos( TArray< AFGPriorityPowerSwitchInfo* >& infos ) const;
	
	/** Switch all the priority switches in the given priority to on or off. Only valid to call on Server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|Power" )
	void PowerCircuit_SetPrioritySwitchGroupOn( int32 priority, bool on );
	
	/** Debugging function to dump stats of all circuits to the log */
	void Debug_DumpCircuitsToLog();
	
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

	/** Rebuild the circuit-group structure. */
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

	/** Called when a power circuit is considered stable. */
	void OnPowerCircuitStable( AFGPlayerController* fuseResetInstigator ) const;

	void RemovePowerCircuitStabilityData( int32 circuitID );

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPowerPrioritySwitchAdded, class AFGPriorityPowerSwitchInfo*, info );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnStructuralChange );
	
	/**
	 * Power circuits: the share of the battery capacity that can be depleted before a warning is raised, in the interval [0.0, 1.0].
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Power Circuit" )
	float mCriticalBatteryDepletionPercent = 0.25f;

	/**
	 * Power circuits: the minimum time that has to pass between battery warnings, in minutes.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Power Circuit" )
	float mMinimumBatteryWarningInterval = 10.0f;
	
	/** Called when a switch has been added, on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "Power Circuit" )
	FOnPowerPrioritySwitchAdded mOnPowerPrioritySwitchAddedDelegate;

	/**
	 * Called when structural changes occured in the circuits. Server and Client.
	 * This can happen for example when a wire is added or removed.
	 * If this is triggered then OnCircuitGroupsRebuilt will also be triggered, but not the other way around.
	 */
	UPROPERTY( BlueprintAssignable, Category = "Circuit" )
	FOnStructuralChange mOnCircuitsRebuiltDelegate;
	/**
	 * Called when structural changes occured in the circuit groups. Server and Client.
	 * Called when structural changes occured in the circuit groups. Server and Client.
	 * This can happen when a circuit is rebuilt or when a switch is flipped.
	 */
	UPROPERTY( BlueprintAssignable, Category = "Circuit" )
	FOnStructuralChange mOnCircuitGroupsRebuiltDelegate;
	
private:
	/** Map with all circuits and the circuit ID as the key. */
	UPROPERTY()
	TMap< int32, class UFGCircuit* > mCircuits;

	//@todo-power This name is misleading now, but hey it works. This is rebuild or changed.
	/** Set if the circuits have been rebuilt this frame so we know if we need to trigger any delegates. */
	bool mHaveCircuitsBeenRebuilt;

	/** There is no support for TMap replication so this is a duplicate of mCircuits in a simple array. */
	UPROPERTY( ReplicatedUsing = OnRep_ReplicatedCircuits )
	TArray< class UFGCircuit* > mReplicatedCircuits;

	/** Counter for generating new circuit ids. */
	int32 IDCounter;
	
	/**
	 * List of all the circuit bridges. They work as delimiters of circuits.
	 * If they are on, they are not delimiters of circuit groups. If they are off, they are delimiter of circuit groups.
	 */
	TSet< TWeakObjectPtr< AFGBuildableCircuitBridge > > mCircuitBridges;

	/** A list of circuits groups. Circuit groups logically work as one circuit. */
	UPROPERTY()
	TArray< class UFGCircuitGroup* > mCircuitGroups;

	/** Used to keep track of rebuilds during tick. */
	bool mAreCircuitGroupsDirty;
	
	/** Set if the circuit groups have been rebuilt this frame so we know if we need to trigger any delegates. */
	bool mHaveCircuitGroupsBeenRebuilt;

	/** Power circuits: all the priority switches in the world. */
	UPROPERTY( Replicated )
	TArray< class AFGPriorityPowerSwitchInfo* > mPriorityPowerSwitchInfos;

	/** Power circuits: Fuse stability timer data. Key is Circuit ID */
	UPROPERTY()
	TMap< int32, FPowerCircuitFuseStabilityData > mPowerCircuitStabilityData;

	/** The amount of time to wait before a power circuit is considered "stable" after resetting the fuse. */
	UPROPERTY( EditDefaultsOnly, Category = "Power Circuit" )
	float mPowerCircuitStabilityTimeRequirement;
};

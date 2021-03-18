// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGSaveInterface.h"
#include "FGCircuit.generated.h"

/**
 * Abstract base for circuit implementations.
 * 
 * Represents and circuit.
 * It keeps track of which components are connected to the same circuit.
 * We can say that A and B are connected (indirectly or directly) but not if there is a wire directly between A and B.
 * The actual connection info is stored in the graph that is made up by all the components (nodes) and wires (edges).
 * 2 or more components are required to make up a circuit. It's not much of a circuit if you're the only one in it!
 */
UCLASS( Abstract, Blueprintable )
class FACTORYGAME_API UFGCircuit : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual bool IsSupportedForNetworking() const override;
	virtual bool IsNameStableForNetworking() const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker );

	UFGCircuit();

	/** Cleanup code */
	virtual void BeginDestroy() override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Get the subsystems world. */
	virtual UWorld* GetWorld() const override;

	/** @return This circuit's unique identifier; -1 if invalid. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Circuit" )
	FORCEINLINE int32 GetCircuitID() const { return mCircuitID; }

	/**
	 * Marks the circuit as changed or for a full rebuild (slow).
	 * @note Do not call this unless you know what you're doing.
	 */
	void MarkAsChanged();
	void MarkForFullRebuild();

	/** Haxx to be able to disable replication when no one is looking at the circuit */
	void RegisterInteractingPlayer( class AFGCharacterPlayer* player );
	void UnregisterInteractingPlayer( class AFGCharacterPlayer* player );

	/** @return true if this circuit is replicating detailed information about it; false otherwise. */
	bool IsReplicatingDetails() const { return mReplicateDetails; }

	int32 GetCircuitGroupID() { return mCircuitGroupId; }

	TArray< class UFGCircuitConnectionComponent* >& GetComponents() { return mComponents; }

	/** Logs the internal state of this circuit. */
	void Debug_LogState() const;

	/**
	 * @return true if this circuit can be removed without any impact on game logic, false otherwise.
	*/
	virtual bool IsTrivial() const;

	/**
	 * Called just after this circuit has been removed from the subsystem
	 */
	virtual void OnRemoved() {}

protected:
	/** Checks if our outer has authority, and assumes that if they have, then so do we. */
	bool HasAuthority() const;

	/** Get the circuit subsystem that owns us. */
	class AFGCircuitSubsystem* GetOwningCircuitSubsystem() const;

	/** Called when the circuit is ticked. */
	virtual void TickCircuit( float dt );

	/** Called by the circuit subsystem when changes are made to the circuitry. */
	virtual void OnCircuitChanged();

	/** @return a newly created circuit of the same type as this circuit, preserving some of the state of this circuit. Will be nullptr if not overridden. */
	virtual UFGCircuit* SplitCircuit( AFGCircuitSubsystem* subsystem ) const { return nullptr; }
	
	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos, float indent );

private:
	/** Set if we should replicate details. */
	void SetReplicateDetails( bool replicateDetails );

	virtual UFGCircuitGroup* CreateCircuitGroup( AFGCircuitSubsystem* subsystem ) const { return nullptr; }

protected:
	/** The id used to identify this circuit. */
	UPROPERTY( SaveGame, Replicated )
	int32 mCircuitID;

	/** List of all the components (nodes) in this circuit. */
	UPROPERTY( SaveGame )
	TArray< class UFGCircuitConnectionComponent* > mComponents;

	/** Do this circuit needs to be rebuilt, e.g. wires or components have been removed. */
	UPROPERTY()
	uint8 mNeedFullRebuild:1;

	/** True if this circuit has changed. */
	UPROPERTY()
	uint8 mHasChanged:1;

	/** If this buildable is replicating details, i.e. for the UI. */
	uint8 mReplicateDetails : 1;

	int32 mCircuitGroupId;
private:
	friend class AFGCircuitSubsystem;
	friend class UFGCheatManager;

	/** All players interacting with a building that's connected to this circuit */
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mInteractingPlayers;
};

UCLASS( Abstract )
class FACTORYGAME_API UFGCircuitGroup : public UObject
{
	GENERATED_BODY()
public:
	virtual void PushCircuit( UFGCircuit* circuit ) { }
	virtual void Reset() { }
	/**
	* Make structural changes to the circuit group as needed.
	* @returns true if such changes were made that the circuit groups need to be rebuilt and pre-tick restarted, false otherwise.
	*/
	virtual bool PreTickCircuitGroup( float dt, bool hasAuthority ) { return false; }
	virtual void TickCircuitGroup( float dt, bool hasAuthority ) { }
	//~ Begin UFGCircuitGroup -> AFGBuildableCircuitSwitch visitor pattern
	virtual void VisitCircuitBridge( class AFGBuildableCircuitBridge* circuitBridge ) { }
	//~ End UFGCircuitGroup -> AFGBuildableCircuitSwitch visitor pattern
};

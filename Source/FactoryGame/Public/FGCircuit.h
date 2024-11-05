// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Replication/FGConditionalReplicationInterface.h"
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
class FACTORYGAME_API UFGCircuit : public UObject, public IFGSaveInterface, public IFGConditionalReplicationInterface
{
	GENERATED_BODY()
public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual bool IsSupportedForNetworking() const override;
	virtual bool IsNameStableForNetworking() const override;

	UFGCircuit();

	// Begin UObject interface
	virtual void BeginDestroy() override;
	// End UObject interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin IFGConditionalReplicationInterface
	virtual bool IsPropertyRelevantForConnection(UNetConnection* netConnection, const FProperty* property) const override;
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	// End IFGConditionalReplicationInterface
	
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

	/** Hax to be able to disable replication when no one is looking at the circuit */
	void RegisterInteractingPlayer( class AFGCharacterPlayer* player );
	void UnregisterInteractingPlayer( class AFGCharacterPlayer* player );
	
	/** @return the group this circuit belongs too. */
	int32 GetCircuitGroupID() const { return mCircuitGroupID; }

	/** @return All components that are part of this circuit, this data might change when circuits are rebuilt. */
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
	virtual class UFGCircuitGroup* CreateCircuitGroup( AFGCircuitSubsystem* subsystem ) const { return nullptr; }

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
	
	/** Which group does this circuit belong too. */
	int32 mCircuitGroupID;

	/** Property replicator handles the replication of conditionally replicated properties */
	UPROPERTY( Replicated, Transient, meta = ( FGPropertyReplicator ) )
	FFGConditionalPropertyReplicator mPropertyReplicator;
private:
	friend class AFGCircuitSubsystem;
	friend class UFGCheatManager;

	/** All players interacting with a building that's connected to this circuit */
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mInteractingPlayers;
};

/**
 * Abstract groups for circuits logically working as a single circuit
 */
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
	virtual bool PreTickCircuitGroup( float dt ) { return false; }
	virtual void TickCircuitGroup( float dt ) { }
	
	//~ Begin UFGCircuitGroup -> AFGBuildableCircuitSwitch visitor pattern
	virtual void VisitCircuitBridge( class AFGBuildableCircuitBridge* circuitBridge ) { }
	//~ End UFGCircuitGroup -> AFGBuildableCircuitSwitch visitor pattern

	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos, float indent ) { }
};

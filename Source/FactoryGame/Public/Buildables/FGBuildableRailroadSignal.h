// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGBuildable.h"
#include "FGRailroadSignalBlock.h"
#include "FGRailroadTrackConnectionComponent.h"
#include "FGTrain.h"
#include "FGBuildableRailroadSignal.generated.h"

class UStaticMesh;

UCLASS( EditInlineNew )
class FACTORYGAME_API UFGBuildableRailroadSignalSparseData : public UObject
{
	GENERATED_BODY()
public:
	/** Properties for right handed signals (game default). */
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mRightHandedMesh;
	UPROPERTY( EditDefaultsOnly )
	FTransform mRightHandedTransform;
	
	/** Properties for left handed signals. */
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mLeftHandedMesh;
	UPROPERTY( EditDefaultsOnly )
	FTransform mLeftHandedTransform;
};

/**
 * A signal for the railroad, these are placed on connection points and separate access to tracks by block signaling.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRailroadSignal : public AFGBuildable, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGBuildableRailroadSignal();
	
	// Begin Actor
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Destroyed() override;
	// End Actor

	// Begin FGBuildable
	virtual void OnBuildEffectFinished() override;
	virtual void OnBuildEffectActorFinished() override;
	virtual bool ShouldBeConsideredForBase_Implementation() override { return false; }
	// End FGBuildable

	// Begin SaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End SaveInterface

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	virtual	void SetupForSignificance() override;
	//End IFGSignificanceInterface

	// Begin IFGDismantleInterface
	virtual void PreUpgrade_Implementation() override;
	// End IFGDismantleInterface
	
	/** @return If this is significant. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	bool IsSignificant() const { return mIsSignificant; }
	
	/** Get the connections that are guarded by this signal. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	TArray< class UFGRailroadTrackConnectionComponent* > GetGuardedConnections() const { return mGuardedConnections; }

	/** Get the connections that are observed by this signal. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	TArray< class UFGRailroadTrackConnectionComponent* > GetObservedConnections() const { return mObservedConnections; }

	/**
	 * @return true if this signal have valid connections and can participate in blocks,
	 *         false if this signal do not have the required connections to participate in a block.
	 */
	bool HasValidConnections() const { return mGuardedConnections.Num() > 0 && mObservedConnections.Num() > 0; }
	
	/** Get the aspect this signal is showing. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	ERailroadSignalAspect GetAspect() const { return mAspect; }

	/** Get the block validation that was run on this block at construction, this will show if the block is not properly set up. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	ERailroadBlockValidation GetBlockValidation() const { return mBlockValidation; }

	/** @return true if this signal is observing a block, false if not. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	bool HasObservedBlock() const { return mObservedBlock.IsValid(); }
	
	/** @return The block observed by this signal, can be null. */
	TWeakPtr< FFGRailroadSignalBlock > GetObservedBlock() { return mObservedBlock; }

	/** @return Is this a path signal. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	bool IsPathSignal() const { return mIsPathSignal; }
	
	/** @return Is this signal bi-directional, true, or is it one-way, false. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	bool IsBiDirectional() const { return mIsBiDirectional; }

	/** @return true if this signal is left-handed, false if right-handed. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	bool IsLeftHanded() const { return mIsLeftHanded; }
	
	/** @return The visual state for this signals material. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	int32 GetVisualState() const { return mVisualState; }
	
	FORCEINLINE const UFGBuildableRailroadSignalSparseData* GetRailroadSignalSparesData() const { return mRailroadSignalSparesDataCDO; }
	
public:
	static const FName SIGNAL_MESH_COMPONENT_NAME;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnAspectChanged, ERailroadSignalAspect, aspect );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBlockValidationChanged, ERailroadBlockValidation, blockValidation );
	
	/** Called when the signals aspect changes. Called on server and client. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Railroad|Signal", DisplayName = "OnAspectChanged" )
	FOnAspectChanged mOnAspectChangedDelegate;

	/** Called when the block is validated. Called on server and client. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Railroad|Signal", DisplayName = "OnBlockValidationChanged" )
	FOnBlockValidationChanged mOnBlockValidationChangedDelegate;

#if WITH_EDITORONLY_DATA
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Signal" )
	UFGBuildableRailroadSignalSparseData* mRailroadSignalSparesData;
#endif

	UPROPERTY( )
	UFGBuildableRailroadSignalSparseData* mRailroadSignalSparesDataCDO;
	
protected:
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
	
	/** Called when the aspect of this signal has changed, can be called in some occasions when the aspect is still the same. */
	void OnAspectChanged();

	/** Called when the validation of this block has changed. */
	void OnBlockValidationChanged();

	/** Called when the bi-directionality changes. */
	void OnDirectionalityChanged();

	/** Called when the visual state changes. Only called if this signal is significant. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad|Signal" )
	void OnVisualStateChanged();

	/** Called when we want to draw debugging state. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad|Signal" )
	void OnDrawDebugVisualState();

private:
	/** Called when this signal is about to be removed. */
	void DisconnectSignal();
	
	/** Updates the material parameters of this signal. */
	void UpdateVisuals();
	void ApplyVisualState( int16 state );
	
	/** Called internally and by the hologram to add a guarded connection. */
	void AddGuardedConnection( class UFGRailroadTrackConnectionComponent* connection );
	/** Called internally to add an observed connection. */
	void AddObservedConnection( class UFGRailroadTrackConnectionComponent* connection );
	/** Update the connections this signal guards and observes. */
	void UpdateConnections();
	
	/** Manage the observed block, these are used by the subsystem. */
	void SetObservedBlock( TWeakPtr< FFGRailroadSignalBlock > block );

	/** Helper to update the aspect from the observed block. */
	void OnBlockChanged();

	/** On reps */
	UFUNCTION()
	void OnRep_Aspect();
	UFUNCTION()
	void OnRep_BlockValidation();
	UFUNCTION()
	void OnRep_VisualState();
	UFUNCTION()
	void OnRep_GuardedConnections(const TArray<UFGRailroadTrackConnectionComponent*>& oldGuardedConnections);
	UFUNCTION()
	void OnRep_ObservedConnections(const TArray<UFGRailroadTrackConnectionComponent*>& oldObservedConnections);

	/** Helpers to update the states of this signal. */
	void UpdateDirectionality();
	void UpdateAspect();
	void UpdateBlockValidation();
protected:
	/** Mesh for this signal, must be using the signal factory material for it to work. */
	UPROPERTY( VisibleAnywhere )
	UFGColoredInstanceMeshProxy* mSignalComponent;

	/** True if we should draw debug cubes visible from afar, also make the signals always significant, must be set before BeginPlay. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Debug|Signal" )
	bool mDrawDebugVisualState;
	
private:
	friend class AFGRailroadSignalHologram;
	friend class AFGRailroadSubsystem;

	/**
	 * @todo-trains This was forgotten about, do it when deemed safe. G2 2024-06-14
	 * DEPRECATED, replaced by mGuardedConnections so we can attach to switch connections.
	 * REMOVE BEFORE U5, when people internally have had a chance to re-save their games.
	 */
	UPROPERTY( SaveGame )
	class UFGRailroadTrackConnectionComponent* mOwningConnection;
	
	/**
	 * A signal can guard and observe many connections if placed on a switch.
	 * An observed connection is a connection inside the block this signal is observing.
	 * A guarded connection is a connection outside the block, this is the connection the self-driver interacts with to read the signal's aspect.
	 * A signal is set as:
	 *   The facing signal on its guarded connections.
	 *   The trailing signal on its observer connections.
	 *
	 *
	 * In the case of a signal on a straight track. (Signal direction is left to right)
	 * 
	 *          1 GUARDED CONNECTION
	 *              FOR BLOCK 2
	 *                   v
	 * o-----BLOCK 1-----o o-----BLOCK 2-----o
	 *                     ^
	 *                1 OBSERVED
	 *              BLOCK CONNECTION
	 *
	 * In the case of a signal going from 3 tracks merging into 1 track. (Signal direction is left to right)
	 *
	 *          3 GUARDED CONNECTIONS
	 *               FOR BLOCK 2
	 *                   v
	 * o-----BLOCK 1-----o
	 * o-----BLOCK 1-----o o-----BLOCK 2-----o
	 * o-----BLOCK 1-----o
	 *                     ^
	 *                 1 OBSERVED
	 *              BLOCK CONNECTION
	 *
	 * In the case of a signal going from 1 track splitting into 3 tracks. (Signal direction is left to right)
	 *
	 *          1 GUARDED CONNECTIONS
	 *               FOR BLOCK 2
	 *                   v
	 *                     o-----BLOCK 2-----o
	 * o-----BLOCK 1-----o o-----BLOCK 2-----o
	 *                     o-----BLOCK 2-----o
	 *                     ^
	 *                3 OBSERVED
	 *             BLOCK CONNECTION
	 */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_GuardedConnections )
	TArray< class UFGRailroadTrackConnectionComponent* > mGuardedConnections;
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_ObservedConnections )
	TArray< class UFGRailroadTrackConnectionComponent* > mObservedConnections;

	/** The signal block this signal observers. */
	TWeakPtr< FFGRailroadSignalBlock > mObservedBlock;

	/** The aspect this signal displays, this is the only information available to clients. */
	UPROPERTY( ReplicatedUsing = OnRep_Aspect )
	ERailroadSignalAspect mAspect;

	/** The validity of this signals block, this contains the error if the block is not setup properly. */
	UPROPERTY( ReplicatedUsing = OnRep_BlockValidation )
	ERailroadBlockValidation mBlockValidation;
	
	/** Here for cleanup. */
	FDelegateHandle mBlockChangedHandle;

	/** Is this a path signal. */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Signal" )
	bool mIsPathSignal;

	/** Is this signal bi-directional mean if this signal is paired with another one facing the opposite direction. */
	UPROPERTY( SaveGame )
	bool mIsBiDirectional;

	/** True if this is a left-handed signal, false if right-handed. */
	UPROPERTY( SaveGame, Replicated )
	bool mIsLeftHanded;

	/** Stored custom data for the signal material. */
	UPROPERTY( ReplicatedUsing = OnRep_VisualState )
	int16 mVisualState;

	/** Indicates if the factory is within significance distance */
	bool mIsSignificant;
	
	/** The range to keep the factory in significance */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceRange;
};

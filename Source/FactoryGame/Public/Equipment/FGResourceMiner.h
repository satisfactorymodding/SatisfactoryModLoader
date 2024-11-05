// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGWeapon.h"
#include "GameFramework/Actor.h"
#include "FGResourceMiner.generated.h"

UCLASS()
class FACTORYGAME_API AFGResourceMiner : public AFGEquipment
{
	GENERATED_BODY()
public:	
	AFGResourceMiner();

	// Begin UObject interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Tick( float DeltaSeconds ) override;
	// End UObject interface

	// Begin AFGEquipment interface
	virtual void UnEquip() override;
	virtual void HandleDefaultEquipmentActionEvent(EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent) override;
	// End AFGEquipment interface

	/** Returns true if we are currently actively mining */
	UFUNCTION( BlueprintPure, Category = "Resource Miner" )
	FORCEINLINE bool IsMining() const { return mActiveResourceNode != nullptr; }

	/** Returns the resource node we are currently mining */
	UFUNCTION( BlueprintPure, Category = "Resource Miner" )
	FORCEINLINE AFGResourceNode* GetMiningResourceNode() const { return mActiveResourceNode; }

	/** Forcefully stops mining if we are currently mining */
	UFUNCTION( BlueprintCallable, Category = "Resource Miner" )
	void ForceStopMining();

	/** Forcefully stops mining unless the player has been mining for more than hold duration minimum */
	UFUNCTION( BlueprintCallable, Category = "Resource Miner" )
	void StopMiningIfNotToggleBased();

	/** Attempts to automatically equip the equipment and start mining */
	UFUNCTION( BlueprintCallable, Category = "Resource Miner" )
	void AttemptAutoEquipAndStartMining( AFGResourceNode* resourceNode = nullptr );

protected:
	/** Attempts to line trace to find a resource node the player is currently looking at */
	void UpdatePendingResourceNode( AFGResourceNode* preferredResourceNode );

	/** Called when the "pending" (the one we are looking at) resource node changes */
	UFUNCTION( BlueprintNativeEvent, Category = "Resource Miner" )
	void OnPendingResourceNodeChanged( AFGResourceNode* oldResourceNode );

	/** Updates the state of the active mining */
	void UpdateActiveMining( float dt, bool forceStopMining );
	
	/** Called when the player has started mining. Will be called on all sides. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resource Miner", DisplayName = "OnStartedMining" )
	void K2_OnStartedMining();

	/** Called when the mining cycle is completed. Will be called on all sides. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resource Miner", DisplayName = "OnMiningCycleCompleted" )
	void K2_OnMiningCycleCompleted();

	/** Called when the player has stopped mining. Will be called on all sides. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Resource Miner", DisplayName = "OnStoppedMining" )
	void K2_OnStoppedMining( AFGResourceNode* oldResourceNode );
	
	bool TraceForResourceNode( FHitResult& out_hitResult ) const;
	bool OverlapForResourceNode( TArray<FOverlapResult>& out_overlapResults ) const;

	/** Gives mining rewards to the player. Can be overriden to change the behavior of the miner. */
	UFUNCTION( BlueprintNativeEvent, Category = "Resource Node" )
	void Server_GiveMiningRewards();
	
	/** Call this locally on the instigator side to complete the mining cycle */
	UFUNCTION( BlueprintCallable, Category = "Resource Miner" )
	void LocalCompleteMiningCycle();

protected:
	/** Forcefully stops mining on the client */
	UFUNCTION( Client, Reliable )
	void Client_ForceStopMining();

	/** Notify the server that client has started mining locally */
	UFUNCTION( Server, Reliable )
	void Server_ClientStartedMining( AFGResourceNode* resourceNode );

	/** Notifies the server that the mining cycle has been completed and we should give resources for it */
	UFUNCTION( Server, Reliable )
	void Server_MiningCycleCompleted();

	/** Called to notify everyone that we have completed the mining cycle. */
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_MiningCycleCompleted();

	/** Ask the server to automatically equip ourselves and start mining the provided node */
	UFUNCTION( Server, Reliable )
	void Server_AttemptAutoEquipAndStartMining( AFGResourceNode* resourceNode );

	/** Asks the client to start mining the given node */
	UFUNCTION( Client, Reliable )
	void Client_StartServerGuidedMining( AFGResourceNode* resourceNode );

	UFUNCTION()
	void OnRep_ActiveResourceNode( AFGResourceNode* oldResourceNode );
protected:

	/** Duration of a single mining cycle */
	UPROPERTY( EditDefaultsOnly, Category = "Resource Miner" )
	float mMiningCycleDuration;

	/** Maximum amount of time the player can hold the button for it to behave as a toggle instead of hold */
	UPROPERTY( EditDefaultsOnly, Category = "Resource Miner" )
	float mMaximumHoldDurationToToggle;

	/** Whenever we should act as a override equipment. That means getting automatically equipped and un-equipped when we start and stop mining, and do that via SetOverrideEquipment */
	UPROPERTY( EditDefaultsOnly, Category = "Resource Miner" )
	bool mOverrideEquipment;
	
	/** The resource node we are currently looking at */
	UPROPERTY()
	class AFGResourceNode* mPendingResourceNode;

	/** The node we are currently mining resources from. If set, we are actively mining. */
	UPROPERTY( ReplicatedUsing = OnRep_ActiveResourceNode )
	class AFGResourceNode* mActiveResourceNode;

	/** Mining progress of the current cycle */
	float mCurrentMiningProgress;

	/** Whenever the player wants to keep mining */
	uint8 mWantsToStartOrKeepMining: 1;
	
	/** Whenever we have already given resources this cycle */
	uint8 mGivenResourceThisCycle: 1;

	/** World time at which we have started mining. Used for toggle based inputs. */
	float mStartMiningWorldTime;
};

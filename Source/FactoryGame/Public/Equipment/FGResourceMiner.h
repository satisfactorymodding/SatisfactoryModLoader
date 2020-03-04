// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGWeapon.h"
#include "FGResourceMiner.generated.h"

UCLASS()
class FACTORYGAME_API AFGResourceMiner : public AFGEquipment
{
	GENERATED_BODY()
public:	
	AFGResourceMiner();

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void UnEquip() override;
	virtual bool ShouldSaveState() const override;

	/** Sets the node we are mining */
	UFUNCTION( BlueprintCallable, Category = "Resource Miner" )
	void SetResourceNode( class AFGResourceNode* inNode ) { mCachedResouceNode = inNode; }

	/** Gets the saved resource node */
	UFUNCTION( BlueprintPure, Category = "Resource Miner" )
	FORCEINLINE class AFGResourceNode* GetResourceNode(){ return mCachedResouceNode; }

	/** This is where we do the actual mining ( claim resource etc ) */
	UFUNCTION( BlueprintCallable, Category = "Resource Miner" )
	void DoMine();

	/** Called when we start mining */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Resource Miner" )
	void StartMining();
	
	/** Called when we stop mining */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Resource Miner" )
	void StopMining();

	/** Starts the actual extraction of resources from the node */
	void ExtractResources();

	/** Used to unequip this equipment from client */
	UFUNCTION( BlueprintCallable, Category = "Resource Miner" )
	void RemoveEquipment();

	/** Returns number of resources extracted per cycle based on the currently cached resource node */
	int32 GetNumResourcesPerExtract() const;

protected:
	/** server notified of hit from client to verify */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_ExtractResources( );
protected:
	/** The effect the spawn when picking. */
	UPROPERTY( EditDefaultsOnly, Category = "Resource Miner" )
	class UParticleSystem* mPickParticleSystem;

	/** Animation to play when picking. */
	UPROPERTY( EditDefaultsOnly, Category = "Resource Miner" )
	class UAnimationAsset* mPickArmsAnim;

	/** The node we want to pick from */
	UPROPERTY( Replicated )
	class AFGResourceNode* mCachedResouceNode;

public:
	FORCEINLINE ~AFGResourceMiner() = default;
};

// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGPipeSubsystem.generated.h"

/**
 * Subsystem that manages all pipes in the game, grouping them into networks and managing the simulation of the networks.
 */
UCLASS()
class FACTORYGAME_API AFGPipeSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGPipeSubsystem();

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
	virtual void Tick( float dt ) override;
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	// End AActor interface

	/** Get the pipe subsystem. */
	static AFGPipeSubsystem* Get( UWorld* world );

	/** Get the pipe subsystem */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGPipeSubsystem* GetPipeSubsystem( UObject* worldContext );

	/***************************************************************************************************
	 * Functions to manage the fluid networks.
	 */

	/**
	 * Called by the network to register themselves.
	 * A network registers itself when spawned on the server or when spawned by relevancy on client.
	 */
	void RegisterPipeNetwork( class AFGPipeNetwork* network );

	/**
	 * Called by the network to register themselves on end play.
	 * This happens on both server and client.
	 */
	void UnregisterPipeNetwork( class AFGPipeNetwork* network );

	/**
	 * Find the network with the given network ID.
	 * @return - The network if found; nullptr if no network exists with that id.
	 *
	 * @note The returned pointer is only valid this tick or until a change is made to the network.
	 */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Pipes" )
	FORCEINLINE class AFGPipeNetwork* FindPipeNetwork( int32 networkID ) const { return mNetworks.FindRef( networkID ); }

	/**
	 * Attempts to set the fluid descriptor on a given network ID. Will fail if a pipe network already has a specified descriptorii.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Pipes" )
	void TrySetNetworkFluidDescriptor( int32 networkID, TSubclassOf< class UFGItemDescriptor > fluidDescriptor );

	/**
	* Resets a single fluid integrant. This emptys its content and flow values but NOT the fluid descriptor as the network maintains that 
	* @note - This takes an AActor for blueprint sanity with the IFGFluidIntegrantInterface ( that is not a blueprint type ) as such, it will cast. If the cast fails it will abort.
	*/
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Pipes" )
	void FlushIntegrant( AActor* integrantActor );

	/**
	 * Flushes a given pipe network by ID. Will clear the fluid descriptor and empty the contents of all fluid integrants
	 * @param networkID - ID of the network to flush.
	 *
	 * @note - This is not blueprint callable as the blueprints will have no reliable way to query the NetworkID
	 */
	void FlushPipeNetwork( int32 networkID );

	/**
	 * Flushes a given pipe network by ID. Will clear the fluid descriptor and empty the contents of all fluid integrants
	 * @param integrantActor - Actor implementing IFGFluidIntegrantInterface. Will resolve the networkID from the passed integrant
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Pipes" )
	void FlushPipeNetworkFromIntegrant( AActor* integrantActor );


	/***************************************************************************************************
	 * Functions to manage the fluid integrants.
	 */

	/**
	 * Add a new fluid integrant to the system.
	 * Fluid integrants are any object that should belong to a pipe network
	 */
	void RegisterFluidIntegrant( class IFGFluidIntegrantInterface* fluidIntegrant );

	/** Remove a fluid integrant. Called when the owning actor is dismantled */
	void UnregisterFluidIntegrant( class IFGFluidIntegrantInterface* fluidIntegrant );

private:
	int32 GenerateUniqueID();

	void TickPipeNetworks( float dt );

	/**
	 * Internal helper to rebuild a network.
	 * Note: This function might split, remove or otherwise change the network so it is not safe to assume anything about the network afterwards.
	 */
	void RebuildPipeNetwork( int32 networkID );

	/** Helpers to manage pipe networks. */
	void MergePipeNetworks( int32 first, int32 second );
	int32 CreatePipeNetwork();
	void RemovePipeNetwork( int32 networkID );

	/** Removes a fluid integrant from an existing network. */
	void RemoveFluidIntegrantFromNetwork( class IFGFluidIntegrantInterface* fluidIntegrant );
	/** Adds a fluid integrant to an existing network. Performs a merge on the network if its already connected */
	void AddFluidIntegrantToNetwork( class IFGFluidIntegrantInterface* fluidIntegrant, int32 networkID );

private:
	int32 mIDCounter;

	/** Map with all circuits and the circuit ID as the key. */
	UPROPERTY()
	TMap< int32, class AFGPipeNetwork* > mNetworks;

public:
	FORCEINLINE ~AFGPipeSubsystem() = default;
};

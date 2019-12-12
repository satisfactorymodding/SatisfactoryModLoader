// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGBuildGun.h"
#include "../ItemAmount.h"
#include "FGBuildGunBuild.generated.h"

USTRUCT()
struct FConnectionRepresentation
{
	GENERATED_BODY()

	FConnectionRepresentation() :
		mConnectionRepresentation( nullptr ),
		mConnectionComponent( nullptr )
	{
	}

	FConnectionRepresentation( class UFGConnectionComponent* connectionComponent, class UStaticMeshComponent * connectionRepresentation ) :
		mConnectionComponent(connectionComponent),
		mConnectionRepresentation(connectionRepresentation)
	{
	}

	UPROPERTY()
	class UFGConnectionComponent* mConnectionComponent;

	UPROPERTY()
	class UStaticMeshComponent* mConnectionRepresentation;
};

USTRUCT()
struct FFactoryClearanceData
{
	GENERATED_BODY()

	FFactoryClearanceData() :
		Factory( nullptr ),
		ClearanceComponent( nullptr )
	{
	}

	FFactoryClearanceData( class AFGBuildableFactory* inFactory, class UStaticMeshComponent* inClearanceComponent ) :
		Factory( inFactory ),
		ClearanceComponent( inClearanceComponent )
	{
	}

	UPROPERTY()
	class AFGBuildableFactory* Factory;

	UPROPERTY()
	class UStaticMeshComponent* ClearanceComponent;

	UPROPERTY()
	TArray< FConnectionRepresentation > mConnectionComponents;
};

/**
 * Build guns build state.
 */
UCLASS()
class FACTORYGAME_API UFGBuildGunStateBuild : public UFGBuildGunState
{
	GENERATED_BODY()

public:
	/** Ctor */
	UFGBuildGunStateBuild();

	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PreNetReceive() override;

	// Begin UFGBuildGunState
	virtual void BeginState_Implementation() override;
	virtual void EndState_Implementation() override;
	virtual void TickState_Implementation( float deltaTime ) override;
	virtual void PrimaryFire_Implementation() override;
	virtual void SecondaryFire_Implementation() override;
	virtual void ScrollDown_Implementation() override;
	virtual void ScrollUp_Implementation() override;
	virtual void ChangeScrollMode_Implementation() override;
	virtual void ChangeNoSnapMode_Implementation() override;
	virtual void ChangeGuideLinesSnapMode_Implementation( bool enabled ) override;
	// End UFGBuildGunState

	/**
	 * Set the recipe to build.
	 * must be called from the local player (client).
	 */
	void SetActiveRecipe( TSubclassOf< class UFGRecipe > recipe );

	/** Get the current descriptor, null if no descriptor is set. */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|Build" )
	TSubclassOf< class UFGItemDescriptor > GetDescriptor() const;

	/** Returns the cost for building the hologram. */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|Build" )
	TArray< FItemAmount > GetHologramCost() const;

	/** Returns the hologram; null if hologram not spawned. */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|Build" )
	class AFGHologram* GetHologram() const;

	/** Spawns a child hologram. */
	class AFGHologram* SpawnChildHologram( AFGHologram* parent, TSubclassOf< class UFGRecipe > recipe );

protected:
	/** Called whenever the hologram is udpated **/
	UFUNCTION()
	void OnRep_Hologram();

	/**
	 * Resets any changes made to the hologram.
	 * @note Must be called on the server.
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGunState|Build" )
	void ResetHologram();

	/**
	 * Let blueprint know when we get a new descriptor, the new descriptor may be null.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "BuildGunState|Build" )
	void OnActiveDescriptorChanged();

	/**
	 * Let blueprint know we performed a multi-step placement.
	 * @param isFinalStep - true if this was the last step, the thing is now built. Hologram is no longer guaranteed to exist on the the client.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "BuildGunState|Build" )
	void OnMultiStepPlacement( bool isFinalStep );

	/**
	 * Let blueprint know we reset the multi-step placement.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "BuildGunState|Build" )
	void OnResetHologram();

	/** Helper to notify the client. */
	UFUNCTION( Client, Reliable )
	void Client_OnResetHologram();

	/** Helper to notify the client that something was built */
	UFUNCTION( Client, Reliable )
	void Client_OnBuildableConstructed( TSubclassOf< UFGItemDescriptor > desc );

private:
	/** Spawn a hologram. */
	void SpawnHologram();

	/** Spawn specific holograms. */
	class AFGHologram* SpawnBuildableHologram( TSubclassOf< class UFGRecipe > recipe );
	class AFGHologram* SpawnVehicleHologram( TSubclassOf< class UFGRecipe > recipe );

	/** Remove the current hologram. */
	void RemoveHologram();

	/** Setup the clearance for our current hologram */
	void SetupHologramClearanceDetection();

	/** Remove the clearance from our current hologram */
	void CleanupHologramClearanceDetection( AFGHologram* hologram );

	/** Save/clear/restore the scroll values for the hologram. */
	void SaveHologramScrollValues();
	void ClearHologramScrollValues();
	void RestoreHologramScrollValues();

	UFUNCTION()
	void BeginClearanceOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );

	UFUNCTION()
	void EndClearanceOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

private:
	/** Stored values between hologram builds on how the hologram was scrolled */
	TArray< int32 > mScrollModeValues;

	/** Stored no snap flag between hologram builds. */
	bool mNoSnapMode;

	/** Stored flag for whether hologram builds should snap to guide lines */
	bool mSnapToGuideLinesMode;

	/** Recipe to activate when state is entered. */
	UPROPERTY()
	TSubclassOf< class UFGRecipe > mPendingRecipe;

	/**
	 * The currently active recipe, this decides which action will be used.
	 * Not replicated as the client sets it locally and then tells the server to set it.
	 */
	UPROPERTY()
	TSubclassOf< class UFGRecipe > mActiveRecipe;

	/** The hologram that the client had before changing it's hologram due to replication, no UPROPERTY as it should only live from PreNetReceive to OnRep_Hologram */
	class AFGHologram* mInternalPrevClientHologram;

	/** The hologram to build. */
	UPROPERTY( ReplicatedUsing=OnRep_Hologram )
	class AFGHologram* mHologram;

	/** The actor to replace (dismantle) when upgrading. */
	UPROPERTY( Replicated )
	class AActor* mUpgradedActor;

	/** Moves the clearance box collision to where we are aiming */
	void UpdateClearanceData();

	/** Contains all the proximate clearances volumes */
	UPROPERTY()
	TArray< FFactoryClearanceData > mProximateClearances;

	/** Component that finds close clearances of nearby buildings and visualize them */
	//@todo G2 2019-04-10 An improvement here would be to make this a component that can keep track of detected
	//                    overlaps so the state does not contain this easily self contained logic.
	UPROPERTY()
	class UBoxComponent* mClearanceDetector;
};

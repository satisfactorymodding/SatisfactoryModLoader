// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Equipment/FGBuildGun.h"
#include "ItemAmount.h"
#include "FGBuildableSubsystem.h"
#include "FGConstructionMessageInterface.h"
#include "Delegates/DelegateCombinations.h"
#include "FGBuildGunBuild.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FBuildModeChangedDelegate, TSubclassOf<class UFGHologramBuildModeDescriptor>, newMode );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnZoopUpdated, float, currentZoop, float, maxZoop, const FVector&, zoopLocation );

USTRUCT()
struct FConnectionRepresentation
{
	GENERATED_BODY()

	FConnectionRepresentation() :
		mConnectionComponent( nullptr ),
		mConnectionRepresentation( nullptr )
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
struct FAttachmentPointRepresentation
{
	GENERATED_BODY()

	FAttachmentPointRepresentation() :
		mAttachmentPoint( nullptr ),
		mAttachmentRepresentation( nullptr )
	{
	}

	FAttachmentPointRepresentation( const struct FFGAttachmentPoint* attachmentPoint, class UStaticMeshComponent* attachmentRepresentation ) :
		mAttachmentPoint( attachmentPoint ),
		mAttachmentRepresentation( attachmentRepresentation )
	{
	}

	const struct FFGAttachmentPoint* mAttachmentPoint;

	UPROPERTY()
	class UStaticMeshComponent* mAttachmentRepresentation;
};

USTRUCT()
struct FBuildableClearanceData
{
	GENERATED_BODY()

	FBuildableClearanceData() :
		Buildable( nullptr ),
		ClearanceMeshComponent( nullptr )
	{
	}

	FBuildableClearanceData( class AFGBuildable* inBuildable ) :
		Buildable( inBuildable ),
		ClearanceMeshComponent( nullptr )
	{
	}

	UPROPERTY()
	class AFGBuildable* Buildable;

	UPROPERTY()
	class UStaticMeshComponent* ClearanceMeshComponent;

	UPROPERTY()
	TArray< FConnectionRepresentation > mConnectionComponents;

	UPROPERTY()
	TArray< FAttachmentPointRepresentation > mAttachmentPointMeshes;

	uint8 ParticipatedInCleranceEncroachFrameCountDownLast = 0;
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

	// Begin UFGBuildGunState
	virtual void BeginState_Implementation() override;
	virtual void EndState_Implementation() override;
	virtual void TickState_Implementation( float deltaTime ) override;
	virtual void PrimaryFire_Implementation() override;
	virtual void PrimaryFireRelease_Implementation() override;
	virtual void SecondaryFire_Implementation() override;
	virtual void ModeSelectPressed_Implementation() override;
	virtual void ModeSelectRelease_Implementation() override;
	virtual void ScrollDown_Implementation() override;
	virtual void ScrollUp_Implementation() override;
	virtual void ChangeScrollMode_Implementation() override;
	virtual void ChangeNoSnapMode_Implementation() override;
	virtual void ChangeGuideLinesSnapMode_Implementation( bool enabled ) override;
	virtual void BuildSampleRelease_Implementation() override;
	virtual bool IsValidBuildingSample( class AFGBuildable* buildable ) const override;
	virtual bool IsValidVehicleSample( class AFGVehicle* vehicle ) const override;
	virtual void OnRecipeSampled_Implementation( TSubclassOf<class UFGRecipe> recipe ) override;
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

	/** Spawns a child hologram */
	AFGHologram* SpawnChildHologram( AFGHologram* parent, TSubclassOf< class UFGRecipe > recipe );

	/** RPC to construct from hologram data */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_ConstructHologram( FNetConstructionID clientNetConstructID, FConstructHologramMessage data );
	void InternalConstructHologram( FNetConstructionID clientNetConstructID );

	UFUNCTION( Server, Reliable, WithValidation )
    void Server_ChangeGuideLinesSnapMode( bool enabled );

	/**Get a list of the currently supported build modes for the current hologram.*/
	UFUNCTION(BlueprintCallable, Category = "BuildModeSelect")
	TArray< TSubclassOf<class UFGHologramBuildModeDescriptor> > GetSupportedBuildModes();

	UFUNCTION( BlueprintPure, Category = "BuildModeSelect" )
	TSubclassOf<class UFGHologramBuildModeDescriptor> GetLastBuildModeForCategory( uint8 category, TSubclassOf< class AActor > actorClass );
	
	/** Set the build mode on the current hologram */
	UFUNCTION( BlueprintCallable, Category = "BuildModeSelect" )
	void SetCurrentBuildMode( TSubclassOf<class UFGHologramBuildModeDescriptor> mode );

	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SetCurrentBuildMode( TSubclassOf<class UFGHologramBuildModeDescriptor> mode );

	UPROPERTY( BlueprintAssignable, Category = "BuildModeSelect", DisplayName = "OnBuildModeChanged" )
	FBuildModeChangedDelegate OnBuildModeChangedDelegate;

	/** Show the  mode selection UI */
	UFUNCTION( BlueprintImplementableEvent, Category = "BuildModeSelect" )
	void ShowBuildModeSelectUI();

	/** Close the  mode selection UI */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "BuildModeSelect" )
	void CloseBuildModeSelectUI();

	/** Called whenever a hologram updates its zoop.
	 * @param currentZoop - How far we have zooped, value depends on hologram implementation. Beams use meters, cosmetic buildables use number of instances.
	 * @param maxZoop - How far we are allowed to zoop with the current hologram.
	 * @param zoopLocation - The location we're zooping to.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Hologram" )
	void OnZoopUpdated( float currentZoop, float maxZoop, const FVector& zoopLocation );

	/** Called whenever a hologram updates its zoop. */
	UPROPERTY( BlueprintAssignable, Category = "Hologram", DisplayName = "OnZoopUpdated" )
	FOnZoopUpdated OnZoopUpdatedDelegate;

	void HookUpUserSettings();

protected:
	
	/** InternalExecuteDuBuildStepInput
	 * Execute the actual build step logic. Called from primary fire, and sometimes from primary fire release
	 * 
	 */
	 void InternalExecuteDuBuildStepInput(bool isInputFromARelease);

	UFUNCTION()
	void OnRep_CurrentHologramBuildMode();

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

	/** Helper to notify the client that something was built */
	UFUNCTION( Client, Reliable )
	void Client_OnBuildableConstructed( TSubclassOf< UFGItemDescriptor > desc );

	UFUNCTION( Client, Reliable )
	void Client_OnBuildableFailedConstruction( FNetConstructionID netConstructionID );

private:
	/** Spawn a hologram. */
	void SpawnHologram();

	/** Remove the current hologram. */
	void RemoveHologram();

	/** Setup the clearance for our current hologram */
	void SetupHologramClearanceDetection();

	/** Remove the clearance from our current hologram */
	void CleanupHologramClearanceDetection( AFGHologram* hologram );

	/** Save/clear/restore the scroll values for the hologram. */
	void SaveHologramScrollValues();
	void ClearHologramScrollValues();
	void RestoreHologramScrollValues(AFGHologram* hologram);

	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SaveHologramScrollValues( const TArray< int32 >& scrollValues );

	AFGHologram* InternalSpawnHologram();

	UFUNCTION()
	void BeginClearanceDetectorOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );

	UFUNCTION()
	void EndClearanceDetectorOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

	UFUNCTION()
	void OnUserSettingsUpdated();

	UFUNCTION( Server, Reliable )
	void Server_SetUseAutomaticClearanceSnapping( bool useAutomaticSnapping );
private:
	/** Stored values between hologram builds on how the hologram was scrolled */
	TArray< int32 > mScrollModeValues;

	/** stores a time we have held the primary fire button for. Used so we can detect if it's a hold or tap or similar*/
	float mPrimaryFireHoldTime = -1;

	/** stores a time we have held the mode select button for. Used so we can detect if it's a hold or tap, to show the menu or not*/
	float mBuildModeSelectHoldTime = -1; //@TODO:[DavalliusA:Thu/28-11-2019] consider using a game time stamp instead so we don't have to rely on tick to update this

	/** Time needed to hold down the key to show the selection UI */
	UPROPERTY( EditDefaultsOnly, Category = "BuildModeSelect" )
	float mBuildModeSelectHoldDownDurationForUI = 0.18f;


	/** True if we are waiting for the selection UI */
	UPROPERTY()
	bool mIsWaitingForSelectionUI = false;


	/** Stored no snap flag between hologram builds. */
	bool mNoSnapMode;

	/** user setting for if we are using the release and press mode or not for advancing build steps. Nett to be in sync on client and ser ver players preferences*/
	UPROPERTY( Replicated )
	bool mIsUsingPressAndReleaseAsBuildSteps = true;


	bool mAllowAutomaticClearanceSnapping = false;

	/** Stored flag for whether hologram builds should snap to guide lines */
	bool mSnapToGuideLinesMode;

	/** Stored flag for whether hologram builds should snap to guide lines */
	bool mPrimaryDownStarted = false; //stores if we have started a primary fire press, so we know to respond to release presses too, so we don't get the release from a previous state or something

	/** Recipe to activate when state is entered. */
	UPROPERTY()
	TSubclassOf< class UFGRecipe > mPendingRecipe;

	/**
	 * The currently active recipe, this decides which action will be used.
	 * Not replicated as the client sets it locally and then tells the server to set it.
	 */
	UPROPERTY()
	TSubclassOf< class UFGRecipe > mActiveRecipe;

	/**
	 * Used to replicate the current build mode of the hologram, since the hologram is only simulated and not replicated on other clients. 
	 */
	UPROPERTY( ReplicatedUsing = OnRep_CurrentHologramBuildMode )
	TSubclassOf< class UFGHologramBuildModeDescriptor > mCurrentHologramBuildMode;

	/** Map used to cache the last used build modes for different categories (keys). */
	TMap< uint8, TSubclassOf< class UFGHologramBuildModeDescriptor > > mLastUsedCategoryBuildmodes;

	/** Map used to cache the last used build modes for different actor class types. */
	TMap< TSubclassOf< class AActor >, TSubclassOf< class UFGHologramBuildModeDescriptor > > mLastUsedActorBuildmodes;

	//@TODO:[DavalliusA:Wed/20-11-2019] should these not be marked as transient?
	/** The hologram to build. */
	UPROPERTY( /*ReplicatedUsing=OnRep_Hologram */ )
	class AFGHologram* mHologram;

	//@TODO:[DavalliusA:Wed/20-11-2019] should these not be marked as transient?
	/** The actor to replace (dismantle) when upgrading. */
	UPROPERTY()
	class AActor* mUpgradedActor;

	/** Moves the clearance box collision to where we are aiming */
	void UpdateClearanceData();

	//@TODO:[DavalliusA:Wed/20-11-2019] should these not be marked as transient?
	/** Contains all the proximate clearances volumes */
	UPROPERTY()
	TArray< FBuildableClearanceData > mProximateClearances;

	//@TODO:[DavalliusA:Wed/20-11-2019] should these not be marked as transient?
	/** Component that finds close clearances of nearby buildings and visualize them */
	//@todo G2 2019-04-10 An improvement here would be to make this a component that can keep track of detected
	//                    overlaps so the state does not contain this easily self contained logic.
	UPROPERTY()
	class UBoxComponent* mClearanceDetector;

	/** All building locations spawned during this frame. Will be cleared at the start of every new frame to avoid spawning multiple buildings at the same location. */
	TArray<FVector> mConstructionLocationDuringFrame;
};

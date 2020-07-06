// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/CoreNet.h"
#include "Array.h"
#include "UnrealString.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "../FGUseableInterface.h"
#include "../ItemAmount.h"
#include "../FGDismantleInterface.h"
#include "../FGBlueprintFunctionLibrary.h"
#include "Animation/AnimInstance.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/SCS_Node.h"
#include "../FGSaveInterface.h"
#include "../FactoryTick.h"
#include "../FGColorInterface.h"
#include "../Replication/FGReplicationDetailActorOwnerInterface.h"
#include "../FGBuildableSubsystem.h"
#include "../FGSaveInterface.h"
#include "../FactoryTick.h"
#include "../FGColorInterface.h"
#include "../Replication/FGReplicationDetailActorOwnerInterface.h"
#include "FGBuildable.generated.h"

//@todonow These should CAPS_CASE according to the coding standard
static const FString MainMeshName( TEXT( "MainMesh" ) );
static const FName ClearanceVolumeName( TEXT( "Clearance" ) ); //@todo There's a duplicate of this in the CPP file.

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FBuildableDismantledSignature );

// Replication graph related delegates
DECLARE_MULTICAST_DELEGATE_ThreeParams( FOnRegisteredPlayerChanged, class AFGBuildable*, class AFGCharacterPlayer* /* registered player */, bool /* bIsUseStateActive */ );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnReplicationDetailActorStateChange, class IFGReplicationDetailActorOwnerInterface*, bool );


/**
 * Base for everything buildable, buildable things can have factory connections, power connections etc.
 *
 * There are two tick functions on buildables, PrimaryActorTick and FactoryTick.
 * PrimaryActorTick is disabled when the buildable is to far away to to not waste cycles on animations and other effects.
 * FactoryTick is always enabled (as long as bCanEverTick is true) so that the factory part of buildings always can simulate.
 */
UCLASS( Abstract, NotPlaceable, Config=Engine, Meta=(AutoJson=true) )
class FACTORYGAME_API AFGBuildable : public AActor, public IFGDismantleInterface, public IFGSaveInterface, public IFGColorInterface, public IFGUseableInterface
{
	GENERATED_BODY()
public:	
	/** Decide on what properties to replicate */
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;

	AFGBuildable();

#if WITH_EDITOR
	virtual void CheckForErrors() override;
#endif

	// Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
	// End UObject interface

	// Begin AActor interface
	virtual void OnConstruction( const FTransform& transform ) override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Destroyed() override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	//~ Begin IFGColorInterface
	void SetColorSlot_Implementation( uint8 newColor );
	uint8 GetColorSlot_Implementation();
	void SetColorSlot_PreBeginPlay( uint8 newColor );
	FLinearColor GetPrimaryColor_Implementation();
	FLinearColor GetSecondaryColor_Implementation();
	bool GetCanBeColored_Implementation();
	virtual void StartIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter );
	virtual void StopIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter );
	//~ End IFGColorInterface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	//~ End IFGUseableInterface

	// Should we skip playing the build effect
	virtual bool ShouldSkipBuildEffect() { return mSkipBuildEffect; }

	/** Get default components from this class. */
	template< class T, class AllocatorType >
	void GetDefaultComponents( TArray< T*, AllocatorType >& out_components ) const;

	/** Enable/disable our primary actor tick, but don't touch our factory tick */
	void EnablePrimaryTickFunctions( bool enable );

	/** Root of factory ticking hierarchy */
	void TickFactory( float dt, ELevelTick TickType );

	/** Always ticking tick, this is where factory logic resides, other tick will be disabled pretty frequent */
	virtual void Factory_Tick( float dt );

	/** Blueprint version of Factory_Tick */
	UFUNCTION( BlueprintImplementableEvent, Category = "Tick", meta = ( DisplayName = "Factory_Tick" ) )
	void Factory_ReceiveTick( float deltaTime );

	//~ Begin IFGDismantleInterface
	virtual bool CanDismantle_Implementation() const override;
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund ) const override;
	virtual FVector GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const override;
	virtual void PreUpgrade_Implementation() override;
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	virtual void Dismantle_Implementation() override;
	virtual void StartIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	//~ End IFGDismantleInferface

	virtual void StartIsLookedAtForConnection( class AFGCharacterPlayer* byCharacter );
	virtual void StopIsLookedAtForConnection( class AFGCharacterPlayer* byCharacter );

	/** Called in ConfigureActor from the hologram. */
	void SetBuiltWithRecipe( TSubclassOf< class UFGRecipe > recipe ) { mBuiltWithRecipe = recipe; }

	/** Getters for the built with recipe. */
	FORCEINLINE TSubclassOf< class UFGRecipe > GetBuiltWithRecipe() const { return mBuiltWithRecipe; }
	TSubclassOf< class UFGItemDescriptor > GetBuiltWithDescriptor() const;
	template< class C > TSubclassOf< C > GetBuiltWithDescriptor() const { return *GetBuiltWithDescriptor(); }

	/** Shutdown this building. */
	void TurnOffAndDestroy();

	/** Finds, caches and returns the MainMesh of this buildable */
	UFUNCTION( BlueprintCallable, Category = "Buildable" )
	const TArray< class UMeshComponent* >& GetMainMeshes();

	/** Get the building this buildable belong to. */
	FORCEINLINE int32 GetBuildingID() const { return mBuildingID; }

	/** Set the building ID for this buildable, be careful when calling this so the relation to the surrounding buildings is not broken. */
	FORCEINLINE void SetBuildingID( int32 buildingID ) { mBuildingID = buildingID; }


	/** Returns the timestamp for when this building was built */
	FORCEINLINE float GetBuildTime() { return mBuildTimeStamp; }

	/** Sets the timestamp for when this building was built */
	FORCEINLINE void SetBuildTime( float inTime ) { mBuildTimeStamp = inTime; }

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

	/** Returns the factory stat ID of the object used for the profiling tool. */
	FORCEINLINE TStatId GetFactoryStatID( bool forDeferredUse = false ) const
	{
#if STATS
		// this is done to avoid even registering stats for a disabled group (unless we plan on using it later)
		if( forDeferredUse || FThreadStats::IsCollectingData( GET_STATID( STAT_UObjectsStatGroupTester ) ) )
		{
			if( !mFactoryStatID.IsValidStat() )
			{
				CreateFactoryStatID();
			}
			return mFactoryStatID;
		}
#endif
		return TStatId(); // not doing stats at the moment, or ever
	}

	/** Getter and setter for the construction ID issued by server used to identify buildables when constructed on client */
	FORCEINLINE void SetNetConstructionID( FNetConstructionID netConstructionID ) { mNetConstructionID = netConstructionID; }
	FNetConstructionID GetNetConstructionID() const { return mNetConstructionID; }

	// Begin FFactoryStatHelpers Functions
	void Stat_Cost( TArray< FItemAmount >& out_amount ) const;
	void Stat_StockInventory( TArray< FItemAmount >& out_amount ) const;
	// End FFactoryStatHelpers Functions

	/**
	 * Build/Dismantle Effects
	 * @param instigator Actor who triggered the effect (i.e. where to throw the resources from).
	 */
	UFUNCTION( BlueprintCallable, Category = "Buildable|Build Effect" )
	virtual void PlayBuildEffects( AActor* inInstigator );
	virtual void ExecutePlayBuildEffects();
	virtual void OnBuildEffectFinished();
	UFUNCTION( Reliable, NetMulticast )
	void PlayDismantleEffects();
	virtual void OnDismantleEffectFinished();

	class UFGMaterialEffect_Build* GetActiveBuildEffect();

	/** Returns true if this buildable can be sampled */
	UFUNCTION( BlueprintNativeEvent )
	bool CanBeSampled() const;

	/** Returns whether or not the build effect is currently running */
	bool IsPlayingBuildEffect() const { return mBuildEffectIsPlaying; }

	/** Display the highlight effect */
	UFUNCTION( BlueprintCallable, Category = "Buildable" )
	void ShowHighlightEffect();

	/** Removes the highlight effect */
	UFUNCTION( BlueprintCallable, Category = "Buildable" )
	void RemoveHighlightEffect();

	/** Returns the cached bounds */
	FORCEINLINE FBox GetCachedBounds() { return mCachedBounds; }

	/** Returns list of players currently interacting with building. */
	FORCEINLINE TArray< class AFGCharacterPlayer* > GetInteractingPlayers() const { return mInteractingPlayers; }

	/** Only used for cheats. Hides/Unhides the actor, and makes sure the instanced meshes hide as well*/
	void SetHiddenIngameAndHideInstancedMeshes( bool hide = false );

	/** Helper function for getting buildable classes from recipes
	*	@note Useful when generating child holograms based off their recipe
	*/
	static TSubclassOf< AFGBuildable > GetBuildableClassFromRecipe( TSubclassOf< class UFGRecipe > inRecipe );

	/** Event on when buildable's replication detail actor changes state */
	static FOnReplicationDetailActorStateChange OnBuildableReplicationDetailActorStateChange;

	UFUNCTION( BlueprintPure, Category = "Buildable" )
	UShapeComponent* GetClearanceComponent();

	/**Function to get info about participation in clearance overlap feedback for the local machines hologram placement*/
	uint8 GetParticipatedInCleranceEncroachFrameCountDown(){ return mParticipatedInCleranceEncroachFrameCountDown; }
	void SetParticipatedInCleranceEncroachFrameCountDown( uint8 value ){ mParticipatedInCleranceEncroachFrameCountDown = FMath::Min( value, (uint8 )3 ); }

	 //Used to let fonudations allow for clerance sepration when stakced on, which most others don't.
	bool AllowCleranceSeparationEvenIfStackedOn()
	{
		return mAllowCleranceSeparationEvenIfStackedOn;
	}

	//[DavalliusA:Mon/17-02-2020] moved these to not be private as I don't understand why they should be
	/** Get the number of power connections */
	UFUNCTION( BlueprintCallable, Category = "Buildable|Connections" )
	uint8 GetNumPowerConnections() const;

		/** Get the number of factory connections */
	uint8 GetNumFactoryConnections() const;

	/** Get the number of factory output connections */
	uint8 GetNumFactoryOuputConnections() const;

	/** Should this buildable be relevant when considering if a location is near a base/factory area */
	UFUNCTION( BlueprintNativeEvent, Category = "Buildable" )
	bool ShouldBeConsideredForBase();

	virtual bool ShouldBeConsideredForBase_Implementation();
#if WITH_EDITOR
	/** Sets the display name for this buildable. Only for editor use */
	UFUNCTION( BlueprintCallable, Category = "Editor|Buildable" )
	static void SetBuildableDisplayName( TSubclassOf< AFGBuildable > inClass, FText displayName );
#endif

	/** Called when materials are updated by the buildable subsystem material sharing or when a new color is set */
	virtual void Native_OnMaterialInstancesUpdated();

protected:

	/** Blueprint event for when materials are updated by the buildable subsystem*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Buildable|Build Effect" )
	void OnMaterialInstancesUpdated();

	/** Plays construction sound, override this event to play a custom sound. */
	UFUNCTION( BlueprintNativeEvent, BlueprintCosmetic, Category = "Buildable|Build Effect" )
	void PlayConstructSound();

	/** Plays dismantle sound, override this event to play a custom sound. */
	UFUNCTION( BlueprintNativeEvent, BlueprintCosmetic, Category = "Buildable|Build Effect" )
	void PlayDismantleSound();


	/** Ugly haxx to remove replication of graph unless any player is looking at it */
	void RegisterInteractingPlayerWithCircuit( class AFGCharacterPlayer* player );
	void UnregisterInteractingPlayerWithCircuit( class AFGCharacterPlayer* player );

	/** Get the distance to the closest camera */
	float GetCameraDistanceSq() const{ return mCameraDistanceSq; }

	/** Called whenever mIsReplicatingDetails has changed, used to enable disable replication of subobjects. */
	virtual void OnReplicatingDetailsChanged();

	/**
	 * For custom connections, if we want a custom implementation for
	 * Called if mForwardPeekAndGrabToProxy is set in the connection.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Buildable|Connections" )
	bool Factory_PeekOutput( const class UFGFactoryConnectionComponent* connection, TArray< FInventoryItem >& out_items, TSubclassOf< UFGItemDescriptor > type ) const;

	/**
	 * For custom connections, if we want a custom implementation for peek
	 * Called if mForwardPeekAndGrabToProxy is set in the connection.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Buildable|Connections" )
	bool Factory_GrabOutput( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type );

	/**
	* This function tells us the maximum amounts of grabs this building can make this frame
	*
	* @ param out_availableSpace - the amount of space until next item.
	*/
	virtual uint8 MaxNumGrab( float delta ) const;

	/**
	*	This tells how many estimated grabs this building can make after the given delta time have passed. It is estimated so it cannot guarantee 100 percent accuracy
	*
	*	@ param estimatedDeltaTime - the amount of time we use to estimate how many items we can grab after that time have passed
	*/
	virtual uint8 EstimatedMaxNumGrab_Threadsafe( float estimatedDeltaTime ) const;


	/**
	 * Override this to verify the default configuration.
	 * @param out_message - Designer friendly message to be displayed.
	 * @return - true if the defaults are valid; false if the defaults are configured wrong.
	 */
	virtual bool VerifyDefaults( FString& out_message );

	/** Helper to get the cost multiplier for a buildable given its length and how long each cost segment is. */
	static int32 GetCostMultiplierForLength( float totalLength, float costSegmentLength );

	/** Get the refundable cost for this building, not including any connected buildings. Not consolidated. */
	void GetDismantleRefundReturns( TArray< FInventoryStack >& out_returns ) const;
	/** Get the multiplier for the refundable cost, e.g. for buildings that cost per length unit. */
	virtual int32 GetDismantleRefundReturnsMultiplier() const;

	/** Get all items to be returned from the buildings inventory on dismantle. Not consolidated. */
	virtual void GetDismantleInventoryReturns( TArray< FInventoryStack >& out_returns ) const;

	/** If blueprint has anything to return when this buildable is dismantled. Not consolidated. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Buildable|Dismantle" )
	void GetDismantleBlueprintReturns( TArray< FInventoryStack >& out_returns ) const;

	/** Get the widget used to interact with this buildable. */
	UFUNCTION( BlueprintPure, Category = "Buildable|Interaction" )
	FORCEINLINE class TSubclassOf< class UFGInteractWidget > GetInteractWidgetClass() const { return mInteractWidgetClass; }

	/** @return true if this building is replicating detailed information about it; false otherwise. */
	bool IsReplicatingDetails() const { return mReplicateDetails; }

	/** Toggles the pending dismantle material on buildable */
	virtual void TogglePendingDismantleMaterial( bool enabled );

	/** Set the buildable to reevaluate material instances with the buildable subsystem when applying color slot */
	UFUNCTION( BlueprintCallable, Category="Buildable")
	void FlagReevaluateMaterialOnColored() { mReevaluateMaterialsWithSubsystem = true; }

	/** Update the color from the current color slot*/
	UFUNCTION( BlueprintCallable )
	void ReapplyColorSlot();

	/** Does this buildable have a material instance manager mapped to the given component? 
	*	The component to material manager map is used to verify we have already updated the factory materials for a given component. 
	*	@todoFactoryMaterialInstance:	Is this still needed? It was used before to ensure we didn't attempt to instance a component multiple times, but this should be done in AddBuildable in the subsystem now
	*									Not, as it was before, in the OnRep_ColorSlot(). We should only be applying materials once... right? [Thoughts from Dylan as he writes the new system]
	*/
	bool HasMaterialInstanceManagerForMaterialName( const FString& lookupName );

	/** Returns the Material Manager for a given component, or null if there is not one */
	class UFGFactoryMaterialInstanceManager* GetMaterialInstanceManagerForMaterialName( const FString& lookupName );

	/** Adds an entry for a given component mapping to its respective Material Instance Manager. Returns false if it could not add an entry (eg. It already exists or failed to create) */
	bool AddMaterialInstanceManagerForMaterialName( const FString& lookupName, class UFGFactoryMaterialInstanceManager* materialInstanceManager );

	/** OnDismantle check to see if the buildable subsystem has any BlockedSharing material instance references that were only relevent to this object and remove them from the master material manager map */
	void CleanUpMaterialInstanceMappingsInSubsystem();
private:
	/** Create a stat for the buildable */
	void CreateFactoryStatID() const;

	/**
	 * Set if we should replicate details.
	 * This is private because this is handled by the buildables use implementation.
	 */
	void SetReplicateDetails( bool replicateDetails );

	/** Helper to verify the connection naming. */
	bool CheckFactoryConnectionComponents( FString& out_message );

	/** Let the client set colors. */
	UFUNCTION()
	void OnRep_ColorSlot();

	/** Let client see the highlight */
	UFUNCTION()
	void OnRep_DidFirstTimeUse();


public:
	//@todoGC Move to the descriptor maybe?
	/** The hologram class to use for constructing this object. */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	TSubclassOf< class AFGHologram > mHologramClass;

	/** The human readable display name of this object. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Buildable" )
	FText mDisplayName;
	
	/** The human readable description of this object. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Buildable", meta= ( MultiLine = true ) )
	FText mDescription;

	/** Delegate will trigger whenever the actor's use state has changed (Start, End) */
	static FOnRegisteredPlayerChanged OnRegisterPlayerChange;

	/** Max draw distance, inactive when < 0 */
	UPROPERTY(EditDefaultsOnly,Category = "Rendering")
	float MaxRenderDistance;

	//@todoGC look at the other todo for highlights.
	/** Vector used to determine highlight effects location */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	FVector mHighlightVector;

protected:
	//@todorefactor With meta = ( ShowOnlyInnerProperties ) it does not show and PrimaryActorTick seems to be all custom properties, so I moved to another category but could not expand.
	/** Controls if we should receive Factory_Tick and how frequent. */
	UPROPERTY( EditDefaultsOnly, Category = "Factory Tick", meta = (NoAutoJson = true) )
	FFactoryTickFunction mFactoryTickFunction;

	//@todoGC Good candidate for maybe moving to the buildable subsystem to get it out of all buildings. FName instead of FString?
	/** Map of colorable mesh materials to their respective colored factory material instance manager */
	UPROPERTY()
	TMap< FString, class UFGFactoryMaterialInstanceManager* > mMaterialNameToInstanceManager;

	/** 
	*	Set to true to keep the materials in this buildable from being added to the material instance manager. Uses include buildings that set other material parameters outside of the color params.
	*	Ex. Pipeline Pumps use a Vertex animation that varies between instances at runtime so it doesn't make sense to attempt to use a universal material instance
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	bool mBlockSharingMaterialInstanceMapping;

	/** Array of mesh elements to selectively block material instancing on. Used in the event that certain buildable components should not attempt to use a shared material instance. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable" )
	TArray< class UMeshComponent* > mExcludeFromMaterialInstancing;

	/** The primary color of this buildable */
	UPROPERTY( SaveGame, meta = (NoAutoJson = true) )
	FLinearColor mPrimaryColor;

	/** The primary color of this buildable */
	UPROPERTY( SaveGame, meta = (NoAutoJson = true) )
	FLinearColor mSecondaryColor;

	/** The color slot of this buildable */
	UPROPERTY( EditAnywhere, SaveGame, ReplicatedUsing = OnRep_ColorSlot, meta = (NoAutoJson = true) )
	uint8 mColorSlot = 0; 


	/** HAXX FLAG! Buildings set this to start replicating power graph if they are interacted with */
	bool mInteractionRegisterPlayerWithCircuit;

	//@todoGC This is a good candidate for cleaning up, do we need to keep track of the build effect on a building.
	/** What build effect to use when building this building */
	UPROPERTY()
	TSubclassOf< class UFGMaterialEffect_Build > mBuildEffectTemplate;

	/** What build effect to use when dismantling this building */
	UPROPERTY()
	TSubclassOf< class UFGMaterialEffect_Build > mDismantleEffectTemplate;

	UPROPERTY()
	UFGMaterialEffect_Build* mActiveBuildEffect = nullptr; //Store the active effect so we can cancel an old one if we need to start a new.

	/** Used to sync and start build effect on buildings when created, but not after creation. Set's to true when creating a building, turns off in the construction effect finish play.*/
	UPROPERTY( Replicated, meta = ( NoAutoJson = true ) )
	AActor* mBuildEffectInstignator = nullptr; //[DavalliusA:Mon/01-04-2019] this is sett to null in default. If it's non null, we expect the build effects need to play.

	/** Name read from config */
	UPROPERTY( config, noclear, meta = (NoAutoJson = true) )
	FSoftClassPath mDismantleEffectClassName;

	/** Name read from config */
	UPROPERTY( config, noclear, meta = (NoAutoJson = true) )
	FSoftClassPath mBuildEffectClassName;

	/** Skip the build effect. */
	UPROPERTY( EditDefaultsOnly, Category = "Build Effect" )
	bool mSkipBuildEffect;

	/** Build effect speed, a constant speed (distance over time) that the build effect should have, so bigger buildings take longer */
	UPROPERTY( EditDefaultsOnly, Category = "Build Effect" )
	float mBuildEffectSpeed;

	/** Whether or not this building should use ForceNetUpdate() when a player registers/unregisters from it. */
	UPROPERTY( EditDefaultsOnly, Category = "Replication" )
	bool mForceNetUpdateOnRegisterPlayer;

	/** Flag for whether the build effect is active */
	uint8 mBuildEffectIsPlaying : 1;

	/** Flag for whether this buildable is being dismantled */
	uint8 mIsDismantled : 1;

	/** Flag to indicate whether the dismantle material should be active. Used to being able to activate the material when other effects end (like the build effect) */
	uint8 mPendingDismantleHighlighted : 1;

	/** Flag for if the buildable undergoes mesh changes and needs to update its shared material instances ( Tex. When a mesh component is added or changed after Native Begin Play */
	uint8 mReevaluateMaterialsWithSubsystem : 1;

	//@todoGC mHighlight*** only needs to be in the space elevator and hub.
	/** Name read from config */
	UPROPERTY( config, noclear, meta = (NoAutoJson = true) )
	FStringClassReference mHighlightParticleClassName;
	/** Particle system component  */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	class UParticleSystem* mHighlightParticleSystemTemplate;
	/** Particle system component  */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	class UParticleSystemComponent* mHighlightParticleSystemComponent;

	/** If this building should show highlight before first use, save when it has been shown */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_DidFirstTimeUse, meta = (NoAutoJson = true) )
	bool mDidFirstTimeUse;

	/** Should we show highlight when building this building */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	bool mShouldShowHighlight;


	UPROPERTY( EditDefaultsOnly, Category = "Stacking" )
	bool mAllowCleranceSeparationEvenIfStackedOn = false;

	/** Caching the extent for use later */
	FBox mCachedBounds;
private:
	friend class UFGFactoryConnectionComponent;
	friend class AFGBuildableSubsystem;

	/** Factory Stat id of this object, 0 if nobody asked for it yet */
	STAT( mutable TStatId mFactoryStatID; )

	/** Squared distance to closest camera */
	UPROPERTY( meta = (NoAutoJson = true) )
	float mCameraDistanceSq;

	/** The building ID this belongs to. */
	UPROPERTY( SaveGame, meta = (NoAutoJson = true) )
	int32 mBuildingID;
	
	/** The cached main mesh of this buildable */
	TArray< UMeshComponent* > mCachedMainMeshes; //@todoGC Do we still use this? Probably not, check with Ben.

	/** The widget that will present our UI. */
	UPROPERTY( EditDefaultsOnly, Category = "Interaction", meta = ( EditCondition = mIsUseable ) )
	TSubclassOf< class UFGInteractWidget > mInteractWidgetClass;

	/** Caches the number of factory components for sanity checking */
	uint8 mNumFactoryConnections;

	/** Caches the number of power components for sanity checking */
	uint8 mNumPowerConnections;

	/** Players interacting with this building */
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mInteractingPlayers;

	uint8 mParticipatedInCleranceEncroachFrameCountDown : 2; //used to indicate a recent clearance overlap for feedback. Only handled and accessed by the build gun on the local machine


	/** If you can interact with this buildable. */
	UPROPERTY( EditDefaultsOnly, Category = "Interaction" )
	uint8 mIsUseable:1;

	/** If this buildable is replicating details, i.e. for the UI. */
	uint8 mReplicateDetails:1;

	/** if true, then blueprint has implemented Factory_ReceiveTick */
	uint8 mHasBlueprintFactoryTick:1;

	/** if true, then blueprint has implemented Factory_PeekOutput */
	uint8 mHasFactory_PeekOutput:1;

	/** if true, then blueprint has implemented Factory_GrabOutput */
	uint8 mHasFactory_GrabOutput:1;

	uint8 mHasColorableComponents : 1;
	uint8 mHasColorableComponentsDirty : 1; //make us update the value the first time

	/** ID given from server when constructed. Has not been assigned a value by server if 0. */
	UPROPERTY(transient, replicated)
	FNetConstructionID mNetConstructionID;

	//@todoGC Weak pointer here but need to go fishing in old saves.
	/** Recipe this building was built with, e.g. used for refunds and stats. */
	UPROPERTY( SaveGame, Replicated )
	TSubclassOf< class UFGRecipe > mBuiltWithRecipe;

	/** Time when this building was built */
	UPROPERTY( SaveGame, meta = (NoAutoJson = true) )
	float mBuildTimeStamp;

	/** Caching the shape component once we have gotten it */
	UPROPERTY()
	UShapeComponent* mCachedShapeComponent;

	/** Has this buildable created its material dynamic material instances for shared coloring? */
	bool mHasInitializedMaterialManagers;

	/** Should the building start as hidden when playing the build effect */
	UPROPERTY( EditDefaultsOnly, Category = "Build Effect" )
    bool mHideOnBuildEffectStart;

public:
	FORCEINLINE ~AFGBuildable() = default;
};

/** Definition for GetDefaultComponents. */
template< class T, class AllocatorType >
void AFGBuildable::GetDefaultComponents( TArray< T*, AllocatorType >& out_components ) const
{
	AFGBuildable* defaultBuildable = GetClass()->GetDefaultObject< AFGBuildable >();
	check( defaultBuildable );

	// Get native components.
	defaultBuildable->GetComponents( out_components );

	// Get blueprint components.
	UBlueprintGeneratedClass* actualBlueprintClass = Cast< UBlueprintGeneratedClass >( GetClass() );
	if( actualBlueprintClass )
	{
		// For blueprints we need to get the class hierarchy.
		TArray< const UBlueprintGeneratedClass* > blueprintClasses;
		const bool isErrorFree = UBlueprintGeneratedClass::GetGeneratedClassesHierarchy( actualBlueprintClass, blueprintClasses );
		if( isErrorFree )
		{
			// Go through the whole hierarchy.
			for( const UBlueprintGeneratedClass* blueprintClass : blueprintClasses )
			{
				// Go through all component templates.
				for( USCS_Node* node : blueprintClass->SimpleConstructionScript->GetAllNodes() )
				{
					// If it's of the desired type.
					if( T* component = Cast< T >( node->GetActualComponentTemplate( actualBlueprintClass ) ) )
					{
						out_components.Add( component );
					}
				}
			}
		}
		else
		{
			// Can only happen in the editor.
			UE_LOG( LogGame, Warning, TEXT( "%s::GetDefaultComponents, the class '%s' has compiler errors." ),
					*GetName(), *GetClass()->GetName() );
		}
	}
}

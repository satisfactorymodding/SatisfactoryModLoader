// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Actor.h"
#include "FGUseableInterface.h"
#include "ItemAmount.h"
#include "FGDismantleInterface.h"
#include "FGBlueprintFunctionLibrary.h"
#include "Animation/AnimInstance.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/SCS_Node.h"
#include "FGSaveInterface.h"
#include "FactoryTick.h"
#include "FGColorInterface.h"
#include "Replication/FGReplicationDetailActorOwnerInterface.h"
#include "FGBuildableSubsystem.h"
#include "FGBuildingTagInterface.h"
#include "FGAttachmentPoint.h"
#include "FGDecorationTemplate.h"
#include "FGRemoteCallObject.h"

#include "FGBuildable.generated.h"

//@todonow These should CAPS_CASE according to the coding standard
static const FString MainMeshName( TEXT( "MainMesh" ) );
static const FName ClearanceDetectorVolumeName( TEXT( "ClearanceDetector" ) ); //@todo There's a duplicate of this in the CPP file.



DECLARE_DYNAMIC_MULTICAST_DELEGATE( FBuildableDismantledSignature );

// Replication graph related delegates
DECLARE_MULTICAST_DELEGATE_ThreeParams( FOnRegisteredPlayerChanged, class AFGBuildable*, class AFGCharacterPlayer* /* registered player */, bool /* bIsUseStateActive */ );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnReplicationDetailActorStateChange, class IFGReplicationDetailActorOwnerInterface*, bool );

/**
 * Production status of the factory, i.e. displayed on the indicator.
 */
UENUM( BlueprintType )
enum class EProductionStatus : uint8
{
	IS_NONE,
	IS_PRODUCING,
	IS_PRODUCING_WITH_CRYSTAL, //We have a crystal in the potential slot and are producing
	IS_STANDBY,
	IS_ERROR,
	IS_MAX
};
DECLARE_MULTICAST_DELEGATE_OneParam( FProductionStatusChanged, EProductionStatus );


/**
 *	Rco for all Signifigance based network logic.
 *	main motivation for this is to reduce the number of objects per unique instance in the world like ladders & trigger boxes.
 *	This should improve scalability for the game to later phases and reduce memory overhead. */
UCLASS()
class FACTORYGAME_API UFGSignificantNetworkRCO : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGSignificantNetworkRemoteCallObject = false;

	UFUNCTION( Server, Reliable )
    void Server_RequestDecoratorSignificantComponents( AFGBuildable* actor, AFGPlayerController* controller );

	UFUNCTION( Server, Reliable )
    void Server_RemoveDecoratorSignificantComponents( AFGBuildable* actor, AFGPlayerController* controller );
};



/**
 * Base for everything buildable, buildable things can have factory connections, power connections etc.
 *
 * There are two tick functions on buildables, PrimaryActorTick and FactoryTick.
 * PrimaryActorTick is disabled when the buildable is to far away to to not waste cycles on animations and other effects.
 * FactoryTick is always enabled (as long as bCanEverTick is true) so that the factory part of buildings always can simulate.
 */
UCLASS( Abstract, Config=Engine, Meta=(AutoJson=true) )
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
	void SetCustomizationData_Implementation( const FFactoryCustomizationData& customizationData );
	void SetCustomizationData_Native( const FFactoryCustomizationData& customizationData );
	void ApplyCustomizationData_Implementation( const FFactoryCustomizationData& customizationData );
	void ApplyCustomizationData_Native( const FFactoryCustomizationData& customizationData );
	FFactoryCustomizationData GetCustomizationData_Implementation() { return mCustomizationData; }
	FFactoryCustomizationData& GetCustomizationData_Native() { return mCustomizationData; }
	bool GetCanBeColored_Implementation();
	virtual bool IsColorApplicationDeferred() { return false; }
	virtual bool CanApplyDeferredColorToBuildable( FVector hitLocation, FVector hitNormal, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController ) { return false; }
	virtual void ApplyDeferredColorToBuildable( FVector hitLocation, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController ) {};
	virtual void StartIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter, bool isValid = true );
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
	virtual void GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const override;
	//~ End IFGDismantleInferface

	virtual void StartIsLookedAtForConnection( class AFGCharacterPlayer* byCharacter, class UFGCircuitConnectionComponent* overlappingConnection );
	virtual void StopIsLookedAtForConnection( class AFGCharacterPlayer* byCharacter );

	/** Called in ConfigureActor from the hologram. */
	void SetBuiltWithRecipe( TSubclassOf< class UFGRecipe > recipe ) { mBuiltWithRecipe = recipe; }

	/** Called in ConfigureActor from the hologram. */
	void SetOriginalBuildableVariant( const TSubclassOf< AFGBuildable > originalVariant ) { mOriginalBuildableVariant = originalVariant; }

	/** Getters for the built with recipe. */
	FORCEINLINE TSubclassOf< class UFGRecipe > GetBuiltWithRecipe() const { return mBuiltWithRecipe; }
	TSubclassOf< class UFGItemDescriptor > GetBuiltWithDescriptor() const;
	template< class C > TSubclassOf< C > GetBuiltWithDescriptor() const { return *GetBuiltWithDescriptor(); }

	/** Shutdown this building. */
	void TurnOffAndDestroy();

	/* The state the pool handles get registered in, useful for lights and other components that reacts to power change.*/
	virtual bool GetPoolHandleInitialState() const;

	/* Creates all component from the decorator that should be constructed on significance  */
	virtual bool CreateDecoratorSignificantComponents( class AFGPlayerController* controller );

	/* Gets called for every component dynamically spawned from the decorator class. */
	virtual void ConfigureDynamicDecoratorComponent( USceneComponent* newComponent );

	/* Removes current controller from the active list, when the list is empty it will remove the significant components. */
	void TryRemoveDecoratorSignificantComponents( class AFGPlayerController* controller );

	/* Removes all component when no client is significant anymore. */
	virtual void RemoveDecoratorSignificantComponents( );

	TArray<USceneComponent*> GetGeneratedSignificantComponents() { return mGeneratedSignificantComponents; }
	
	/** Finds, caches and returns the MainMesh of this buildable */
	UFUNCTION( BlueprintCallable, Category = "Buildable" )
	const TArray< class UMeshComponent* >& GetMainMeshes();

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
	class UFGClearanceComponent* GetClearanceComponent();

	UFUNCTION( BlueprintPure, Category = "Buildable" )
	class UFGComplexClearanceComponent* GetComplexClearanceComponent() const { return mComplexClearanceComponent; }

	/** Spawns the complex clearance component if one can be found on the decorator class. Returns it if successful. */
	UFGComplexClearanceComponent* SpawnComplexClearanceComponent();
	void DestroyComplexClearanceComponent();

	/**Function to get info about participation in clearance overlap feedback for the local machines hologram placement*/
	uint8 GetParticipatedInCleranceEncroachFrameCountDown(){ return mParticipatedInCleranceEncroachFrameCountDown; }
	void SetParticipatedInCleranceEncroachFrameCountDown( uint8 value ){ mParticipatedInCleranceEncroachFrameCountDown = FMath::Min( value, (uint8 )3 ); }

	bool ShouldCreateClearanceMeshRepresentation() const { return mCreateClearanceMeshRepresentation; }

	/** Get the number of connections components on this buildable, may not be the same as the number of usable connections. */
	uint8 GetNumPowerConnections() const;
	uint8 GetNumFactoryConnections() const;
	uint8 GetNumFactoryOuputConnections() const;

	UFUNCTION( BlueprintPure, Category = "Buildable" )
	bool ShouldModifyWorldGrid() const { return mShouldModifyWorldGrid; }

	UFUNCTION( BlueprintPure, Category = "Buildable" )
	bool ShouldShowAttachmentPointVisuals() const { return mShouldShowAttachmentPointVisuals; }

	/** Fills an array with all attachment points of this buildable. */
	virtual void GetAttachmentPoints( TArray< const FFGAttachmentPoint* >& out_points ) const;

	/** Creates an array of attachment points from components on this buildable and its deco class. */
	void CreateAttachmentPointsFromComponents( TArray< FFGAttachmentPoint >& out_points, AActor* owner ) const;

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

	/* Returns a default object containing cosmetic components used for the pooler. */
	TSubclassOf< class AFGDecorationTemplate > GetDecorationTemplate() const { return mDecoratorClass; }

	/** Helper to get the cost multiplier for a buildable given its length and how long each cost segment is. */
	static int32 GetCostMultiplierForLength( float totalLength, float costSegmentLength );

	/** Get if dormancy is expected to toggle when interaction ceases. This is used by the buildable subsystem to toggle later (after interaction) on rep detail actor cleanup */
	bool GetToggleDormancyOnInteraction() const { return mToggleDormancyOnInteraction; }

	/** Return the specified default swatch for this buildable. If one is not specified return the default swatch*/	
	UFUNCTION()
	class TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > GetDefaultSwatchCustomizationOverride( UObject* worldContext );

	/** Is this buildable dismantled? */
	FORCEINLINE bool GetIsDismantled() const { return mIsDismantled; }

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

	/** Called whenever mIsReplicatingDetails has changed, used to enable disable replication of subobjects. */
	virtual void OnReplicatingDetailsChanged();

	/**
	 * For custom connections, if we want a custom implementation for
	 * Called if mForwardPeekAndGrabToProxy is set in the connection.
	 */
	UFUNCTION( BlueprintNativeEvent, CustomEventUsing=mHasFactory_PeekOutput, Category = "Buildable|Connections" )
	bool Factory_PeekOutput( const class UFGFactoryConnectionComponent* connection, TArray< FInventoryItem >& out_items, TSubclassOf< UFGItemDescriptor > type ) const;

	/**
	 * For custom connections, if we want a custom implementation for peek
	 * Called if mForwardPeekAndGrabToProxy is set in the connection.
	 */
	UFUNCTION( BlueprintNativeEvent, CustomEventUsing=mHasFactory_GrabOutput, Category = "Buildable|Connections" )
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

	/** Update all none Instanced Mesh Colors / params. This sets the primitive data so is responsible for coloring Skel_Meshes etc. */
	UFUNCTION( BlueprintCallable, Category="Buildable|Customization" )
	void ApplyMeshPrimitiveData( const FFactoryCustomizationData& customizationData );

	UFUNCTION()
	void ApplyHasPowerCustomData();

	/** Visually (CustomData / PIC ) does this building have "power". For now powered buildings this should always return true to light the emissive channel */
	FORCEINLINE virtual float GetEmissivePower() { return 1.f; }

	/** Setter for mDidFirstTimeUse so we can ensure that it is flagged for replication property */
	void SetDidFirstTimeUse( bool didUse );

	UFUNCTION( BlueprintCallable, Category = "Buildable" )
	TArray< UStaticMeshComponent* > CreateBuildEffectProxyComponents();

	UFUNCTION( BlueprintCallable, Category = "Buildable" )
	void DestroyBuildEffectProxyComponents();
	
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

	/** Let the client know custom color / material information has been applied to the building */
	UFUNCTION()
	void OnRep_CustomizationData();

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

	/* Pool handles used by the pooling system. */
	TArray< struct FPoolHandle* > mPoolHandles;

	UPROPERTY(EditDefaultsOnly, Category = "Buildable")
	TSubclassOf< class AFGDecorationTemplate > mDecoratorClass;

	/** Callback for when the production indicator state changes. Called locally on both server and client. */
	FProductionStatusChanged mOnProductionStatusChanged;
	
protected:
	//@todorefactor With meta = ( ShowOnlyInnerProperties ) it does not show and PrimaryActorTick seems to be all custom properties, so I moved to another category but could not expand.
	/** Controls if we should receive Factory_Tick and how frequent. */
	UPROPERTY( EditDefaultsOnly, Category = "Factory Tick", meta = (NoAutoJson = true) )
	FFactoryTickFunction mFactoryTickFunction;

	/** The color slot of this buildable */
	UPROPERTY( EditAnywhere, SaveGame, Replicated, meta = (NoAutoJson = true) )
	uint8 mColorSlot = 0;

	/** Custom Color/Mat data. Stored in a TArray so it can be variable (or 0 size) to reduce save footprint since many buildings will only utilize the slot index */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CustomizationData, meta = ( NoAutoJson = true ) )
	FFactoryCustomizationData mCustomizationData;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable" )
	TSubclassOf< UFGFactoryCustomizationDescriptor_Swatch > mDefaultSwatchCustomizationOverride;

	/** if true, then this buildable will accept swatches and patterns */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	bool mAllowColoring;

	/** HAXX FLAG! Buildings set this to start replicating power graph if they are interacted with */
	bool mInteractionRegisterPlayerWithCircuit;

	//@todoGC This is a good candidate for cleaning up, do we need to keep track of the build effect on a building.
	/** What build effect to use when building this building */
	UPROPERTY()
	TSubclassOf< class UFGMaterialEffect_Build > mBuildEffectTemplate;

	/** What build effect to use when dismantling this building */
	UPROPERTY()
	TSubclassOf< class UFGMaterialEffect_Build > mDismantleEffectTemplate;

	/** Store the active effect so we can cancel an old one if we need to start a new. */
	UPROPERTY()
	UFGMaterialEffect_Build* mActiveBuildEffect;

	/**
	 * Used to sync and start build effect on buildings when created, but not after creation.
	 * This is sett to null in default. If it's non null, we expect the build effects need to play.
	 */
	UPROPERTY( Replicated, meta = ( NoAutoJson = true ) )
	AActor* mBuildEffectInstignator;

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
	
	/** Whether or not this building should set Dorm_Awake when a player registers interaction and to set Dorm_DormantAll when no more players are interacting. */
	UPROPERTY( EditDefaultsOnly, Category = "Replication" )
	bool mToggleDormancyOnInteraction;

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

	/** Whether or not we should create the visual mesh representation for attachment points. */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	bool mShouldShowAttachmentPointVisuals;

	/** Whether or not we should create a clearance mesh representation for this buildable. */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	bool mCreateClearanceMeshRepresentation;

	/** Caching the extent for use later */
	FBox mCachedBounds;

	/** List of attachmentpoints for this buildable. */
	UPROPERTY()
	TArray< FFGAttachmentPoint > mAttachmentPoints;
	
private:
	friend class UFGFactoryConnectionComponent;
	friend class AFGBuildableSubsystem;

	/** Factory Stat id of this object, 0 if nobody asked for it yet */
	STAT( mutable TStatId mFactoryStatID; )
	
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

	/** Used to indicate a recent clearance overlap for feedback. Only handled and accessed by the build gun on the local machine */
	uint8 mParticipatedInCleranceEncroachFrameCountDown : 2;

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

	/** ID given from server when constructed. Has not been assigned a value by server if 0. */
	UPROPERTY(transient, replicated)
	FNetConstructionID mNetConstructionID;

	//@todoGC Weak pointer here but need to go fishing in old saves.
	/** Recipe this building was built with, e.g. used for refunds and stats. */
	UPROPERTY( SaveGame, Replicated )
	TSubclassOf< class UFGRecipe > mBuiltWithRecipe;

	/** If we were built as a variant, this is the class of the buildable we are a variant of. */
	UPROPERTY( SaveGame, Replicated )
	TSubclassOf< class AFGBuildable > mOriginalBuildableVariant;

	/** Time when this building was built */
	UPROPERTY( SaveGame, meta = (NoAutoJson = true) )
	float mBuildTimeStamp;

	/** Clearance component of the buildable. */
	UPROPERTY()
	class UFGClearanceComponent* mClearanceComponent;
	
	/** Complex clearance component of the buildable. */
	UPROPERTY()
	class UFGComplexClearanceComponent* mComplexClearanceComponent;

	/** Has this buildable created its material dynamic material instances for shared coloring? */
	bool mHasInitializedMaterialManagers;

	/** Should the building start as hidden when playing the build effect */
	UPROPERTY( EditDefaultsOnly, Category = "Build Effect" )
    bool mHideOnBuildEffectStart;

	/** Whether or not this buildable should affect the WorldGrid subsystem */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	bool mShouldModifyWorldGrid;

	UPROPERTY( Transient )
	TArray< UStaticMeshComponent* > mProxyBuildEffectComponents;

	UPROPERTY( Transient, VisibleAnywhere )
	TArray< class AFGPlayerController* > mActiveSignificantControllers;

	UPROPERTY( Transient, VisibleAnywhere )
	TArray< USceneComponent* > mGeneratedSignificantComponents;
};

/** Definition for GetDefaultComponents. */
template< class T, class AllocatorType >
void AFGBuildable::GetDefaultComponents( TArray< T*, AllocatorType >& out_components ) const
{
	AFGBuildable* defaultBuildable = GetClass()->GetDefaultObject< AFGBuildable >();
	fgcheck( defaultBuildable );

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

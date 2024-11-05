// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AbstractInstanceInterface.h"
#include "AkSwitchValue.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/SCS_Node.h"
#include "FGAttachmentPoint.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FGBuildableSubsystem.h"
#include "FGColorInterface.h"
#include "FGDecorationTemplate.h"
#include "FGDismantleInterface.h"
#include "FGFactoryClipboard.h"
#include "FGRainOcclusionActor.h"
#include "FGRemoteCallObject.h"
#include "FGSaveInterface.h"
#include "FGUseableInterface.h"
#include "FactoryTick.h"
#include "FGClearanceData.h"
#include "FGClearanceInterface.h"
#include "GameFramework/Actor.h"
#include "ItemAmount.h"
#include "GameplayTagContainer.h"
#include "FGBuildable.generated.h"

// Begin forward declaration
class UAkComponent;
class AFGBuildEffectActor;
class UAkAudioEvent;
// End

DECLARE_STATS_GROUP( TEXT( "FactoryQuick" ), STATGROUP_FactoryQuick, STATCAT_Advanced );

#define FACTORY_QUICK_SCOPE_CYCLE_COUNTER(Stat) \
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT(#Stat),Stat,STATGROUP_FactoryQuick)

static const FString MAIN_MESH_NAME( TEXT( "MainMesh" ) );

#define GetLWActorTransform( inputActor ) IAbstractInstanceInterface::Execute_GetLightweightInstanceActorTransform( inputActor )

// Replication graph related delegates
DECLARE_MULTICAST_DELEGATE_ThreeParams( FOnRegisteredPlayerChanged, class AFGBuildable*, class AFGCharacterPlayer* /* registered player */, bool /* bIsUseStateActive */ );


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
 *	Rco for all Significance based network logic.
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

USTRUCT()
struct FCustomizationDescToRecipeData
{
	GENERATED_BODY()
	UPROPERTY( EditDefaultsOnly )
	TSoftClassPtr< UFGFactoryCustomizationDescriptor_Material > mMaterial;

	UPROPERTY( EditDefaultsOnly )
	TSoftClassPtr< class UFGRecipe > mRecipe;
};

UCLASS( EditInlineNew )
class FACTORYGAME_API UFGBuildableSparseDataObject : public UObject
{
	GENERATED_BODY()

public:
	/** Class of the build effect actor for this buildable */
	UPROPERTY( EditDefaultsOnly, Category = "Build Effect" )
	TSubclassOf<AFGBuildEffectActor> mSparseBuildEffectActorTemplate;
	
	/* Array of particle effects used for alien overclocking, Expected usage:
	 * For lookup AO_#ArrayIndex_01, AO_#ArrayIndex_02 etc.  */
	UPROPERTY( EditDefaultsOnly, Category = "Alien Overclocking" )
	TArray<class UNiagaraSystem*> AlienOverClockingParticles;

	/** Audio event to start the alien overclocking loop SFX */
	UPROPERTY( EditDefaultsOnly, Category = "Alien Overclocking" )
	UAkAudioEvent* AlienOverClockingLayeredLoopingEvent;

	/** Audio event to stop the alien overclocking loop SFX */
	UPROPERTY( EditDefaultsOnly, Category = "Alien Overclocking" )
	UAkAudioEvent* AlienOverClockingLayeredLoopingStopEvent;

	/** Audio switch to pass th the alien overclocking loop event, for customizing it */
	UPROPERTY( EditDefaultsOnly, Category = "Alien Overclocking" )
	UAkSwitchValue* AlienOverclockingSweetenerValue;

	/** Offset on the Z axis from the actor location on which the alien overclocking audio component should be spawned, in world units */
	UPROPERTY( EditDefaultsOnly, Category = "Alien Overclocking" )
	float AlienOverClockingZOffset;
	
	/** Attenuation scaling factor for the alien overclocking audio */
	UPROPERTY( EditDefaultsOnly, Category = "Alien Overclocking" )
	float AlienOverClockingAttenuationScalingFactor{12.0f};

	/** Volume of the alien overclocking audio to be passed to the audio as RTPC parameter */
	UPROPERTY( EditDefaultsOnly, Category = "Alien Overclocking" )
	float AlienOverClockingVolumeDB_RTPC;

	/** Highpass RTPC to be passed to the overclocking audio */
	UPROPERTY( EditDefaultsOnly, Category = "Alien Overclocking" )
	float AlienOverClockingHighpass_RTPC;

	/** Pitch of the overclocking audio to be passed to the event as RTPC parameter */
	UPROPERTY( EditDefaultsOnly, Category = "Alien Overclocking" )
	float AlienOverClockingPitch_RTPC;

	/** Tag of the buildable to account for the total amount of it for granting certain achievements */
	UPROPERTY( EditDefaultsOnly, Category = "Achievement")
	FGameplayTag mBuildableTag;

	UPROPERTY( EditDefaultsOnly,Category = "Visuals|FogPlanes" )
	TArray<FTransform> mFogPlaneLocations;

	UPROPERTY( EditDefaultsOnly,Category = "Visuals|FogPlanes" )
	UStaticMesh* FogPlaneMesh;

#if WITH_EDITORONLY_DATA
	/** True if we migrated old data for alien overclocking from buildable to the Sparse Data Object */
	UPROPERTY()
	bool bMigratedOldAlienOverclockingData{false};
#endif
};


/**
 * Base for everything buildable, buildable things can have factory connections, power connections etc.
 *
 * There are two tick functions on buildables, PrimaryActorTick and FactoryTick.
 * PrimaryActorTick is disabled when the buildable is to far away to to not waste cycles on animations and other effects.
 * FactoryTick is always enabled (as long as bCanEverTick is true) so that the factory part of buildings always can simulate.
 */
UCLASS( Abstract, Meta=(AutoJson=true) )
class FACTORYGAME_API AFGBuildable : public AActor, public IFGDismantleInterface, public IFGSaveInterface, public IFGColorInterface, public IFGUseableInterface, public IFGFactoryClipboardInterface, public IAbstractInstanceInterface, public IFGClearanceInterface
{
	GENERATED_BODY()
public:	
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	AFGBuildable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR
	virtual void CheckForErrors() override;
#endif

	// Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
	virtual void PostLoad() override;
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

	// Begin IAbstractInstanceInterface
	virtual TArray<struct FInstanceData> GetActorLightweightInstanceData_Implementation() override;
	virtual bool DoesContainLightweightInstances_Implementation() override { return DoesContainLightweightInstances_Native(); }
	virtual FTransform GetLightweightInstanceActorTransform_Implementation() const override { return GetActorTransform(); }
		//mLightweightTransform; }
	virtual FInstanceHandleArray GetLightweightInstanceHandles() const override { return FInstanceHandleArray{mInstanceHandles}; }
	virtual void PostLazySpawnInstances_Implementation() override;
	// End IAbstractInstanceInterface

	// Begin IFGClearanceInterface
	virtual void GetClearanceData_Implementation( TArray< FFGClearanceData >& out_data ) const override;
	// End IFGClearanceInterface

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const;
#endif

	/** Add clearance data to this buildable. */
	void AddClearanceData( const FFGClearanceData& newData );
	void AddClearanceData( const TArray< FFGClearanceData >& newData );
	void ResetClearanceData();

	/** Returns a box created by combining all clearence boxes on this buildable. */
	UFUNCTION( BlueprintPure, Category = "Clearance" )
	FBox GetCombinedClearanceBox() const;

	FORCEINLINE FTransform GetActorLightweightInstanceTransform() const { return GetActorTransform(); }
	
	/* Object containing default variables shared for all of the same class. */
	UFGBuildableSparseDataObject* GetBuildableSparseData() const { return mBuildableSparseDataCDO; }

	//~ Begin IFGColorInterface
	void SetCustomizationData_Implementation( const FFactoryCustomizationData& customizationData );
	void SetCustomizationData_Native( const FFactoryCustomizationData& customizationData, bool skipCombine = false );
	void ApplyCustomizationData_Implementation( const FFactoryCustomizationData& customizationData );
	void ApplyCustomizationData_Native( const FFactoryCustomizationData& customizationData );
	FFactoryCustomizationData GetCustomizationData_Implementation() { return mCustomizationData; }
	FFactoryCustomizationData& GetCustomizationData_Native() { return mCustomizationData; }
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Implementation() { return mFactorySkinClass; }
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Native() { return mFactorySkinClass; }
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Native();
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Implementation();
	bool GetCanBeColored_Implementation();
	bool GetCanBePatterned_Implementation();
	virtual bool IsColorApplicationDeferred() { return false; }
	virtual bool CanApplyDeferredColorToBuildable( FVector hitLocation, FVector hitNormal, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController ) { return false; }
	virtual void ApplyDeferredColorToBuildable( FVector hitLocation, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController ) {};
	virtual void StartIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter, bool isValid = true );
	virtual void StopIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter );
	//~ End IFGColorInterface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
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
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled ) const override;
	virtual FVector GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const override;
	virtual void PreUpgrade_Implementation() override;
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	virtual void Dismantle_Implementation() override;
	virtual void StartIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const override;
	virtual FText GetDismantleDisplayName_Implementation(AFGCharacterPlayer* byCharacter) const override;
	virtual void GetDismantleDependencies_Implementation(TArray<AActor*>& out_dismantleDependencies) const override;
	//~ End IFGDismantleInterface

	/** Gets the parent actor that this buildable belongs to, if any. */
	UFUNCTION( BlueprintPure, Category = "Dismantle" )
	AActor* GetParentBuildableActor() const { return mParentBuildableActor; }

	/** Sets the parent actor that this buildable belongs to. Used when redirecting dismantling, sampling, etc. */
	UFUNCTION( BlueprintCallable, Category = "Dismantle" )
	void SetParentBuildableActor( AActor* parentActor ) { mParentBuildableActor = parentActor; }

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
	
	UFUNCTION()
	void ApplyHasPowerCustomData();
	
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

	/** Called when the build effect is finished to notify the blueprints */
	UFUNCTION( BlueprintImplementableEvent, Category = "Buildable|Build Effect", DisplayName = "On Build Effect Finished" )
	void K2_OnBuildEffectFinished();

	UFUNCTION( BlueprintCallable, Category = "Buildable|Build Effect" )
	virtual void PlayBuildEffectActor( AActor* inInstigator );

	UFUNCTION()
	virtual void ExecutePlayBuildActorEffects();
	
	UFUNCTION()
	virtual void OnBuildEffectActorFinished();

	/*Handles logic for blueprint / zooping build effect behaviour, returns true when it should be a part of the multi
	 * build effect actor, false when it shouldn't */
	virtual bool HandleBlueprintSpawnedBuildEffect( AFGBuildEffectActor* inBuildEffectActor );

	UFUNCTION( Reliable, NetMulticast )
	virtual void NetMulticast_Dismantle();
	void CloseAllInteractUIsWithBuildable() const;
	void PlayDismantleEffects();
	virtual void OnDismantleEffectFinished();

	class UFGMaterialEffect_Build* GetActiveBuildEffect();

	/** Returns true if this buildable can be sampled */
	UFUNCTION( BlueprintNativeEvent )
	bool CanBeSampled() const;

	/** Used by the blueprint subsystem to notify a buildable a build effect is playing (before the build effect starts so that begin play can expect it) */
	void SetIsPlayingBuildEffect( bool isPlaying ) { mBuildEffectIsPlaying = isPlaying; }

	/** Used by the blueprint subsystem that a Lightweight Buildable is playing a blueprint build effect*/
	void SetIsPlayingBlueprintBuildEffect( bool isPlaying ) { mBlueprintBuildEffectIsPlaying = isPlaying; }

	/** Returns whether or not the build effect is currently running */
	UFUNCTION( BlueprintPure, Category = "Buildable|Build Effect" )
	bool IsPlayingBuildEffect() const { return mBuildEffectIsPlaying; }
	
	/** Returns the cached bounds */
	FORCEINLINE FBox GetCachedBounds() const { return mCachedBounds; }

	/** Returns list of players currently interacting with building. */
	FORCEINLINE TArray< class AFGCharacterPlayer* > GetInteractingPlayers() const { return mInteractingPlayers; }

	/**
	 * Hides the buildable and disables the collision. Will hide instanced meshes and static instances as well
	 */
	UFUNCTION( BlueprintCallable, Category = "Buildable" )
	void SetBuildableHiddenInGame( bool hide = false );

	/** Helper function for getting buildable classes from recipes
	*	@note Useful when generating child holograms based off their recipe
	*/
	static TSubclassOf< AFGBuildable > GetBuildableClassFromRecipe( TSubclassOf< class UFGRecipe > inRecipe );

	/** Whether or not this building should block guidelines "clear path" traces for the specified hologram. */
	virtual bool ShouldBlockGuidelinePathForHologram( const class AFGHologram* hologram ) const;
	/** Whether or not this building should show center guidelines for the specified hologram. */
	virtual bool ShouldShowCenterGuidelinesForHologram( const class AFGHologram* hologram ) const;

	/** Get the number of connections components on this buildable, may not be the same as the number of usable connections. */
	uint8 GetNumPowerConnections() const;
	uint8 GetNumPowerConnectionsCached() const;
	uint8 GetNumFactoryConnections() const;
	uint8 GetNumFactoryOuputConnections() const;

	UFUNCTION( BlueprintPure, Category = "Buildable" )
	FORCEINLINE bool ShouldModifyWorldGrid() const { return mShouldModifyWorldGrid; }

	UFUNCTION( BlueprintPure, Category = "Buildable" )
	FORCEINLINE bool ShouldShowAttachmentPointVisuals() const { return mShouldShowAttachmentPointVisuals; }

	void SetMarkedForDismantle() { mIsAboutToBeDismantled = true; }
	FORCEINLINE bool IsAboutToBeDismantled() const { return mIsAboutToBeDismantled; }

	/** Fills an array with all attachment points of this buildable. */
	virtual void GetAttachmentPoints( TArray< const FFGAttachmentPoint* >& out_points ) const;

	/** Creates an array of attachment points from components on this buildable and its deco class. */
	void CreateAttachmentPointsFromComponents( TArray< FFGAttachmentPoint >& out_points, AActor* owner ) const;

	/** Should this buildable be relevant when considering if a location is near a base/factory area */
	UFUNCTION( BlueprintNativeEvent, Category = "Buildable" )
	bool ShouldBeConsideredForBase();

	/** Set on begin play.*/
	UFUNCTION( BlueprintNativeEvent, Category = "Buildable" )
	float GetConsideredForBaseWeight() const;
	float GetConsideredForBaseWeight_Implementation() const { return mIsConsideredForBaseWeightValue; }

	/** Sets the display name for this buildable. Only for editor use */
	UFUNCTION( BlueprintCallable, Category = "Editor|Buildable" )
	static void SetBuildableDisplayName( TSubclassOf< AFGBuildable > inClass, FText displayName );

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

	FORCEINLINE bool DoesAffectOcclusionSystem() const 										{ return mAffectsOcclusion; }
	FORCEINLINE EFGRainOcclusionShape GetOcclusionShape() const 							{ return mOcclusionShape; }
	FORCEINLINE UStaticMesh* GetCustomOcclusionShape() const 								{ return mCustomOcclusionShape; }
	FORCEINLINE TArray<FBox> GetOcclusionBoxes() const  									{ return mOcclusionBoxInfo; }
	FORCEINLINE float GetOcclusionShapeCustomScaleOffset() const 							{ return mScaleCustomOffset; }
	FORCEINLINE EFGRainOcclusionShapeScaling GetOcclusionShapeCustomScalingMode() const		{ return mCustomScaleType; }
	FORCEINLINE virtual FSimpleBuildingInfo GetRainOcclusionShape()							{ return FSimpleBuildingInfo(this); }

	/* Not replicated! */
	void ToggleInstanceVisibility( bool bNewState );

	/** Specify that this buildable is inside of a blueprint designer. */
	void SetInsideBlueprintDesigner( class AFGBuildableBlueprintDesigner* designer );
	class AFGBuildableBlueprintDesigner* GetBlueprintDesigner() const;

	/** Gets the blueprint proxy this buildable belongs to. */
	FORCEINLINE class AFGBlueprintProxy* GetBlueprintProxy() const { return mBlueprintProxy; }

	/**
	* Called from blueprint subsystem after being loaded. Can be used to run custom logic post serialization
	*/
	virtual void PreSerializedToBlueprint();

	/**
	 * Called After blueprint serialization. This is commonly used for reapplying back properties that we dont want saved but
	 * may be expected to exist like in UI interaction. Tex. DroneStations need to clear their DroneInfo so it isn't saved however we still want
	 * that dummy info around after (so it gets cleared and then set back)
	 */
	virtual void PostSerializedToBlueprint();
	
	/**
	 * Called from blueprint subsystem after being loaded. Can be used to run custom logic post serialization
	 */
	virtual void PostSerializedFromBlueprint( bool isBlueprintWorld = false );
	
	/** Assign a blueprint build effect id. The blueprint subsystem uses this to sync and then spawn build effects for blueprint buildings on clients*/
	void SetBlueprintBuildEffectID( int32 buildEffectID ) { mBlueprintBuildEffectID = buildEffectID; }
	int32 GetBlueprintBuildEffectID() const { return mBlueprintBuildEffectID; }

	/** @return the build effect used by this buildable */
	UFUNCTION( BlueprintNativeEvent, Category = "Buildable|Build Effect" )
	TSoftClassPtr< UFGMaterialEffect_Build > GetBuildEffectTemplate() const;

	/** Set from deferred spawn for special buildables that are just temporaries spawned by the lightweightBuildableSubsystem */
	void SetIsLightweightTemporary( TArray< FInstanceHandle* >& instanceHandles, int32 indexOfRuntimeData );
	FORCEINLINE bool GetIsLightweightTemporary() const { return mIsLightweightTemporary; }
	
	/** When a lightweight temporary this index will be set to avoid having to search for the runtime data when its modified */
	FORCEINLINE int32 GetRuntimeDataIndex() const { return mRuntimeDataIndex; }
	
	/** Sets that this buildable has been requested for dismantle. Clients use this to track locally */
	FORCEINLINE void SetIsPendingDismantleRemoval( bool isPending ) { mIsPendingDismantleRemoval = isPending; }
	FORCEINLINE bool GetIsPendingDismantleRemoval() const { return mIsPendingDismantleRemoval; }
	

	/**
	 * Set via the lightweight subsystem when its clearing up stale lightweight temps. This "informs" the buildable that its destruction is just
	 * It being converted back into an instance and thus it shouldn't notify the subsystem of its destruction (in the even of dismantle)
	 */
	FORCEINLINE void SetIsStaleLightweightTemporary() { mIsStaleLightweightTemporary = true; }

	/** Called by paint state to notify a temporary contains updated customization data */
	void SetTemporaryHasModifiedCustomizationData() { mHasTemporaryModifiedItsCustomiazationData = true; }

	FORCEINLINE void SetBlockCleanupOfTemporary(bool blockCleanUp ) { mBlockCleanupForStaleTemporary = blockCleanUp; }
	FORCEINLINE bool GetBlockCleanupOfTemporary() const { return mBlockCleanupForStaleTemporary; }
	
	/** @return the dismantle effect used by this buildable */
	UFUNCTION( BlueprintNativeEvent, Category = "Buildable|Build Effect" )
	TSoftClassPtr< UFGMaterialEffect_Build > GetDismantleEffectTemplate() const;

#if WITH_EDITOR
	/** Returns the ID of the timelapse bucket this buildable is in */
	UFUNCTION( BlueprintPure, Category = "Cinematic | Timelapse" )
	FORCEINLINE int32 GetTimelapseBucketId() const { return mTimelapseBucketId; }

	/** Returns the delay from the start of the timelapse until this buildable plays it's build effect */
	UFUNCTION( BlueprintPure, Category = "Cinematic | Timelapse" )
	FORCEINLINE float GetTimelapseDelay() const { return mTimelapseDelay; }

	/** Updates the Timelapse Bucket ID of the buildable */
	UFUNCTION( BlueprintCallable, Category = "Cinematic | Timelapse" )
	FORCEINLINE void SetTimelapseBucketId( int32 bucketId ) { mTimelapseBucketId = bucketId; }

	/** Updates the timelapse delay of the buildable */
	UFUNCTION( BlueprintCallable, Category = "Cinematic | Timelapse" )
	FORCEINLINE void SetTimelapseDelay( float delay ) { mTimelapseDelay = delay; }
#endif

	/** For lightweight temporaries we need a way of manually setting the blueprint proxy */
	void SetBlueprintProxy( class AFGBlueprintProxy* blueprintProxy ) { mBlueprintProxy = blueprintProxy; }

	/** Most common check for determining if this buildable is to become a lightweight instance or has already been considered */
	FORCEINLINE bool ShouldConvertToLightweight() const { return HasAuthority() && GetLightweightInstanceData() && ManagedByLightweightBuildableSubsystem() && mBlueprintDesigner == nullptr; };

	/** If true, this buildable will be Destroyed and migrated to the LightweightBuildableSubsystem */
	virtual bool ManagedByLightweightBuildableSubsystem() const;

	void SetBuildEffectActor(AFGBuildEffectActor* BuildEffectActor) { mBuildEffectActor = BuildEffectActor; }
	AFGBuildEffectActor* GetBuildEffectActor() const { return mBuildEffectActor; }
	
protected:
	/** Blueprint event for when materials are updated by the buildable subsystem*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Buildable|Build Effect" )
	void OnMaterialInstancesUpdated();

	UFUNCTION( BlueprintNativeEvent, Category = "Buildable|Customization" )
	void OnSkinCustomizationApplied( TSubclassOf< class UFGFactoryCustomizationDescriptor_Skin > skin );

	/** Plays construction sound, override this event to play a custom sound. */
	UFUNCTION( BlueprintNativeEvent, BlueprintCosmetic, Category = "Buildable|Build Effect" )
	void PlayConstructSound();

	/** Plays dismantle sound, override this event to play a custom sound. */
	UFUNCTION( BlueprintNativeEvent, BlueprintCosmetic, Category = "Buildable|Build Effect" )
	void PlayDismantleSound();

	/** Ugly haxx to remove replication of graph unless any player is looking at it */
	void RegisterInteractingPlayerWithCircuit( class AFGCharacterPlayer* player );
	void UnregisterInteractingPlayerWithCircuit( class AFGCharacterPlayer* player );

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

	/* Returns the mesh that contains all sockets for the alien over clocking. Needs to be in FGBuildable because there are blueprints overriding this function already and UE is too dumb to convert them to override for a child class */
	UFUNCTION( BlueprintNativeEvent, Category = "Alien Overclocking" )
	void GetAlienOverClockingSourceMesh(UStaticMesh*& SourceMesh, FTransform& Transform);

	/** Get the widget used to interact with this buildable. */
	UFUNCTION( BlueprintPure, Category = "Buildable|Interaction" )
	FORCEINLINE class TSubclassOf< class UFGInteractWidget > GetInteractWidgetClass() const { return mInteractWidgetClass; }

	/** Toggles the pending dismantle material on buildable */
	virtual void TogglePendingDismantleMaterial( bool enabled );

	/** Set the buildable to reevaluate material instances with the buildable subsystem when applying color slot */
	UFUNCTION( BlueprintCallable, Category="Buildable")
	void FlagReevaluateMaterialOnColored() { mReevaluateMaterialsWithSubsystem = true; }

	/** Update all the instance groups for proxy meshes. This will be called when updating a buildables Skin */
	UFUNCTION( BlueprintCallable, Category = "Buildable|Customization" )
	void ApplySkinData( TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > newSkinDesc );

	/** Update all none Instanced Mesh Colors / params. This sets the primitive data so is responsible for coloring Skel_Meshes etc. */
	UFUNCTION( BlueprintCallable, Category="Buildable|Customization" )
	void ApplyMeshPrimitiveData( const FFactoryCustomizationData& customizationData );
	
	/** Visually (CustomData / PIC ) does this building have "power". For now powered buildings this should always return true to light the emissive channel */
	FORCEINLINE virtual float GetEmissivePower() { return 1.f; }
	
	UFUNCTION( BlueprintCallable, Category = "Buildable" )
	TArray< UStaticMeshComponent* > CreateBuildEffectProxyComponents();

	UFUNCTION( BlueprintCallable, Category = "Buildable" )
	void DestroyBuildEffectProxyComponents();
	
	/** Let the client know custom color / material information has been applied to the building */
	UFUNCTION()
	void OnRep_CustomizationData();

	/* Spawns all instances in the lightweight instance system associated by this buildable. */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category ="Buildable|Instancing")
	void SetupInstances( bool bInitializeHidden = false );
	virtual void SetupInstances_Native( bool bInitializeHidden = false );

	/* Tries to call the most efficient route for setting up instances. */
	FORCEINLINE void CallSetupInstances( bool bInitializeHidden = false )
	{
		if ( !mLightweightInstancesRegistered )
		{
			mLightweightInstancesRegistered = true;
			
			/* Only call native to avoid blueprint VM */
			if( !mHasSetupInstances )
			{
				SetupInstances_Native( bInitializeHidden );
				return;
			}

			SetupInstances( bInitializeHidden );
		}
	}
	
	/* Removes all instances in the lightweight instance system associated by this buildable. */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category ="Buildable|Instancing")
	void RemoveInstances();
	virtual void RemoveInstances_Native();
	/** When a buildable needs to be converted into a lightweight instance this is the way */
	bool HandleLightweightAddition();

private:
	// TODO @Ben modding support make this available in runtime.
	/* Force add material to the material desc, editor only for now.*/
	void ForceUpdateCustomizerMaterialToRecipeMapping( bool bTryToSave = false );
	
	/** Create a stat for the buildable */
	void CreateFactoryStatID() const;
	
	/** Helper to verify the connection naming. */
	bool CheckFactoryConnectionComponents( FString& out_message );
	
	UFUNCTION()
	void OnRep_LightweightTransform();

	/** Registers with background thread if it has not been done already */
	void RegisterWithBackgroundThread();
public:
	bool virtual DoesContainLightweightInstances_Native() const;
	class UAbstractInstanceDataObject* GetLightweightInstanceData() const { return mInstanceDataCDO; }
	
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

	/** Max draw distance, inactive when < 0 */
	UPROPERTY(EditDefaultsOnly,Category = "Rendering")
	float MaxRenderDistance;

	/* Pool handles used by the pooling system. */
	TArray< struct FPoolHandle* > mPoolHandles;

	UPROPERTY(EditDefaultsOnly, Category = "Buildable")
	TSubclassOf< class AFGDecorationTemplate > mDecoratorClass;

	/** Callback for when the production indicator state changes. Called locally on both server and client. */
	FProductionStatusChanged mOnProductionStatusChanged;

//#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category = "Customization Editor only")
	TArray<FCustomizationDescToRecipeData> mAlternativeMaterialRecipes;
//#endif
	
	UPROPERTY(EditDefaultsOnly, Category = "Buildable")
	bool mContainsComponents = true;

	UPROPERTY(EditDefaultsOnly, Category="Proximity")
	float mIsConsideredForBaseWeightValue = 1.f;
	
protected:
	/* Begin css sparse data implementation */
#if	WITH_EDITORONLY_DATA
	UPROPERTY(instanced,EditDefaultsOnly)
	UFGBuildableSparseDataObject* mBuildableSparseDataEditorObject;
#endif
	/* Assigned by post edit property */
	UPROPERTY()
	UFGBuildableSparseDataObject* mBuildableSparseDataCDO;

	UPROPERTY()
	AActor* mParentBuildableActor;
	
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

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable" )
	TSubclassOf< class UFGSwatchGroup > mSwatchGroup;
	
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	TSubclassOf< class UFGFactorySkinActorData > mFactorySkinClass;

	/* Force the ancient build effect, mainly used for space elevator. */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	bool bForceLegacyBuildEffect = false;
	
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	bool bForceBuildEffectSolo = false;
	
	/** Store the active effect so we can cancel an old one if we need to start a new. */
	UPROPERTY()
	UFGMaterialEffect_Build* mActiveBuildEffect;

	/**
	 * Used to sync and start build effect on buildings when created, but not after creation.
	 * This is sett to null in default. If it's non null, we expect the build effects need to play.
	 */
	UPROPERTY(BlueprintReadOnly, Replicated, meta = ( NoAutoJson = true ) )
	AActor* mBuildEffectInstignator;

	UPROPERTY()
	class AFGBuildEffectActor* mBuildEffectActor;
	
	/** Build effect speed, a constant speed (distance over time) that the build effect should have, so bigger buildings take longer */
	UPROPERTY( EditDefaultsOnly, Category = "Build Effect" )
	float mBuildEffectSpeed;
	
	/** if true, then this buildable will accept swatches and patterns */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	uint8 mAllowColoring:1;

	/** Absolute override for whether patterns are allowed on this buildable. AllowColoring must also be true to allow. */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	uint8 mAllowPatterning:1;

	/** True if buildable should register the interacting player with a circuit and thus replicate power circuit details (e.g. power graph) to the interacting players */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable", DisplayName = "Replicate Power Graph To Interacting Players" )
	uint8 mInteractionRegisterPlayerWithCircuit:1;

	/** Skip the build effect. */
	UPROPERTY( EditDefaultsOnly, Category = "Build Effect" )
	uint8 mSkipBuildEffect:1;
	
	/** Whether or not this building should use ForceNetUpdate() when a player registers/unregisters from it. */
	UPROPERTY( EditDefaultsOnly, Category = "Replication" )
	uint8 mForceNetUpdateOnRegisterPlayer:1;
	
	/** Whether or not this building should set Dorm_Awake when a player registers interaction and to set Dorm_DormantAll when no more players are interacting. */
	UPROPERTY( EditDefaultsOnly, Category = "Replication" )
	uint8 mToggleDormancyOnInteraction:1;

	/** Whenever the buildable is spawned through zooping, blueprints or any other mass building method. */
	UPROPERTY( Replicated )
	uint8 mIsMultiSpawnedBuildable:1;
	
	/** Flag for whether the build effect is active */
	uint8 mBuildEffectIsPlaying : 1;

	/** Flag specifically that this is a blueprint build effect */
	uint8 mBlueprintBuildEffectIsPlaying : 1;

	/** Flag for whether this buildable is being dismantled */
	uint8 mIsDismantled : 1;
	
	/** Local Only. This Buildable has had a dismantle request issued for it. If we are a client this could take some time during which we may wish to know its soon to be invalid */
	uint8 mIsPendingDismantleRemoval:1;

	/** Flag to indicate whether the dismantle material should be active. Used to being able to activate the material when other effects end (like the build effect) */
	uint8 mPendingDismantleHighlighted : 1;

	/** Flag for if the buildable undergoes mesh changes and needs to update its shared material instances ( Tex. When a mesh component is added or changed after Native Begin Play */
	uint8 mReevaluateMaterialsWithSubsystem : 1;

	/** True if the building has been already registered with the background thread */
	uint8 mRegisteredWithBackgroundThread: 1;

	/** True if the building already had it lightweight instances registered */
	uint8 mLightweightInstancesRegistered: 1;
	
	/** Whether or not we should create the visual mesh representation for attachment points. */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	uint8 mShouldShowAttachmentPointVisuals:1;

	UPROPERTY( EditDefaultsOnly, Category = "Buildable|Instances" )
	uint8 mCanContainLightweightInstances:1;

	UPROPERTY( EditDefaultsOnly, Category = "Buildable|Instances" )
	uint8 mManagedByLightweightBuildableSubsystem:1;
	
	/** For certain buildables we may want immediate removal from the buildable subsystem on Dismantle rather than waiting for endplay */
	UPROPERTY()
	uint8 mRemoveBuildableFromSubsystemOnDismantle:1;

	/** Set to true on dismantle so that we know not to remove in endplay if this buildable has already been removed */
	UPROPERTY()
	uint8 mHasBeenRemovedFromSubsystem:1;

#if WITH_EDITORONLY_DATA
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Buildable|Instances" )
	UAbstractInstanceDataObject* mInstanceData;
#endif
	
	UPROPERTY( VisibleDefaultsOnly )
	UAbstractInstanceDataObject* mInstanceDataCDO;

protected:
	/* Handle data */
	TArray< struct FInstanceHandle* > mInstanceHandles;

	
	
protected:
	/** Should affect the occlusion system .*/
	UPROPERTY( EditDefaultsOnly, Category = "Buildable|OcclusionSystem" )
	bool mAffectsOcclusion;
	
	/** Shape used for the occlusion system, used for weather and maybe grass in the future.*/
	UPROPERTY( EditDefaultsOnly, Category = "Buildable|OcclusionSystem",meta= ( EditCondition="mAffectsOcclusion", EditConditionHides) )
	EFGRainOcclusionShape mOcclusionShape;

	UPROPERTY( EditDefaultsOnly, Category = "Buildable|OcclusionSystem",meta = ( EditCondition="mOcclusionShape == EFGRainOcclusionShape::ROCS_CustomMesh && mAffectsOcclusion", EditConditionHides ) )
	UStaticMesh* mCustomOcclusionShape;

	/* Scale offset */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable|OcclusionSystem",meta= ( EditCondition="mAffectsOcclusion", EditConditionHides) )
	float mScaleCustomOffset = 1.f;

	UPROPERTY( EditDefaultsOnly, Category = "Buildable|OcclusionSystem",meta= ( EditCondition="mAffectsOcclusion", EditConditionHides) )
	EFGRainOcclusionShapeScaling mCustomScaleType = EFGRainOcclusionShapeScaling::ROCSS_Center;

	/* Visible anywhere for editing reasons. */
	UPROPERTY( EditAnywhere, Category = "Buildable|OcclusionSystem",meta = ( EditCondition="mOcclusionShape == EFGRainOcclusionShape::ROCS_Box_Special && mAffectsOcclusion", EditConditionHides ) )
	TArray<FBox> mOcclusionBoxInfo;

	/* Dev QOL. */
#if WITH_EDITOR
	UFUNCTION(CallInEditor, Category="Buildable|OcclusionSystem")
	void DebugDrawOcclusionBoxes();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;

#endif
	
	/** Caching the extent for use later */
	FBox mCachedBounds;

	/** List of attachmentpoints for this buildable. */
	UPROPERTY()
	TArray< FFGAttachmentPoint > mAttachmentPoints;
	
	/** If the buildable is inside of a blueprint designer, this will be the reference to the designer. */
	UPROPERTY( SaveGame, Replicated )
	class AFGBuildableBlueprintDesigner* mBlueprintDesigner;

	/** True if this building was built inside of the blueprint designer. Used to make decisions early in BeginPlay on the clients when blueprint designer is not yet replicated. Not saved, derived from mBlueprintDesigner on load and on begin play on authority */
	UPROPERTY( Replicated )
	bool mReplicatedBuiltInsideBlueprintDesigner{false};
private:
	friend class UFGFactoryConnectionComponent;
	friend class AFGBuildableSubsystem;
	friend class AFGBuildableBlueprintDesigner;

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
	/** Cached actual number of power components **/
	uint8 mNumPowerConnectionsOnPlay;

	/** Players interacting with this building */
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mInteractingPlayers;

	/** If you can interact with this buildable. */
	UPROPERTY( EditDefaultsOnly, Category = "Interaction" )
	uint8 mIsUseable:1;

	/** if true, then blueprint has implemented Factory_ReceiveTick */
	uint8 mHasBlueprintFactoryTick:1;

	/** if true, then blueprint has implemented Factory_PeekOutput */
	uint8 mHasFactory_PeekOutput:1;

	/** if true, then blueprint has implemented Factory_GrabOutput */
	uint8 mHasFactory_GrabOutput:1;

	/** if true, then blueprint has implemented SetupInstances */
	uint8 mHasSetupInstances:1;

	/** if true, this buildable is just a temporary created by the lightweight instance subsystem */
	uint8 mIsLightweightTemporary:1;

	/** if true, this buildable is a stale lightweight temporary, as such its destruction should trigger no further action ie. its not really being dismantled */
	uint8 mIsStaleLightweightTemporary:1;

	/** Block Cleanup of stale temporary (for instance, if the temporary was multi selected for dismantle just because no instigator is near them doesnt mean we can remove it)*/
	uint8 mBlockCleanupForStaleTemporary:1;

	/** This temporary has had its customization data change */
	uint8 mHasTemporaryModifiedItsCustomiazationData:1;

	/** If this is a lightweight temporary this value indicates its index in the runtime data array to avoid having to look this up again (noteably when dismantled) */
	int32 mRuntimeDataIndex = INDEX_NONE;
	
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

	/** Clearance data of this buildable */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	TArray< FFGClearanceData > mClearanceData;

	/** Has this buildable created its material dynamic material instances for shared coloring? */
	bool mHasInitializedMaterialManagers;

	/** Should the building start as hidden when playing the build effect */
	UPROPERTY( EditDefaultsOnly, Category = "Build Effect" )
    bool mHideOnBuildEffectStart;

	/** Whether or not this buildable should affect the WorldGrid subsystem */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	bool mShouldModifyWorldGrid;

	/** True if this building is about to be dismantled. */
	bool mIsAboutToBeDismantled;
	
	UPROPERTY( Transient )
	TArray< UStaticMeshComponent* > mProxyBuildEffectComponents;

	UPROPERTY( Transient, VisibleAnywhere )
	TArray< class AFGPlayerController* > mActiveSignificantControllers;

	UPROPERTY( Transient, VisibleAnywhere )
	TArray< USceneComponent* > mGeneratedSignificantComponents;

#if WITH_EDITORONLY_DATA
	/** ID of the Timelapse bucket this building belongs to. When replaying the build effect using the Timelapse tool, the bucket ID specifies which buildings should have the replayed */
	UPROPERTY( EditInstanceOnly, SaveGame, Category = "Cinematic | Timelapse", meta = (ClampMin = 0, UIMin = 0) )
	int32 mTimelapseBucketId;

	/** Delay from the start of the timelapse until this buildable will start playing it's build effect */
	UPROPERTY( EditInstanceOnly, SaveGame, Category = "Cinematic | Timelapse", meta = (ClampMin = "0.0", UIMin = "0.0") )
	float mTimelapseDelay;
#endif

#if WITH_EDITORONLY_DATA
	// Deprecated properties for the alien overclocking data that got moved into the sparse data object
	UPROPERTY()
	float mAlienOverClockingZOffset_DEPRECATED;
	UPROPERTY()
	float mAlienOverClockingAttenuationScalingFactor_DEPRECATED{12.0f};
	UPROPERTY()
	float mAlienOverClockingVolumeDB_RTPC_DEPRECATED;
	UPROPERTY()
	float mAlienOverClockingHighpass_RTPC_DEPRECATED;
	UPROPERTY()
	float mAlienOverClockingPitch_RTPC_DEPRECATED;
#endif
	
	// Editor tools
#if WITH_EDITOR
	friend class UFGLightweightInstanceTools;
#endif

	/** If we were built as part of a blueprint, this will reference the blueprint proxy. */
	UPROPERTY( SaveGame, Replicated )
	class AFGBlueprintProxy* mBlueprintProxy;
	friend class AFGBlueprintProxy; // Friend in order for the proxy to set this reference.
	friend class AFGBuildableBlueprintDesigner; // Friend in order for the blueprint designer to temporarily clear the proxy reference before serializing this building to a blueprint.

	UPROPERTY( Replicated )
	int32 mBlueprintBuildEffectID;
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

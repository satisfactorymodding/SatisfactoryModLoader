// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "BuildableColorSlotBase.h"
#include "FGSaveInterface.h"
#include "FGBuildingColorSlotStruct.h"
#include "FactoryTick.h"
#include "Materials/Material.h"
#include "FGBuildableSubsystem.generated.h"

class UFGProductionIndicatorInstanceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildableConstructedGlobal, AFGBuildable*, buildable );

/** Distances where we switch tick rate */
USTRUCT( BlueprintType )
struct FDistanceBasedTickRate
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float Distance;
	
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float TickRate;
};

USTRUCT()
struct FBuildableBucket
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf< class AFGBuildable > BuildableClass;

	UPROPERTY()
	TArray< class AFGBuildable* > Buildables;
};

/**
 * Subsystem responsible for spawning and maintaining buildables.
 * This enables and disables ticks on the buildable.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGBuildableSubsystem();

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
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	/** Calls Factory_Tick on all factory buildings */
	void TickFactory( float dt, ELevelTick TickType );

	/** Get the buildable subsystem in the current world, can be nullptr, e.g. on game ending (destroy) or game startup. */
	static AFGBuildableSubsystem* Get( UWorld* world );

	/** Get the buildable subsystem in the current world, can be nullptr, e.g. on game ending (destroy) or game startup. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory", DisplayName = "GetBuildableSubsystem", meta = ( DefaultToSelf = "WorldContext" ) )
	static AFGBuildableSubsystem* Get( UObject* worldContext );

	/**
	 * Spawn a buildable at a specified location, you need to call FinishSpawning on the buildable after this to finalize the spawning.
	 *
	 * @param inClass - The class we want to spawn (need to be valid).
	 * @param inTransform - where we want to spawn the buildable.
	 */
	class AFGBuildable* BeginSpawnBuildable( TSubclassOf< class AFGBuildable > inClass, const FTransform& inTransform );

	/** Adds a buildable to the buildable array. */
	void AddBuildable( class AFGBuildable* buildable );
	/** Remove the buildable from the subsystem, this is called by the buildable when destroyed. */
	void RemoveBuildable( class AFGBuildable* buildable );

	/** Get all buildables of the supplied type. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory" )
	void GetTypedBuildable( TSubclassOf< class AFGBuildable > inClass, TArray< class AFGBuildable* >& out_buildables ) const;

	/** Get all buildables of the supplied type. */
	template< typename T >
	void GetTypedBuildable( TArray< T* >& out_buildables ) const;

	/** Starts replaying of build effects in the build order of the buildings. */
	UFUNCTION()
	void ReplayBuildingEffects();

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	void DebugEnableInstancing( bool enabled );
	void DebugGetFactoryActors( TArray< AActor* >& out_actors );

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

protected:
	// Find and return a local player
	class AFGPlayerController* GetLocalPlayerController() const;

	/** Distance from a location to closest point of buildables AABB */
	float GetDistanceSqToBoundingBox( const FVector& point,  class AFGBuildable* buildable ) const;

	/** Register/unregister our factory tick function */
	void RegisterFactoryTickFunction( bool shouldRegister );
private:
	/** Create a stat for the buildable */
	void CreateFactoryStatID() const;

	void UpdateReplayEffects( float dt );

	void AddBuildableMeshInstances( class AFGBuildable* buildable );

public:
	/** Distance used when calculating if a location is near a base */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float mDistanceConsideredClose;

	/** How many factories need to be within the close range for it to count as if a given location is near a base */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	int32 mNumFactoriesNeededForCloseCheck;

	/** Broadcast when a buildable or decor has been constructed. Regardless of who built it */
	UPROPERTY( BlueprintAssignable, Category = "Build", DisplayName = "OnBuildableConstructedGlobal" )
	FOnBuildableConstructedGlobal BuildableConstructedGlobalDelegate;

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	void setColorSlotPrimary( uint8 index, FColor color );
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	void setColorSlotSecondary( uint8 index, FColor color );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	FColor getColorSlotPrimary( uint8 index );
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	FColor getColorSlotSecondary( uint8 index );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	FLinearColor GetColorSlotPrimaryLinear( uint8 index );
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	FLinearColor GetColorSlotSecondaryLinear( uint8 index );


	UMaterial* GetFactoryDefaultMaterial()
	{
		return mDefaultFactoryMaterial;
	}

	/**
	 * Used by UFGColoredInstanceMeshProxy to get an instance if it's not already been assigned
	 */
	class UFGColoredInstanceManager* GetColoredInstanceManager( class UFGColoredInstanceMeshProxy* proxy );

private:
	/** List of all buildables. */
	UPROPERTY()
	TArray< class AFGBuildable* > mBuildables;

	/** Grouping buildings into buckets by class */
	UPROPERTY()
	TArray< FBuildableBucket> mBuildableBuckets;

	/** Hierarchical instances for the factory buildings. */
	UPROPERTY()
	AActor* mBuildableInstancesActor;
	// MODDING EDIT
	//UPROPERTY()
	//TMap< class UStaticMesh*, class UProxyHierarchicalInstancedStaticMeshComponent* > mBuildableMeshInstances;

	/**/
	UPROPERTY()
	UFGProductionIndicatorInstanceManager* mProductionIndicatorInstanceManager = nullptr;

	/**/
	UPROPERTY()
	TMap< class UStaticMesh*, class UFGColoredInstanceManager* > mColoredInstances;


	bool mColorSlotsAreDirty = false;
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Customization" )
	FColor mColorSlotsPrimary[ BUILDABLE_COLORS_MAX_SLOTS ];

	UPROPERTY( SaveGame, EditDefaultsOnly,  Category = "Customization" )
	FColor mColorSlotsSecondary[ BUILDABLE_COLORS_MAX_SLOTS ];

	uint8 mColorSlotDirty[ BUILDABLE_COLORS_MAX_SLOTS ];




	/** Maximum number of buildables that we consider their optimization level during the same frame */
	int32 mMaxConsideredBuildables;

	/** Last buildable that was considered */
	int32 mLastConsideredBuildableIdx;

	/** Distance we disable buildables ticking on */
	float mDisabledBuildableTickDistance;

	/** Information about what distances we change the tick rate on */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	TArray< FDistanceBasedTickRate > mDistanceBasedTickRate;

	/** Is factory optimization ( tick control ) active */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	bool mFactoryOptimizationEnabled;

	/** How much time can differ between each build effect */
	UPROPERTY( EditDefaultsOnly, Category = "Replay" )
	float mReplayEffecTimeDilation;

	/** How much time between each build effect when replaying the whole factory */
	UPROPERTY( EditDefaultsOnly, Category = "Replay" )
	float mReplayEffectTimerDefault;

	/** Timer used for the replay effect */
	float mReplayEffectTimer;

	/** Array with all the buildings that should replay their effect */
	TArray< AFGBuildable* > mReplayEffectArray;

	/**used for comparing and finding materials of factory meshes*/
	UPROPERTY( EditDefaultsOnly )
	UMaterial* mDefaultFactoryMaterial;


	enum class EPropagateColorState : uint8
	{
		SettingTransitionColor,
		SettingHalfRealColor,
		SettingRealColor,
		SettingColorOnly,
		Done
	};

	EPropagateColorState mColorPropState = EPropagateColorState::Done;
	int32 mColorPropagationProgressIndex = 0;
	float mColorPropagationTimer = 0;
	/** Array with all the buildings that should replay their effect */
	TArray< AFGBuildable* > mColorPropagationArray;
	bool IsBasedOn( const UMaterialInterface* instance, const UMaterial* base );

	//@todorefactor With meta = ( ShowOnlyInnerProperties ) it does not show and PrimaryActorTick seems to be all custom properties, so I moved to another category but could not expand.
	/** Controls if we should receive Factory_Tick and how frequent. */
	UPROPERTY( EditDefaultsOnly, Category = "Factory Tick", meta = ( NoAutoJson = true ) )
	FFactoryTickFunction mFactoryTickFunction;

	/** Factory Stat id of this object, 0 if nobody asked for it yet */
	STAT( mutable TStatId mFactoryStatID; )
public:
};

template< typename T >
void AFGBuildableSubsystem::GetTypedBuildable( TArray< T* >& out_buildables ) const
{
	for( auto buildable : mBuildables )
	{
		T* specificBuildable = Cast< T >( buildable );
		if( IsValid( specificBuildable ) )
		{
			out_buildables.Add( specificBuildable );
		}
	}
}

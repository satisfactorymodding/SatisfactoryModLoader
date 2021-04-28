// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "HAL/Runnable.h"
#include "Containers/Queue.h"
#include "Engine/DeveloperSettings.h"
#include "FGBackgroundThread.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPoolSystem, Error, All);

class AActor;
class AFGPlayerControllerBase;
struct FPoolItem;
struct FPoolInstanceBase;
struct FFGPoolType;

// Flags
UENUM( Blueprintable, Meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class EPoolInstanceFlags : uint8
{
	None = 						0x00,
	Dirty_EnvironmentContext = 	0x01,
	Dirty_ColorState = 			0x02,
	Dirty_ForceStateOff = 		0x04,
	Dirty_StateOn = 			0x08,
	Dirty_Scalability = 		0x16,
	
	Dirty_Any = Dirty_EnvironmentContext |  Dirty_ColorState | Dirty_ForceStateOff | Dirty_StateOn
};
ENUM_CLASS_FLAGS( EPoolInstanceFlags );

USTRUCT( BlueprintType )
struct FACTORYGAME_API FPoolFloatScalability
{
	GENERATED_BODY()
	
	UPROPERTY( BlueprintReadWrite )
	TArray< float > Values;
	
	float GetValueForScalability( int32 Level ) const
	{
		return Values[ FMath::Clamp(Level,0,Values.Num() ) ];
	}

	FPoolFloatScalability( )
	{}
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FPoolBoolScalability
{
	GENERATED_BODY()
	
	UPROPERTY( BlueprintReadWrite )
	TArray< bool > Values;
	
	bool GetValueForScalability( int32 Level ) const
	{
		return Values[ FMath::Clamp( Level, 0, Values.Num() -1 ) ];
	}

	FPoolBoolScalability( )
	{}	
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FPoolLightSettings
{
	GENERATED_BODY()
	UPROPERTY( BlueprintReadWrite )
	float mDefaultDrawRange;

	UPROPERTY( BlueprintReadWrite )
	float mFadePercentage;
	
	UPROPERTY( BlueprintReadWrite )
	float mMaxTraceDistance;
	
	UPROPERTY( BlueprintReadWrite )
	float mMinIntensity;

	UPROPERTY( BlueprintReadWrite )
	float mMaxIntensity;

	UPROPERTY( BlueprintReadWrite )
	float mInnerConeAngle;
	
	UPROPERTY( BlueprintReadWrite )
	float mOuterConeAngle;

	/* Keep this value low */
	UPROPERTY( BlueprintReadWrite )
	float mLightFalloff;
	
	UPROPERTY( BlueprintReadWrite )
	FPoolBoolScalability bUseDistanceFieldShadows;

	UPROPERTY( BlueprintReadWrite )
	FPoolBoolScalability mCastShadows;
	
	UPROPERTY( BlueprintReadWrite )
	FPoolBoolScalability mCastDFShadows;

	FPoolLightSettings()
	{
		mDefaultDrawRange = 50000.f;
		mMaxTraceDistance = 5000.f;
		mMinIntensity = 10.f;
		mMaxIntensity = 20.f;
		mLightFalloff = 1.5f;
		mInnerConeAngle = 45.f;
		mOuterConeAngle = 45.f;
		mFadePercentage = 0.95f;
	}
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FPoolMeshSettings
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite )
	float mMaxTraceDistance;
	
	FPoolMeshSettings()
	{
		mMaxTraceDistance = 5000;
	};
};

struct FACTORYGAME_API FPoolHandle
{
	int32 HandleID;
	TWeakObjectPtr< const AActor > Owner;
	
	FORCEINLINE bool IsUsed() const
	{
		return HandleID != INDEX_NONE;
	}

	FORCEINLINE int32 GetHandleId() const
	{
		return HandleID;
	}

	FORCEINLINE void SetHandle( int32 Id, const AActor* inOwner )
	{
		UE_LOG(LogPoolSystem, VeryVerbose, TEXT("[%p] Seting id from %d to %d"),this, HandleID, Id);
		HandleID = Id;
		
		if ( IsValid( inOwner ) )
		{
			Owner =	inOwner;
		}
	}

	FORCEINLINE void Release()
	{
		HandleID = INDEX_NONE;
		Owner = nullptr;
	}
	
	FORCEINLINE const AActor* GetOwner() const
	{
		if( !Owner.IsStale() )
		{
			return Owner.Get();
		}

		return nullptr;
	}

	FPoolHandle()
	{
		HandleID = INDEX_NONE;
        Owner = nullptr;
	}
};

struct FACTORYGAME_API FPoolInstanceBase
{
	TWeakObjectPtr< USceneComponent > Component;
	int32 PoolItemId;
	bool bIsEnvironmentAware;
	EPoolInstanceFlags mFlags;
	
	/* Releases instance and marks dirty */
	FORCEINLINE virtual void Release( int32 Entry )
	{
		MarkDirty();
		SetPoolItemId( INDEX_NONE );
	};

	// Called on thread.
	FORCEINLINE virtual void Claim( int32 EntryId = 0 )
	{
	}
	
	FORCEINLINE virtual bool Update( const TArray< FPoolItem* >& entries)
	{
		return false;
	}
	
	FORCEINLINE virtual bool IsFree() const
	{
		return PoolItemId == INDEX_NONE;
	}

	FORCEINLINE void SetPoolItemId(int32 Id)
	{
		UE_LOG( LogPoolSystem, VeryVerbose, TEXT("[%p]Setting id from %d to %d"), this, PoolItemId, Id );
		PoolItemId = Id;
	}
	
	FORCEINLINE USceneComponent* GetActorComponent()
	{
		if ( Component.IsValid() )
		{
			return Component.Get();
		}
		
		return nullptr;
	};

	FORCEINLINE virtual UClass* GetComponentClass() const
	{
		return USceneComponent::StaticClass();
	};

	FORCEINLINE void MarkDirty()
	{
		mFlags = EPoolInstanceFlags::Dirty_Any;
	}

	FORCEINLINE void SetFlags( EPoolInstanceFlags inFlags )
	{
		mFlags |= inFlags;	
	}

	FORCEINLINE void ClearFlags ()
	{
		mFlags = EPoolInstanceFlags::None;
	}
	
	FORCEINLINE bool IsDirty() const
	{
		return mFlags != EPoolInstanceFlags::None; // uint8(mFlags) & uint8(EPoolInstanceFlags::Dirty_Any);
	}

	FORCEINLINE bool IsFlagSet(EPoolInstanceFlags Flag) const
	{
		return uint8( mFlags) & uint8(Flag );
	}

	FORCEINLINE class FFGBackgroundThread* GetRunnable( const AActor* owner ) const;

	/* Resolve input hits to ensure we check against the correct types.*/
	bool ResolveHitResults( const TArray<FHitResult>& inHits, const TArray<UClass*>& classesToCheckAgainst, FVector& outHitLocation, float& inNearestDistance );

	FPoolInstanceBase()
	{
		PoolItemId = INDEX_NONE;
		Component = nullptr;	
		mFlags = EPoolInstanceFlags::None;
	};

	FPoolInstanceBase( USceneComponent* inComponent )
	{
		PoolItemId = INDEX_NONE;
		Component = TWeakObjectPtr< USceneComponent >(inComponent);
		mFlags = EPoolInstanceFlags::None;
	};
	
	virtual ~FPoolInstanceBase()
	{
		// Cleanup component.
		if ( Component.IsValid( false,true ) )
		{
			Component.Get()->DestroyComponent(false);
		}
	};
};

struct FACTORYGAME_API FPoolItem
{
	friend class FFGBackgroundThread;

	/* Location in world position. */
	FTransform Transform;

	/* -1 means disabled, range from
	 * ( relevant ) 0 - 1 ( irrelevant ) */
	float Relevance;

	/* Radius of the relevance. */
	float mRadius;
	
	/* Pointer to the handle given to this instance, this way we can safely 
	* remove the instance from the list when the actor is destroyed*/
	FPoolHandle* Handle;

	/* Current owned instance if any */
	FPoolInstanceBase* Instance;

	/* Quick pointer to the type to identify how to interact with this item. */
	FFGPoolType* Settings;

	/* Relevance location when used. */
	FVector RelevanceLocation;

	/* Returns true when item is allowed to use the pool system
	* for example, the context has no power, or is disabled etc */
	FORCEINLINE bool IsActive() const		{ return Relevance != INDEX_NONE; }

	/* Returns true when instance is assigned. */
	FORCEINLINE bool IsInstanced() const	{ return Instance != nullptr; }
	
	/* Try to release the Instance if owning any. */
	FORCEINLINE void TryReleaseInstance( int32 handleId = 0 )
	{		
		if ( Instance )
		{
			Instance->SetPoolItemId( INDEX_NONE );
			Instance->MarkDirty();
			Instance = nullptr;
		}
	}

	/* Tries to mark instance dirty. */
	FORCEINLINE void TryMarkInstanceDirty()
	{
		if ( Instance )
		{
			Instance->MarkDirty();
		}
	}

	FORCEINLINE void ComputeRelevance( FVector pawnLocation, FVector pawnDirection, float MaxRelevance, float RelevancyMultiplier = 1.f )
	{
		const bool bUseRelevanceLocation = !this->RelevanceLocation.IsNearlyZero(0.0001f);
		const float dist = FVector::DistSquared( ( Transform.GetLocation() * !bUseRelevanceLocation ) + ( RelevanceLocation * bUseRelevanceLocation ), pawnLocation )  - ( mRadius * mRadius ); 

		// Max 0 since it can become below zero otherwise when applying the radius offset, below 0 values are considered "off" 
		Relevance = FMath::Max< float >( dist / FMath::Square( MaxRelevance * RelevancyMultiplier ), 0.f);

		
#if 0
		// Maybe to consider for the future.
		FVector dirToInstance = Transform.GetLocation() - pawnLocation;
		dirToInstance.Normalize(0.01f);
		
		float dotP = FMath::Clamp(FVector::DotProduct( dirToInstance, pawnDirection ),-1.f,1.f);
		float relevanceInfluence = dotP > -0.5 ? 1 :  2.f;	
		
		const float dist = FVector::DistSquared( Transform.GetLocation(), pawnLocation );
		Relevance = (dist / FMath::Square( MaxRelevance ) ) * relevanceInfluence;	
#endif
	}

	/* Assign relevancy location, can be different from the instance due to their target location; see lights. */
	FORCEINLINE void SetRelevanceLocation( FVector &t )
	{
		RelevanceLocation = t;
	}

	/* The radius offset used to improve pool item selection. */
	FORCEINLINE void SetRadius( float newRadius )
	{
		mRadius = newRadius;
	}
	
	FPoolItem( const FTransform &t )
	{
		Transform = t;
		Relevance = 0;
		Handle = nullptr;
		Instance = nullptr;
		mRadius = 0.f;

		RelevanceLocation = FVector( 0 );
	}
		
	FPoolItem( const FTransform &t, FPoolHandle* h )
	{
		Transform = t;
		Handle = h;
		Relevance = 0;
		Instance = nullptr;
		mRadius = 0.f;
		
		RelevanceLocation = FVector( 0 );
	}
};

struct FACTORYGAME_API FPoolInstanceComponent : FPoolInstanceBase
{
	virtual void Claim(int32 EntryId) override;
	virtual bool Update(const TArray<FPoolItem*>& entries) override;
	FORCEINLINE virtual void Release( int32 Entry ) override
	{
		MarkDirty();
		mClaimedIds.RemoveSingleSwap( Entry );
	};
	
	virtual UClass* GetComponentClass() const override
	{
		return UInstancedStaticMeshComponent::StaticClass(); 
	}
	
	TArray<int32> mClaimedIds;
			
	FPoolInstanceComponent()
	{
		PoolItemId = INDEX_NONE;
		MarkDirty();
	}
	
	FPoolInstanceComponent( UInstancedStaticMeshComponent* inComponent )
	{
		PoolItemId = INDEX_NONE;
		MarkDirty();
		Component = TWeakObjectPtr<USceneComponent>( inComponent );
	}
};

struct FACTORYGAME_API FPoolMeshComponent : FPoolInstanceBase
{
	virtual void Claim( int32 EntryId ) override;
	virtual bool Update( const TArray< FPoolItem* >& entries ) override;
	virtual UClass* GetComponentClass() const override
	{
		return UStaticMeshComponent::StaticClass();
	}

	FPoolMeshComponent()
	{
		PoolItemId = INDEX_NONE;
		MarkDirty();
	}
	
	FPoolMeshComponent( UStaticMeshComponent* inComponent )
	{
		PoolItemId = INDEX_NONE;
		MarkDirty();
		Component = TWeakObjectPtr<USceneComponent>( inComponent );
	}
};

struct FACTORYGAME_API FPoolActorComponent : FPoolInstanceBase
{
	
};

struct FACTORYGAME_API FPoolLightComponent : FPoolInstanceBase
{
	FORCEINLINE virtual bool IsFree() const override
	{
		return PoolItemId == INDEX_NONE;
	};
	
	virtual void Claim( int32 EntryId ) override;
	virtual bool Update( const TArray< FPoolItem* >& entries ) override;
	virtual UClass* GetComponentClass() const override
	{
		return USpotLightComponent::StaticClass();
	}
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// ~~~~~~~~~~~ Background runnable ~~~~~~~~~~~ //
struct FACTORYGAME_API FPoolInstanceType
{
	TArray< FPoolInstanceBase* > mInstances;
	FThreadSafeCounter mNumClaimed;
	
	FORCEINLINE int32 GetMaxCount() const { return mInstances.Num(); } 

	FPoolInstanceType()
	{
		mNumClaimed.Set(0 );
	}
};

class FACTORYGAME_API FFGBackgroundThread :	public FRunnable
{
	FFGBackgroundThread( UWorld* WorldContext );

	~FFGBackgroundThread();

	friend class APoolRoot;
	
	friend struct FPoolComponentBase;
	friend struct FPoolMeshComponent;
	friend struct FPoolLightComponent;

public:	
#if WITH_EDITOR
	/* For PIE functionality. */
	static TMap<UWorld*,FFGBackgroundThread*> PIE_Threads;
#else
	/** Reference to self. */
	static FFGBackgroundThread* Runnable;
#endif
	
private:
	// TODO consider a weak ptr?
	/** Cached pointer to the world, made when initialized. */
	UWorld* mWorldContext;
	
	FRunnableThread* Thread;
	
	// Actor
	TWeakObjectPtr<AActor> mPoolRootActor;
	
	// To stop the thread safely.
	FThreadSafeCounter StopTaskCounter;

	// Thread safe array of newly registered actors.
	TQueue< TWeakObjectPtr< AActor >, EQueueMode::Mpsc > mRegisteredActors;
	
	/* Queue of removed handles in an array, since we remove per building and buildings contain several handles.*/
	TQueue< FPoolHandle*, EQueueMode::Mpsc > mRemovedHandlesToProcess;

	// TODO improve desc.
	/* Queue of removed actor locations, used for updating environment context. */
	TQueue<FVector, EQueueMode::Mpsc > mRemovedLocations;
	
	/* Queue of instances to update status, TPair<Handle,NewStatus> */
	TQueue< TPair< FPoolHandle*, bool >, EQueueMode::Mpsc > mInstanceStatusToUpdate;

	TQueue< TPair< FPoolHandle*, EPoolInstanceFlags >, EQueueMode::Mpsc > mInstanceFlagsToUpdate;

	// Smart pointer to task graph event.
	TArray< FGraphEventRef > mStartedGraphTasks;
	
	//////////////////////////////////
	// Buckets
	// TODO deprecate buckets dont seem to be needed, the system seems fast enough.
	TArray< FPoolItem* > Bucket_Near;
	TArray< FPoolItem* > Bucket_Medium;
	TArray< FPoolItem* > Bucket_Dormant;

	float mLastUpdateTime;
	float mLastUpdateTime_Medium;

	/* Cached version pulled from the pool system config. */
	TArray< struct FFGPoolType > mPoolTypes;

	/*	Array of all pool instances in the world the system can pick from
	*	A more ordered version of this is in the buckets. */
	TArray< FPoolItem* > mItems;

	/* 	Array of arrays that contains the instances
	* 	NOTE should never change after initial construction.
	* 	[Type Setting][Item] */
	TArray< FPoolInstanceType > mInstances;

	// Proxy index from world to system for removal and repointing
	TArray< FPoolHandle* > mHandles;

	uint64 mCachedFrame;

	/* Scalability cached value */
	int32 mCachedShadowQuality;
	int32 mCachedLightCount;
	int32 mCachedLightShaftCount;
	float mCachedLightRelevancyMultiplier;
	
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// Begin FRunnable interface.
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	// End FRunnable interface.
	void EnsureCompletion();

	/* Cleanup all objects */
	void Cleanup();
		
	public:
	/* Static function to register an actor consisting poolable components.
	* Must be called from GT */
	static void RegisterActor( AActor* NewActor, float instancePriority = 1.f );

	/* Static function to remove an entry.
	* Must be called from GT */
	static void RemoveHandles( const TArray<FPoolHandle*> handlesToRemove, FVector actorLocation, UWorld *WorldContext );

	static void UpdateItemStateViaHandle( FPoolHandle* &handleToUpdate, bool newStatus, UWorld *WorldContext );
	static void UpdateItemStateViaHandle( TArray<FPoolHandle*> &handleToUpdate, bool newStatus, UWorld *WorldContext );

	/* Init called when first actor get registered to the system */
	static FFGBackgroundThread* InitFactoryGameBackgroundThread( UWorld* WorldContext );
	int32 FindVisualTypeIndex( const FPoolItem* Item );
	
	/** Shutdown thread, World context only needed for PIE */
	static void Shutdown( UWorld* WorldContext = nullptr );

private:
	/* Resolve handles removed since last background thread update. */
	void ResolveHandles_internal();
	
	/* Resolves new added actors to the world and their handles.*/
	void ResolveRegisterActor_internal();

	/* Updates handles states for example when a building loses power or day/night switch */
	void ResolveHandleStates_internal();
	
	void ResolveUpdates_internal();
	
	void ResolveEnvironmentAwareness_internal();

	void CleanupTasks();
	
	FORCEINLINE bool IsThreadHealthy() const { return StopTaskCounter.GetValue() == 0; } 

	// DEPRECATED
	void UpdateBuckets( const FVector playerLocation );
	
	void UpdateRelevance( const FVector playerLocation, const FVector playerViewDirection, TArray<FPoolItem*> &Items );
	
	void InitializeDefaultPoolComponents();

	void UpdateItems( TArray<FPoolItem*> &Bucket, const FVector pawnLocation, const FVector pawnForwardVector );

	FORCEINLINE static bool IsFacing( const FPoolItem& A,const FVector& B )
	{
		// Right vector because we use Y forward.
		return FVector::DotProduct(A.Transform.GetRotation().GetRightVector() , B ) < 0.f;
	}
	
	void DumpDebug();

	/* Helper to fetch the correct world context. */
	UWorld* GetWorldContext() const
	{
		return mWorldContext;
	}

	// Scalability
	int32 CurrentLevel;
	bool bForceUpdate;

	FThreadSafeCounter mShouldUpdateScalability;

	void RefreshScalabilityVariables();
	void ApplyScalability();
	
public:
	void MarkScalabilityDirty() { mShouldUpdateScalability.Set( 1 ); }
	FORCEINLINE int32 GetCurrentScalabilityLevel() const { return CurrentLevel; }
	// End Scalability	
	
#if !UE_BUILD_SHIPPING
public:
	FThreadSafeCounter mSafeReadCycle;
	
	bool CanRead() const;
	void LockRead();
	void UnlockRead();
#endif	
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// ~~~~~~~~~~~~~~ Interface  ~~~~~~~~~~~~~~~~~~//
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGPoolDataReaderInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGPoolDataReaderInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintNativeEvent )
	float GetLightIntensity() const;
	virtual float GetLightIntensity_Implementation() const
	{
		return 0;
	}

	UFUNCTION( BlueprintNativeEvent )
	FLinearColor GetLightColor() const;	
	virtual FLinearColor GetLightColor_Implementation() const
	{
		return FLinearColor( 0,0,0,0 ); 
	}

	UFUNCTION( BlueprintNativeEvent )
	UMaterialInterface* GetLightMaterialFunction() const;
	virtual UMaterialInterface* GetLightMaterialFunction_Implementation() const
	{
		return nullptr;
	}

	/* static settings per implementation. */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Pool|Lights" )
	FPoolLightSettings GetLightSettings() const;
	virtual FPoolLightSettings GetLightSettings_Implementation() const
	{
		return FPoolLightSettings();
	}

	UFUNCTION( BlueprintNativeEvent )
	FPoolMeshSettings GetMeshSettings() const;
	virtual FPoolMeshSettings GetMeshSettings_Implementation() const
	{
		return FPoolMeshSettings();
	}
		
	UFUNCTION( BlueprintNativeEvent )
	FTransform GetCustomTransform() const;
	virtual FTransform GetCustomTransform_Implementation() const
	{
		return FTransform(FRotator( 0 ),FVector( 0 ) );
	}

	UFUNCTION( BlueprintNativeEvent )
	FLinearColor GetMeshColor() const;
	virtual FLinearColor GetMeshColor_Implementation() const
	{
		return FLinearColor(1,1,1,1);
	}
	
	/* Do we need to check for a custom transform?
	 * Separate function since it isn't just there for lights or meshes but shared */
	UFUNCTION( BlueprintNativeEvent )
	bool DoesNeedCustomTransform() const;
	virtual bool DoesNeeCustomTransform()
	{
		return false;
	}
};

UCLASS()
class FACTORYGAME_API APoolRoot : public AActor
{
	GENERATED_BODY()

public:
	void UpdateBuildingState( class AFGBuildable* Building, int32 FlagsToSet );

	void DisplayDebug( UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos ) override;

	UFUNCTION( BlueprintCallable, Category = "Pool sytem" )
	static void SetFlag( AFGBuildable* Buildable, UPARAM( meta = (Bitmask, BitmaskEnum = EPoolInstanceFlags) ) int32 Flags );

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	UPROPERTY( VisibleAnywhere )
	TArray<UActorComponent*> Components;
};

UCLASS( Blueprintable )
class FACTORYGAME_API AFGDecorationTemplate : public AActor
{
	GENERATED_BODY()

	AFGDecorationTemplate();
	
public:

#if WITH_EDITORONLY_DATA
	/* Preview actor to make it easier to place component(s) */
	UPROPERTY(EditAnywhere, meta = ( AllowPrivateAccess = "true") )
	UChildActorComponent* mChildActorComponent;
#endif
	
	static TArray< class UFGPoolableProxyComponentBase* > GetPoolAbleComponentsFromSubclass( const UClass* InActorClass );
};

UENUM()
enum class EPoolType : uint8
{
	EPT_Undefined,
	EPT_StaticMesh,
	EPT_InstanceMesh,
	EPT_Light,
	EPT_Component
};

UCLASS(Blueprintable)
class FACTORYGAME_API UFGPoolableProxyComponentBase : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	UFGPoolableProxyComponentBase();
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
// Begin developer settings

USTRUCT()
struct FACTORYGAME_API FFGPoolType
{
	GENERATED_BODY()
	
	/* Type */
	UPROPERTY( EditDefaultsOnly )
	EPoolType Type;

	/* Component placed in the blueprint to handle this instance. */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< UFGPoolableProxyComponentBase > mProxyComponent;
	
	/* Max Default count of instances in the world. */
	UPROPERTY( EditDefaultsOnly, meta = ( EditCondition = "!bInstanced" ) )
	int32 Count;
	
	/* Draw distance the world instances get relevant,
	* it could be that lights further away from the player still isn't relevant due to the max pool count.*/
	UPROPERTY( EditDefaultsOnly)
	float RelevanceDistance;
	
	/* Should the instance try to snap to the nearest foundation / non factory building.
    * Needed for ceiling lights and other spotlight based lights */
    UPROPERTY( EditDefaultsOnly, Category = "Range" )
    bool bAdjustHeight;
    	
	// TODO uncomment with ue 4.25
	UPROPERTY( EditDefaultsOnly, Category = "Mesh" /*, meta = ( EditCondition = "Type == EPT_StaticMesh || Type == EPT_InstanceMesh") */)
	UStaticMesh* mVisual_Mesh;

	/* DEPRECATED */
	UPROPERTY( EditDefaultsOnly )
	bool bVisual_Instanced;

	/*~~~~~~ Count scalability ~~~~~~*/
	/* The string used for count scalability checks. */
	UPROPERTY( EditDefaultsOnly )
	FString mCVarCountScalabilityString;
	IConsoleVariable* mCachedCountScalabilityConsoleVariable;

	UPROPERTY( EditDefaultsOnly, meta = (DisplayName = "Count Default Value"))
	int32 mCachedCountScalabilityValue;
	bool mIsCountScalabilityDirty;

	/*~~~~~~ Relevancy scalability ~~~~~~*/
	/* The string used for relevancy scalability checks. */
	UPROPERTY( EditDefaultsOnly )
	FString mCVarRelevancyScalabilityString;	
	IConsoleVariable* mCachedRelevancyScalabilityConsoleVariable;
	
	UPROPERTY( EditDefaultsOnly, meta = (DisplayName = "Relevancy Scale Default Value"))
	float mCachedRelevancyScaleScalabilityValue;
	bool mIsRelevancyScalabilityDirty;

	/*~~~~~~ Quality scalability ~~~~~~*/
	/* The string used for quality scalability checks. */
	UPROPERTY( EditDefaultsOnly )
	FString mCvarQualityScalabilityString;	
	IConsoleVariable* mCachedQualityScaleConsoleVariable;
	
	UPROPERTY( EditDefaultsOnly, meta = (DisplayName = "Quality Default Value"))
	int32 mCachedQualityScalabilityValue;
	bool mIsQualityScalabilityDirty;
};

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Pool settings" ) )
class FACTORYGAME_API UFGPoolSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, config)
	TArray< FFGPoolType > PoolEntry;
		
public:
	static TArray< FFGPoolType > GetPoolTypes()
	{
		return GetDefault< UFGPoolSettings >()->PoolEntry;	
	}
};

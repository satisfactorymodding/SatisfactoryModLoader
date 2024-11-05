// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "AbstractInstanceManager.h"
#include "FGBlueprintProxy.h"
#include "FGFactoryColoringTypes.h"
#include "FGSaveInterface.h"
#include "FGRecipe.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "FGLightweightBuildableSubsystem.generated.h"

DECLARE_STATS_GROUP( TEXT( "LightweightSubsystem" ), STATGROUP_LightweightSubsystem, STATCAT_Advanced );

class AFGBuildEffectActor;

namespace LightweightBuildables
{
	extern bool GAllowLightweightManagement;
}

USTRUCT()
struct FACTORYGAME_API FBuildEffectAndRuntimeInfo
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AFGBuildable> BuildableClass = nullptr;
	
	UPROPERTY()
	int32 RuntimeIndex = INDEX_NONE;

	UPROPERTY()
	class AFGBuildEffectActor* BuildEffectActor = nullptr;
};


USTRUCT()
struct FACTORYGAME_API FRuntimeBuildableInstanceData
{
	GENERATED_BODY()

	FRuntimeBuildableInstanceData() {}
	FRuntimeBuildableInstanceData( const FTransform& transform, FFactoryCustomizationData& customizationData, TSubclassOf< class UFGRecipe > builtWith, class AFGBlueprintProxy* proxy ) :
		Transform( transform ),
		CustomizationData( customizationData ),
		BuiltWithRecipe( builtWith ),
		BlueprintProxy( proxy )
	{}
	
	// Saved
	FTransform Transform;

	// Saved
	FFactoryCustomizationData CustomizationData;

	// Saved
	TSubclassOf< class UFGRecipe > BuiltWithRecipe;

	// Saved - Holds runtime object for the ObjectReferenceDisc of the proxy
	class AFGBlueprintProxy* BlueprintProxy  = nullptr;

	// Not Serialized - Truly runtime only data
	TArray< FInstanceHandle* > Handles;
	
	// Not Serialized - Only valid on newly added buildables
	int16 ConstructId = MAX_uint16; // Max value indicates invalid and won't be added for replication (only relevant on newly constructed buildables by a client)
	
	bool IsValid() const { return Handles.Num() > 0 && BuiltWithRecipe; }
	bool IsValidOnLoad() const { return BuiltWithRecipe != nullptr; }
	void Clear()
	{
		Handles.Empty();
		BuiltWithRecipe = nullptr;
		BlueprintProxy = nullptr;
		CustomizationData = FFactoryCustomizationData();
	}

	// Used on empty (place holder) runtimedata
	void Set(const FRuntimeBuildableInstanceData& from )
	{
		fgcheck( Handles.Num() <= 0 ) // This set should only ever be called if this runtime data is known empty otherwise we may lose handle references - it would be messy
		fgcheck( BlueprintProxy == nullptr ) // If this is valid then we failed to clear prior to setting. Hard crash to catch these danagerous sistuations

		Transform = from.Transform;
		CustomizationData = from.CustomizationData;
		BuiltWithRecipe = from.BuiltWithRecipe;
		BlueprintProxy = from.BlueprintProxy;
		Handles.Append( from.Handles );
	}
	
};

// A Simple pool struct for spawning and reusing buildables as lightweights
USTRUCT()
struct FACTORYGAME_API FLightweightBuildablePool
{
	GENERATED_BODY()
	FLightweightBuildablePool() {}
	
public:
	void PreallocPool( AActor* owner, TArray< TSubclassOf< AFGBuildable > > availableClasses );
	AFGBuildable* GetBuildableFromPool( AActor* owner, FRuntimeBuildableInstanceData* runtimeData, int32 indexOfRuntimeData, TSubclassOf<AFGBuildable> buildableClass );
	void ReturnBuildableToPool( AFGBuildable* buildable );
	AFGBuildable* SpawnBuildableForPool( AActor* owner, TSubclassOf< AFGBuildable > buildableClass );

public:
	TMap< TSubclassOf< AFGBuildable >, TArray< AFGBuildable* > > BuildableClassToPool;
	inline static const FTransform PoolTransform = FTransform( FVector( 0.f, 0.f, -100000.f ) );
	TArray< FInstanceHandle* > emptyHandles;
};


FArchive& operator<<( FArchive& ar, FRuntimeBuildableInstanceData& runtimeInstanceData );

struct FACTORYGAME_API FInstanceToTemporaryBuildable
{

	FInstanceToTemporaryBuildable() {}
	FInstanceToTemporaryBuildable( int32 index, class AFGBuildable* buildable ) :
		RuntimeDataIndex( index ),
		Buildable( buildable )
	{}

	bool IsValid() { return RuntimeDataIndex != INDEX_NONE && Buildable != nullptr; }

	//FRuntimeBuildableInstanceData* RuntimeInstanceData = nullptr;
	int32 RuntimeDataIndex = INDEX_NONE;
	
	AFGBuildable* Buildable = nullptr;

	AFGBlueprintProxy* BlueprintProxy = nullptr;
};

USTRUCT()
struct FACTORYGAME_API FInstanceConverterInstigator
{
	GENERATED_BODY()

	FInstanceConverterInstigator() {}
	FInstanceConverterInstigator(AActor* instigator, float radius) :
		Instigator( instigator ),
		InfluenceRadius( radius )
	{}

	FORCEINLINE bool TryAddInstigatedBuildable( FInstanceToTemporaryBuildable* instanceToTemp );
	
	UPROPERTY()
	AActor* Instigator = nullptr;

	float InfluenceRadius = 0.f;

	FVector LastUpdateLocation = FVector( 0.f, 0.f, 0.f );

	// Array of all buildables that were spawned as a result of this instigator
	TArray< FInstanceToTemporaryBuildable* > InstigatedBuildables;
};


USTRUCT()
struct FLightweightBuildableReplicationItem
{
	GENERATED_BODY()

	FLightweightBuildableReplicationItem() :
		Transform( FTransform::Identity ),
		CustomizationData( FFactoryCustomizationData() ),
		Index( INDEX_NONE ),
		IsValid( false )
	{}

	FLightweightBuildableReplicationItem( const FRuntimeBuildableInstanceData& runtimeData, int32 index ) :
		Transform( runtimeData.Transform ),
		CustomizationData( runtimeData.CustomizationData ),
		Index( index ),
		IsValid( runtimeData.IsValid() )
	{}
	

	FLightweightBuildableReplicationItem( const FLightweightBuildableReplicationItem& lightWeightReplicationItem ) noexcept :
		Transform( lightWeightReplicationItem.Transform ),
		CustomizationData( lightWeightReplicationItem.CustomizationData ),
		Index( lightWeightReplicationItem.Index ),
		IsValid( lightWeightReplicationItem.IsValid )
	{}
	
	FLightweightBuildableReplicationItem( const FLightweightBuildableReplicationItem&& lightWeightReplicationItem ) noexcept :
		Transform( lightWeightReplicationItem.Transform ),
		CustomizationData( lightWeightReplicationItem.CustomizationData ),
		Index( lightWeightReplicationItem.Index ),
		IsValid( lightWeightReplicationItem.IsValid )
	{}

	FLightweightBuildableReplicationItem& operator=(const FLightweightBuildableReplicationItem& other )
	{
		if( this == &other )
		{
			return *this;
		}
		
		this->Transform = other.Transform;
		this->CustomizationData = other.CustomizationData;
		this->Index = other.Index;
		this->IsValid = other.IsValid;

		return *this;
	}
	
	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	FFactoryCustomizationData CustomizationData;

	UPROPERTY()
	int32 Index;

	UPROPERTY()
	uint8 IsValid;

	
};

USTRUCT()
struct FLightweightBuildableRemovalItem : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FLightweightBuildableRemovalItem() = default;
	FLightweightBuildableRemovalItem( int32 idx ) :
		Index(idx)
	{
		FFastArraySerializerItem();
	}
	
	UPROPERTY()
	int32 Index;
};

DECLARE_DELEGATE_OneParam(FOnPostReplicatedAddRemoveLightweightBuildable, const TArrayView<int32>& AddedIndices );

USTRUCT()
struct FLightweightBuildableRemovalArray : public FFastArraySerializer
{
	GENERATED_BODY()

	UPROPERTY()
	TArray< FLightweightBuildableRemovalItem > Items;

	FOnPostReplicatedAddRemoveLightweightBuildable OnLightweightRemovalAdded;
	
	bool NetDeltaSerialize( FNetDeltaSerializeInfo& DeltaParams )
	{
		return FastArrayDeltaSerialize< FLightweightBuildableRemovalItem >( Items, DeltaParams, *this );
	}

	void PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize);
};

template<>
struct TStructOpsTypeTraits<FLightweightBuildableRemovalArray>: public TStructOpsTypeTraitsBase2<FLightweightBuildableRemovalArray>
{
	enum { WithNetDeltaSerializer = true };
};

USTRUCT()
struct FLightweightBuildableCustomizationItem : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FLightweightBuildableCustomizationItem() = default;
	FLightweightBuildableCustomizationItem( int32 idx, const FFactoryCustomizationData& customizationData ) :
		Index(idx),
		CustomizationData( customizationData )
	{
		FFastArraySerializerItem();
	}
	
	UPROPERTY()
	int32 Index;

	UPROPERTY()
	FFactoryCustomizationData CustomizationData;
};

DECLARE_DELEGATE_OneParam(FOnPostReplicatedLightweightCustomization, const TArrayView<int32>& AddedIndices );

USTRUCT()
struct FLightweightBuildableCustomizationArray : public FFastArraySerializer
{
	GENERATED_BODY()

	UPROPERTY()
	TArray< FLightweightBuildableCustomizationItem > Items;

	FOnPostReplicatedLightweightCustomization OnCustomizationAdded;
	
	bool NetDeltaSerialize( FNetDeltaSerializeInfo& DeltaParams )
	{
		return FastArrayDeltaSerialize< FLightweightBuildableCustomizationItem >( Items, DeltaParams, *this );
	}

	void PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize);
};

template<>
struct TStructOpsTypeTraits<FLightweightBuildableCustomizationArray>: public TStructOpsTypeTraitsBase2<FLightweightBuildableCustomizationArray>
{
	enum { WithNetDeltaSerializer = true };
};

UCLASS()
class FACTORYGAME_API UFGLightweightBuildableConstructionBundle : public UObject
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }

	UFUNCTION()
	void OnRep_IncomingConstructIds();

	UFUNCTION()
	void OnRep_BuildableClass();
	
	UPROPERTY()
	AFGLightweightBuildableSubsystem* mCachedLightweightSubsystem;
	
	UPROPERTY()
	TArray< FLightweightBuildableReplicationItem > mLightweightBuildableArray;
	
	UPROPERTY( Replicated )
	TSubclassOf< class UFGRecipe > mBuiltWithRecipe;

	UPROPERTY( ReplicatedUsing=OnRep_BuildableClass )
	TSubclassOf< class AFGBuildable > mBuildableClass;

	UPROPERTY( Replicated )
	int32 mMaxSize;
	
	UPROPERTY( Replicated )
	int32 mBlueprintBuildEffectIndex = INDEX_NONE;

	// Stores the index we have replicated up to
	UPROPERTY()
	int32 mCurrentRepIndex;

	UPROPERTY( ReplicatedUsing=OnRep_IncomingConstructIds )
	TArray< uint16 > mIncomingNetConstructIds;

	UPROPERTY( Replicated )
	AActor* mConstructionInstigator;
	
	UPROPERTY()
	bool mClientHasReceivedInitial = false;

	struct FRreplicatorWrapper
	{
		friend class UFGLightweightBuildableConstructionBundle;
		UFGLightweightBuildableConstructionBundle* Replicator = nullptr;

		FRreplicatorWrapper( UFGLightweightBuildableConstructionBundle* inReplicator )
			: Replicator( inReplicator ) {}
	};

	FRreplicatorWrapper Wrap()
	{
		return FRreplicatorWrapper( this );
	}
};

UCLASS()
class FACTORYGAME_API UFGLightweightBuildableRemovalBundle : public UObject
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual void PostInitProperties() override;

	UFUNCTION()
	void OnRep_BuildableClass();
	
	UPROPERTY()
	AFGLightweightBuildableSubsystem* mCachedLightweightSubsystem;

	UPROPERTY()
	AFGLightweightBuildableRepProxy* mCachedRepProxy;
	
	UPROPERTY( Replicated )
	FLightweightBuildableRemovalArray mLightweightBuildableRemovalArray;

	UPROPERTY( ReplicatedUsing = OnRep_BuildableClass )
	TSubclassOf< class AFGBuildable > mBuildableClass;

	UPROPERTY()
	TArray< int32 > mPendingIndices;

	UPROPERTY( Replicated )
	int32 mFullSize;

	UPROPERTY()
	int32 mNumReceived = 0;
	
};

UCLASS()
class FACTORYGAME_API UFGLightweightCustomizationBundle : public UObject
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual void PostInitProperties() override;
	
	UFUNCTION()
	void OnRep_BuildableClass();

	UPROPERTY()
	AFGLightweightBuildableSubsystem* mCachedLightweightSubsystem;
	
	UPROPERTY( Replicated )
	FLightweightBuildableCustomizationArray mLightweightCustomizationArray;

	UPROPERTY( ReplicatedUsing=OnRep_BuildableClass )
	TSubclassOf< class AFGBuildable > mBuildableClass;

	UPROPERTY()
	TArray< int32 > mPendingIndices;

	UPROPERTY( Replicated )
	int32 mFullSize;

	UPROPERTY()
	int32 mNumReceived = 0;
	
};

UCLASS()
class FACTORYGAME_API AFGLightweightBuildableRepProxy : public AFGStaticReplicatedActor
{
	GENERATED_BODY()

public:
	AFGLightweightBuildableRepProxy();
	
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick( float DeltaTime ) override;

	void AddConstructedRuntimeDataForIndex(TSubclassOf< class AFGBuildable > buildableClass, FRuntimeBuildableInstanceData& runtimeData, int32 index, uint16 constructId, AActor* instigator, int32
	                                       blueprintBuildIndex);
	void AddRemovedRuntimeDataForIndex( TSubclassOf< class AFGBuildable > buildableClass, int32 index );
	void AddCustomizationDataForIndex( TSubclassOf< class AFGBuildable > buildableClass, const FFactoryCustomizationData& customizationData, int32 index );

	UFUNCTION( Server, Reliable )
	void Server_NotifyBundleBunchReceived(UFGLightweightBuildableConstructionBundle* bundle );

	UFUNCTION( Server, Reliable )
	void Server_NotifyBundleInitialRepReceived( UFGLightweightBuildableConstructionBundle* bundle);
	void NotifyConstructBundleInitialRepReceived(UFGLightweightBuildableConstructionBundle* bundle );
	
	UFUNCTION( Client, Reliable )
	void Client_SendConstructionBundle( UFGLightweightBuildableConstructionBundle* bundle, const TArray< FLightweightBuildableReplicationItem >& Items );
	
	UFUNCTION(Server, Reliable)
	void Server_NotifyRemovalBundleReplicated( int32 clientCount, UFGLightweightBuildableRemovalBundle* removalBundle);

	UFUNCTION(Server, Reliable)
	void Server_NotifyCustomizationBundleReplicated( int32 clientCount, UFGLightweightCustomizationBundle* customizationBundle );
	
	UPROPERTY( Replicated )
	TArray< UFGLightweightBuildableConstructionBundle* > mPendingConstructionBundles;

	// Bundles which are in the process of being sent
	UPROPERTY()
	TArray< UFGLightweightBuildableConstructionBundle* > mSendingBundles;
	
	UPROPERTY( Replicated )
	TArray< UFGLightweightBuildableRemovalBundle* > mPendingRemovalBundles;

	UPROPERTY( Replicated )
	TArray< UFGLightweightCustomizationBundle* > mPendingCustomizationBundle;
	
	// Removals that were sent BEFORE client ever recieved the full bundle state
	TMap< TSubclassOf< AFGBuildable >, TArray< int32 > > mRemovalsPendingIntialRep; 

	// When the server sends a block of data this is incremented. We only want to allow a select number of sends to avoid a reliable buffer overflow
	UPROPERTY()
	int32 mNumPendingSend = 0;

	
};

USTRUCT()
struct FACTORYGAME_API FPendingGamestateRuntimeDataAdd
{
	GENERATED_BODY()

public:
	FPendingGamestateRuntimeDataAdd() {}
	FPendingGamestateRuntimeDataAdd( const FRuntimeBuildableInstanceData& runtimeData, int32 index ) :
		RuntimeData( runtimeData ),
		Index( index )
	{}
	
	// The runtime data. When the gamestate arrives this will be copied to the usual map
	FRuntimeBuildableInstanceData RuntimeData;
	// While Pending We need to track its index so we know where to insert it
	int32 Index;
};

USTRUCT()
struct FACTORYGAME_API FInstanceHandleIdToRuntimeIndex
{
	GENERATED_BODY()

	FInstanceHandleIdToRuntimeIndex() {}
	FInstanceHandleIdToRuntimeIndex( FInstanceHandle* handle, int32 runtimeIndex ) :
		Handle( handle ),
		RuntimeIndex( runtimeIndex )
	{}

	FInstanceHandle* Handle = nullptr;
	int32 RuntimeIndex = INDEX_NONE;
};


struct FACTORYGAME_API FRuntimeDataBuildEffectProxyData
{
	FRuntimeBuildableInstanceData RuntimeData;
	TArray< UMeshComponent* > MeshComponents;
};

/** Metadata set on the abstract instances to associate them with a lightweight buildable */
struct FACTORYGAME_API FLightweightBuildableInstanceHandleMetadata : FInstanceHandleMetadata
{
	/** Class of the buildable */
	TSubclassOf<AFGBuildable> BuildableClass;
	/** ID of the lightweight buildable */
	int32 BuildableID{INDEX_NONE};
};

/**
 * A descriptor of a lightweight buildable existing in the world
 * Can be used to perform manipulations on the lightweight actor and stored indefinitely without worrying about the lifetime of the lightweight
 * Also caches the position of the lightweight so it can be used to check if the lightweight is still alive
 */
USTRUCT(BlueprintType)
struct FACTORYGAME_API FLightweightBuildableInstanceRef
{
	GENERATED_BODY()
public:
	/** Initializes this struct with the given lightweight buildable data*/
	void Initialize(AFGLightweightBuildableSubsystem* ownerSubsystem, TSubclassOf<AFGBuildable> buildableClass, int32 buildableIndex);

	/** Returns the subsystem that owns this buildable */
	AFGLightweightBuildableSubsystem* GetOwnerSubsystem() const;

	/** Returns the class of this buildable */
	FORCEINLINE TSubclassOf<AFGBuildable> GetBuildableClass() const { return BuildableClass; }

	/** Returns the transform of the buildable */
	FORCEINLINE FTransform GetBuildableTransform() const { return Transform; }

	/** Returns the recipe that this buildable was built with, if any */
	FORCEINLINE TSubclassOf<UFGRecipe> GetBuiltWithRecipe() const { return BuiltWithRecipe; }

	/** Returns the instance data for this buildable, if it is still alive. Will return nullptr if the buildable is no longer valid */
	const FRuntimeBuildableInstanceData* ResolveBuildableInstanceData() const;

	/** Returns true if this lightweight buildable is still valid */
	FORCEINLINE bool IsValid() const { return ResolveBuildableInstanceData() != nullptr; }

	/** Removes the buildable from the world, if it is still valid */
	bool Remove();

	/** Updates the customization data on the buildable, if it is still valid */
	bool SetCustomizationData(const FFactoryCustomizationData& customizationData) const;

	/** Spawns a temporary buildable for this lightweights. Must only be called on game thread, buildable is not replicated or saved. */
	AFGBuildable* SpawnTemporaryBuildable() const;
protected:
	/** The subsystem that owns this lightweight buildable */
	UPROPERTY(SaveGame)
	TWeakObjectPtr<class AFGLightweightBuildableSubsystem> OwnerSubsystem;

	/** Class of this buildable. Used for lookups into the lightweight system */
	UPROPERTY(SaveGame)
	TSubclassOf<AFGBuildable> BuildableClass;

	/** Cached transform of the buildable. Since the index can be re-purposed by another lightweight buildable, we use the transform to be able to tell if this is the same buildable or not */
	UPROPERTY(SaveGame)
	FTransform Transform;

	/** The recipe that the buildable was built with. Cached here because it does not change and also so that this information can be retrieved even when the buildable is no longer there */
	UPROPERTY(SaveGame)
	TSubclassOf<UFGRecipe> BuiltWithRecipe;

	/** ID of the lightweight buildable. Used for lifetime checking and making modifications to the lightweight */
	UPROPERTY(SaveGame)
	int32 LightweightBuildableID{INDEX_NONE};
};

/**
 * Subsystem to manage buildables that dont have an actual actor representation persistent in the world.
 * The primary purpose of this system is to handle walls and foundations without creating persistent actors for them
 * The subsytems is responsible for saving slim data representing the minimum amount of info we need to save and represent the meshes/collision.
 * Temporary actors are spawned (locally only) on the fly so that other systems like holograms and buildgun states can work normally as if
 * an actor was there. These temporary actors are destroyed when they are no longer needed.
 */
UCLASS()
class FACTORYGAME_API AFGLightweightBuildableSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	AFGLightweightBuildableSubsystem();

	
	/** Get the LightweightBuildableSubsystem in the current world, can be nullptr, e.g. on game ending (destroy) or game startup. */
	static AFGLightweightBuildableSubsystem* Get( UWorld* world );

	/** Get the LightweightBuildableSubsystem */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory", DisplayName = "GetLightweightBuildableSubsystem", meta = ( DefaultToSelf = "WorldContext" ) )
	static AFGLightweightBuildableSubsystem* Get( UObject* worldContext );

	// Begin AActor Interface
	virtual void Serialize( FArchive& ar ) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	// End AActor Interface
	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// For clients to notify the gamestate is valid
	void NotifyGamestateReceived();
	
	// Adds an instance converter - If Null will use the system default
	AActor* AddInstanceConverterInstigator( float radius, AActor* instigator = nullptr, FTransform transform = FTransform::Identity );
	void RemoveInstanceConverterInstigator( AActor* instigator = nullptr );
	
	FInstanceToTemporaryBuildable* FindOrSpawnBuildableForRuntimeData( FRuntimeBuildableInstanceData* runtimeData, int32 indexOfRunrtimeData, bool& out_DidSpawn );
	
	// This should only be called when migrating from old save data to the new system. Ie. The buildable will detect its meant for lightweightbuildable system and call into this with itself
	int32 AddFromBuildable(class AFGBuildable* buildable, AActor* buildEffectInstigator = nullptr, class AFGBlueprintProxy* blueprintProxy = nullptr );

	// Removes a buildable and its instances - The buildable will be a lightweight temporary that has been spawned via an instigator
	void RemoveByBuildable( class AFGBuildable* buildable );

	// Removes a instance directly by its class and index
	void RemoveByInstanceIndex( TSubclassOf< class AFGBuildable > buildableClass, int32 instanceIndex );

	// Invalidates the data and will add a removal object to be replicated
	void InvalidateRuntimeInstanceDataForIndex( TSubclassOf<AFGBuildable> buildableClass, int32 index );

	// Lean method of adding an instance from BuildableInstanceData (no instance required)
	int32 AddFromBuildableInstanceData(TSubclassOf< class AFGBuildable > buildableClass, FRuntimeBuildableInstanceData& buildableInstanceData, bool fromSaveData = false, int32 saveDataBuildableIndex = INDEX_NONE, uint16 constructId = MAX_uint16, AActor* buildEffectInstigator = nullptr, int32 blueprintBuildEffectIndex = INDEX_NONE );

	void AddFromReplicatedData( TSubclassOf< AFGBuildable > buildableClass, TSubclassOf< class UFGRecipe > builtWithRecipe, const FLightweightBuildableReplicationItem& replicationData, int32 maxSize, AActor* buildEffectInstigator, int32 blueprintBuildIndex );

	// Called end of tick. Destroys and buildables and deletes the instance to temp data for them
	void RemoveStaleTemporaryBuildables();

	// Removes Temporary Buildables by runtime instance (if a building is destroyed that has a temporary instance this handles its removal / destruction )
	void RemoveTemporaryBuildableForInstanceIndex( TSubclassOf<AFGBuildable> buildableClass, int32 instanceIndex );

	void RemoveInstanceToTemporary( FInstanceToTemporaryBuildable* instanceToTemp );

	// Called by other systems to position the Generic Instigator (for dismantle, or customizaiton)
	void SetInstanceInstigatorLocation( AActor* instigator, const FVector& location );

	void CopyCustomizationDataFromTemporaryToInstance( AFGBuildable* buildable );

	void SetCustomizationDataOnInstance( TSubclassOf< AFGBuildable > buildableClass, FFactoryCustomizationData customizationData, int32 index );

	int32 GetRuntimeDataIndexForBuildable( class AFGBuildable* buildable );
	class AFGBuildable* FindTemporaryByBuildableClassAndIndex( TSubclassOf< class AFGBuildable > buildableClass, int32 index );

	void RegisterReplicationProxy( class AFGLightweightBuildableRepProxy* repProxy ) { mAllLightweightReplicationProxies.AddUnique( repProxy ); }
	void UnregisterReplicationProxy( class AFGLightweightBuildableRepProxy* repProxy ) { mAllLightweightReplicationProxies.Remove( repProxy ); }

	uint32 GetSnappedGridHashLocationForInstanceLocation( TSubclassOf< AFGBuildable > buildableClass, UStaticMesh* staticMesh, const FVector& instanceLocation ) const;
	void AddGridHashEntryForNewInstance( TSubclassOf< AFGBuildable > buildableClass, UStaticMesh* staticMesh, const FVector& instanceLocation, FInstanceHandle* handle, int32 runtimeIndex );

	TSubclassOf< class UFGRecipe > GetBuiltWithRecipeForBuildableClass( TSubclassOf< AFGBuildable > buildableClass );

	void BlueprintProxyHoveredForDismantle( class AFGBlueprintProxy* blueprintProxy );
	void BlueprintProxyStopHoveredForDismantle( class AFGBlueprintProxy* blueprintProxy );

	/** Called from OnRep in blueprint PRoxies. The reason for this is because blueprint proxies may arrive after the instances are replicated */
	void NotifyInstancesOfBlueprintProxy( const TArray< FBuildableClassLightweightIndices >& lightweightInstancesAndIndices, AFGBlueprintProxy* blueprintProxy );

	FRuntimeBuildableInstanceData* GetRuntimeDataForBuildableClassAndIndex( TSubclassOf< class AFGBuildable > buildableClass, int32 index );

	void NotifyRepProxyCreated( AFGLightweightBuildableRepProxy* proxy ) { mCachedLocalRepProxy = proxy; }

	FORCEINLINE void SetColorSlotDataDirty() { mColorSlotDataDirty = true; }

	void AddBuildEffectForRuntimeData( AFGBuildEffectActor* buildEffectActor, TSubclassOf< AFGBuildable > buildableClass, int32 index );
	void RemoveBuildEffectForRuntimeData( AFGBuildEffectActor* buildEffectActor );

	/** Resolves a hit of the lightweight buildable subsystem instance into the info about the buildable that was hit */
	UFUNCTION(BlueprintCallable, Category = "Lightweight Buildable")
	static bool ResolveLightweightInstance(const FInstanceHandle& instanceHandle, FLightweightBuildableInstanceRef& out_buildableDescriptor);
public:
	// When loading we will repeatedly use this storage location to store temporary instances that then get copied to their correct location
	static FRuntimeBuildableInstanceData mStaticRuntimeInstanceDataStorage;


private:
	TSoftClassPtr< class UFGMaterialEffect_Build > GetBuildEffectTemplate() const;
	TSoftClassPtr< class UFGMaterialEffect_Build > GetDismantleEffectTemplate() const;

	void CreateBuildEffectForRuntimeData( TSubclassOf<AFGBuildable> buildableClass, FRuntimeBuildableInstanceData& runtimeData, AActor* instigator, UAbstractInstanceDataObject* instanceData, int32 Index );
	void OnBuildEffectFinished( class UFGMaterialEffectComponent* materialEffect );

	void CreateDismantleEffectForRuntimeData( FRuntimeBuildableInstanceData& runtimeData, AActor* instigator, class UAbstractInstanceDataObject* instanceData );
	void OnDismantleEffectFinished( class UFGMaterialEffectComponent* materialEffect );
private:
	friend class AFGLightweightBuildableRepProxy;
	friend class UFGLightweightBuildableRemovalBundle;

	// Simple pool struct for handling pre spawned buildables to reduce overhead on creating lightweight temporaries (just reuse buildings)
	FLightweightBuildablePool mLightweightBuildablePool;

	// Cached Gamestate to allow us to initialize customization data without getting it everytime
	class AFGGameState* mCachedGameState;

	// When color slots change mark it here so we can update color data on instances in tick - like we do for buildables
	bool mColorSlotDataDirty;

	// For tracking how far along we are when updating the color data when it changes (don't want to apply all in one pass as it could cause hitching)
	TArray< TSubclassOf< AFGBuildable > > mBuildableClassColorUpdateArray;
	int32 mColorUpdateRuntimeIndex = 0;
	
	// For clients they can keep a cached ref to their rep proxy
	UPROPERTY()
	AFGLightweightBuildableRepProxy* mCachedLocalRepProxy;
	
	// The actor to attach temporary build components effects too
	UPROPERTY()
	class AActor* mBuildEffectComponentActor;

	// For clients there is a race condition where they might receive instance data before the game state is ready, in which case that data is added here while we wait for the gamestate
	TMap< TSubclassOf < class AFGBuildable >, TArray< FPendingGamestateRuntimeDataAdd > > mPendingGameStateInstances;
	
	// Generic Actor that can be utilized as an instance converter - Useful for build gun states that are isolated and dont have a placement actor ie. hologram
	UPROPERTY()
	TArray< AActor* > mGenericInstanceInstigators;
	
	// Holds a map of each buildable type to its corresponding runtime instance data. Each data holds handles to the managers instanceID
	TMap< TSubclassOf< class AFGBuildable >, TArray< FRuntimeBuildableInstanceData > > mBuildableClassToInstanceArray;
	
	// Holds a map of each buildable type to a list of empty Indexes. We don't actually shrink the array so we track which index is "invalid" we then overright those "empty" spots when we add new elements
	TMap< TSubclassOf< class AFGBuildable >, TArray< int32 > > mBuildableClassToEmptyIndices;

	// While build effect actors are running we track instance information so that we can notify the build effect if such an instance is removed
	UPROPERTY()
	TArray< FBuildEffectAndRuntimeInfo > mActiveBuildEffectToRuntimeData;

	// Just a cache of the building type to the AbstractInstanceData object. This is just to speed up access looks without having to resolve each time
	UPROPERTY()
	TMap< TSubclassOf< class AFGBuildable >, UAbstractInstanceDataObject* > mBuildableToCachedAbstractInstanceData;

	// This is the cache map to speed up search time when looking for a specific runtime data. The map key is the grid snapped hash location of the instance
	// Using this we only need to search in the cells immediately around where the search is taking place
	TMap< uint32, TArray< FInstanceHandleIdToRuntimeIndex > > mGridHashToHandleIdMap;

	// Array of all handles and their associated temporary buildables
	TArray< FInstanceToTemporaryBuildable* > mInstigatedInstanceToTemporaryBuildables = {};

	// Instance To Temp Builds that were found "this frame" others will be culled at the end of tick
	TArray< FInstanceToTemporaryBuildable* > mRefreshedInstanceToTemporaryBuildables = {};

	// Array of Instance to temporaries for a given blueprintProxy
	UPROPERTY()
	TArray< class AFGBlueprintProxy* > mCurrentlyHoveredBlueprintProxies;

	// Active instance converters. Updated in tick, when the AActor in question is removed the converter will self destruct
	UPROPERTY()
	TArray< FInstanceConverterInstigator > mActiveInstanceConverters = {};

	// Each replication proxy created per player (cached for quick access)
	UPROPERTY()
	TArray< class AFGLightweightBuildableRepProxy* > mAllLightweightReplicationProxies;

	// Array of all newly created runtime data that is pending add from build effects 
	TMap< UFGMaterialEffect_Build*, FRuntimeDataBuildEffectProxyData > mPendingAddFromBuildEffect;

	TMap< UFGMaterialEffect_Build*, FRuntimeDataBuildEffectProxyData > mPendingRemovalFromDismantleEffect;

	TArray< TTuple < TSubclassOf< AFGBuildable >, int32, class AFGBlueprintProxy* >> mPendingAssignBlueprintProxy;

	UPROPERTY()
	TSubclassOf< UFGMaterialEffect_Build > mCachedBuildEffectTemplate;
	UPROPERTY()
	TSubclassOf< UFGMaterialEffect_Build > mCachedDismantleEffectTemplate;
	
	// The amount of time since we last attempted to remove stale temporaries
	UPROPERTY()
	float mTimeSinceLastStaleTemporaryCulling;

};

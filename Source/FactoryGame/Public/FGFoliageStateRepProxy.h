// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Containers/RingBuffer.h"
#include "CoreMinimal.h"
#include "FGFoliageTypes.h"
#include "GameFramework/Actor.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGFoliageStateRepProxy.generated.h"


DECLARE_DELEGATE_OneParam(FOnNewFoliageRemovalReplicated, uint32);
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogFoliageReplication, Verbose, Verbose );

USTRUCT()
struct FFoliageLocationHash : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FFoliageLocationHash() = default;
	FFoliageLocationHash(const FFoliageLocationHash&) = default;
	FFoliageLocationHash(FFoliageLocationHash&&) = default;

	FFoliageLocationHash& operator=(const FFoliageLocationHash&) = default;
	FFoliageLocationHash& operator=(FFoliageLocationHash&&) = default;
	
	FFoliageLocationHash(uint32 inHash)
		: Hash( inHash )
		{}
	
	UPROPERTY()
	uint32 Hash = 0;
};

DECLARE_DELEGATE_TwoParams(FOnPostReplicatedAddFoliage, const TArrayView<int32>& AddedIndices, int32 FinalSize);

USTRUCT()
struct FFoliageRemovalHashArray : public FFastArraySerializer
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FFoliageLocationHash> Items;

	FOnPostReplicatedAddFoliage OnHashesAdded;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FastArrayDeltaSerialize<FFoliageLocationHash>(Items, DeltaParms, *this);
	}

	void PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize);
};

template<>
struct TStructOpsTypeTraits<FFoliageRemovalHashArray>: public TStructOpsTypeTraitsBase2<FFoliageRemovalHashArray>
{
	enum { WithNetDeltaSerializer = true };
};

UCLASS()
class FACTORYGAME_API UFGFoliageRemovalBundle: public UObject
{
GENERATED_BODY()
public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitProperties() override;
	virtual bool IsSupportedForNetworking() const override;
	
	UPROPERTY(Replicated)
	FFoliageRemovalHashArray ReplicationBuffer;

	UPROPERTY(Replicated)
	TObjectPtr<const UFoliageType> FoliageType;

	UPROPERTY(Replicated)
	FIntVector FoliageCell = {};

	UPROPERTY(Replicated)
	int32 NumHashes = INDEX_NONE;

	struct FRreplicatorWrapper
	{
		friend class UFGFoliageRemovalBundle;
		UFGFoliageRemovalBundle* Replicator = nullptr;
	private:
		FRreplicatorWrapper( UFGFoliageRemovalBundle* inReplicator )
			: Replicator( inReplicator ) {}
	};

	FRreplicatorWrapper Wrap()
	{
		return FRreplicatorWrapper( this );
	}
};

UCLASS()
class FACTORYGAME_API AFGFoliageStateRepProxy: public AFGStaticReplicatedActor
{
	GENERATED_BODY()
public:
	void ConfirmFullyReplicated( UFGFoliageRemovalBundle::FRreplicatorWrapper replicator );
	
protected:
	AFGFoliageStateRepProxy();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	UFUNCTION(Server, Reliable)
	void Server_ConfirmFullyReplicated(UFGFoliageRemovalBundle* replicator);
	
	UFUNCTION()
	void OnFoliageBucketRemoved(const FIntVector& inCell, const UFoliageType* forFoliageType, int32 bucketId );
	
	/**
	 * Only relevant on the server. All the removal buckets that have been created but for which replication hasn't begun yet
	 */
	TPerCellPerTypeMap< int32 > mFirstUnreplicatedBucketInfos;
	
	UPROPERTY(Replicated)
	TArray< UFGFoliageRemovalBundle* > mPendingBundles;

	/* Replication radius, reflects "very far" foliage loading distance setting.*/
	UPROPERTY(EditDefaultsOnly)
	float mReplicationRadius = 102400.f; 

	UPROPERTY(EditDefaultsOnly)
	int32 mMaxPendingBundles = 24;
};

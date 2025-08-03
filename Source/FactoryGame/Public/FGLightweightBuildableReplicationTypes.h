// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGLightweightBuildableSubsystem.h"

class AFGBuildable;
class UFGRecipe;
class AActor;

enum class ELightweightBuildableMessageId : uint32
{
	InitialReplication = 0x01,
	BuildableAdded = 0x02,
	BuildableRemoved = 0x03,
	BuildableUpdated = 0x04
};

struct FLightweightBuildableInstanceSerialData
{
	FTransform Transform;
	FFactoryCustomizationData CustomizationData;
	int32 InstanceID{INDEX_NONE};
	FFGDynamicStruct BuildableTypeSpecificData;

	friend FArchive& operator<<(FArchive& Ar, FLightweightBuildableInstanceSerialData& SerialData);
};

struct FLightweightBuildableConstructionData
{
	TSubclassOf<AFGBuildable> BuildableClass;
	TSubclassOf<UFGRecipe> BuiltWithRecipe;
	int32 ServerNumInstances{};
	TArray<FLightweightBuildableInstanceSerialData> Instances;
	int32 BlueprintBuildEffectIndex{INDEX_NONE};
	TSet<uint16> IncomingNetConstructIds;
	AActor* ConstructionInstigator{};
	TSet<int32> NotReplicatedContainedInstanceIDs;

	// Note that this does not compare incoming net construct IDs and instances
	friend bool operator==(const FLightweightBuildableConstructionData& A, const FLightweightBuildableConstructionData& B);

	friend FArchive& operator<<(FArchive& Ar, FLightweightBuildableConstructionData& ConstructionData);
};

struct FLightweightBuildableRemovalData
{
	TSubclassOf<AFGBuildable> BuildableClass;
	TArray<int32> InstanceIDs;

	friend FArchive& operator<<(FArchive& Ar, FLightweightBuildableRemovalData& RemovalData);
};

struct FLightweightBuildableUpdateData
{
	TSubclassOf<AFGBuildable> BuildableClass;
	TArray<FLightweightBuildableInstanceSerialData> UpdatedInstances;
	TSet<int32> NotReplicatedContainedInstanceIDs;

	friend FArchive& operator<<(FArchive& Ar, FLightweightBuildableUpdateData& UpdateData);
};

struct FLightweightBuildableConstructionMessage
{
	static constexpr ELightweightBuildableMessageId MessageId = ELightweightBuildableMessageId::BuildableAdded;
	TArray<FLightweightBuildableConstructionData> ConstructionData;

	friend FArchive& operator<<(FArchive& Ar, FLightweightBuildableConstructionMessage& Message);
};

struct FLightweightBuildableRemovalMessage
{
	static constexpr ELightweightBuildableMessageId MessageId = ELightweightBuildableMessageId::BuildableRemoved;
	TArray<FLightweightBuildableRemovalData> RemovalData;

	friend FArchive& operator<<(FArchive& Ar, FLightweightBuildableRemovalMessage& Message);
};

struct FLightweightBuildableInitialReplicationMessage
{
	static constexpr ELightweightBuildableMessageId MessageId = ELightweightBuildableMessageId::InitialReplication;
	TArray<FLightweightBuildableConstructionData> InitialConstructionData;
	
	friend FArchive& operator<<(FArchive& Ar, FLightweightBuildableInitialReplicationMessage& Message);
};

struct FLightweightBuildableUpdateMessage
{
	static constexpr ELightweightBuildableMessageId MessageId = ELightweightBuildableMessageId::BuildableUpdated;
	TArray<FLightweightBuildableUpdateData> UpdateData;

	friend FArchive& operator<<(FArchive& Ar, FLightweightBuildableUpdateMessage& Message);
};

struct FLightweightBuildableReplicationSendState
{
	/** Lightweight buildables constructed since last replication */
	TArray<FLightweightBuildableConstructionData> PendingConstructions;

	/** Lightweight buildables removed since last replication */
	TArray<FLightweightBuildableUpdateData> PendingUpdates;

	/** Lightweight buildables removed since last replication */
	TArray<FLightweightBuildableRemovalData> PendingRemovals;

	FORCEINLINE bool IsEmpty() const { return PendingConstructions.IsEmpty() && PendingUpdates.IsEmpty() && PendingRemovals.IsEmpty(); }
};

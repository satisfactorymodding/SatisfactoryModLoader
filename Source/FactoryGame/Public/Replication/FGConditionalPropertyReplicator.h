// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/CoreNet.h"
#include "FGConditionalPropertyReplicator.generated.h"

class IFGConditionalReplicationInterface;

class FFGConditionalPropertyReplicatorDeltaState : public INetDeltaBaseState
{
public:
	/** The bits are set for properties that are actually relevant for this connection */
	TBitArray<> mRelevantPropertyMask;
	/** The bits on this set are set when the property has */
	TBitArray<> mInitialReplicationPendingMask;
	/** The changelist that has been sent to that connection last time */
	TArray<FThreadSafeCounter::IntegerType, TInlineAllocator<16>> mCurrentChangelist;
	/** Net delta serialization states used by structs with custom NetDeltaSerialize */
	TArray<TSharedPtr<INetDeltaBaseState>> mCurrentDeltaStates;
	/** Changelist number for the relevant properties mask. If it differs from the one of the property replicator the cache will be re-computed */
	FThreadSafeCounter::IntegerType mRelevantPropertiesChangelist;
	
	virtual bool IsStateEqual( INetDeltaBaseState* Otherstate ) override
	{
		const FFGConditionalPropertyReplicatorDeltaState* other = static_cast<const FFGConditionalPropertyReplicatorDeltaState*>( Otherstate );
		return mCurrentChangelist == other->mCurrentChangelist;
	}
};

enum class EFGCondRepPropertyType
{
	PlainOldData, // Property can be serialized/deserialized as a binary blob
	NetSerializeItem, // Property is serialized/deserialized through FProperty virtual functions
	Struct, // Property is a struct and should be initialized through NetSerializeStruct
	DeltaStruct, // Property is a struct with a custom delta serializer and should be serialized manually
	CustomSerializer, // Property has a CustomSerializer specified
	PlainOldDataArray, // Property is ArrayProperty that can be serialized as a Bulk because it's elements are POD types
	ComplexArray, // Property is ArrayProperty that has complex element types that need their serializers ran (NetSerialize or Struct ones)
};

/** Type used by custom serializers that can be supplied to the replicated property */
using FFGCustomCondPropertySerializerType = bool( FProperty* property, void* propertyValuePtr, FNetDeltaSerializeInfo& deltaParams );

/** Holds information about a conditionally replicated property */
struct FACTORYGAME_API FFGCondReplicatedProperty
{
	/** Property being replicated */
	FProperty* Property;
	/** RepNotify function bound to this property */
	UFunction* RepNotifyFunction;
	/** Custom serializer for the property, can be used on the property of any type */
	TFunction<FFGCustomCondPropertySerializerType> CustomSerializer;

	// Derived properties automatically populated by the registration code
	EFGCondRepPropertyType RepPropertyKind;
	UScriptStruct* ScriptStruct;
	int32 CustomDeltaStructPropIndex;
	// Inner property of the array property, used for actual element serialization as we literally cannot trust arrays to sensibly serialize anything themselves
	// because they would just bail out on struct properties (good system design btw)
	TSharedPtr<FFGCondReplicatedProperty> ArrayInnerProperty;
	int32 ArrayNumBytesPerElement;
};

/** Data stored on a per-class basis and only initialized and allocated once per class */
struct FACTORYGAME_API FFGCondPropsClassData
{
	/** Conditionally replicated properties owned by this class */
	TArray<FFGCondReplicatedProperty> Properties;
	/** Total number of properties that have custom delta serializers */
	int32 NumCustomDeltaStructProps;
	/** Map of property names to property indices */
	TMap<FName, int32> PropertyIndicesMap;
	/** Property that holds a FGConditionalPropertyReplicator for this class. Should never be null. */
	FProperty* ReplicatorProperty;
};

/** Internal state used by the property replicator, held as a pointer and not copied when the struct is carried around */
class FACTORYGAME_API FFGConditionalPropertyReplicatorState
{
	/** The UObject that owns this state */
	TScriptInterface<IFGConditionalReplicationInterface> mStateOwner;
	/** Cached pointer to the class data for the list of props for faster lookups */
	const FFGCondPropsClassData* mClassData;
	

	/**
	 * Current changelist numbers for the replicated properties
	 * The data for the relevant property will be re-sent to the client if the changelist number is different
	 */
	TArray<FThreadSafeCounter, TInlineAllocator<16>> mActiveChangelistNumbers;

	/** Current changelist of the relevant properties cache. When it does not match the connection one, the relevant property mask for the connection is rebuilt */
	FThreadSafeCounter mRelevantPropertiesChangelist;

	/**
	 * A delegate to which things can bind to get notified when the relevant properties cache is rebuild for this replicator
	 * Keep in mind that binding to this delegate is not in fact thread safe, but getting the notify is.
	 */
	FSimpleMulticastDelegate mInvalidateRelevantPropertiesChange;
public:
	FFGConditionalPropertyReplicatorState( UObject* stateOwner );

	void AddReferencedObjects( FReferenceCollector& collector );
	bool NetDeltaSerialize( FNetDeltaSerializeInfo& deltaParams );
	void EnsureStateOwnerIsTheSame( const UObject* stateOwner ) const;

	/**
	 * Invalidates relevant properties cache for all of the connections
	 * That will result in all connections calling IsPropertyRelevantForConnection on the interface to re-fetch the relevant status
	 * the next time the actor is replicated
	 */
	void InvalidateRelevantPropertiesCache();

	/** Allows being notified when relevant properties cache for this replicator is invalidated */
	FORCEINLINE FSimpleMulticastDelegate& OnInvalidateRelevantPropertiesChange() { return mInvalidateRelevantPropertiesChange; }

	/**
	 * Marks the property with the specified name as dirty
	 * That means the property will be re-sent next time the actor is replicated
	 */
	void MarkPropertyDirty( const FName& propertyName );

	/** Initializes class data for the provided class */
	static void InitializeClassData( UClass* inClass, FFGCondPropsClassData* classData );
private:
	static void InitializeDerivedDataForProperty( FFGCondReplicatedProperty& inProperty, int32& customDeltaPropertyCount );
	static FProperty* ValidateReplicatorPropertyPreconditions( UClass* inClass );
	void MarkPropertyDirty( int32 propertyIndex );
	bool IsPropertyRelevantForConnection( const FNetDeltaSerializeInfo& deltaParams, const FFGCondReplicatedProperty& propData ) const;

	static FNetDeltaSerializeInfo MakeChildDeltaSerializeInfo( const FNetDeltaSerializeInfo& parentInfo );
	static bool NetDeltaSerializeProperty( const FNetDeltaSerializeInfo& deltaParams, const FFGCondReplicatedProperty& property, void* propertyValuePtr, FFGConditionalPropertyReplicatorDeltaState* currentState );
};

/**
 * Conditional property replicator manages the replication of properties on a per-connection relevancy basis
 *
 * The way to use it is to have a single U-PROPERTY(Replicated) of type FGConditionalPropertyReplicator and call Init in the constructor
 * 
 */
USTRUCT()
struct FACTORYGAME_API FFGConditionalPropertyReplicator
{
	GENERATED_BODY()
private:
	TSharedPtr<FFGConditionalPropertyReplicatorState> State;
public:
	/**
	 * Marks particular property dirty and forces it to be re-sent to the remote connections on the next replication loop
	 * The property must be relevant for the connection to be replicated to it as well
	 */
	void MarkPropertyDirty( const FName& propertyName ) const;

	/**
	 * Invalidates relevant properties cache on the connections and forces them all to recompute the relevance
	 * of the properties and potentially start or stop replicating old/new properties according to what the interface considers relevant
	 */
	void InvalidateRelevantPropertiesCache() const;

	/**
	 * Returns the delegate to which people can bind to be notified when this replicator invalidates it's property relevance cache
	 * Keep in mind that this function is not a simple getter and will more frequently than not cause this replicator to acquire State that is
	 * usually lazily created during the NetDeltaSerialize from the provided context object
	 *
	 * Extra caution must be paid to make sure that this function is the called with the actual object this replicator belongs to.
	 * Failed to do so will result in replication being broken and a failed check next time the correct object is passed.
	 *
	 * Normally you should not call this function manually, but instead use IFGConditionalReplicationInterface::OnInvalidateRelevantPropertiesCache()
	 * which will call it for you with the correct object argument.
	 */
	FSimpleMulticastDelegate& GetOrComputeOnInvalidateRelevantPropertiesCache( UObject* stateOwner );

	// Function overrides for replication
	void AddReferencedObjects(FReferenceCollector& collector) const;
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& deltaParams);
};

template<>
struct TStructOpsTypeTraits<FFGConditionalPropertyReplicator> : TStructOpsTypeTraitsBase2<FFGConditionalPropertyReplicator>
{
	enum
	{
		WithNetDeltaSerializer = true,
		WithCopy = true,
		WithAddReferencedObjects = true,
	};
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EngineLogs.h"
#include "UObject/Interface.h"
#include "FGConditionalPropertyReplicator.h"
#include "FGConditionalReplicationInterface.generated.h"


#define FG_DOREPCONDITIONAL_EXTRA( c, v, ... ) \
{ \
	FProperty* replicatedProperty = FGCondPropRep_GetReplicatedProperty(StaticClass(), c::StaticClass(), GET_MEMBER_NAME_CHECKED(c,v)); \
	FGCondPropRep_EnsurePropertyHasNoRepNotifyFunc(replicatedProperty); \
	outProps.Add( FFGCondReplicatedProperty{ replicatedProperty, __VA_ARGS__ } ); \
}

#define FG_DOREPCONDITIONAL_WITH_NOTIFY_EXTRA( c, v, notify, ... ) \
{ \
	FProperty* replicatedProperty = FGCondPropRep_GetReplicatedProperty(StaticClass(), c::StaticClass(), GET_MEMBER_NAME_CHECKED(c,v)); \
	UFunction* repNotifyFunction = FGCondPropRep_GetRepNotifyFunc(replicatedProperty, GET_FUNCTION_NAME_CHECKED(c, notify)); \
	outProps.Add( FFGCondReplicatedProperty{ replicatedProperty, repNotifyFunction, __VA_ARGS__ } ); \
}

#define FG_DOREPCONDITIONAL( c, v ) FG_DOREPCONDITIONAL_EXTRA(c, v, nullptr)
#define FG_DOREPCONDITIONAL_WITH_NOTIFY( c, v, notify ) FG_DOREPCONDITIONAL_WITH_NOTIFY_EXTRA(c, v, notify, nullptr)

class UNetConnection;

UINTERFACE()
class FACTORYGAME_API UFGConditionalReplicationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to be implemented on the objects that are willing to undergo a conditional property replication based on the relevancy of each property to each connection
 * This is commonly used to e.g. replicate data only relevant when the UI is open to the players that have the UI in question open, and to nobody else
 * That saves the bandwidth and reduces the cost of replication when having many replicating actors.
 *
 * In addition to implementing the interface, you need to declare a struct property of type FFGConditionalPropertyReplicator
 */
class FACTORYGAME_API IFGConditionalReplicationInterface
{
	GENERATED_BODY()

public:
	/**
	 * Use this function to register conditionally replicated properties declared in this class
	 * The correct way to do that is to use the macros, such as 'FG_DOREPCONDITIONAL' and 'FG_DOREPCONDITIONAL_WITH_NOTIFY'
	 * 
	 * They work in a very similar way to the UE's 'DOREPLIFETIME' and have similar semantics, the main difference is that for these
	 * You do not need (and should not!) mark the property as Replicated, and should also specify the name of the RepNotify here instead of specifying it on the property
	 *
	 * This will only be called once per class on the CDO and should not contain any conditional logic.
	 */
	virtual void GetConditionalReplicatedProps( TArray<FFGCondReplicatedProperty>& outProps ) const = 0;

	/**
	 * Called every time the relevancy of the properties is recomputed for the connection to check if the property is relevant to it
	 * Keep in mind that this function will only be called if you manually request the FGConditionalPropertyReplicator to refresh the properties states
	 * 
	 * by calling 'FGConditionalPropertyReplicator::InvalidatePropertyRelevancyCache()'
	 * That will invalidate the cached data for all connections and re-compute it on the next replication attempt.
	 */
	virtual bool IsPropertyRelevantForConnection( UNetConnection* netConnection, const FProperty* property ) const = 0;

	/**
	 * Returns the conditional property replicator used by this interface
	 * This will look up the class data to automatically find the relevant property and return the pointer to it, so it does not need to be manually overriden.
	 */
	FFGConditionalPropertyReplicator& GetConditionalPropertyReplicator() const;

	/**
	 * Returns a delegate to which you can bind to be notified when the relevant properties cache on this object has been invalidated
	 * This is useful when your object relevance cache depends on another object and you would like to be notified when that object flushes it's cache
	 */
	FSimpleMulticastDelegate& OnInvalidateRelevantPropertiesCache() const;
	
};

static bool FGCondPropRep_ValidateReplicatedClassInheritance( const UClass* callingClass, const UClass* propClass, const TCHAR* propertyName )
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if (!callingClass->IsChildOf(propClass))
	{
		UE_LOG(LogNet, Fatal, TEXT("Attempt to replicate property '%s.%s' in C++ but class '%s' is not a child of '%s'"), *propClass->GetName(), propertyName, *callingClass->GetName(), *propClass->GetName());
	}
#endif
	return true;
}

static UFunction* FGCondPropRep_GetRepNotifyFunc( const FProperty* replicatedProperty, const FName& functionName )
{
	UFunction* repNotifyFunc = FindFieldChecked<UFunction>( replicatedProperty->GetOwnerClass(), functionName );
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	// The function should have no return value, at most 1 parameter (old value of the property), and the parameter should have the exact same type as the replicated property
	if ( repNotifyFunc->GetReturnProperty() != nullptr || repNotifyFunc->NumParms > 1 || ( repNotifyFunc->PropertyLink != nullptr && !repNotifyFunc->PropertyLink->SameType( replicatedProperty ) ) )
	{
		UE_LOG(LogNet, Fatal, TEXT("Attempt to set RepNotify function '%s' on the conditionally replicated property '%s', but it has invalid parameters. RepNotify should have no return value and either no parameters or one parameter matching the property type'"), *repNotifyFunc->GetFullName(), *replicatedProperty->GetFullName());
	}

	// We only run the logic below in the editor builds as metadata is not present in packaged game builds
#if WITH_EDITOR

	// Make sure the registration type matches the metadata type
	if ( !replicatedProperty->HasMetaData( TEXT("FGReplicatedUsing") ) )
	{
		UE_LOG(LogNet, Fatal, TEXT("Conditionally Replicated Property '%s' is registered with RepNotify %s. But does not specify it's name in 'FGReplicatedUsing'. Please fix the property declaration.'"), *replicatedProperty->GetFullName(), *functionName.ToString() );
	}

	// Make sure the name of the RepNotify that was passed to the registration matches the metadata
	const FString metadataRepNotifyName = replicatedProperty->GetMetaData( TEXT("FGReplicatedUsing") );
	if ( metadataRepNotifyName != functionName.ToString() )
	{
		UE_LOG(LogNet, Fatal, TEXT("Conditionally Replicated Property '%s' was registered with RepNotify '%s', but specifies RepNotify '%s' in the 'FGReplicatedUsing' Metadata. Please fix the property registration.'"), *replicatedProperty->GetFullName(), *functionName.ToString(), *metadataRepNotifyName );
	}
#endif

#endif
	return repNotifyFunc;
}

static void FGCondPropRep_EnsurePropertyHasNoRepNotifyFunc( const FProperty* replicatedProperty )
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	
	// We only run the logic below in the editor builds as metadata is not present in packaged game builds
#if WITH_EDITOR

	// Make sure the normal property is not marked as RepNotify one, otherwise either the metadata or the registration is messed up
	if ( replicatedProperty->HasMetaData( TEXT("FGReplicatedUsing") ) )
	{
		const FString metadataRepNotifyName = replicatedProperty->GetMetaData( TEXT("FGReplicatedUsing") );
		UE_LOG(LogNet, Fatal, TEXT("Conditionally Replicated Property '%s' is marked as FGReplicatedUsing = '%s', but is registered without a RepNotify. Please fix the registration.'"), *replicatedProperty->GetFullName(), *metadataRepNotifyName );
	}
#endif

#endif
}

/** Wrapper to find the replicated property and also make sure that UE will not attempt to replicate it normally (because that conflicts with conditional replication) */
static FProperty* FGCondPropRep_GetReplicatedProperty( const UClass* callingClass, const UClass* propClass, const FName& propName )
{
	FGCondPropRep_ValidateReplicatedClassInheritance(callingClass, propClass, *propName.ToString());

	FProperty* theProperty = FindFieldChecked<FProperty>(propClass, propName);
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if ( theProperty->HasAnyPropertyFlags( CPF_Net ) || theProperty->RepNotifyFunc != NAME_None )
	{
		UE_LOG(LogNet, Fatal, TEXT("Attempt to conditionally replicate property '%s' that was tagged 'Replicated' or 'ReplicatedUsing'. Conditionally replicated properties should never be replicated by UE!'"), *theProperty->GetFullName());
	}

	// We only run the logic below in the editor builds as metadata is not present in packaged game builds
#if WITH_EDITOR

	// Make sure we have at least one of these
	if ( !theProperty->HasMetaData( TEXT("FGReplicated") ) && !theProperty->HasMetaData( TEXT("FGReplicatedUsing") ) )
	{
		UE_LOG(LogNet, Fatal, TEXT("Conditionally Replicated Property '%s' that was not marked as 'FGReplicated' or 'FGReplicatedUsing'. Conditionally Replicated properties should be marked as either 'FGReplicated' or 'FGReplicatedUsing'.'"), *theProperty->GetFullName());
	}

	// Make sure we do not actually have both though
	if ( theProperty->HasMetaData( TEXT("FGReplicated") ) && theProperty->HasMetaData( TEXT("FGReplicatedUsing") ) )
	{
		UE_LOG(LogNet, Fatal, TEXT("Conditionally Replicated Property '%s' that is marked both as 'FGReplicated' and 'FGReplicatedUsing'. It should only have one.'"), *theProperty->GetFullName());
	}
#endif
	
#endif
	return theProperty;
}
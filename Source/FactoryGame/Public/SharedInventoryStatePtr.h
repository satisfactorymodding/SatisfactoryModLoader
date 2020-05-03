// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UnrealString.h"

#include "FGSaveSession.h"
#include "GameFramework/Actor.h"
#include "SharedPointer.h"
#include "Engine/PackageMapClient.h"
#include "Engine/NetConnection.h"
#include "SharedInventoryStatePtr.generated.h"

USTRUCT()
struct FACTORYGAME_API FSharedInventoryStatePtr
{
	GENERATED_USTRUCT_BODY()
public:
	/** Null inventory state, use this to null an inventory state pointer. */
	static FSharedInventoryStatePtr NullState;

	/**
	 * Make a shared pointer of for an actor.
	 * @note Only valid to call on the server.
	 */
	FORCEINLINE static FSharedInventoryStatePtr MakeShared( AActor* actor )
	{
		if( ::IsValid( actor ) )
		{
			checkf( actor->GetNetMode() != ENetMode::NM_Client, TEXT( "Clients can't create shared inventory pointers") );
		}

		return FSharedInventoryStatePtr( actor );
	}

public:
	FORCEINLINE FSharedInventoryStatePtr() :
		ActorPtr( nullptr ),
		SharedReferenceCount()
	{
	}

	FORCEINLINE FSharedInventoryStatePtr( const FSharedInventoryStatePtr& inSharedPtr ) :
		ActorPtr( inSharedPtr.ActorPtr ),
		SharedReferenceCount( inSharedPtr.SharedReferenceCount )
	{
	}

	FORCEINLINE FSharedInventoryStatePtr( FSharedInventoryStatePtr&& inSharedPtr ) :
		ActorPtr( inSharedPtr.ActorPtr ),
		SharedReferenceCount( MoveTemp( inSharedPtr.SharedReferenceCount ) )
	{
		inSharedPtr.ActorPtr = nullptr;
	}

	FORCEINLINE FSharedInventoryStatePtr& operator=( const FSharedInventoryStatePtr& inSharedPtr )
	{
		SharedReferenceCount = inSharedPtr.SharedReferenceCount;
		ActorPtr = inSharedPtr.ActorPtr;
		return *this;
	}

	FORCEINLINE FSharedInventoryStatePtr& operator=( FSharedInventoryStatePtr&& inSharedPtr )
	{
		if( this != &inSharedPtr )
		{
			ActorPtr = inSharedPtr.ActorPtr;
			inSharedPtr.ActorPtr = nullptr;
			SharedReferenceCount = MoveTemp( inSharedPtr.SharedReferenceCount );
		}
		return *this;
	}

	FORCEINLINE FSharedInventoryStatePtr& operator=( SharedPointerInternals::FNullTag* )
	{
		Reset();
		return *this;
	}

	/**
	 * Use a custom serialize so we can start the reference counting on a loaded pointer.
	 */
	FORCEINLINE bool Serialize( FArchive& ar )
	{
		ar << *this;

		return !ar.IsError();
	}
	
	FORCEINLINE friend FArchive& operator<<( FArchive& ar, FSharedInventoryStatePtr& state )
	{
		ar << state.ActorPtr;

		if( ar.IsSaveGame() && ar.IsLoading() )
		{
			// Give the save session a chance to handle the loaded pointer.
			UFGSaveSession::SharedInventoryPtrLoaded( state );

			// Start reference counting.
			if( state.ActorPtr )
			{
				// This is safe as ActorPtr was set manually (no ref counting started).
				state = FSharedInventoryStatePtr( state.ActorPtr );
			}
		}

		return ar;
	}

	/**
	 * Use a custom net serialize to only allow replication from server to client and never the other way around.
	 */
	FORCEINLINE bool NetSerialize( FArchive& ar, class UPackageMap* map, bool& out_Success )
	{
		bool isServer = false;
		if( UPackageMapClient* client = Cast<UPackageMapClient>( map ) )
		{
			check( client->GetConnection() );
			check( client->GetConnection()->GetDriver() );
			isServer = client->GetConnection()->GetDriver()->IsServer();
		}
					
		if( ar.IsSaving() )
		{
			checkf( isServer, TEXT( "Sending a FSharedInventoryStatePtr from client, probably trying to send server a FInventoryStack, try sending a FItemAmount instead" ) );
			AActor* toSerialize = isServer ? ActorPtr : nullptr;
			ar << toSerialize;			
		}
		else
		{
			// Server should never receive a FSharedInventoryStatePtr
			checkf(!isServer, TEXT("Received a FSharedInventoryStatePtr, probably trying to send server a FInventoryStack, try sending a FItemAmount instead"));
			ar << ActorPtr;
		}

		out_Success = !ar.IsError();
		return true;
	}

	FORCEINLINE AActor* operator->() const
	{
		check( IsValid() );
		return Get/*Simulator*/();
	}

	/** @return true if pointer points to a valid actor; false if not valid or null. */
	FORCEINLINE bool IsValid() const
	{
		return ActorPtr && ActorPtr->IsValidLowLevel() && ::IsValid( ActorPtr );
	}

	/** @return the actor held by this pointer; nullptr if actor is null or invalid. */
	FORCEINLINE AActor* Get() const
	{
		if( IsValid() )
		{
			return ActorPtr;
		}

		return nullptr;
	}

	FORCEINLINE int32 GetSharedReferenceCount() const
	{
		return SharedReferenceCount.GetSharedReferenceCount();
	}

	/** Set the pointer to null and release the reference. */
	FORCEINLINE void Reset()
	{
		*this = NullState;
	}

	FORCEINLINE friend bool operator==( const FSharedInventoryStatePtr& a, const FSharedInventoryStatePtr& b )
	{
		return a.Get() == b.Get();
	}

	FORCEINLINE friend bool operator!=( const FSharedInventoryStatePtr& a, const FSharedInventoryStatePtr& b )
	{
		return a.Get() != b.Get();
	}

private:
	/**
	 * Custom reference counter with deleter.
	 */
	class TReferenceControllerWithNextFrameDeleter : public SharedPointerInternals::FReferenceControllerBase
	{
	public:
		FORCEINLINE explicit TReferenceControllerWithNextFrameDeleter( AActor* inActorPtr ) :
			ActorPtr( inActorPtr )
		{}

		FORCEINLINE virtual void DestroyObject() override
		{
			//[FreiholtzK:Mon/16-03-2020] Added support for removing objects in non game thread, E.g  parallelfor in buildable subsystem
			FSimpleDelegateGraphTask::CreateAndDispatchWhenReady
			(
				FSimpleDelegateGraphTask::FDelegate::CreateLambda( [ = ]()
				{
					if( !GExitPurge && ActorPtr.IsValid() && !ActorPtr->IsPendingKill() )
					{
						ActorPtr->SetActorHiddenInGame( true );
						ActorPtr->SetLifeSpan( 0.001f ); // Delete next frame.
					}
				} ),
				TStatId(), nullptr, ENamedThreads::GameThread
			);
		}

		// Non-copyable
		TReferenceControllerWithNextFrameDeleter( const TReferenceControllerWithNextFrameDeleter& ) = delete;
		TReferenceControllerWithNextFrameDeleter& operator=( const TReferenceControllerWithNextFrameDeleter& ) = delete;

	private:
		/** The actor associated with this reference counter.  */
		TWeakObjectPtr< AActor > ActorPtr;
	};

	FORCEINLINE SharedPointerInternals::FReferenceControllerBase* NewReferenceControllerWithNextFrameDeleter( AActor* inActorPtr )
	{
		return new TReferenceControllerWithNextFrameDeleter( inActorPtr );
	}
// MODDING EDIT
public: // VarToFString requires this
	/**
	 * Private constructor to create a pointer with reference counting enabled.
	 *
	 * Modders, please use FSharedInventoryStatePtr::MakeShared, using this might cause a runtime crash.
	 */
	FORCEINLINE FSharedInventoryStatePtr( AActor* actor ) :
		ActorPtr( actor ),
		SharedReferenceCount( NewReferenceControllerWithNextFrameDeleter( actor ) )
	{
	}

private:
	/** The actor we've shared ownership over. */
	UPROPERTY()
	class AActor* ActorPtr;

	/**
	 * Reference counter for this state pointer.
	 * this is only setup on the server and is completely ignored on clients and replication.
	 */
	SharedPointerInternals::FSharedReferencer< ESPMode::Fast > SharedReferenceCount;

public:
	FORCEINLINE ~FSharedInventoryStatePtr() = default;
};
FORCEINLINE FString VarToFString( FSharedInventoryStatePtr var ){ return FString::Printf( TEXT( "%s" ), *VarToFString(var.Get()) ); }

template<> struct TIsZeroConstructType<FSharedInventoryStatePtr> { enum { Value = true }; };

template<>
struct FACTORYGAME_API TStructOpsTypeTraits<FSharedInventoryStatePtr> : public TStructOpsTypeTraitsBase2<FSharedInventoryStatePtr>
{
	enum
	{
		WithNetSerializer = true,
		WithSerializer = true
	};

public:
	FORCEINLINE ~TStructOpsTypeTraits<FSharedInventoryStatePtr>() = default;
};
#pragma once

#include "FGObjectReference.h"
#include "FGSaveInterface.h"

/** All data needed by a object to be saved to disc */
struct FACTORYGAME_API FObjectBaseSaveHeader
{
	// Name of the class
	FString ClassName;
	// A Reference to the object
	FObjectReferenceDisc Reference;

	/** ctor */
	FObjectBaseSaveHeader(){}

	/** Reset all values to sensible defaults without deallocating them */
	void Reset()
	{
		Reference.Reset();
		ClassName.Reset();
	}

	/** Helper to find the level this actor/object resides in */
	FORCEINLINE ULevel* FindLevel( UWorld* world ) const
	{
		return Reference.FindLevel( world );
	}

	/** Helper to get object names */
	FORCEINLINE void ParseObjectName( FString& out_objName ) const
	{
		Reference.ParseObjectName( out_objName );
	}

	/** Set all data needed by the object to save it */
	void Set( UObject* obj )
	{
		Reference.Set( obj );
		ClassName = obj->GetClass()->GetPathName();
	}

	/** Save/load data from disc */
	friend FArchive& operator<<( FArchive& ar, FObjectBaseSaveHeader& header )
	{
		ar << header.ClassName << header.Reference;

		return ar;
	}

	FString ToString() const;
	UClass* ResolveClass() const;
};

struct FACTORYGAME_API FObjectSaveHeader
{
	/** Base data */
	FObjectBaseSaveHeader BaseHeader;

	// Pathname of our outer, can't be null
	FString OuterPathName;

	/** Reset all values to sensible defaults without deallocating them */
	void Reset()
	{
		BaseHeader.Reset();
		OuterPathName.Reset();
	}

	/** Set all data needed by the object to save it */
	void Set( UObject* obj )
	{
		BaseHeader.Set( obj );

		FObjectReferenceDisc::GetRelativePath( obj->GetOuter(), OuterPathName );
	}
	
	FString ToString() const;

	/** Save/load data from disc */
	friend FArchive& operator<<( FArchive& ar, FObjectSaveHeader& header )
	{
		ar << header.BaseHeader << header.OuterPathName;

		return ar;
	}
};

/** Header with all data needed to store the metadata of a actor */
struct FACTORYGAME_API FActorSaveHeader
{
	/** Reference and class */
	FObjectBaseSaveHeader ObjectHeader;
	// Transform of the actor
	FTransform3f Transform = FTransform3f::Identity;
	// If true, then transform is set and we need transform
	bool NeedTransform = false;
	// if true, then this actor was places on level, and hence, if it isn't found when loading, then it shouldn't be spawned
	bool WasPlacedInLevel = false;

	/** Reset values to default values */
	void Reset()
	{
		ObjectHeader.Reset();
		NeedTransform = false;
		WasPlacedInLevel = false;
	}

	/** Set a object before saving */
	bool Set( UObject* obj )
	{
		ObjectHeader.Set( obj );
		if( AActor* actor = Cast<AActor>( obj ) )
		{
			Transform = FTransform3f(actor->GetTransform());
			NeedTransform = IFGSaveInterface::Execute_NeedTransform( actor );
			WasPlacedInLevel = actor->HasAnyFlags( RF_WasLoaded );

			return true;
		}

		return false;
	}

	bool Set( UObject* obj, FTransform overrideTransform )
	{
		ObjectHeader.Set( obj );
		if( AActor* actor = Cast<AActor>( obj ) )
		{
			Transform = FTransform3f( overrideTransform );
			NeedTransform = IFGSaveInterface::Execute_NeedTransform( actor );
			WasPlacedInLevel = actor->HasAnyFlags( RF_WasLoaded );

			return true;
		}

		return false;
	}

	/** Helper to get object names */
	FORCEINLINE void ParseObjectName( FString& out_objName ) const
	{
		ObjectHeader.ParseObjectName( out_objName );
	}


	/** Save/load data */
	friend FArchive& operator<<( FArchive& ar, FActorSaveHeader& header )
	{
		// We always store transform, so that the need transform switch can be flicked anytime during development without breaking savegames
		ar << header.ObjectHeader << header.NeedTransform << header.Transform << header.WasPlacedInLevel;
	
		return ar;
	}
};
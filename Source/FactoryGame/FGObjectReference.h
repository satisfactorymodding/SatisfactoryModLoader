#pragma once
#include "Engine/Level.h"
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"

#include "Templates/TypeHash.h"

struct FObjectRedirect
{
	/**
	 * Creates a redirector
	 */
	FObjectRedirect( const FString& source, const FString& destination );

	/** Redirected string */
	FString Source;

	/** New Name for the redirector */
	FString Destination;
};

/** Level agnostic object reference */
struct FObjectReferenceDisc
{
	// Name of the level we reside in, if empty, PathName is a absolute path
	FString LevelName;
	// Pathname including sublevel name
	FString PathName;

	/** ctor */
	FObjectReferenceDisc();

	/** Setups reference from a object  */
	FObjectReferenceDisc( UObject* obj );

	/** If returning true, then this is a nullptr */
	bool IsNullptr() const;

	/** Reset all values to sensible defaults without deallocating them */
	void Reset();

	/** Resolve the object in the context of the specified world */
	UObject* Resolve( UWorld* world ) const;

	/**
	* Potentially redirect subobject, will call the same functions as Resolve, but if it fails,
	* then it will try to see if the object is redirected
	*
	* @param world - the world this object lives in
	* @param outerName - outer object for this actor
	* @param outer - returns the outer object for this object if found
	*/
	bool ResolveWithRedirect( UWorld* world, const FString& outerName, UObject*& out_object, UObject*& out_outer ) const;

	template<typename T>
	T* Resolve( UWorld* world ) const
	{
		return Cast<T>( Resolve( world ) );
	}

	/** Set the reference to a object */
	void Set( UObject* obj );

	/** Parse out the name of the object from the relative path */
	void ParseObjectName( FString& out_objName ) const;

	/** Parse out the name of the object from the relative path */
	void ParseObjectNameAndPath( FString& out_objPath, FString& out_objName ) const;

	/** Get the relative path between the level the object resides in */
	static void GetRelativePath( UObject* obj, FString& out_pathName );

	/** Find the level a object resides in */
	static ULevel* FindOuterLevel( UObject* obj );

	/** Find the level this actor/object resides in with redirector support */
	ULevel* FindLevel( UWorld* world ) const;

	/** Save/load data from disc */
	friend FArchive& operator<<( FArchive& ar, FObjectReferenceDisc& reference );

	/** Returns true if this instance is valid */
	bool Valid() const;

	/** For debug, prints Level::Path */
	FString ToString() const;

	/** @return true if this most probably is a class */
	bool IsProbablyClass() const{ return LevelName.Len() == 0 && PathName.EndsWith( TEXT("_C") ); }

	/** @return true if this references something in a level. */
	bool IsInLevel() const { return !LevelName.IsEmpty(); }

	/** Clear all redirects that has been done */
	static void ClearRedirects();

	/**
	 * Looks up a redirector for asset references
	 *
	 * @param oldName - a asset reference that we will try to lookup
	 * @param out_newRedirectedName - only valid if we return true
	 *
	 * @return true if we found a redirected name
	 */
	static bool FindRedirect( const FString& oldName, FString& out_newRedirectedName );

	/** For comparisons of references */
	FORCEINLINE bool operator ==( const FObjectReferenceDisc& other ) const { return LevelName == other.LevelName && PathName == other.PathName; }

private:
	friend UObject* InternalResolve( const FObjectReferenceDisc& reference, UWorld* world, UObject* searchOuter, UObject* outer );

	/**
	 * Add a redirector from a object name to a new object name
	 */
	static void AddRedirector( const FString& source, const FString& destination );

	/**
	 * Redirects done during this latest session
	 */
	static TArray< FObjectRedirect > Redirects;

	/**
	* Does the internal level finding logic
	*/
	ULevel* InternalFindLevel( UWorld* world, const FString& levelName ) const;
};

/**
 * Allow FObjectReference to be placed in TSet
 */
inline uint32 GetTypeHash( const FObjectReferenceDisc& r )
{
	return HashCombine( GetTypeHash( r.LevelName ), GetTypeHash( r.PathName ) );
}

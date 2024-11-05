#pragma once

#include "Serialization/ArchiveProxy.h"

/**
 * Serializes the "TOC" of a object, that is it's name, class and path, transform and other relevant properties that is need for a object to be spawned.
 * During load, it spawns the object from this data.
 * As it's a FArchiveProxy, this object doesn't have any own data to work with, but will work with the passed in data in it's constructor
 */
class FACTORYGAME_API FArchiveObjectTOCProxy : public FArchiveProxy
{
public:
	FArchiveObjectTOCProxy( FArchive& inInnerArchive, class UWorld* world );

	/** Found a new object, save metadata about it if saving, spawn or find the object if load */
	virtual FArchive& operator<<( class UObject*& Res ) override;
	virtual FArchive& operator<<( struct FObjectPtr& Value ) override;

private:
	/** World to spawn new objects in if loading */
	class UWorld* mWorld;

};


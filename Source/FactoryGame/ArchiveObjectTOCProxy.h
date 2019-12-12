#pragma once
#include "Engine/World.h"
#include "UnrealString.h"

#include "Serialization/ArchiveProxy.h"
#include "EngineGlobals.h"
#include "Engine.h"

/**
 * First step in the two step rocket. With this class we go through all objects we want to save/load and serialize their name, class and path                                                                    
 */
class FArchiveObjectTOCProxy : public FArchiveProxy
{
public:
	/** ctor */
	FArchiveObjectTOCProxy( FArchive& inInnerArchive, class UWorld* world );

	/** Found a new object, save metadata about it if saving, spawn or find the object if load */
	virtual FArchive& operator<<( class UObject*& Res ) override;
private:
	/** World to spawn new objects in if loading */
	class UWorld* mWorld;

	/** Keep track of the names of objects, so we can find them faster */
	TMap< FString, UObject* > mObjectNames;
};


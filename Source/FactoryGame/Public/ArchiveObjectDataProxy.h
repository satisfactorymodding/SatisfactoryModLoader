#pragma once
#include "Engine/World.h"

#include "Serialization/ArchiveProxy.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "ObjectWriterFName.h"
#include "ObjectReaderFName.h"

/**
 * This class serializes the bulk data of the save objects.
 *
 * As it's a FArchiveProxy, this object doesn't have any own data to work with, but will work with the passed in data in it's constructor
 */
class FACTORYGAME_API FArchiveObjectDataProxy : public FArchiveProxy
{
public:
	/** Ctor */
	FArchiveObjectDataProxy( FArchive& inInnerArchive, class UWorld* world );

	/** Write down reference names */
	FArchive& operator<<( class UObject*& Res ) override;
private:
	class UWorld* mWorld;

public:
	FORCEINLINE ~FArchiveObjectDataProxy() = default;
};

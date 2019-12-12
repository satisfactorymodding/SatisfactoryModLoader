#pragma once
#include "Engine/World.h"

#include "Serialization/ArchiveProxy.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "ObjectWriterFName.h"
#include "ObjectReaderFName.h"

/**
 * This class transplants the byte data
 */
class FArchiveObjectDataProxy : public FArchiveProxy
{
public:
	/** Ctor */
	FArchiveObjectDataProxy( FArchive& inInnerArchive, class UWorld* world );

	/** Write down reference names */
	FArchive& operator<<( class UObject*& Res ) override;
private:
	class UWorld* mWorld;
};

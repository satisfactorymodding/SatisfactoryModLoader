#pragma once
#include "Array.h"

#include "Serialization/ArchiveUObject.h"
#include "EngineGlobals.h"
#include "Engine.h"



/** 
 * Our modded version of object writer. When this is used we serialize the objects name and path
 */
class FObjectWriterFName : public FObjectWriter
{
public:
	FObjectWriterFName( UObject* Obj, TArray<uint8>& InBytes, int32 saveVersion );

	virtual FObjectWriterFName& operator<<( class UObject*& Res ) override;
	virtual FArchive& operator<<( class FName& N ) override;

};
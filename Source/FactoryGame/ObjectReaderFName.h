#pragma once
#include "Engine/World.h"
#include "Array.h"

#include "Serialization/ArchiveUObject.h"
#include "EngineGlobals.h"
#include "Engine.h"

/**
 * Our modded version of object reader. When this is used we have already spawned/created dummy object. We then use this class 
 * to transplant the loaded data into those objects                                                                 
 **/
class FObjectReaderFName : public FObjectReader
{
public:
	FObjectReaderFName( UObject* Obj, TArray<uint8>& InBytes, int32 saveVersion, class UWorld* world );

	FObjectReaderFName& operator<<( class UObject*& Res );
	virtual FArchive& operator<<( class FName& N ) override;
private:
	class UWorld* mWorld;
};

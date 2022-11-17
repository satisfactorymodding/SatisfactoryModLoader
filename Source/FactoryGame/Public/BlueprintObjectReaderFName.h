// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Serialization/ArchiveUObject.h"
#include "EngineGlobals.h"
#include "Engine.h"

/**
 * Our modded version of object reader but modified for blueprints. When this is used we have already spawned/created dummy object. We then use this class 
 * to transplant the loaded data into those objects                                                                 
 **/
class FBlueprintObjectReaderFName : public FObjectReader
{
public:
	FBlueprintObjectReaderFName( UObject* Obj, TArray<uint8>& InBytes, int32 saveVersion, class UWorld* world );

	FBlueprintObjectReaderFName& operator<<( class UObject*& Res );
	virtual FArchive& operator<<( class FName& N ) override;
private:
	class UWorld* mWorld;

};

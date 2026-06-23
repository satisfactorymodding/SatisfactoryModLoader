// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Serialization/ObjectReader.h"

struct FSaveObjectVersionData;
class UWorld;

/**
 * Our modded version of object reader but modified for blueprints. When this is used we have already spawned/created dummy object. We then use this class 
 * to transplant the loaded data into those objects                                                                 
 **/
class FBlueprintObjectReaderFName : public FObjectReader
{
public:
	FBlueprintObjectReaderFName( UObject* Obj, UWorld* World, TArray<uint8>& InBytes, const FArchive& InnerArchive );

	FBlueprintObjectReaderFName& operator<<( class UObject*& Res );
	virtual FArchive& operator<<( class FName& N ) override;
	FArchive& operator<<( FObjectPtr& Res );
private:
	UWorld* mWorld;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Serialization/ObjectWriter.h"

/** 
 * Our modded version of object writer. When this is used we serialize the objects name and path
 */
class FObjectWriterFName : public FObjectWriter
{
	FCustomVersionContainer& mCustomVersionContainer;
public:
	FObjectWriterFName( UObject* Obj, TArray<uint8>& InBytes, FCustomVersionContainer& customVersionContainer );

	virtual const FCustomVersionContainer& GetCustomVersions() const;
	virtual FArchive& operator<<( class UObject*& Res ) override;
	virtual FArchive& operator<<( FObjectPtr& Res ) override;
	virtual FArchive& operator<<( class FName& N ) override;
};
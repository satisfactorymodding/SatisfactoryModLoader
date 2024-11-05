// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Serialization/ObjectReader.h"

struct FObjectReferenceDisc;
/**
 * Our modded version of object reader. When this is used we have already spawned/created dummy object. We then use this class 
 * to transplant the loaded data into those objects                                                                 
 **/
class FACTORYGAME_API FObjectReaderFName : public FObjectReader
{
public:
	FObjectReaderFName( UObject* Obj, TArray<uint8>& InBytes, int32 saveVersion, class UWorld* world, FPackageFileVersion version, bool migrateObjectRefsToPersistent );

	virtual FArchive& operator<<( class UObject*& Res ) override;
	virtual FArchive& operator<<( FObjectPtr& Res ) override;
	virtual FArchive& operator<<( class FName& N ) override;

	/** The behavior of this functional is identical to operator<<(UObject*&) for this reader from the archive layout perspective, but this function will not try to load the resulting object, just return the reference to it */
	static void SerializeObjectWithoutLoading( FArchive& Ar, FSoftObjectPath& OutObjectPath );
private:
	/** Resolves object using the active redirect. Not very fast */
	UObject* ResolveObjectWithRedirect( FObjectReferenceDisc& ObjectReference );
	
	class UWorld* mWorld;
	bool mMigrateObjectRefsToPersistentLevel;
};

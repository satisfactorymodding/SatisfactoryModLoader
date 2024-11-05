#pragma once

#include "Serialization/ArchiveProxy.h"

/**
 * This class serializes the bulk data of the save objects.
 *
 * As it's a FArchiveProxy, this object doesn't have any own data to work with, but will work with the passed in data in it's constructor
 */
class FACTORYGAME_API FArchiveObjectDataProxy : public FArchiveProxy
{
public:
	/** Ctor */
	FArchiveObjectDataProxy( FArchive& inInnerArchive, class UWorld* world, bool objectRefsNeedMigration );

	/** Write down reference names */
	virtual FArchive& operator<<( class UObject*& Res ) override;
	virtual FArchive& operator<<( struct FObjectPtr& Value ) override;

private:
	class UWorld* mWorld;
	bool mObjectRefsNeedMigration;
};

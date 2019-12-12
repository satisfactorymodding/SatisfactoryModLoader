#pragma once

#include "Array.h"
#include "Serialization/Archive.h"

class FSaveCollectorArchive : public FArchive
{
	/** Handles serialization of UObject references */
	FArchive& operator<<( class UObject*& Obj );

	/** The set of objects encountered when traversing the object graph */
	TArray<class UObject*>& mObjectsToSave = *(new TArray<class UObject*>); // MODDING EDIT: Constructor says it should be initialized
public:
	/**
	 * Sets up the array that we want to add objects to
	 **/
	FSaveCollectorArchive( TArray<class UObject*>& toFill );
	
	/** Generates objects to the member that was passed in when class was setup */
	void GenerateSaveObjects( const TArray<class UObject*>& rootSet );
};
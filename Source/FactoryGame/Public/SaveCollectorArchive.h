// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Serialization/Archive.h"

/**
* Archive that gathers Actors/UObjects that implement the IFGSaveInterface. When GenerateSaveObjects is called Serialize will be called on passed in UObjects
* If the objects discovered implement the save interface it will be added to the ObjectsToSave list which will later be sorted to write out in order of dependency.
*/
class FSaveCollectorArchive : public FArchive
{
	/** Handles serialization of UObject references */
	FArchive& operator<<( class UObject*& Obj );

	/** The set of objects encountered when traversing the object graph */
	TArray<class UObject*>& mObjectsToSave;
public:
	/**
	 * Sets up the array that we want to add objects to
	 **/
	FSaveCollectorArchive( TArray<class UObject*>& toFill );
	
	/** Generates objects to the member that was passed in when class was setup */
	void GenerateSaveObjects( const TArray<class UObject*>& rootSet );
};
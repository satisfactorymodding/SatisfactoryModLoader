// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Serialization/Archive.h"

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
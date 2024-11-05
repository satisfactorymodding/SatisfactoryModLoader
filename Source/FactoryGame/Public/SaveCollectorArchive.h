// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "UObject/Object.h"

/**
* Reference collector that gathers Actors/UObjects that implement the IFGSaveInterface. When GenerateSaveObjects is called Serialize will be called on passed in UObjects
* If the objects discovered implement the save interface it will be added to the ObjectsToSave list which will later be sorted to write out in order of dependency.
*/
class FFastSaveReferenceCollector : public FReferenceCollector
{
	TArray<UObject*>& mObjectsToSave;
	TSet<UObject*> mAllObjectsEncountered;
	TSet<ULevel*> mAllowedLevels;
public:
	/**
	 * Sets up the array that we want to add objects to
	 **/
	FFastSaveReferenceCollector( UWorld* world, ULevel* level, TArray<class UObject*>& toFill );

	void SetBlacklistedClasses( TArray< TSubclassOf< UObject > >& blacklist )
	{
		mBlacklistedClasses.Append( blacklist );
	}
	
	/** Generates objects to the member that was passed in when class was setup */
	void GenerateSaveObjects( const TArray<class UObject*>& rootSet );
	
	virtual bool IsIgnoringTransient() const override { return true; }
	virtual bool IsIgnoringArchetypeRef() const override { return true; }
	virtual void HandleObjectReference(UObject*& InObject, const UObject* InReferencingObject, const FProperty* InReferencingProperty) override;
public:
	/** When generating saves objects ignore objects of these classes. This is for Blueprint serialization */
	TArray< TSubclassOf< UObject > > mBlacklistedClasses;
};

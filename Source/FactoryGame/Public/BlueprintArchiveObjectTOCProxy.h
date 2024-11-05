#pragma once

#include "Serialization/ArchiveProxy.h"

/**
 * Blueprint Implementation for the "TOC" of a object, that is it's name, class and path, transform and other relevant properties that is need for a object to be spawned.
 * During load, it spawns the object from this data.
 * This version of the TOC proxy also handles custom "local" redirectors for redirecting newly created objects since the names will not match
 * when creating blueprinted versions
 */
class FACTORYGAME_API FBlueprintArchiveObjectTOCProxy : public FArchiveProxy
{
public:
	FBlueprintArchiveObjectTOCProxy( FArchive& inInnerArchive, class UWorld* world, FTransform newOrigin );

	/** Found a new object, save metadata about it if saving, spawn or find the object if load */
	virtual FArchive& operator<<( class UObject*& Res ) override;

	void SetBuildablesBlueprintDesigner( class AFGBuildableBlueprintDesigner* designer) { mDesigner = designer; }
	void SetSuppressSaveWarnings( const bool suppress ) { mSuppressSaveWarnings = suppress; }
	
private:
	/** World to spawn new objects in if loading */
	class UWorld* mWorld;

	/** Keep track of the names of objects, so we can find them faster */
	TMap< FString, UObject* > mObjectNames;
	
	/** Rebase transforms to this origin. Useful for blueprinted Actors */
	FTransform mNewOrigin;

	/** Should newly spawned buildables belong to a blueprint designer */
	class AFGBuildableBlueprintDesigner* mDesigner;

	/** When loading to blueprint world save warnings / errors are expected and that is fine */
	bool mSuppressSaveWarnings = false;
};


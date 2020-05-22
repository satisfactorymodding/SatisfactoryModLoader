#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"
// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#include "FactoryGame.h"
#include "FGFactoryMaterialInstanceManager.generated.h"


/**
*	Utility class to hold a DynamicMaterialInstance for each possible color for every different colorable material instance on constructed buildables
*	This should be utilized to share a single DynamicMaterialInstance between skeletal and instance meshes where applicable
*	Material instances are identified by their name, which is in turn used as the key mapping each material by name to one instance of this class.
*/
UCLASS()
class FACTORYGAME_API UFGFactoryMaterialInstanceManager : public UObject
{
	GENERATED_BODY()

public:
	// Constructor, always set the size to match the total number of colors possible
	UFGFactoryMaterialInstanceManager();

	/**
	 * Will initialize list with correct instance colors for a given material interface
	 * @param materialInterface -Material interface to copy for instance creation. Can already be UMaterialInstanceDynamic
	 * @param lookupName -	Often the name of the material interface, however when sharing is disabled on a buildable or component this lookup can also be prepended with the lookupPrefix
	 * @param lookupPrefix -	Prefix to prepend to the start of additions to the material lookup table. Will be added to the front of the Default Material Instance Dynamic names so that future lookups 
	 *							from buildables can send in their Unique lookup name and have it match the newly created instances.
	 * @param worldContext - Used to get the buildable subsystem and cache it since it is persistent for an entire game session
	 * @param canBeColored - Optional, defaults to True. This property is precomputed before instantiating new Manager Instances so it should be passed in if needed.
	*/
	void Init( UMaterialInterface* materialInterface, FString& lookupName, FString& lookupPrefix, UWorld* worldContext, bool canBeColored = true, class AFGBuildable* forBuildable = nullptr );

	/** Update the colors on all material instances */
	void RefreshMaterialColors();

	/** Update the colors on a material instance for a given index (call when the user changes the Buildable Color array */
	void RefreshMaterialColorForIndex( int32 index );

	/** Set Vector Parameter on all instances */
	void SetVectorParameterOnAllInstances( FName paramName, FVector value );

	/** Get the lookup name that identifies this manager in the buildable subsystem */
	const FString& GetInitialLookupString() const { return mInitialLookupString; }

	/** Get whether this manager is shared across multiple buildables */
	bool GetIsSharedInstance() const { return mIsShared; }

	/** Returns the material instance for a given color index */
	UMaterialInstanceDynamic* GetMaterialForIndex( int32 index );

	void GetMaterialInstanceNames( TArray<FString>& out_instanceNames );
	TArray<FString>& GetMaterialInstanceNames();

private:
	void AppendPrefixToInstanceName( const FString& prefix, const FString& baseName, FString& out_PrefixedName );

private:
	// The string that is the identifier for this manager in the BuildableSubsystem
	FString mInitialLookupString;

	// Initial Material Interface used to Init this manager
	UPROPERTY()
	UMaterialInterface* mInitializingFromInterface;

	// All materials are the same but their params are set to match the colors specified by the color gun
	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> mMaterialInstances;

	UPROPERTY()
	TArray<FString> mInstanceNames;

	// Hold a reference to the worlds BuildableSubsystem so that we dont have to do look ups / pass world context into function calls
	// Should be assigned in constructors where possible. NOT a UPROPERTY because we don't own this object
	class AFGBuildableSubsystem* mCachedBuildSystem;

	/** Is this a colorable material instance? */
	bool mCanBeColored;

	/** Is this manager shared across multiple buildables? */
	bool mIsShared;


public:
	FORCEINLINE ~UFGFactoryMaterialInstanceManager() = default;
};
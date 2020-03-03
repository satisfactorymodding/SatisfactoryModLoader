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

	// Preferred Constructor, will initialize list with correct instance colors for a given material interface
	void Init( UMaterialInterface* materialInterface, UWorld* worldContext, bool canBeColored = true );

	/** Update the colors on all material instances */
	void RefreshMaterialColors();

	/** Update the colors on a material instance for a given index (call when the user changes the Buildable Color array */
	void RefreshMaterialColorForIndex( int32 index );

	/** Set Vector Parameter on all instances */
	void SetVectorParameterOnAllInstances( FName paramName, FVector value );

	/** Returns the material instance for a given color index */
	UMaterialInstanceDynamic* GetMaterialForIndex( int32 index );

	TArray<FString>& GetMaterialInstanceNames();

private:
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


public:
	FORCEINLINE ~UFGFactoryMaterialInstanceManager() = default;
};
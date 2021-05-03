// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildingTagInterface.generated.h"

/**
* For blueprint support of the interface, we will never add anything to it, just use it to
* have a UCLASS to be able to access
*/
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGBuildingTagInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
* @brief Interface for buildings that may or may not have a tag
*/
class FACTORYGAME_API IFGBuildingTagInterface
{
	GENERATED_IINTERFACE_BODY()

	/**
	 * @returns true if the building tag is currently enabled on this object, false otherwise.
	 */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Building Tag" )
	bool HasBuildingTag() const;

	/**
	 * Set to true to enable building tag for this object, false to disable it.
	 */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Building Tag" )
	void SetHasBuildingTag( bool hasBuildingTag );

	/**
	 * @returns the building tag for this object. Mainly used to identify a building object to players.
	 */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Building Tag" )
	FString GetBuildingTag() const;

	/**
	 * Store a building tag for this object, mainly used to identify it to players.
	 */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Building Tag" )
	void SetBuildingTag( const FString& buildingTag );

};

inline UFGBuildingTagInterface::UFGBuildingTagInterface( class FObjectInitializer const& objectInitializer )
	: Super( objectInitializer )
{
}
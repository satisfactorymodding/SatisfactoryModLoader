// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGColorInterface.generated.h"

/**
 * Interface for actors that should be colorable with the colorgun.
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGColorInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()	
};

class FACTORYGAME_API IFGColorInterface
{
	GENERATED_IINTERFACE_BODY()

	/** Sets the color slot for the buildable */
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Color" )
	void SetColorSlot( uint8 index );

	/** Returns the primary color of this building */
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Color" )
	FLinearColor GetPrimaryColor();

	/** Returns the primary color of this building */
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Color" )
	FLinearColor GetSecondaryColor();

	/** Returns the color slot index of this building */
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Color" )
	uint8 GetColorSlot();

	/** Returns wherther the building can be colored right now or not */
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Color")
	bool GetCanBeColored();

	/**
	* Called on by the interface if we are looking at something that's useable
	*/
	UFUNCTION( BlueprintNativeEvent, Category = "Use" )
	void StartIsAimedAtForColor( AFGCharacterPlayer* byCharacter );

	/**
	* Called when we stop looking at the item
	*/
	UFUNCTION( BlueprintNativeEvent, Category = "Use" )
	void StopIsAimedAtForColor( AFGCharacterPlayer* byCharacter );
};
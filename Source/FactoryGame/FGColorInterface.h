#pragma once
#include "UObject/Interface.h"
#include "UObject/Class.h"

#include "FGColorInterface.generated.h"

/**
* For blueprint support of the interface, we will never add anything to it, just use it to
* have a UCLASS to be able to access
*/
UINTERFACE( Blueprintable )
class UFGColorInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGColorInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 
};

/**
*
*/
class IFGColorInterface
{
	GENERATED_IINTERFACE_BODY()

	/** Sets the color slot for the buildable */
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Color" )
	void SetColorSlot( uint8 index );

	/** Sets the primary color for the buildable */
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Color" )
	void SetPrimaryColor( FLinearColor newColor );

	/** Sets the secondary color for the buildable */
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Color" )
	void SetSecondaryColor( FLinearColor newColor );

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
// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGFactoryColoringTypes.h"
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

	/** Set the active/saved customization. This in turn should call ApplyCustomizationData. They are split to allow for previewing without fully setting */
	virtual void SetCustomizationData_Native( const FFactoryCustomizationData& customizationData ) = 0;
	
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Factory Customization" )
	void SetCustomizationData( const FFactoryCustomizationData& customizationData );

	/** Get Customization data for implementing actor */
	virtual FFactoryCustomizationData& GetCustomizationData_Native() = 0;

	/** Quick getter for returning the current active skin */
	virtual TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Native() = 0;

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Factory Customization" )
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin();

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Factory Customization" )
	FFactoryCustomizationData GetCustomizationData();

	/** This function should be used to actually apply the custom/pic data to meshes on the implementing object */
	virtual void ApplyCustomizationData_Native( const FFactoryCustomizationData& customizationData ) = 0;

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Factory Customization" )
	void ApplyCustomizationData( const FFactoryCustomizationData& customizationData );

	/** Gets the buildable/vehicle skin data */
	virtual TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Native() = 0;

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Factory Customization" )
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass();

	/** Returns wherther the building can be colored right now or not */
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Customization")
	bool GetCanBeColored();

	/** For special case buildables, do we want to defer how colors are applied to the buildable itself? */
	virtual bool IsColorApplicationDeferred() = 0;

	/** For Deferred color application, can the current customization be applied at a location */
	virtual bool CanApplyDeferredColorToBuildable( FVector hitLocation, FVector hitNormal, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController ) = 0;

	/** Apply a Color swatch to a buildable that has specified to use defered apply */
	virtual void ApplyDeferredColorToBuildable( FVector hitLocation, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController ) = 0;

	/** For special cases where actors are in chanrge of their own color application, can */

	/**
	* Called on by the interface if we are looking at something that's useable
	*/
	UFUNCTION( BlueprintNativeEvent, Category = "Use" )
	void StartIsAimedAtForColor( AFGCharacterPlayer* byCharacter, bool isValid = true );

	/**
	* Called when we stop looking at the item
	*/
	UFUNCTION( BlueprintNativeEvent, Category = "Use" )
	void StopIsAimedAtForColor( AFGCharacterPlayer* byCharacter );
};
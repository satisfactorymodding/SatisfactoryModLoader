// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGRecipe.h"
#include "ItemAmount.h"
#include "FGEventSubsystem.h"
#include "FGCustomizationRecipe.generated.h"


/**
 * Unlock recipe for a customization Descriptor
 */
UCLASS( Blueprintable, Meta=(AutoJSON=true) )
class FACTORYGAME_API UFGCustomizationRecipe : public UFGRecipe
{
	GENERATED_BODY()
public:
	UFGCustomizationRecipe();

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid( TArray< FText >& ValidationErrors ) override;
#endif

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Customization" )
	static TSubclassOf< class UFGFactoryCustomizationDescriptor > GetCustomizationDescriptor( TSubclassOf< UFGCustomizationRecipe > inClass );

	FORCEINLINE TSubclassOf< class UFGFactoryCustomizationDescriptor > GetCustomizationDesc() { return mCustomizationDesc; }

	/** Returns the menu property for the underlying customization descriptor, lower is earlier */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Customization" )
	static float GetCustomizationDescMenuPriority( TSubclassOf< UFGCustomizationRecipe > inClass );
	
protected:
	UPROPERTY( EditDefaultsOnly, Category = "Customization" )
	TSubclassOf< class UFGFactoryCustomizationDescriptor > mCustomizationDesc;

};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "FGScannableDetails.h"
#include "Engine/DeveloperSettings.h"
#include "FGScannableSettings.generated.h"


/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Scannable Settings" ) )
class FACTORYGAME_API UFGScannableSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGScannableSettings* Get() { return GetDefault<UFGScannableSettings>(); };

	/** Returns all scannable objects/items the given scanner object are allowed to scan for at the start of the game */
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	TArray<TSubclassOf<class UFGItemDescriptor>> GetStartingScannableObjects( const UObject* scannerObject ) const;
	
	/** We might want to solve this in a different way maybe with an interface but this works for now */
	UPROPERTY( EditAnywhere, config, Category = "Hostile Creatures", meta = ( ToolTip = "This is the additional hostile creature classes that doesn't inherit from FGCreature. This is so we are able to scan for them" ) )
	TArray< TSoftClassPtr< AActor > > mAdditionalHostileCreatureClasses;

	// Objects of this class or derived from this class will be allowed to scan for the item descriptors in the value of that pair.
	UPROPERTY( EditAnywhere, config, Category = "Scannable Objects", meta = ( ToolTip = "These are the scannable objects that should be unlocked from the start of the game" ) )
	TMap< TSoftClassPtr< UObject>, FItemDescriptors > mStartingScannableObjects;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Resources/FGItemDescriptor.h"
#include "FGBuildDescriptor.generated.h"

/**
 * Descriptor for things that can be built in the BuildGun.
 */
UCLASS( Abstract )
class FACTORYGAME_API UFGBuildDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	UFGBuildDescriptor();

	/** Get the category for this building descriptor. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Build" )
	static TSubclassOf< class UFGBuildCategory > GetBuildCategory( TSubclassOf< UFGBuildDescriptor > inClass );

	/** The order we want stuff in the build menu, lower is earlier */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Build" )
	static float GetBuildMenuPriority( TSubclassOf< UFGBuildDescriptor > inClass );

	/** The order we want stuff in the build menu, lower is earlier */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Build" )
	static UClass* GetHologramClass( TSubclassOf< UFGBuildDescriptor > inClass );

	/** Get the build actor class for this building descriptor. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Building" )
	static TSubclassOf< AActor > GetBuildClass( TSubclassOf< UFGBuildDescriptor > inClass );

protected:
	virtual TSubclassOf< class AFGHologram > GetHologramClassInternal() const;
	virtual TSubclassOf< AActor > GetBuildClassInternal() const;
};

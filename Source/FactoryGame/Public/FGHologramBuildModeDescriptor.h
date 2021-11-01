// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGHologramBuildModeDescriptor.generated.h"

/**
 * Used to define a Build Mode for holograms. Which changes how the hologram behaves.
 */
UCLASS(Blueprintable, Abstract,HideCategories=(Icon, Preview),meta=(AutoJSON=true))
class FACTORYGAME_API UFGHologramBuildModeDescriptor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintPure, Category = "BuildMode" )
	const FText& GetDisplayNameInternal() const { return mDisplayName; }

	UFUNCTION( BlueprintPure, Category = "BuildMode" )
	static FText GetDisplayName( TSubclassOf<UFGHologramBuildModeDescriptor> inClass );

protected:
	UPROPERTY( EditDefaultsOnly )
	FText mDisplayName;
};

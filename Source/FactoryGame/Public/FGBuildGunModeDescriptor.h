// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGBuildGunModeDescriptor.generated.h"

/**
 * Base class used to define different modes for the build gun.
 */
UCLASS( Blueprintable, Abstract,HideCategories=(Icon, Preview),meta=(AutoJSON=true) )
class FACTORYGAME_API UFGBuildGunModeDescriptor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintPure, Category = "BuildGunMode" )
	const FText& GetDisplayNameInternal() const { return mDisplayName; }

	UFUNCTION( BlueprintPure, Category = "BuildGunMode" )
	static FText GetDisplayName( TSubclassOf< UFGBuildGunModeDescriptor > inClass );

protected:
	UPROPERTY( EditDefaultsOnly )
	FText mDisplayName;
};

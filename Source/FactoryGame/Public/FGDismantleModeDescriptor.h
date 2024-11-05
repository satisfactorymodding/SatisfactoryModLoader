// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildGunModeDescriptor.h"
#include "FGDismantleModeDescriptor.generated.h"

/**
 * Used to define a dismantle mode for the buildgun.
 */
UCLASS()
class FACTORYGAME_API UFGDismantleModeDescriptor : public UFGBuildGunModeDescriptor
{
	GENERATED_BODY()

public:
	UFGDismantleModeDescriptor();

	UFUNCTION( BlueprintPure, Category = "Dismantle" )
	FORCEINLINE int32 GetMultiDismantleLimit() const { return mMultiDismantleLimit; }

private:
	/** When using this dismantle mode, this is the limit of actors we can dismantle at once with the mass dismantle feature. <= 0 to disable. */
	UPROPERTY( EditDefaultsOnly, Category = "Dismantle" )
	int32 mMultiDismantleLimit;
};

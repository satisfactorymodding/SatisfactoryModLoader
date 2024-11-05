// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGUnlockCustomization.generated.h"

class UAddOnEntitlement;
class UFGPlayerCustomizationDesc;
/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGUnlockCustomization : public UFGUnlock
{
	GENERATED_BODY()
public:
	// Begin FGUnlock interface
	virtual void Apply(AFGUnlockSubsystem* unlockSubssytem) override;
	// End FGUnlock interface

	FORCEINLINE const TArray< TSubclassOf< UFGPlayerCustomizationDesc > >& GetCustomizationDescriptors() const { return mCustomizationUnlocks; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization")
	TArray< TSubclassOf< UFGPlayerCustomizationDesc > > mCustomizationUnlocks;
};

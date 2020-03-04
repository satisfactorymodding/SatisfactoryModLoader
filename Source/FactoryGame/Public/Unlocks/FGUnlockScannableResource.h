// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGUnlockScannableResource.generated.h"

/**
 * Unlocks scanning of the specified resources
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockScannableResource : public UFGUnlock
{
	GENERATED_BODY()

public:
	// Begin FGUnlock interface
	virtual void Apply( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface

#if WITH_EDITORONLY_DATA
	void Init( TArray< TSubclassOf< class UFGResourceDescriptor > > resources ) { mResourcesToAddToScanner = resources; }
#endif

	UFUNCTION( BlueprintPure, Category=Unlocks )
	FORCEINLINE TArray< TSubclassOf< class UFGResourceDescriptor > > GetResourcesToAddToScanner() const { return mResourcesToAddToScanner; }

protected:
	/**  These are the resources that are scannable after this unlock */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf< class UFGResourceDescriptor > > mResourcesToAddToScanner;


public:
	FORCEINLINE ~UFGUnlockScannableResource() = default;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Unlocks/FGUnlock.h"
#include "FGCentralStorageUnlock.generated.h"

/**
 * Increases the limit for how many items we can store in the central storage
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockCentralStorageItemLimit : public UFGUnlock
{
	GENERATED_BODY()

	virtual void Apply( class AFGUnlockSubsystem* unlockSubsystem ) override;

	UFUNCTION( BlueprintPure, Category=Unlocks )
	FORCEINLINE int32 GetItemStackLimitIncrease() const { return mItemStackLimitIncrease; }

protected:
	/** Determines how many extra item stacks we can store in the central storage */
	UPROPERTY( EditDefaultsOnly )
	int32 mItemStackLimitIncrease;
	
};

/**
 * Increases how fast we can upload items to the the central storage
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockCentralStorageUploadSpeed : public UFGUnlock
{
	GENERATED_BODY()

	virtual void Apply( class AFGUnlockSubsystem* unlockSubsystem ) override;

	UFUNCTION( BlueprintPure, Category=Unlocks )
	FORCEINLINE float GetUploadSpeedPercentageDecrease() const { return mUploadSpeedPercentageDecrease; }

protected:
	/** Determines how much faster we can upload items to the the central storage
	 *	We will decrease UFGCentralStorageSettings::mDefaultTimeToUpload with this percentage
	 */
	UPROPERTY( EditDefaultsOnly, meta=( Units="Percent" ) )
	float mUploadSpeedPercentageDecrease;
	
};

/**
 * Increases how many upload slots the player will have where they can queue up uploads for central storage
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockCentralStorageUploadSlots : public UFGUnlock
{
	GENERATED_BODY()

	virtual void Apply( class AFGUnlockSubsystem* unlockSubsystem ) override;

	UFUNCTION( BlueprintPure, Category=Unlocks )
	int32 GetNumUploadSlotsToUnlock() const { return mNumSlotsToUnlock; }

protected:
	/** Number of upload slots this unlock adds to the players upload inventory */
	UPROPERTY( EditDefaultsOnly )
	int32 mNumSlotsToUnlock;
	
};
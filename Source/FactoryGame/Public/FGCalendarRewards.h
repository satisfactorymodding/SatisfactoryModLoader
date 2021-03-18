// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/NoExportTypes.h"
#include "ItemAmount.h"
#include "FGCalendarRewards.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGCalendarRewards : public UObject
{
	GENERATED_BODY()
	
public:
	// Begin UObject Interface
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(TArray<FText>& ValidationErrors) override;
#endif
	// End UObject Interface
	
    static TArray< FItemAmount > GetSlotRewards( TSubclassOf< UFGCalendarRewards > inClass );

	static TArray< FItemAmount > GetRandomRewards( TSubclassOf< UFGCalendarRewards > inClass );

protected:
	/** The rewards for the slots in the calendar. If a slot is left empty it will grab a random reward from the Random Rewards.  */
	UPROPERTY( EditDefaultsOnly, Category = "Calendar" )
	TArray< FItemAmount > mSlotRewards;

	/** The random rewards for a calendar. Used when no reward is available for a slot in the Slot Rewards*/
	UPROPERTY( EditDefaultsOnly, Category = "Calendar" )
	TArray< FItemAmount > mRandomRewards;
};

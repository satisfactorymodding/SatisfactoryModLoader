// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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
	
		
	static TArray< class UFGUnlock* > GetSlotUnlocks( TSubclassOf< UFGCalendarRewards > inClass );
	static TArray< class UFGUnlock* > GetRandomUnlocks( TSubclassOf< UFGCalendarRewards > inClass );

	static class UFGUnlock* GetSlotUnlock( TSubclassOf< UFGCalendarRewards > inClass, int32 index );
	static class UFGUnlock* GetRandomUnlock( TSubclassOf< UFGCalendarRewards > inClass, int32 index );

protected:

	/** The rewards for the slots in the calendar. If a slot is left empty it will grab a random reward from the Random Unlocks.  */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Calendar" )
	TArray< class UFGUnlock* > mSlotUnlocks;

	/** The random rewards for a calendar. Used when no reward is available for a slot in the Slot Rewards*/
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Calendar" )
	TArray< class UFGUnlock* > mRandomUnlocks;
	
	UPROPERTY( VisibleDefaultsOnly, Category = "Deprecated" )
	TArray< FItemAmount > mSlotRewards;
	UPROPERTY( VisibleDefaultsOnly, Category = "Deprecated" )
	TArray< FItemAmount > mRandomRewards;

};

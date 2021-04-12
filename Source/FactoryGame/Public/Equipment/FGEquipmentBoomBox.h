// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGMusicPlayerInterface.h"
#include "Equipment/FGEquipment.h"
#include "FGEquipmentBoomBox.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGEquipmentBoomBox : public AFGEquipment, public IFGMusicPlayerInterface
{
	GENERATED_BODY()
public:
	AFGEquipmentBoomBox();

	// Replication
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	/* Returns inventory index where next tape is
	 * @param nextIndex - valid numbers are -1, 0 and 1
	 **/
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void UpdateTapeIndex( int32 indexToAdd );

	/** Get for mCurrentTapeIndex */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
    FORCEINLINE int32 GetCurrentTapeIndex( ) { return mCurrentTapeIndex; }
private:
	/** Inventory index of current tape */
	UPROPERTY( Replicated )
	int32 mCurrentTapeIndex;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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

	/** Get for mCurrentTapeDescriptor */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	FORCEINLINE TSubclassOf< class UFGTapeDescriptor > GetCurrentTapeDescriptor( ) { return mCurrentTapeDescriptor; }

	/** Set for mCurrentTapeDescriptor */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void SetCurrentTapeDescriptor( TSubclassOf< class UFGTapeDescriptor > newTape ) { mCurrentTapeDescriptor = newTape; }

	/**
	 * Returns list of tapedescriptors in the users inventory
	 * */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	TArray< TSubclassOf< class UFGTapeDescriptor > > GetAvailableTapes();

private:
	/** current tape to play */
	UPROPERTY( Replicated )
	TSubclassOf< class UFGTapeDescriptor > mCurrentTapeDescriptor;
};

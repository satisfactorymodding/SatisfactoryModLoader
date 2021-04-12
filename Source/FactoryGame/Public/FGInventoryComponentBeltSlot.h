// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGInventoryComponent.h"
#include "FGInventoryComponentBeltSlot.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGInventoryComponentBeltSlot : public UFGInventoryComponent
{
	GENERATED_BODY()
public:
	/** Constructor */
	UFGInventoryComponentBeltSlot();

	bool ContainsStackItemTypeAndHasEnoughRoom( FInventoryStack itemStack );

protected:
	// Begin UFGInventoryComponent interface
	virtual void OnItemsAdded( int32 idx, int32 num ) override;
	virtual void OnItemsRemoved( int32 index, int32 num, FInventoryItem item ) override;
	// End UFGInventoryComponent interface
private:
	/** @copydoc UFGInventoryComponent::FilterEquipmentClasses */
	bool FilterEquipmentClasses( TSubclassOf< UObject > object, int32 idx ) const;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGInventoryComponent.h"
#include "FGInventoryComponentTrash.generated.h"

UCLASS()
class FACTORYGAME_API UFGInventoryComponentTrash : public UFGInventoryComponent
{
	GENERATED_BODY()

public:
	/** Constructor */
	UFGInventoryComponentTrash();
	// Begin UFGInventoryComponent interface
	virtual void OnItemsAdded( int32 idx, int32 num ) override;
	// End UFGInventoryComponent interface
private:
private:
	/** @copydoc UFGInventoryComponent::FilterEquipmentClasses */
	bool FilterExcludedItems( TSubclassOf< UObject > object, int32 idx ) const;

	/** Can item be trashed? */
	UFUNCTION()
	bool IsValidItem( TSubclassOf< class UFGItemDescriptor > resource ) const;
};
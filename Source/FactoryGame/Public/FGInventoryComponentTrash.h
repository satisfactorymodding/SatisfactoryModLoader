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
	virtual void OnItemsAdded( const int32 idx, const int32 num, UFGInventoryComponent* sourceInventory = nullptr ) override;
	// End UFGInventoryComponent interface
private:
private:
	/** @copydoc UFGInventoryComponent::FilterEquipmentClasses */
	bool FilterExcludedItems( TSubclassOf< UObject > object, int32 idx ) const;

	/** Can item be trashed? */
	UFUNCTION()
	bool IsValidItem( TSubclassOf< class UFGItemDescriptor > resource ) const;
};
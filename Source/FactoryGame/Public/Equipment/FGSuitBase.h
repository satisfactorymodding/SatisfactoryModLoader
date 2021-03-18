// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Equipment/FGEquipment.h"
#include "Equipment/FGEquipmentAttachment.h"
#include "FGSuitBase.generated.h"


USTRUCT( BlueprintType )
struct FACTORYGAME_API FMaterialAndSlotName
{
	GENERATED_BODY()
public:
	/** This is the slot name on the character */
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	FName SlotName;

	/** The material to put on that slot name */
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	UMaterialInterface* Material;
};

/**
 * Base class for "suit"-like equipment. Updates player visuals on equip/unequip etc.
 */
UCLASS()
class FACTORYGAME_API AFGSuitBase : public AFGEquipment
{
	GENERATED_BODY()

public:
	AFGSuitBase();

	// Begin AFGEquipment
	virtual void WasEquipped_Implementation() override;
	virtual void WasUnEquipped_Implementation() override;
	// End AFGEquipment

protected:
	/** Materials to replace on the first person players mesh. */
	UPROPERTY( EditDefaultsOnly, Category = "Materials" )
	TArray< FMaterialAndSlotName > mSuit1PMeshMaterials;
};

UCLASS()
class FACTORYGAME_API AFGSuitBaseAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()
public:
	// Begin AFGEquipmentAttachment
	virtual void OnAttach_Implementation() override;
	virtual void OnDetach_Implementation() override;
	// End AFGEquipmentAttachment
	
protected:
	/** Materials to replace on the third person players mesh. */
	UPROPERTY( EditDefaultsOnly, Category = "Materials" )
	TArray< FMaterialAndSlotName > mSuit3PMeshMaterials;
};

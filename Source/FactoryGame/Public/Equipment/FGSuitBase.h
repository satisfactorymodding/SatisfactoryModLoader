// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Equipment/FGEquipment.h"
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
	UPROPERTY( BlueprintReadWrite, EditAnywhere, DisplayName = "Material 1P" )
	UMaterialInterface* Material;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, DisplayName = "Material 3P" )
	UMaterialInterface* Material3P;
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
	TArray< FMaterialAndSlotName > mSuitMeshMaterials;

	/** Player mesh materials that we have swapped out */
	UPROPERTY( Transient )
	TArray< FMaterialAndSlotName > mSwappedOutMeshMaterials;
};

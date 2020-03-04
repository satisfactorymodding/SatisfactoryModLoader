// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "FGEquipment.h"
#include "FGEquipmentAttachment.h"
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

public:
	FORCEINLINE ~FMaterialAndSlotName() = default;
};

/**
 * Base class for "suit"-like equipment. Updates visuals on equip/unequip etc.
 */
UCLASS()
class FACTORYGAME_API AFGSuitBase : public AFGEquipment
{
	GENERATED_BODY()

public:
	/** Ctor */
	AFGSuitBase();

	/**
	* equipment equipped.
	*/
	virtual void WasEquipped_Implementation() override;

	/**
	* equipment put away.
	*/
	virtual void WasUnEquipped_Implementation() override;

protected:
	UPROPERTY( EditDefaultsOnly, Category = "Materials" )
	TArray< FMaterialAndSlotName > mSuit1PMeshMaterials;
	

public:
	FORCEINLINE ~AFGSuitBase() = default;
};

UCLASS()
class FACTORYGAME_API AFGSuitBaseAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()

	/**
	* equipment attached.
	*/
	virtual void OnAttach_Implementation() override;

	/**
	* equipment detached.
	*/
	virtual void OnDetach_Implementation() override;

protected:
	UPROPERTY( EditDefaultsOnly, Category = "Materials" )
	TArray< FMaterialAndSlotName > mSuit3PMeshMaterials;

public:
	FORCEINLINE ~AFGSuitBaseAttachment() = default;
};

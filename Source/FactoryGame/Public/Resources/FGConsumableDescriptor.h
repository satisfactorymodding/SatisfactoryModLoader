#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "Engine/StaticMesh.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGEquipmentDescriptor.h"
#include "FGConsumableDescriptor.generated.h"

/**
 * Item descriptor for consumable items.
 */
UCLASS()
class FACTORYGAME_API UFGConsumableDescriptor : public UFGEquipmentDescriptor
{
	GENERATED_BODY()
public:
	UFGConsumableDescriptor();

	/**
	 * NEVER EVER change any state of this object in this function, it's the default object.
	 *
	 * @param player - the player consuming the consumeable
	 */
	UFUNCTION( BlueprintImplementableEvent ,Category = "FactoryGame|Descriptor|Consumable" )
	void ConsumedBy( class AFGCharacterPlayer* player ) const;

	/** The skeletal mesh we want for representing the resource when they are in the production line.
	* @return The items mesh; a default mesh if the item has no mesh specified, nullptr if inClass is nullptr. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Consumable" )
	static class USkeletalMesh* GetFPOverrideMesh( TSubclassOf< UFGConsumableDescriptor > inClass );

	/** The static mesh we want for representing the item when viewed as thir person.
	* @return The items mesh; a default mesh if the item has no mesh specified, nullptr if inClass is nullptr. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Consumable" )
	static class UStaticMesh* GetTPOverrideMesh( TSubclassOf< UFGConsumableDescriptor > inClass );

public:
	/** Sound played when consuming */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Consumeable" )
	class UAkAudioEvent* mConsumeEvent;

protected:
	/** Custom scale of mesh in hands */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Consumeable" )
	float mCustomHandsMeshScale;

	/** Custom local rotaion of mesh in hands */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Consumeable" )
	FRotator mCustomRotation;

	/** Custom local location of mesh in hands */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Consumeable" )
	FVector mCustomLocation;

	/** The skeletal  mesh we want for representing the resource when it is in first person. */
	UPROPERTY( EditDefaultsOnly, Category = "Consumeable" )
	class USkeletalMesh* mFPOverrideMesh;

	/** The static mesh we want for representing the resource when it is in third person. */
	UPROPERTY( EditDefaultsOnly, Category = "Consumeable" )
	class UStaticMesh* mTPOverrideMesh;

public:
	FORCEINLINE ~UFGConsumableDescriptor() = default;
};
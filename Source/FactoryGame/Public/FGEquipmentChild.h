// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment/FGEquipment.h"
#include "FGEquipmentChild.generated.h"

/**
* Equipment children are a second actor spawned when the FGEquipable parent is spawned from FGCharacterPlayer
* They are not saved and thus all actions should be driven by their parent.
* If the FGEquipable parent is loaded from save, then their FGEquipmentChild (this) is spawned in PostLoadGame()
*/
UCLASS()
class FACTORYGAME_API AFGEquipmentChild : public AActor
{
	GENERATED_BODY()
public:	
	AFGEquipmentChild();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	/** Called by Equipable parent when it is equipped */
	virtual void Equip( class AFGCharacterPlayer* character, class AFGEquipment* parentEquipment );
	/** Called by UnEquip parent when it is unequiped */
	virtual void UnEquip();

	/** Called by after equip has run allowing for blueprint functionality */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void OnEquip( class AFGCharacterPlayer* character );

	/** Called by after Unequip has run allowing for blueprint functionality */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void OnUnEquip( );

	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	FTransform GetAttachSocketTransform();

	/** Updates materials based on the camera mode */
	void UpdateMaterialsFromCameraMode();

	/** Called when the camera mode of the player having the equipment changes to third or first person */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void OnCameraModeChanged( ECameraMode newCameraMode );

	/** Called to update the equipment visibility based on the external conditions such as player visibility and/or status (e.g. hand equipments are hidden inside of the hyper tube) */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void SetEquipmentVisibility( bool bNewEquipmentVisible );

	/**
	 * Convenience blueprint function to return Instigator as a FGCharacterPlayer
	 * @return The instigator for this equipment; nullptr if not equipped or Instigator is not an FGCharacterPlayer.
	 */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	class AFGCharacterPlayer* GetInstigatorCharacter() const;

	/** Returns the current camera mode of the player the equipment is attached to. Will return ECM_None if not equipped */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	ECameraMode GetInstigatorCameraMode() const;
protected:
	/** stores a reference to the FGEquipment that spawned this class */
	UPROPERTY( BlueprintReadOnly, Category = "Equipment" )
	class AFGEquipment* mParentEquipment;

	/** Each Mesh Component should have an entry here to remap its materials to the First person material (one with the panini switch enabled) */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment")
	TMap< FName, FFirstPersonMaterialArray > mComponentNameToFirstPersonMaterials;

private:
	/** The socket to attach any child equipment to */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	FName mAttachSocket;

	/** Materials that were swapped out during the change of the POV to first person */
	UPROPERTY( VisibleInstanceOnly, Category = "Equipment" )
	TMap<FName, FFirstPersonMaterialArray> mSwappedOutThirdPersonMaterials;
};

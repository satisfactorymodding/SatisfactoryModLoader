// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

protected:
	/** stores a reference to the FGEquipment that spawned this class */
	UPROPERTY( BlueprintReadOnly, Category = "Equipment" )
	class AFGEquipment* mParentEquipment;

private:
	/** The socket to attach any child equipment to */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	FName mAttachSocket;
	

public:
	FORCEINLINE ~AFGEquipmentChild() = default;
};

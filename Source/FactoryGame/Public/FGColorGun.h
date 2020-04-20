// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Equipment/FGWeaponInstantFire.h"
#include "FGColorGun.generated.h"


UENUM( BlueprintType )
enum class EFGColorGunTargetType : uint8
{
	ECGT_noTarget,
	ECGT_nonColorable,
	ECGT_validTarget,
	ECGT_sameColorSlot,
};
/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGColorGun : public AFGWeaponInstantFire
{
	GENERATED_BODY()

	AFGColorGun();

public:

	/** Sets the currently active color slot index for the gun  */
	UFUNCTION( BlueprintCallable, Category = "Color Gun" )
	void SetColorSlot( uint8 slotIndex);

	/** Sets the currently active color slot index for the gun on the server */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SetColorSlot( uint8 slotIndex );

	/** Gets the mac number of color slots */
	UFUNCTION( BlueprintPure, Category = "Color Gun" )
	uint8 GetMaxNumColorSlots();

	UFUNCTION( BlueprintPure, Category = "Color Gun" )
	uint8 GetNumColorSlotsExposedToPlayers();

	/** Set the secondary color for a given slot*/
	UFUNCTION( BlueprintCallable, Category = "Color Gun" )
	void SetPrimaryColorForSlot( uint8 slotIndex, FLinearColor newColor );

	/** Set the secondary color for a given slot on the server */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SetPrimaryColorForSlot( uint8 slotIndex, FLinearColor newColor );

	/** Set the secondary color for a given slot index*/
	UFUNCTION( BlueprintCallable, Category = "Color Gun" )
	void SetSecondaryColorForSlot( uint8 slotIndex, FLinearColor newColor );

	/** Sets the primary color for a given slot index on the server*/
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SetSecondaryColorForSlot( uint8 slotIndex, FLinearColor newColor );

	/** Get the primary color for a given color slot index*/
	UFUNCTION( BlueprintPure, Category = "Color Gun" )
	FLinearColor GetPrimaryColorForSlot(uint8 index) const;

	/** Get the secondary color for a given color slot index*/
	UFUNCTION( BlueprintPure, Category = "Color Gun" )
	FLinearColor GetSecondaryColorForSlot( uint8 index ) const;

	/** Get the the currently active color slot index for the gun */
	UFUNCTION( BlueprintPure, Category = "Color Gun" )
	FORCEINLINE uint8 GetColorSlotIndex() const { return mColorSlot; }

	/** Opens the UI so that the player can select both colors */
	UFUNCTION( BlueprintImplementableEvent, Category = "Color Gun" )
	void ToggleColorPickerUI();

	/** Opens the UI so that the player can select both colors */
	UFUNCTION( BlueprintImplementableEvent, Category = "Color Gun" )
	void OnTargetStateChanged( EFGColorGunTargetType targetType);

	/**[DEPRECATED]  Get the primary color */
	UFUNCTION( BlueprintPure, Category = "Color Gun" )
	FORCEINLINE FLinearColor GetPrimaryColor() const { return mPrimaryColor_DEPRECATED; }

	/**[DEPRECATED] Get the Secondary color*/
	UFUNCTION( BlueprintPure, Category = "Color Gun" )
	FORCEINLINE FLinearColor GetSecondaryColor() const { return mSecondaryColor_DEPRECATED; }


	virtual void Equip( class AFGCharacterPlayer* character ) override;


	virtual void Tick( float DeltaSeconds ) override;

	void ApplyCrosshairState();

	EFGColorGunTargetType FindIfValidColorTarget();




	virtual void UnEquip() override;

protected:

	/** continue processing the instant hit, as if it has been confirmed by the server */
	virtual void ProcessInstantHit_Confirmed( const FHitResult& hitResult ) override;

	// Begin AFGEquipment interface
	virtual void AddEquipmentActionBindings() override;
	// End AFGEquipment interface

	/** Called when we press secondary fire */
	UFUNCTION()
	void OnSecondaryFirePressed();


protected:
	/**[DEPRECATED] This will be the color used when shooting */
	UPROPERTY()
	FLinearColor mPrimaryColor_DEPRECATED;

	/**[DEPRECATED] This will be the color used when shooting */
	UPROPERTY()
	FLinearColor mSecondaryColor_DEPRECATED;

	/**crosshair color used when aiming at a target that already have the same color slot as you are painting*/
	UPROPERTY( EditDefaultsOnly, Category = "Color Gun" )
	FLinearColor mRedundantTargetCrosshairColor = FLinearColor( 0.5f, 0.2f, 0.2f, 0.7f );

	/**crosshair texture used when aiming at a target that already have the same color slot as you are painting*/
	UPROPERTY( EditDefaultsOnly, Category = "Color Gun" )
	class UTexture2D * mRedundantTargetCrosshairTexture = nullptr;


	/**crosshair color used when aiming at a target too far away or not aiming at a target at all */
	UPROPERTY( EditDefaultsOnly, Category = "Color Gun" )
	FLinearColor mNoTargetCrosshairColor = FLinearColor( 0.4f, 0.1f, 0.1f, 0.4f );

	/**crosshair texture used when aiming at a target too far away or not aiming at a target at all */
	UPROPERTY( EditDefaultsOnly, Category = "Color Gun" )
	class UTexture2D * mNoTargetCrosshairTexture = nullptr;
	

	/**crosshair color used when aiming at a target that can't be colored*/
	UPROPERTY( EditDefaultsOnly, Category = "Color Gun" )
	FLinearColor mNonColorableTargetCrosshairColor = FLinearColor( 0.1f, 0.05f, 0.05f, 0.92f );

	/**crosshair texture used when aiming at a target that can't be colored*/
	UPROPERTY( EditDefaultsOnly, Category = "Color Gun" )
	class UTexture2D * mNonColorableTargetCrosshairTexture = nullptr;


	/**crosshair texture used when aiming at a target isvalid*/
	UPROPERTY( EditDefaultsOnly, Category = "Color Gun" )
	class UTexture2D * mValidTargetCrosshairTexture = nullptr;

	/** This will be the color slot used when shooting */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Color Gun" )
	uint8 mColorSlot = 1; //[DavalliusA:Fri/01-03-2019] don't use the first color as default, as it will make players maybe not notice when thye fire on a building already using the default color

	UPROPERTY()
	AActor* mCurrentColorTarget;

	EFGColorGunTargetType mAimingOnTarget;

	class AFGCharacterPlayer* mCharOwner; //[DavalliusA:Wed/20-03-2019] saved so we can easily handle outline stuff
	bool mHadUseTargetLastFrame;

public:
	FORCEINLINE ~AFGColorGun() = default;
};

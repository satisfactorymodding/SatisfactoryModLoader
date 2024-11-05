// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGItemPickup.h"
#include "NativeGameplayTags.h"
#include "FGUnlockPickup.generated.h"

struct FPickupTags
{
	static FNativeGameplayTag PickedUpBoomboxTape;
};

/**
 * The state an unlock pickup can be in
 */ 
UENUM( BlueprintType )
enum class ESchematicPickupState : uint8
{ 
	/**
	 * @brief State is unknown. Will be the case on clients until a client receives the first net update from the server. In this state, the
	 * pickup should hide it's visual representation from the world.
	 */
	Unknown,
	/**
	 * @brief The pick-up is still available and can be interacted with. In this state it should have a visual representation.
	 */
	Available, 
	/**
	 * @brief The pick-up has been collected. In this state, it should be thoroughly hidden.
	 */
	Collected
};

/**
 * Can be used to place schematics in world, that can be picked up by the player, in effect unlocking those schematics.
 * Has no visual representation natively and it needs to be set up in derived BP classes, as the actual visuals would vary quite a bit
 * from one schematic type to another. 
 */ 
UCLASS( Blueprintable )
class FACTORYGAME_API AFGUnlockPickup : public AFGStaticReplicatedActor, public IFGUseableInterface, public IFGSaveInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGUnlockPickup();

	// Begin UObject interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void Serialize( FArchive& ar ) override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End


	// Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override;
	// End

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	// End

protected:
	/**
	 * Pick up this unlock.
	 */
	virtual void PickUpByCharacter( class AFGCharacterPlayer* byCharacter );

	/**
	 * Use this event to play any animations or effects when picking up this schematic. 
	 */ 
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "Pickup" )
	void PlayPickupEffect( class AFGCharacterPlayer* byCharacter );

	/**
	 * Use this event to update the visual representation of the pick-up in relation to @mPickupState
	 */ 
	UFUNCTION( BlueprintNativeEvent, Category = "Pickup" )
	void UpdateVisuals();

	UFUNCTION()
	void OnRep_PickedUp();

	UFUNCTION()
	void SomeSchematicPurchased( TSubclassOf< class UFGSchematic > schematic );

	/** Multicast to everyone so picking up clients can see effects */
	UFUNCTION( Unreliable, NetMulticast )
	void Multicast_PlayPickupEffect( class AFGCharacterPlayer* byCharacter );

	/** The schematic you can unlock through this pick-up. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf< class UFGSchematic > mSchematic;

	/** The current state of this pickup. Replicated. */
	UPROPERTY( ReplicatedUsing=OnRep_PickedUp, SaveGame, BlueprintReadOnly )
	ESchematicPickupState mPickupState = ESchematicPickupState::Unknown;
};

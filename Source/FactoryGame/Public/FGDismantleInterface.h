// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGInventoryComponent.h"
#include "FGDismantleInterface.generated.h"

class UFGConstructDisqualifier;

/**
 * Interface for actors that can be dismantled by the buildgun.
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGDismantleInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGDismantleInterface
{
	GENERATED_IINTERFACE_BODY()

	/**
	 * Can this be dismantled.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	bool CanDismantle() const;

	/**
	 * How much do we get back when dismantling this.
	 * @param noBuildCostEnabled If the player unique game rules NoBuildCost is enabled. This is needed here because we can't check this
	 * in a global scope since it's per player. If noBuildCostEnabled is true we only want to return content of buildings (inventory, potential inventory etc.)
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	void GetDismantleRefund( UPARAM( ref ) TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled ) const;

	/**
	 * Returns the location where the refund should be spawned and the area
	 * if the player doesn't have room in the inventory.
	 *
	 * @param aimHitLocation - the location we aimed at when dismantling happened
	 * @param out_radius - radius we want to spawn stuff within
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	FVector GetRefundSpawnLocationAndArea( const FVector& aimHitLocation, float& out_radius ) const;

	/**
	 * If we want to dismantle something else along with this, then add it through this
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	void GetChildDismantleActors( TArray< AActor* >& out_ChildDismantleActors ) const;

	/**
	 * Called prior to dismantle and prior to an upgrade from this actor to another actor.
	 * Use it to clear connections and other stuff that might interfere with upgrades.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	void PreUpgrade();

	/**
	 * Called when an upgrade is performed from this actor to another actor.
	 * @param newActor  The new actor that replaces this.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	void Upgrade( AActor* newActor );

	/**
	 * Dismantle this.
	 */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Dismantle" )
	void Dismantle();

	/**
	 * Called on by the interface if we are looking at something we can dismantle.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	void StartIsLookedAtForDismantle( AFGCharacterPlayer* byCharacter );

	/**
	 * Called when we stop looking at the item
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	void StopIsLookedAtForDismantle( AFGCharacterPlayer* byCharacter );

	/**
	 * Returns true if the dismantle mode should ignore this buildable and disallow sampling it in dismantle
	 * The original function name was CanDismantleSample, but unfortunately UHT is dumb and does not allow having a default implementation of interface BP NativeEvent functions
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	bool ShouldBlockDismantleSample() const;

	/** Returns the display name of the actor when it is looked at for dismantle */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	FText GetDismantleDisplayName( AFGCharacterPlayer* byCharacter ) const;

	/**
	 * Returns the dependencies that need to be dismantled first to successfully dismantle this buildable
	 * For example, tracks require trains that are occupying them to be dismantled first before they can be dismantled
	 * When cycles are present, the dismantle order is undefined.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	void GetDismantleDependencies( TArray<AActor*>& out_dismantleDependencies ) const;

	/** Returns true if this dismantle-able actor is willing to have GetDismantleDisqualifiers called on it. Used to prevent a fairly expensive call to GetDismantleDisqualifiers which copies the selected buildables array */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	bool SupportsDismantleDisqualifiers() const;

	/** Allows providing dismantle disqualifiers to the build gun to give visual feedback as to why the given buildable cannot be dismantled. Keep in mind that this is only used for the visual feedback. */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	void GetDismantleDisqualifiers( TArray<TSubclassOf<UFGConstructDisqualifier>>& out_dismantleDisqualifiers, const TArray<AActor*>& allSelectedActors ) const;
};

/**
 * Shared magic between holograms
 */
struct FACTORYGAME_API FDismantleHelpers
{
	/**
	 * @param dismantledActor	Actor to be dismantled.
	 * @param aimHitLocation	Where the actor is dismantled, i.e. where on the actor did the player initiate the dismantle action.
	 * @param refund			The refund to drop.
	 */
	static void DropRefundOnGround( class AActor* dismantledActor, const FVector& aimHitLocation, const TArray< FInventoryStack >& refund );
	
	/**
	 * @param world				World To Place Refund.
	 * @param aimHitLocation	Where the object was dismantled, i.e. where on the actor did the player initiate the dismantle action (but for lightweights we dont have an actor so this will be a lightweight location).
	 * @param refund			The refund to drop.
	 */
	static void DropRefundOnGroundNoActor( class UWorld* world, const FVector& lightweightLocation, AActor* ignoreActor, const TArray< FInventoryStack >& refund );
};

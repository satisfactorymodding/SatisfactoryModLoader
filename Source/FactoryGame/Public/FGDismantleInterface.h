#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "UObject/Class.h"

#include "FGInventoryComponent.h"
#include "FGDismantleInterface.generated.h"

/**
* For blueprint support of the interface, we will never add anything to it, just use it to
* have a UCLASS to be able to access
*/
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGDismantleInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGDismantleInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGDismantleInterface() = default;
};

/**
* @brief Interface for all "dismantle-able" classes out there
*/
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
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
	void GetDismantleRefund( UPARAM( ref ) TArray< FInventoryStack >& out_refund ) const;

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
	UFUNCTION( BlueprintNativeEvent, Category = "Dismantle" )
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

public:
	FORCEINLINE IFGDismantleInterface() = default;
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

public:
	FORCEINLINE ~FDismantleHelpers() = default;
};

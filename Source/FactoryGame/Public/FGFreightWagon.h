// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGRailroadVehicle.h"
#include "FGFreightWagon.generated.h"

// Enum to track the two types of cargo (Standard and Liquid)
UENUM( BlueprintType )
enum class EFreightCargoType : uint8
{
	FCT_NONE		UMETA( DisplayName = "None" ),
	FCT_Standard	UMETA( DisplayName = "Standard" ),
	FCT_Liquid		UMETA( DisplayName = "Liquid" ),
	FCT_MAX			UMETA( Hidden )
};

/**
 * Freight cart that has an inventory component to transport items.
 * Depending on the inventory it is holding it can be either a liquid / gas container or a standard storage container
 */
UCLASS()
class FACTORYGAME_API AFGFreightWagon : public AFGRailroadVehicle
{
	GENERATED_BODY()
	
public:
	AFGFreightWagon();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;

	// Begin Movement
	virtual class UPawnMovementComponent* GetMovementComponent() const override;
	virtual class UFGRailroadVehicleMovementComponent* GetRailroadVehicleMovementComponent() const override;
	// End Movement

	//~ Begin IFGUseableInterface
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	//~ End IFGUseableInterface

	/** Get the inventory where we store the cargo. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|FreightCar" )
	class UFGInventoryComponent* GetFreightInventory() const;

	/** Get the inventory where we store the cargo. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|FreightCar" )
	float GetFreightInventoryFilledPercent() const { return 0.23f; } //@todotrains return a correct value - Update on todo - This really doesn't seem used. Remove this.

	/** Get the override stack size scaled for fluid types. Specified in class / BP defaults */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Inventory" )
	FORCEINLINE int32 GetScaledFluidStackSize() const { return mCachedFluidStackSize * mFluidStackSizeMultiplier; }

	/** Sets the visibility on the cargo mesh component. Toggled during load / unload sequences. As well when there is no inventory present or some is added */
	void SetCargoMeshVisibility( bool isVisible );

	/** Sets the transitory cargo type ( see property declaration for its used ) */
	FORCEINLINE void SetTransitoryCargoType( EFreightCargoType type ) { mTransitoryCargoType = type; }

	/** Updates the type of this freight based on the items in its inventory */
	void UpdateFreightCargoType();

	/** Gets the types of Freight Cargo this freight is carrying*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Inventory")
	FORCEINLINE EFreightCargoType GetFreightCargoType() const { return mFreightCargoType; }

	/** Checks if a freight is valid to dock with a certain platform and its type */
	bool CanDockWithPlatformOfType( EFreightCargoType platformType ) const;

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

private:
	UFUNCTION()
	void OnItemAddedToFreight( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numAdded );

	UFUNCTION()
	void OnItemRemovedFromFreight( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numRemoved );

	UFUNCTION()
	void InitializeInventoryComponent();

	/** When the player is first killed by an appearing container (items were added to an empty container) this is called. */
	void BeginLaunchOverlappedCharacter( class UPrimitiveComponent* OverlappedComp, class AFGCharacterPlayer* otherCharacter );

	/** Called a frame after a player is killed by an appearing container */
	void EndLaunchOverlappedCharacters( );

	/** Returns a UStaticMesh pointer ( loaded if necessary ) that matches the inventory housed in our inventory component */
	UStaticMesh* GetCargoStaticMesh();

public:
	/** Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName VehicleMovementComponentName;

	/** Name of the cargo mesh component */
	static FName CargoMeshComponentName;

private:

	/** The current type of inventory this freight is holding. Default is FCT_Standard. */
	UPROPERTY()
	EFreightCargoType mFreightCargoType;

	/** 
	 * When docking with a platform a freight may not have a defined type, however the inventory will transfer after the need to swap container visibility ( it may show the wrong mesh )
	 * This temporary type does not carry any influence when updating mFreightCargoType but will be used as an override to specify container type when getting the needed static mesh if mFreightCargoType is FCT_None
	 * @note - Is reset to FCT_None by calls to UpdateFrieghtCargoType() which sets the actually value based on the inventory present
	 */
	UPROPERTY()
	EFreightCargoType mTransitoryCargoType;

	UPROPERTY()
	TArray<AFGCharacterPlayer*> mLaunchedCharacters;

	/** vehicle simulation component */
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = Vehicle, meta = ( AllowPrivateAccess = "true" ) )
	class UFGRailroadVehicleMovementComponent* mVehicleMovement;

	/** Responsible for handling our inventory */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mStorageInventory;

	/** Static mesh to use when freight is holding standard inventory ( factory items ) */
	UPROPERTY( EditDefaultsOnly, Category = "FreightWagon" )
	TSoftObjectPtr< UStaticMesh > mContainerMeshStandard;

	/** Static mesh to use when freight is holding liquid / gas inventory */
	UPROPERTY( EditDefaultsOnly, Category = "FreightWagon" )
	TSoftObjectPtr< UStaticMesh > mContainerMeshLiquid;
	
	/** The size of the inventory for this wagon. */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mInventorySize;

	/** Item stack size Enum to use as base for how much fluid a Liquid / Gas Item descriptor can be stored on an index in an inventory */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	EStackSize mFluidStackSizeDefault;

	/** The size of the inventory for this wagon. */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mFluidStackSizeMultiplier;

	/** Cached value of Fluid Resource Stack Size ( set in begin play from the default stack enum ) */
	int32 mCachedFluidStackSize;

	UPROPERTY()
	class UStaticMeshComponent* mCargoMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "FreightWagon")
	float mLaunchCharacterScalar;

	UPROPERTY( VisibleAnywhere )
	class UBoxComponent* mCargoOverlapCollision;


public:
	FORCEINLINE ~AFGFreightWagon() = default;
};

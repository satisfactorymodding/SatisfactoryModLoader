// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGRailroadVehicle.h"
#include "FGFreightWagon.generated.h"

/**
 * 
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
	float GetFreightInventoryFilledPercent() const { return 0.23f; } //@todotrains return a correct value

	/** Sets the visibility on the cargo mesh component. Toggled during load / unload sequences. As well when there is no inventory present or some is added */
	void SetCargoMeshVisibility( bool isVisible );

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

private:
	UFUNCTION()
	void OnItemAddedToFreight( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numAdded );

	UFUNCTION()
	void OnItemRemovedFromFreight( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numRemoved );

	UFUNCTION()
	void InitializeInventoryComponent();

	void BeginLaunchOverlappedCharacter( class UPrimitiveComponent* OverlappedComp, class AFGCharacterPlayer* otherCharacter );

	void EndLaunchOverlappedCharacters( );

public:
	/** Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName VehicleMovementComponentName;

	/** Name of the cargo mesh component */
	static FName CargoMeshComponentName;

private:

	UPROPERTY()
	TArray<AFGCharacterPlayer*> mLaunchedCharacters;

	/** vehicle simulation component */
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = Vehicle, meta = ( AllowPrivateAccess = "true" ) )
	class UFGRailroadVehicleMovementComponent* mVehicleMovement;

	/** Responsible for handling our inventory */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mStorageInventory;

	/** The size of the inventory for this wagon. */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mInventorySize;

	UPROPERTY()
	class UStaticMeshComponent* mCargoMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "FreightWagon")
	float mLaunchCharacterScalar;

	UPROPERTY( VisibleAnywhere )
	class UBoxComponent* mCargoOverlapCollision;
};

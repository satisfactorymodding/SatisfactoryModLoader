// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGEquipment.h"
#include "FGGolfCartDispenser.generated.h"

UENUM( BlueprintType )
enum class EGolfCartPlacementError : uint8
{
	ERROR_InvalidPlacement		UMETA(DisplayName = "Invalid Placement" ),
	ERROR_Clearance				UMETA(DisplayName = "Clearance Overlap" )
};

/**
 * TODO: Refactor alongside FGPortableMinerDispenser into an "AFGEquipment_ActorSpawner" base class.
 */
UCLASS()
class FACTORYGAME_API AFGGolfCartDispenser : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGGolfCartDispenser();

	void BeginPlay();

	void SetMaterial( class UMaterialInterface* material );

	void SpawnGolfCart();

protected:
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;
	
	bool TraceForPlacementLocation( FVector& out_Location, FRotator& out_Rotation ) const;

	UFUNCTION( BlueprintNativeEvent, Category = "Golf Cart Dispenser" )
	void ConfigureSpawnedGolfCart( AActor* golfCartActor );

	UFUNCTION( BlueprintNativeEvent, Category = "Golf Cart Dispenser" )
	void OnFailedPlacement( EGolfCartPlacementError reason );

	UFUNCTION( Server, Reliable )
	void Server_SpawnGolfCart( const FVector& spawnLocation, const FRotator& spawnRotation );

	UFUNCTION( Client, Reliable )
	void Client_OnFailedPlacement( EGolfCartPlacementError reason );
	
public:
	UPROPERTY( EditDefaultsOnly, Category = "Golf Cart Dispenser" )
	FVector mCartPlacementClearance;

	UPROPERTY( EditDefaultsOnly, Category = "Golf Cart Dispenser" )
	float mCartPlacementDistance;

	UPROPERTY( EditDefaultsOnly, Category = "Golf Cart Dispenser" )
	TSubclassOf< AActor > mGolfCartClass;
	
	/** Material on hologram for valid placement. */
	UPROPERTY()
	class UMaterialInstance* mValidPlacementMaterial;

	/** Material on hologram for invalid placement. */
	UPROPERTY()
	class UMaterialInstance* mInvalidPlacementMaterial;
};

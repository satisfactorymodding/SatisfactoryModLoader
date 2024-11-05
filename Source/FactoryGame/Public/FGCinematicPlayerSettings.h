
#pragma once

#include "CoreMinimal.h"
#include "Equipment/FGEquipment.h"
#include "Templates/SubclassOf.h"
#include "FGCinematicPlayerSettings.generated.h"

/** Settings related to the cinematic behavior of the player */
USTRUCT( )
struct FACTORYGAME_API FFGCinematicPlayerSettings
{
	GENERATED_BODY()

	/** The camera mode the player character should have */
	UPROPERTY( EditAnywhere, Category = "Cinematic | General" )
	ECameraMode CinematicCameraMode{ECameraMode::ECM_ThirdPerson};

	/** Player name to set on the player state */
	UPROPERTY( EditAnywhere, Category = "Cinematic | General" )
	FString PlayerName{TEXT("Cinematic Player")};

	/** A list of items that will be added to the player's inventory by default. They will *not* be automatically equipped though */
	UPROPERTY( EditAnywhere, Category = "Cinematic | Inventory" )
	TArray<FItemAmount> DefaultInventoryItems;

	/**
	 * When set, the cinematic driver will keep track of the transform change from the previous frame and attempt to interpolate the movement input
	 * to match the transform changes, resulting in the adequate movement animations playing while offering the freedom of directly manipulating the Transform track from the Sequencer
	 */
	UPROPERTY( EditAnywhere, Category = "Cinematic | Movement" )
	bool bInterpolateTransform{true};

	/** When set to true, the player character will automatically face the movement direction (yaw) wise. The Pitch and Roll values will be still read from mViewRotation */
	UPROPERTY( EditAnywhere, Category = "Cinematic | Movement" )
	bool bUseMovementYawRotation{true};

	/** When set to true, the player will automatically equip equipments from the inventory */
	UPROPERTY( EditAnywhere, Category = "Cinematic | Inventory" )
	bool bAutoEquipEquipments{true};

	/** Whenever to show the name tag for this player */
	UPROPERTY( EditAnywhere, Category = "Cinematic | General" )
	bool bShowNameTag{false};

	/** Class to use for the cinematic driver initialization */
	UPROPERTY( EditAnywhere, Category = "Cinematic | Advanced" )
	TSoftClassPtr<class UFGPlayerCinematicDriver> CinematicDriverClass;
};

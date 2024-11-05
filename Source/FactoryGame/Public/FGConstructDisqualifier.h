// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Templates/SubclassOf.h"
#include "Internationalization/StringTableRegistry.h"
#include "FGConstructDisqualifier.generated.h"

#define LOCTEXT_NAMESPACE "Construct Disqualifiers"  

/**
 * This specifies the reason why the player could not build.
 */
UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API UFGConstructDisqualifier : public UObject
{
	GENERATED_BODY()

public:
	UFGConstructDisqualifier() :
		mDisqfualifyingText( LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Generic/ThisShouldNeverBeSeen" ) ),
		mIsSoftDisqualifier( false )
	{
	}

	/** Getter for mDisfualifyingText */
	UFUNCTION( BlueprintPure )
	static FText GetDisqualifyingText( TSubclassOf< UFGConstructDisqualifier > inClass );
	
	/** Getter for mIsSoftDisqualifier */
	UFUNCTION( BlueprintPure )
	static bool GetIsSoftDisqualifier( TSubclassOf< UFGConstructDisqualifier > inClass );

protected:

	/** Text displayed to the player when they couldn't build */
	UPROPERTY( EditDefaultsOnly )
	FText mDisqfualifyingText;

	/** Whether or not this is a soft disqualifier. If so, the player is still allowed to construct the hologram. */
	UPROPERTY( EditDefaultsOnly )
	bool mIsSoftDisqualifier;
};

UCLASS()
class FACTORYGAME_API UFGCDInitializing : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInitializing()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Generic/Initializing" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDInvalidAimLocation : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidAimLocation()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/InvalidAimLocation" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDUnaffordable : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDUnaffordable()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/CannotAfford" );
	}
};


UCLASS()
class FACTORYGAME_API UFGCDInvalidPlacement : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidPlacement()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/InvalidPlacement" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDEncroachingClearance : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDEncroachingClearance()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/Clearance" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDEncroachingSoftClearance : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDEncroachingSoftClearance()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/OverlappingPossibleClipping" );
		mIsSoftDisqualifier = true;
	}
};

UCLASS()
class FACTORYGAME_API UFGCDEncroachingPlayer : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDEncroachingPlayer()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/PlayerInTheWay" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDEncroachingCreature : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDEncroachingCreature()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/CreatureInTheWay" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDEncroachingVehicle : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDEncroachingVehicle()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/VehicleInTheWay" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDInvalidFloor : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidFloor()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/FloorTooSteep" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDUniqueBuilding : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDUniqueBuilding()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/ThereCanBeOnlyOne" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustSnap()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/RequiresSnapToFoundation" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustSnapWall : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustSnapWall()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/RequiresSnapToWall" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustSnapToCeiling : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustSnapToCeiling()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/CeilingRequired" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDShouldntSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDShouldntSnap()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/CannotSnapToFoundation" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDNeedsResourceNode : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNeedsResourceNode()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/RequiresResourceNode" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustSnapStation : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustSnapStation()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Drones/RequiresSnapToPort" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDOccupiedStation : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDOccupiedStation()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Drones/PortOccupied" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDDroneStationHasDrone : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDDroneStationHasDrone()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Drones/AssignedToDronePort" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDNeedsFrackingCoreNode : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNeedsFrackingCoreNode()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/RequiresFrackingCoreNode" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDNeedsFrackingSatelliteNode : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNeedsFrackingSatelliteNode()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/RequiresFrackingSatelliteNode" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDResourceNodeIsOccuped : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDResourceNodeIsOccuped()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Resources/NodeOccupied" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDResourceIsTooShallow : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDResourceIsTooShallow()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Resources/NotDeepEnough" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDNeedsWaterVolume : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNeedsWaterVolume()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/RequiresDeepWater" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDResourceDeposit : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDResourceDeposit()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Resources/PlaceExtractorOnNode" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDWireSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDWireSnap()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/PowerLines/RequiresHookUpToConnection" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDWireTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDWireTooLong()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/PowerLines/WireTooLong" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDWireConnectionAlreadyExists : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDWireConnectionAlreadyExists()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/PowerLines/AlreadyConnected" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDInvalidSignSize : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidSignSize() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Signs/CannotSnap" ); }
};

UCLASS()
class FACTORYGAME_API UFGCDWireTooManyConnections : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDWireTooManyConnections()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/PowerLines/CantConnectMore" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDBeltMustSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDBeltMustSnap()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Belts/SnapToConveyorPole" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorTooLong()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Belts/TooLong" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorTooShort : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorTooShort()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Belts/TooShort" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorTooSteep : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorTooSteep()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Belts/TooSteep" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorInvalidShape : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorInvalidShape()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Belts/InvalidShape" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorAttachmentTooSharpTurn : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorAttachmentTooSharpTurn()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Belts/TooSharp" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustHaveRailRoadTrack : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustHaveRailRoadTrack()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/RequiresRailroad" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDNotEnoughSpaceOnTrack : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNotEnoughSpaceOnTrack()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/RailroadTracks/NoSpace" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDSignalAlreadyPlaced : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDSignalAlreadyPlaced()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/RailroadTracks/OtherSignal" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDSignalCannotBePlaceAtTheEndOfATrack : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDSignalCannotBePlaceAtTheEndOfATrack()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/RailroadTracks/EndOfTrack" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDInvalidDoubleSwitch : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidDoubleSwitch()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/SwitchTooClose" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDTooManySwitchPositions : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDTooManySwitchPositions()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/SwitchPositionsTooMany" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustAttachToTrainPlatform : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustAttachToTrainPlatform()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/RailroadTracks/RequiresPlacedInlineWithPlatform" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDTrackTooLong()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/RailroadTracks/TooLong" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTooShort : public UFGConstructDisqualifier
{
	GENERATED_BODY()

		UFGCDTrackTooShort()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/RailroadTracks/TooShort" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTooSteep : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDTrackTooSteep()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/RailroadTracks/TooSteep" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTrunToSharp : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDTrackTrunToSharp()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/RailroadTracks/TurnTooSharp" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeTooShort : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeTooShort()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Pipes/TooShort" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeTooLong()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Pipes/TooLong" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeAttachmentTooSharpTurn : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeAttachmentTooSharpTurn()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Pipes/TooSharp" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeMustSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeMustSnap()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Pipes/RequiresSnapToPipeSupport" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeFluidTypeMismatch : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeFluidTypeMismatch()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Pipes/DifferentFluids" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeInvalidShape : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeInvalidShape()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Pipes/InvalidShape" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeNoPathFound : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDPipeNoPathFound()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Pipes/NoPath" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDIdenticalOverlappingBuildable : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDIdenticalOverlappingBuildable()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BuildMode/IdenticalBuildable" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDNotAllowedInBlueprint : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDNotAllowedInBlueprint()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BlueprintDesigner/CannotBePlaced" );
	}
};


UCLASS()
class FACTORYGAME_API UFGCDIntersectingBlueprintDesigner : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDIntersectingBlueprintDesigner()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BlueprintDesigner/Overlapping" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDDesignerWorldCommingling : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDDesignerWorldCommingling()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/BlueprintDesigner/CannotConnect" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDInvalidUpgradeConnections : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDInvalidUpgradeConnections()
	{
		mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Upgrades/Invalid" );
	}
};

// Note the discrepancy between the code spelling "customiZation" vs "customiSation". I changed it here only as this is a LOC key and figured it would be best to have it as the
// stupid british way of spelling it for the sake of localization. That's right I said it. Its stupid. Also, UE uses the "Z" form so its consistent.
// Alex: we have En-US as our default locale, though in reality we seem to be producing a mix of US and UK... Changed this to customization since it's what we use in most other places.
UCLASS()
class FACTORYGAME_API UFGCDInvalidCustomizationTarget : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidCustomizationTarget() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Customization/InvalidTarget" ); }
};

UCLASS()
class FACTORYGAME_API UFGCDCustomizationAlreadyApplied : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDCustomizationAlreadyApplied() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/Customization/AlreadyApplied" ); }
};

UCLASS()
class FACTORYGAME_API UFGDDBuildablesInsideBlueprintDesigner : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGDDBuildablesInsideBlueprintDesigner() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/DismantleMode/OccupiedBlueprintDesigner" ); }
};

UCLASS()
class FACTORYGAME_API UFGDDRailroadStationDocking : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGDDRailroadStationDocking() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/DismantleMode/OccupiedTrainPlatform/TrainDocking" ); }
};


UCLASS()
class FACTORYGAME_API UFGDDRailroadPlatformHasVehicles : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGDDRailroadPlatformHasVehicles() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/DismantleMode/OccupiedTrainPlatform/VehiclesOnIt" ); }
};

UCLASS()
class FACTORYGAME_API UFGDDRailwayHasVehicles : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGDDRailwayHasVehicles() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/DismantleMode/OccupiedRailwaySegment" ); }
};

UCLASS()
class FACTORYGAME_API UFGDDRailwayVehicleIsMoving : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGDDRailwayVehicleIsMoving() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/DismantleMode/MovingVehicle" ); }
};

UCLASS()
class FACTORYGAME_API UFGDDRailwayVehicleIsDocked : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGDDRailwayVehicleIsDocked() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/DismantleMode/DockingVehicle" ); }
};

UCLASS()
class FACTORYGAME_API UFGDDRailwayVehicleDerailed : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGDDRailwayVehicleDerailed() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/DismantleMode/DerailedVehicle" ); }
};

UCLASS()
class FACTORYGAME_API UFGDDVehicleHasDriver : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGDDVehicleHasDriver() { mDisqfualifyingText = LOCTABLE( "Messages_UI", "ConstructDisqualifiers/DismantleMode/OccupiedVehicle" ); }
};

#undef LOCTEXT_NAMESPACE


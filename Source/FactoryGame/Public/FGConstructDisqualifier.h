// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
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
		mDisqfualifyingText( LOCTEXT( "UFGConstructDisqualifier", "This should never be seen!" ) )
	{
	}

	/** Getter for mDisfualifyingText */
	UFUNCTION( BlueprintPure )
	static FText GetDisqualifyingText( TSubclassOf< UFGConstructDisqualifier > inClass );

protected:

	/** Text displayed to the player when they couldn't build */
	UPROPERTY( EditDefaultsOnly )
	FText mDisqfualifyingText;
};

UCLASS()
class FACTORYGAME_API UFGCDInitializing : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInitializing()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDInitializing", "Initializing" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDInvalidAimLocation : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidAimLocation()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDInvalidAimLocation", "Invalid aim location!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDUnaffordable : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDUnaffordable()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDUnaffordable", "Can't afford!" );
	}
};


UCLASS()
class FACTORYGAME_API UFGCDInvalidPlacement : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidPlacement()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDInvalidPlacement", "Invalid placement!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDEncroachingClearance : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDEncroachingClearance()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDEncroachingClearance", "Encroaching other's clearance!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDEncroachingPlayer : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDEncroachingPlayer()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDEncroachingPlayer", "A player is in the way!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDInvalidFloor : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidFloor()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDInvalidFloor", "Floor is too steep!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDUniqueBuilding : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDUniqueBuilding()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDUniqueBuilding", "You can only build one!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustSnap()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDMustSnap", "Must snap to a foundation or similar!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustSnapToCeiling : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustSnapToCeiling()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDMustSnapToCeiling", "This must be built on a ceiling!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDShouldntSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDShouldntSnap()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDShouldntSnap", "This building can't snap to foundations!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDNeedsResourceNode : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNeedsResourceNode()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDNeedsResourceNode", "You need to place this on a Resource Node!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustSnapStation : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustSnapStation()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDMustSnapStation", "Must snap to a Drone Port!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDOccupiedStation : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDOccupiedStation()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDOccupiedStation", "Drone Port is currently occupied!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDDroneStationHasDrone : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDDroneStationHasDrone()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDDroneStationHasDrone", "Port already has a drone assigned to it!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDNeedsFrackingCoreNode : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNeedsFrackingCoreNode()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDNeedsFrackingCoreNode", "You need to place this on a Fracking Core Node!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDNeedsFrackingSatelliteNode : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNeedsFrackingSatelliteNode()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDNeedsFrackingSatelliteNode", "You need to place this on an activated Fracking Satellite Node!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDResourceNodeIsOccuped : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDResourceNodeIsOccuped()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDResourceNodeIsOccuped", "Resource Node is occupied!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDResourceIsTooShallow : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDResourceIsTooShallow()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDResourceIsTooShallow", "Resource is not deep enough!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDNeedsWaterVolume : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNeedsWaterVolume()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDNeedsWaterVolume", "You need to place this on deep water!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDResourceDeposit : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDResourceDeposit()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDResourceDeposit", "You can't place a Resource Extractor on a Resource Deposit, it needs a Resource Node!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDWireSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDWireSnap()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDWireSnap", "You need to hook this up to a connection!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDWireTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDWireTooLong()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDWireTooLong", "Wire is too long!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDWireTooManyConnections : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDWireTooManyConnections()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDWireTooManyConnections", "You can't connect more lines to this connection!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDBeltMustSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDBeltMustSnap()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDBeltMustSnap", "The Conveyor Belt must snap to a Conveyor Pole or an Input/Output of a building!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorTooLong()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDConveyorTooLong", "The Conveyor Belt is too long!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorTooShort : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorTooShort()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDConveyorTooShort", "The Conveyor Belt is too short!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorTooSteep : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorTooSteep()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDConveyorTooSteep", "The Conveyor Belt is too steep!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorInvalidShape : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorInvalidShape()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDConveyorInvalidShape", "The Conveyor Belt has an invalid shape!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorAttachmentTooSharpTurn : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorAttachmentTooSharpTurn()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDConveyorAttachmentTooSharpTurn", "The turn of the belt is too sharp of an attachment!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustHaveRailRoadTrack : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustHaveRailRoadTrack()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDMustHaveRailRoadTrack", "This must be placed on a railroad track!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDMustAttachToTrainPlatform : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustAttachToTrainPlatform()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDMustAttachToTrainPlatform", "This must be placed inline with another train platform!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDTrackTooLong()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDTrackTooLong", "The Railroad Track is too long" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTooShort : public UFGConstructDisqualifier
{
	GENERATED_BODY()

		UFGCDTrackTooShort()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDTrackTooShort", "The Railroad Track is too short" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTooSteep : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDTrackTooSteep()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDTrackTooSteep", "The Railroad Track is too steep" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTrunToSharp : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDTrackTrunToSharp()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDTrackTrunToSharp", "The Railroad Track has a too sharp turn" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeTooShort : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeTooShort()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeTooShort", "The Pipe is too short" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeTooLong()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeTooLong", "The Pipe is too long" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeAttachmentTooSharpTurn : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeAttachmentTooSharpTurn()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeAttachmentTooSharpTurn", "The turn of the Pipe is too sharp for attachment!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeMustSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeMustSnap()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeMustSnap", "The Pipe must snap to a Pipe Support or a building connection!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeFluidTypeMismatch : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeFluidTypeMismatch()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeFluidTypeMismatch", "Cannot connect pipe networks containing different fluids!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeInvalidShape : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeInvalidShape()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeInvalidShape", "The Pipe has an invalid shape!" );
	}
};

UCLASS()
class FACTORYGAME_API UFGCDPipeNoPathFound : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDPipeNoPathFound()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeNoPathFound", "No path could be found to construct the pipe" );
	}
};


#undef LOCTEXT_NAMESPACE 

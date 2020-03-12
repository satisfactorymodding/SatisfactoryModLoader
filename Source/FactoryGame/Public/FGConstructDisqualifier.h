// Copyright 2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Object.h"
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

public:
	FORCEINLINE ~UFGConstructDisqualifier() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDInitializing : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInitializing()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDInitializing", "Initializing" );
	}

public:
	FORCEINLINE ~UFGCDInitializing() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDInvalidAimLocation : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidAimLocation()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDInvalidAimLocation", "Invalid Aim Location!" );
	}

public:
	FORCEINLINE ~UFGCDInvalidAimLocation() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDUnaffordable : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDUnaffordable()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDUnaffordable", "Can't Afford!" );
	}

public:
	FORCEINLINE ~UFGCDUnaffordable() = default;
};


UCLASS()
class FACTORYGAME_API UFGCDInvalidPlacement : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidPlacement()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDInvalidPlacement", "Invalid Placement!" );
	}

public:
	FORCEINLINE ~UFGCDInvalidPlacement() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDEncroachingClearance : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDEncroachingClearance()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDEncroachingClearance", "Encroaching other's Clearance!" );
	}

public:
	FORCEINLINE ~UFGCDEncroachingClearance() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDEncroachingPlayer : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDEncroachingPlayer()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDEncroachingPlayer", "A player is in the way!" );
	}

public:
	FORCEINLINE ~UFGCDEncroachingPlayer() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDInvalidFloor : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDInvalidFloor()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDInvalidFloor", "Floor is too Steep!" );
	}

public:
	FORCEINLINE ~UFGCDInvalidFloor() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDUniqueBuilding : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDUniqueBuilding()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDUniqueBuilding", "You can only build one!" );
	}

public:
	FORCEINLINE ~UFGCDUniqueBuilding() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDMustSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustSnap()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDMustSnap", "Must snap to a foundation or similar!" );
	}

public:
	FORCEINLINE ~UFGCDMustSnap() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDShouldntSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDShouldntSnap()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDShouldntSnap", "This building can't snap to foundations!" );
	}

public:
	FORCEINLINE ~UFGCDShouldntSnap() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDNeedsResourceNode : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNeedsResourceNode()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDNeedsResourceNode", "You need to place this on a Resource Node!" );
	}

public:
	FORCEINLINE ~UFGCDNeedsResourceNode() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDResourceNodeIsOccuped : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDResourceNodeIsOccuped()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDResourceNodeIsOccuped", "Resource Node is Occupied!" );
	}

public:
	FORCEINLINE ~UFGCDResourceNodeIsOccuped() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDResourceIsTooShallow : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDResourceIsTooShallow()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDResourceIsTooShallow", "Resource is not Deep Enough!" );
	}

public:
	FORCEINLINE ~UFGCDResourceIsTooShallow() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDNeedsWaterVolume : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDNeedsWaterVolume()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDNeedsWaterVolume", "You need to place this on Deep Water!" );
	}

public:
	FORCEINLINE ~UFGCDNeedsWaterVolume() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDResourceDeposit : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDResourceDeposit()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDResourceDeposit", "You can't place a Resource Extractor on a Resource Deposit, it needs a Resource Node!" );
	}

public:
	FORCEINLINE ~UFGCDResourceDeposit() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDWireSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDWireSnap()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDWireSnap", "You need to hook this up to a connection!" );
	}

public:
	FORCEINLINE ~UFGCDWireSnap() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDWireTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDWireTooLong()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDWireTooLong", "Wire is too long!" );
	}

public:
	FORCEINLINE ~UFGCDWireTooLong() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDWireTooManyConnections : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDWireTooManyConnections()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDWireTooManyConnections", "You can't connect more lines to this connection!" );
	}

public:
	FORCEINLINE ~UFGCDWireTooManyConnections() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDBeltMustSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDBeltMustSnap()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDBeltMustSnap", "The Conveyor Belt must snap to a Conveyor Pole or an Input/Output of a building!" );
	}

public:
	FORCEINLINE ~UFGCDBeltMustSnap() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorTooLong()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDConveyorTooLong", "The Conveyor Belt is too long!" );
	}

public:
	FORCEINLINE ~UFGCDConveyorTooLong() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorTooShort : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorTooShort()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDConveyorTooShort", "The Conveyor Belt is too short!" );
	}

public:
	FORCEINLINE ~UFGCDConveyorTooShort() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorTooSteep : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorTooSteep()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDConveyorTooSteep", "The Conveyor Belt is too steep!" );
	}

public:
	FORCEINLINE ~UFGCDConveyorTooSteep() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorInvalidShape : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorInvalidShape()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDConveyorInvalidShape", "The Conveyor Belt has an invalid shape!" );
	}

public:
	FORCEINLINE ~UFGCDConveyorInvalidShape() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDConveyorAttachmentTooSharpTurn : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDConveyorAttachmentTooSharpTurn()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDConveyorAttachmentTooSharpTurn", "The turn of the belt is too sharp of an attachment!" );
	}

public:
	FORCEINLINE ~UFGCDConveyorAttachmentTooSharpTurn() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDMustHaveRailRoadTrack : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustHaveRailRoadTrack()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDMustHaveRailRoadTrack", "This must be placed on a railroad track!" );
	}

public:
	FORCEINLINE ~UFGCDMustHaveRailRoadTrack() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDMustAttachToTrainPlatform : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDMustAttachToTrainPlatform()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDMustAttachToTrainPlatform", "This must be placed inline with another train platform!" );
	}

public:
	FORCEINLINE ~UFGCDMustAttachToTrainPlatform() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDTrackTooLong()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDTrackTooLong", "The Railroad Track is too long" );
	}

public:
	FORCEINLINE ~UFGCDTrackTooLong() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTooShort : public UFGConstructDisqualifier
{
	GENERATED_BODY()

		UFGCDTrackTooShort()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDTrackTooShort", "The Railroad Track is too short" );
	}

public:
	FORCEINLINE ~UFGCDTrackTooShort() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTooSteep : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDTrackTooSteep()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDTrackTooSteep", "The Railroad Track is too steep" );
	}

public:
	FORCEINLINE ~UFGCDTrackTooSteep() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDTrackTrunToSharp : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDTrackTrunToSharp()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDTrackTrunToSharp", "The Railroad Track has a too sharp turn" );
	}

public:
	FORCEINLINE ~UFGCDTrackTrunToSharp() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDPipeTooShort : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeTooShort()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeTooShort", "The Pipe is too short" );
	}

public:
	FORCEINLINE ~UFGCDPipeTooShort() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDPipeTooLong : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeTooLong()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeTooLong", "The Pipe is too long" );
	}

public:
	FORCEINLINE ~UFGCDPipeTooLong() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDPipeAttachmentTooSharpTurn : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeAttachmentTooSharpTurn()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeAttachmentTooSharpTurn", "The turn of the Pipe is too sharp for attachment!" );
	}

public:
	FORCEINLINE ~UFGCDPipeAttachmentTooSharpTurn() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDPipeMustSnap : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeMustSnap()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeMustSnap", "The Pipe must snap to a Pipe Support or a building connection!" );
	}

public:
	FORCEINLINE ~UFGCDPipeMustSnap() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDPipeFluidTypeMismatch : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeFluidTypeMismatch()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeFluidTypeMismatch", "Cannot connect pipe networks containing different fluids!" );
	}

public:
	FORCEINLINE ~UFGCDPipeFluidTypeMismatch() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDPipeInvalidShape : public UFGConstructDisqualifier
{
	GENERATED_BODY()

	UFGCDPipeInvalidShape()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeInvalidShape", "The Pipe has an invalid shape!" );
	}

public:
	FORCEINLINE ~UFGCDPipeInvalidShape() = default;
};

UCLASS()
class FACTORYGAME_API UFGCDPipeNoPathFound : public UFGConstructDisqualifier
{
	GENERATED_BODY()
	
	UFGCDPipeNoPathFound()
	{
		mDisqfualifyingText = LOCTEXT( "UFGCDPipeNoPathFound", "No path could be found to construct the pipe" );
	}

public:
	FORCEINLINE ~UFGCDPipeNoPathFound() = default;
};


#undef LOCTEXT_NAMESPACE 
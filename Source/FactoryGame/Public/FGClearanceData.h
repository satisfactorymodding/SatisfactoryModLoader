// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "FGClearanceData.generated.h"

/** Different types of clearances. */
UENUM( BlueprintType )
enum class EClearanceType : uint8
{
	// Default clearance, will block if overlapping another default clearance type.
	CT_Default				UMETA( DisplayName = "Default" ),

	// Soft clearance, can clip with other clearance boxes but will warn.
	CT_Soft					UMETA( DisplayName = "Soft" ),

	// Block everything, will not allow soft clearance overlaps.
	CT_BlockEverything		UMETA( DisplayName = "Block Everything" ),
};

/** Different results for overlapping clearances. */
UENUM( BlueprintType )
enum class EClearanceOverlapResult : uint8
{
	// No overlap
	COR_None		UMETA( DisplayName = "No Overlap" ),

	// Soft overlap
	COR_Soft		UMETA( DisplayName = "Soft" ),

	// Blocked overlap
	COR_Block	UMETA( DisplayName = "Block" ),
};

/** How to respond to soft clearance overlaps. */
UENUM( BlueprintType )
enum class ESoftClearanceOverlapResponse : uint8
{
	// Default
	SCOR_Default			UMETA( DisplayName = "Default" ),

	// Ignore if both clearance boxes are soft
	SCOR_IgnoreBothSoft		UMETA( DisplayName = "Ignore Both Soft" ),
};

/**
 * Clearance data used for overlapping checks when building.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGClearanceData
{
	GENERATED_BODY()

	FFGClearanceData() :
		Type( EClearanceType::CT_Default ),
		ClearanceBox( EForceInit::ForceInitToZero ),
		SoftClearanceResponse( ESoftClearanceOverlapResponse::SCOR_Default ),
		ExcludeForSnapping( false )

#if WITH_EDITORONLY_DATA
		,Visualize( false )
#endif
	{
	}

	virtual ~FFGClearanceData() {}

	FORCEINLINE bool IsValid() const { return ClearanceBox.IsValid != 0; }

	FORCEINLINE FBox GetTransformedClearanceBox() const { return ClearanceBox.TransformBy( RelativeTransform ); }

	/** What type of clearance this is. */
	UPROPERTY( EditDefaultsOnly, Category = "Clearance" )
	EClearanceType Type;

	/** Simple clearance box, used for overlap checks. */
	UPROPERTY( EditDefaultsOnly, Category = "Clearance" )
	FBox ClearanceBox;

	/** Relative transform of the clearance box. */
	UPROPERTY( EditDefaultsOnly, Category = "Clearance" )
	FTransform RelativeTransform;

	/** Whether or not we want to ignore soft clearance overlaps. */
	UPROPERTY( EditDefaultsOnly, Category = "Clearance" )
	ESoftClearanceOverlapResponse SoftClearanceResponse;

	/** If true, this clearance data will not be combined into the snapping box used for clearance snapping. */
	UPROPERTY( EditDefaultsOnly, Category = "Clearance" )
	bool ExcludeForSnapping;

#if WITH_EDITORONLY_DATA
	friend class UEditorDebugSubsystem;
private:
	/** Whether or not to visualize this clearance box. (Used when setting up the clearance box)*/
	UPROPERTY( EditDefaultsOnly, Transient, NonTransactional, SkipSerialization, Category = "Clearance" )
	bool Visualize;
#endif
};
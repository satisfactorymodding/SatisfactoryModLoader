// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "FGBuildableFactoryBuilding.generated.h"

UENUM()
enum class EFoundationSide : uint8
{
	FoundationFront UMETA(DisplayName = "Front"),
	FoundationRight UMETA( DisplayName = "Right" ),
	FoundationBack UMETA( DisplayName = "Back" ),
	FoundationLeft UMETA( DisplayName = "Left" ),
	FoundationTop UMETA( DisplayName = "Top" ),
	FoundationBottom UMETA( DisplayName = "Bottom" ),

	FoundationNumSides UMETA( DisplayName = "Num Sides" ),

	Invalid UMETA( DisplayName = "Invalid" )
};

/** Disable snapping on specific sides. */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFoundationSideSelectionFlags
{
	GENERATED_BODY()
public:
	static const FFoundationSideSelectionFlags NoEdges;
	static const FFoundationSideSelectionFlags AllEdges;

public:
	FFoundationSideSelectionFlags();
	FFoundationSideSelectionFlags( bool defaults );

	bool GetValueForSide( EFoundationSide Side );

	FFoundationSideSelectionFlags RotateEdges( int32 steps ) const;

public:
	UPROPERTY( EditDefaultsOnly, Category = "Sides" )
	uint8 Front : 1;
	UPROPERTY( EditDefaultsOnly, Category = "Sides" )
	uint8 Right : 1;
	UPROPERTY( EditDefaultsOnly, Category = "Sides" )
	uint8 Back : 1;
	UPROPERTY( EditDefaultsOnly, Category = "Sides" )
	uint8 Left : 1;
	UPROPERTY( EditDefaultsOnly, Category = "Sides" )
	uint8 Top : 1;
	UPROPERTY( EditDefaultsOnly, Category = "Sides" )
	uint8 Bottom : 1;
};

struct FFoundationSideNormal
{
	FFoundationSideNormal() {}
	FFoundationSideNormal( EFoundationSide side, FVector normal ) : Side( side ), LocalNormal( normal ) {}
	
	EFoundationSide Side = EFoundationSide::Invalid;
	FVector LocalNormal = FVector{ EForceInit::ForceInit };
};

struct FFoundationHelpers
{
	static FVector GetLocalSpaceNormalFromFoundationSide( EFoundationSide side );
	static FFoundationSideNormal FindBestMatchingFoundationSideFromLocalNormal( class AFGBuildableFoundation* foundation, FVector normal );
};

/**
 * Base for all kinds of factory building parts, like foundations, walls etc.
 */
UCLASS(Abstract)
class FACTORYGAME_API AFGBuildableFactoryBuilding : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableFactoryBuilding();

protected:
	FORCEINLINE class UFGColoredInstanceMeshProxy* GetMeshComponentProxy() const { return mMeshComponentProxy; }

private:
	/** Mesh component for the factory building. */
	UPROPERTY( VisibleAnywhere )
	class UFGColoredInstanceMeshProxy* mMeshComponentProxy = nullptr;
};

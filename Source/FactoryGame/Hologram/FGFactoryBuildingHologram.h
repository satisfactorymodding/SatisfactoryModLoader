// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "UObject/Class.h"

#include "FGBuildableHologram.h"
#include "../Buildables/FGBuildableFactoryBuilding.h"
#include "FGFactoryBuildingHologram.generated.h"


UCLASS()
class FACTORYGAME_API AFGFactoryBuildingHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
	
public:
	AFGFactoryBuildingHologram();

protected:
	virtual void BeginPlay() override;

	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;

	/** Helper */
	bool CheckClearanceForBuildingMesh( UStaticMeshComponent* mesh, const FComponentQueryParams& params = FComponentQueryParams::DefaultComponentQueryParams );

	/**
	 * Get the direction of the edge facing towards us.
	 * A floor is a square with four edges, it has a location and a rotation.
	 *
	 * @param floorLoc - Center of the floor.
	 * @param floorRot - Rotation of the floor.
	 * @param testLoc - Location to test for a facing edge.
	 * @param excludeEdges - Edges to not consider. (Top and bottom is ignored)
	 *
	 * @return Edge direction facing testLoc and facing away from floorLoc.
	 */
	FVector GetFloorEdgeDirection( const FVector& floorLoc, const FRotator& floorRot, const FVector& testLoc, FFoundationSideSelectionFlags excludeEdges = FFoundationSideSelectionFlags::NoEdges ) const;

	/**
	 * Get the offset along the the floors edge.
	 * A floor is a square with four edges, it has a location and a rotation.
	 * @note Assumes that testSize is a multiple of floorSize.
	 *
	 * @param floorLoc - Center of the floor.
	 * @param floorRot - Rotation of the floor.
	 * @param floorSize - Width of the floor.
	 * @param testLoc - Location to test for a facing edge.
	 * @param testSize - Width of the tested object.
	 *
	 * @return Offset from the center of the floors width.
	 */
	FVector GetFloorEdgeOffset( const FVector& floorLoc, const FRotator& floorRot, float floorSize, const FVector& testLoc, float testSize, FFoundationSideSelectionFlags excludeEdges = FFoundationSideSelectionFlags::NoEdges ) const;

	/**
	 * Get the direction of the side of a wall facing towards us.
	 *
	 * @param wallLoc - Bottom center of the wall.
	 * @param wallRot - Rotation of the wall.
	 * @param testLoc - Location to test to get the facing direction to.
	 *
	 * @return Direction of the side facing testLoc.
	 */
	FVector GetWallEdgeDirection( const FVector& wallLoc, const FRotator& wallRot, const FVector& testLoc ) const;

private:
	UPROPERTY()
	UStaticMeshComponent* mBuildingMesh;
};

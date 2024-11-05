// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "UObject/Interface.h"
#include "FGSplineBuildableInterface.generated.h"

class UFGConnectionComponent;

// This class does not need to be modified.
UINTERFACE( MinimalAPI, meta = ( CannotImplementInterfaceInBlueprint ) )
class UFGSplineBuildableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Universal functions that we use to get data from different buildables to reconstruct their spline meshes (used by the blueprint hologram)
 */
class FACTORYGAME_API IFGSplineBuildableInterface
{
	GENERATED_BODY()

public:
	/** Returns the bounding box of the spline, taking the middle spline point and the half length of the spline. Only returns valid data after BeginPlay as it relies on spline component to have valid data! */
	FBox GetSplineBoundingBox() const;

	/** Returns the first connection of the spline buildable */
	UFUNCTION( BlueprintCallable, Category = "Spline Buildable Interface" )
	virtual UFGConnectionComponent* GetSplineConnection0() const = 0;
	/** Returns the first connection of the spline buildable */
	UFUNCTION( BlueprintCallable, Category = "Spline Buildable Interface" )
	virtual UFGConnectionComponent* GetSplineConnection1() const = 0;
	
	/** Returns the spline component holding the current state of the spline. This should only be used after BeginPlay, before BeginPlay use GetSplinePointsData! */
	UFUNCTION( BlueprintCallable, Category = "Spline Buildable Interface" )
	virtual USplineComponent* GetSplineComponent() const = 0;

	/**
	 * Returns the immutable raw spline point data, in local space.
	 * Safe to be used before BeginPlay before we initialize the spline component with it's data.
	 * Used for blueprint hologram as blueprints do not begin play in blueprint world.
	 */
	virtual const TArray< FSplinePointData >& GetSplinePointData() const = 0;

	/**
	 * Returns mutable raw spline point data, in local space.
	 * Must be called before BeginPlay as after BeginPlay the current version of the data will be flushed into the spline component and should not be modified.
	 * Used for populating spline data independent of the buildable type.
	 */
	virtual TArray< FSplinePointData >* GetMutableSplinePointData() { return nullptr; }

	/** Returns the length of the spline buildable mesh, in world units */
	UFUNCTION( BlueprintCallable, Category = "Spline Buildable Interface" )
	virtual float GetMeshLength() const = 0;
	
	/** Returns the spline mesh that should be used for visualizing this spline buildable. Used by blueprint holograms. */
	UFUNCTION( BlueprintCallable, Category = "Spline Buildable Interface" )
	virtual UStaticMesh* GetSplineMesh() const = 0;
};

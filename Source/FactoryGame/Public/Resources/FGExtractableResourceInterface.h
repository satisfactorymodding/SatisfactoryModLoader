// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGExtractableResourceInterface.generated.h"

/**
 * Interface for all mineable resource objects ( Resource Nodes, Water Volumes )
 */
UINTERFACE( Blueprintable, meta = ( CannotImplementInterfaceInBlueprint ) )
class FACTORYGAME_API UFGExtractableResourceInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGExtractableResourceInterface
{
	GENERATED_IINTERFACE_BODY()
public:

	/** Notify that a miner / pump has claimed this resource object */
	UFUNCTION( BlueprintCallable, Category = "Resource" )
	virtual void SetIsOccupied( bool occupied ) = 0;

	/** Does another miner / pump occupy this extractable resource? */
	UFUNCTION( BlueprintCallable, Category = "Resource" )
	virtual bool IsOccupied() const = 0;

	/** Should this resource node become occupied when an extractor is built upon it? Return false for resources that can hold many extractors */
	UFUNCTION( BlueprintCallable, Category = "Resource" )
	virtual bool CanBecomeOccupied() const = 0;

	/** Is there anything left to mine? */
	UFUNCTION( BlueprintCallable, Category = "Resource" )
	virtual bool HasAnyResources() const = 0;

	/** Gets the descriptor for the resource being mined from this object */
	UFUNCTION( BlueprintCallable, Category = "Resource" )
	virtual TSubclassOf< class UFGResourceDescriptor > GetResourceClass() const = 0;

	/** Actually extract the resource 
	 *	@param amount - quantity to attempt to mine
	 *	@return - Actual amount that was able to be mined
	 */
	UFUNCTION( BlueprintCallable, Category = "Resource" )
	virtual int32 ExtractResource( int32 amount ) = 0;

	/** Speed modifier for rate at which this resource is extracted */
	UFUNCTION( BlueprintCallable, Category = "Resource" )
	virtual float GetExtractionSpeedMultiplier() const = 0;

	/** Used by holograms to get the correct location for snapping when placed on this extractable resource */
	UFUNCTION( BlueprintCallable, Category = "Resource" )
	virtual FVector GetPlacementLocation( const FVector& hitLocation ) const = 0;

	/** Can an extractor be placed on this resource object? */
	UFUNCTION( BlueprintCallable, Category = "Resource" )
	virtual bool CanPlaceResourceExtractor() const = 0;
};
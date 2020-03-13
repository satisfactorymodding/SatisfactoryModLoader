#pragma once
#include "UObject/Interface.h"
#include "SubclassOf.h"

#include "FGExtractableResourceInterface.generated.h"

/**
*
*/
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGExtractableResourceInterface : public UInterface
{
	
    GENERATED_BODY()
    UFGExtractableResourceInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGExtractableResourceInterface() = default;
};

/**
* Interface for all mineable resource objects ( Resource Nodes, Water Volumes )
*/
class FACTORYGAME_API IFGExtractableResourceInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	/** Notify that a miner / pump has claimed this resource object */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource" )
	void SetIsOccupied( bool occupied );

	/** Does another miner / pump occupy this extractable resource? */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Resource" )
	bool IsOccupied() const;

	/** Should this resource node become occupied when an extractor is built upon it? Return false for resources that can hold many extractors */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Resource" )
	bool CanBecomeOccupied() const;

	/** Is there anything left to mine? */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Resource" )
	bool HasAnyResources() const;

	/** Gets the descriptor for the resource being mined from this object */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Resource" )
	TSubclassOf< class UFGResourceDescriptor > GetResourceClass() const;

	/** Actually extract the resource 
	*	@param amount - quantity to attempt to mine
	*	@return - Actual amount that was able to be mined
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource" )
	int32 ExtractResource( int32 amount );

	/** Speed modifier for rate at which this resource is extracted */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Resource" )
	float GetExtractionSpeedMultiplier() const;

	/** Used by holograms to get the correct location for snapping when placed on this extractable resource */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Resource" )
	FVector GetPlacementLocation( const FVector& hitLocation ) const;

	/** Can an extractor be placed on this resource object? */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Resource" )
	bool CanPlaceResourceExtractor() const;

	

public:
	FORCEINLINE IFGExtractableResourceInterface() = default;
};
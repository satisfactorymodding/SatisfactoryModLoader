// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGBuildingDescriptor.h"
#include "FGDecorDescriptor.generated.h"

/**
 * Descriptor for buildable decor.
 */
UCLASS(Meta=(AutoJson=false))
class FACTORYGAME_API UFGDecorDescriptor : public UFGBuildingDescriptor
{
	GENERATED_BODY()
public:
	UFGDecorDescriptor();

	/** Get the mesh of the decor. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Decor" )
	static class UStaticMesh* GetDecorMesh( TSubclassOf< UFGDecorDescriptor > inClass );

protected:
	/** The static mesh for the decor. */
	UPROPERTY( EditDefaultsOnly, Category = "Decor" )
	class UStaticMesh* mDecorMesh;
};

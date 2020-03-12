// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "../FGFluidIntegrantInterface.h"
#include "FGBuildablePipelineAttachment.generated.h"

/**
 * Base for pipe attachments such as pumps and junctions.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipelineAttachment : public AFGBuildableFactory, public IFGFluidIntegrantInterface
{
	GENERATED_BODY()
public:
	AFGBuildablePipelineAttachment();

	//Begin Actor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	//End Actor Interface

	// Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	// End IFGDismantleInferface

	// Begin Fluid Integrant Interface
	virtual FFluidBox* GetFluidBox() override;
	virtual TArray< class UFGPipeConnectionComponent* > GetPipeConnections() override;
	// End Fluid Integrant Interface

protected:
	/** Radius of the pipes this connects too, used to approximate a volume. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment" )
	float mRadius;

	/** Fluid Box volume scale. WIll multiply the determined volume by this scalar ( useful if the object is physically smaller than its desired volume ) */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment" )
	float mFluidBoxVolumeScale;

	/** Fluid box belonging to this integrant */
	UPROPERTY( SaveGame )
	FFluidBox mFluidBox;

	/** Cached pipe connections from the blueprint. */
	UPROPERTY()
	TArray< class UFGPipeConnectionComponent* > mPipeConnections;

	/** 
	* Cached pipeline network fluidDescriptor ( used to ensure we don't run the same application code over and over if a descriptor is set but not changed 
	* Not all pipeline buildings and attachments care about their descriptor and will not implement the IFGFluidIntegrant call to set this, so null is quite likely.
	*/
	UPROPERTY()
	TSubclassOf< class UFGItemDescriptor > mCachedFluidDescriptor;


public:
	FORCEINLINE ~AFGBuildablePipelineAttachment() = default;
};

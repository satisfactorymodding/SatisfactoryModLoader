// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Resources/FGItemDescriptor.h"
#include "FGPipelineFlowIndicatorComponent.generated.h"


/**
 * Indicator used for the pipelines to show content and flow etc.
 */
UCLASS( Blueprintable, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGPipelineFlowIndicatorComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	// Begin ActorComponent
	virtual void BeginPlay() override;
	// End ActorComponent

	// Called from the owning pipe when the pipes fluid descriptor is set
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Pipes|Indicator" )
	void OnFluidDescriptorSet( TSubclassOf< UFGItemDescriptor > fluidDescriptor );

	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Pipes|Indicator" )
	void OnMaterialInstanceUpdated();

protected:
	/** Get the pipeline this is indicating status for. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Indicator" )
	class AFGBuildablePipeline* GetPipeline() const { return mPipeline; }

private:
	/** Pipeline we indicate status for. */
	UPROPERTY()
	class AFGBuildablePipeline* mPipeline;

public:
	FORCEINLINE ~UFGPipelineFlowIndicatorComponent() = default;
};

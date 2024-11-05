// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildableConveyorLift.h"
#include "InstancedSplineMeshComponent.h"
#include "FGConveyorInstanceSplineMesh.generated.h"

UCLASS()
class FACTORYGAME_API UFGConveyorInstancedSplineMeshComponent : public UInstancedSplineMeshComponent
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void ReportVisibility() const override;
	virtual bool ShouldReportVisibility() const override { return !IsRelevantToConveyorRenderer(); }

	// We mark this true once it has been reported.
	mutable bool bIsRelevantToConveyorRenderer;

	UPROPERTY()
	AFGBuildableConveyorBelt* mOwnerBelt;
	
public:
	FORCEINLINE bool IsRelevantToConveyorRenderer() const { return bIsRelevantToConveyorRenderer; }
	FORCEINLINE void SetRelevant(bool Value) const { bIsRelevantToConveyorRenderer = Value; }
	FORCEINLINE AFGBuildableConveyorBelt* GetOuterConveyorBeltActor() const { return mOwnerBelt; }
};

UCLASS()
class FACTORYGAME_API UFGConveyorLiftVisibilityMesh : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void ReportVisibility() const override;
	virtual bool ShouldReportVisibility() const override { return !IsRelevantToConveyorRenderer(); }

	// We mark this true once it has been reported.
	mutable bool bIsRelevantToConveyorRenderer;

	UPROPERTY()
	AFGBuildableConveyorLift* mOwnerLift;
	
	public:
	FORCEINLINE bool IsRelevantToConveyorRenderer() const { return bIsRelevantToConveyorRenderer; }
	FORCEINLINE void SetRelevant(bool Value) const { bIsRelevantToConveyorRenderer = Value; }
	FORCEINLINE AFGBuildableConveyorLift* GetOuterConveyorLift() const { return mOwnerLift; }
	
};

UCLASS()
class FACTORYGAME_API UFGConveyorBeltVisibilityMesh : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void ReportVisibility() const override;
	virtual bool ShouldReportVisibility() const override { return !IsRelevantToConveyorRenderer(); }

	// We mark this true once it has been reported.
	mutable bool bIsRelevantToConveyorRenderer;

	UPROPERTY()
	AFGBuildableConveyorBelt* mOwnerBelt;
	
public:
	FORCEINLINE bool IsRelevantToConveyorRenderer() const { return bIsRelevantToConveyorRenderer; }
	FORCEINLINE void SetRelevant(bool Value) const { bIsRelevantToConveyorRenderer = Value; }
	FORCEINLINE AFGBuildableConveyorBelt* GetOuterConveyorBeltActor() const { return mOwnerBelt; }
	
};

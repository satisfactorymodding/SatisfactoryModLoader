// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/InstancedStaticMesh.h"
#include "StaticMeshResources.h"
#include "RenderTransform.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "FGConveyorInstanceMeshBucket.generated.h"

class FACTORYGAME_API FConveyorBucketSceneProxy : public FInstancedStaticMeshSceneProxy
{
public:
	FConveyorBucketSceneProxy(UInstancedStaticMeshComponent* InComponent, ERHIFeatureLevel::Type InFeatureLevel);

	//Delete copy c-tor and assignment operator. Without it the compiler will generate them, which will cause issues with the FInstancedStaticMeshSceneProxy and deleted copy c-tors in its members like FRayTracingGeometry
	FConveyorBucketSceneProxy(const FConveyorBucketSceneProxy&) = delete;
	FConveyorBucketSceneProxy& operator=(const FConveyorBucketSceneProxy&) = delete;
	FConveyorBucketSceneProxy(FConveyorBucketSceneProxy&&) = delete;
	FConveyorBucketSceneProxy& operator=(FConveyorBucketSceneProxy&&) = delete;
	
	void UpdateInstanceData(const TArray<FRenderTransform>& CurrentFrame,const TArray<FRenderTransform>& PreviousFrame,int32 Offset, int32 Count);
};

UCLASS(ClassGroup = Rendering, meta = (BlueprintSpawnableComponent), Blueprintable)
class FACTORYGAME_API UFGConveyorInstanceMeshBucket : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

	UFGConveyorInstanceMeshBucket();

	virtual bool ShouldCreatePhysicsState() const override { return false; }
	virtual FPrimitiveSceneProxy* CreateStaticMeshSceneProxy(Nanite::FMaterialAudit& NaniteMaterials, bool bCreateNanite) override;
public:
	void Init(int32 Count);
	
	UFUNCTION(BlueprintCallable)
	void SetNumInstances(int32 Count)
	{
		mNumInstances = Count;
	}
	
	void CheckNANs();
	void SubmitToGPU(int32 StartID, int32 Count,const TArray<FRenderTransform>& CurrentPos,const TArray<FRenderTransform>& PrevPos);
	
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
protected:
	virtual bool ShouldIgnoreOcclusionChecks() const override { return true; }
public:
	UPROPERTY( EditDefaultsOnly )
	int32 mNumInstances;

	TArray<FMatrix> NewInstanceMatrices;
	TArray<FMatrix> OldInstanceMatrices;
	
	/* Ids for instances, needed for update transforms*/
	TArray<int32> mIds;

	bool bIsInitialized;
	
	FStaticMeshInstanceData NewRenderData;

	friend class AFGConveyorItemSubsystem;
	friend class FParallelUpdateGPUDatadateTask;

	bool bFirstRun = true;
};

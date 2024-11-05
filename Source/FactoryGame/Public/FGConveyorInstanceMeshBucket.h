// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/InstancedStaticMesh.h"
#include "StaticMeshResources.h"
#include "RenderTransform.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "FGConveyorInstanceMeshBucket.generated.h"

enum class UpdateCommand : uint8
{
	UC_None,
	UC_UploadToGPU,
	UC_Hide
};

class FACTORYGAME_API FConveyorBucketSceneProxy : public FInstancedStaticMeshSceneProxy
{
public:
	FConveyorBucketSceneProxy(UInstancedStaticMeshComponent* InComponent, ERHIFeatureLevel::Type InFeatureLevel);

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

	FORCEINLINE void PrepareInstanceUpdateBuffer( int32 Count )
	{
		{	// copy paste from epic's code, doesn't compile otherwise.
			InstanceUpdateCmdBuffer.Cmds.Empty(Count);
			InstanceUpdateCmdBuffer.NumCustomDataFloats = 0;
			InstanceUpdateCmdBuffer.NumAdds = 0;
			InstanceUpdateCmdBuffer.NumCustomFloatUpdates = 0;
			InstanceUpdateCmdBuffer.NumRemoves = 0;
		}
	
		InstanceUpdateCmdBuffer.Cmds.AddDefaulted(Count);
		InstanceUpdateCmdBuffer.NumUpdates = Count;
		InstanceUpdateCmdBuffer.NumEdits = Count;
	}
	
	FORCEINLINE void UpdateInstanceData(const int32 Id, const FMatrix& M,const FMatrix& PrevM)
	{
		auto& Entry = InstanceUpdateCmdBuffer.Cmds.GetData()[Id];
		Entry.InstanceIndex = Id;
		FMemory::Memcpy(&Entry.XForm,&M,sizeof(FMatrix));
		FMemory::Memcpy(&Entry.PreviousXForm,&PrevM,sizeof(FMatrix));
		Entry.Type = FInstanceUpdateCmdBuffer::Update;
	}
	
	UpdateCommand UpdateCommand = UpdateCommand::UC_None;
	
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

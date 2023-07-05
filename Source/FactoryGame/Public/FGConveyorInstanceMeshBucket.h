// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/InstancedStaticMesh.h"
#include "StaticMeshResources.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "FGConveyorInstanceMeshBucket.generated.h"

// 3x4 half float matrix to be used on the gpu, supports other types in case he platform doesn't support float16.
template<typename T>
struct FMatrixHalfFloat
{
public:
	T m[3][4];
	FMatrixHalfFloat(float Value[4][4])
	{
		m[0][0] = T(Value[0][0]);
		m[0][1] = T(Value[0][1]);
		m[0][2] = T(Value[0][2]);
		m[0][3] = T(Value[0][3]);
		
		m[1][0] = T(Value[1][0]);
		m[1][1] = T(Value[1][1]);
		m[1][2] = T(Value[1][2]);
		m[1][3] = T(Value[1][3]);

		m[2][0] = T(Value[2][0]);
		m[2][1] = T(Value[2][1]);
		m[2][2] = T(Value[2][2]);
		m[2][3] = T(Value[2][3]);
	}

	void Set(float Value[4][4])
	{
		m[0][0] = T(Value[0][0]);
		m[0][1] = T(Value[0][1]);
		m[0][2] = T(Value[0][2]);
		m[0][3] = T(Value[0][3]);
		
		m[1][0] = T(Value[1][0]);
		m[1][1] = T(Value[1][1]);
		m[1][2] = T(Value[1][2]);
		m[1][3] = T(Value[1][3]);
		
		m[2][0] = T(Value[2][0]);
		m[2][1] = T(Value[2][1]);
		m[2][2] = T(Value[2][2]);
		m[2][3] = T(Value[2][3]);
	}
	
	FMatrixHalfFloat()
	{
		Set( FTransform::Identity.ToMatrixNoScale().M);
	}
};

/**
 * 
 */
struct FRawTransformData
{
	MS_ALIGN( 16 ) float M[4][4] GCC_ALIGN(16);
	
	FRawTransformData()
	{
		FMemory::Memzero((uint8*)M[0], 16*sizeof(float));
	}
	
	// We bypass scale.
	void operator=( float Other[4][4] )
	{
		FMemory::Memcpy( &M, Other,sizeof(float) * 16 );
	}
};

enum class UpdateCommand : uint8
{
	UC_None,
	UC_UploadToGPU,
	UC_Hide
};

UCLASS(ClassGroup = Rendering, meta = (BlueprintSpawnableComponent), Blueprintable)
class FACTORYGAME_API UFGConveyorInstanceMeshBucket : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

	UFGConveyorInstanceMeshBucket();

	virtual bool ShouldCreatePhysicsState() const override { return false; }
	
public:
	void Init();
	
	UFUNCTION(BlueprintCallable)
	void SetNumInstances(int32 Count)
	{
		mNumInstances = Count;
	}

	void PrepareInstanceUpdateBuffer( int32 Count );
	void UpdateInstanceData(const int32 Id, const FMatrix& M,const FMatrix& PrevM);
	//void UpdateInstancesData();
	
	UpdateCommand UpdateCommand = UpdateCommand::UC_None;
	
	/* With the fast update version we are assuming the correct amount of instances are set and we are not adding or removing
	 * nor updating per instance custom data.
	 * All the safety checks, Add, Remove and cpu data updating has been stripped for performance sake. */
	void UpdateInstancesFast();

	void CheckNANs();
	void SubmitToGPU();
	
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
};

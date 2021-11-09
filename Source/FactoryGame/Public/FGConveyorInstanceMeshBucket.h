// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "FGConveyorInstanceMeshBucket.generated.h"

// 3x4 half float matrix to be used on the gpu, supports other types in case he platform doesn't support float16.
template<typename T>
struct FMatrixHalfFloat
{
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

UCLASS(ClassGroup = Rendering, meta = (BlueprintSpawnableComponent), Blueprintable)
class FACTORYGAME_API UFGConveyorInstanceMeshBucket : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

	UFGConveyorInstanceMeshBucket();

	virtual bool ShouldCreatePhysicsState() const override { return false; }
	
public:
	void Init();
	
	/* Submit transform directly to RT */
	void DirectUpdateInstance( );
	
	UFUNCTION(BlueprintCallable)
	void SetNumInstances(int32 Count) { mNumInstances = Count; }

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	
protected:
	// We need dynamic locations & buffers since we update them really often.
	virtual bool ShouldHaveDynamicTransformAndLocationBuffers() const override { return true; }
	virtual bool ShouldIgnoreOcclusionChecks() const override { return true; }
public:
	UPROPERTY( EditDefaultsOnly )
	int32 mNumInstances;

private:
	/* Transient location buffer to avoid memory allocation. */
	TArray<FVector4> mTransientPositionBuffer;

	/* Transient transform buffer to avoid memory allocation. */
	TArray<FMatrixHalfFloat<FFloat16>> mTransientTransformBuffer;
	
	/* Transient Transforms set by the conveyor renderer */
	//TArray<FTransform> mTransientTransforms;

	/* Transient Transforms set by the conveyor renderer */
	TArray<FRawTransformData> mRawTransientTransforms;

	bool bIsInitialized;

	friend class AFGConveyorItemSubsystem;
	friend class FParallelUpdateGPUDatadateTask;
};

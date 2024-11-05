// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGSignificanceInterface.h"
#include "FoliageType.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "FGCliffActor.generated.h"


struct FGCliffActorTask
{
	FAsyncTask<class FFGAsyncCliffGrassBuilderTask>* mTask;
	TWeakObjectPtr<class AFGCliffActor> mCliffActor;
};


UCLASS()
class FACTORYGAME_API AFGCliffActorManager : public AActor
{
	GENERATED_BODY()

	AFGCliffActorManager();
	
public:	
	static void EnqueueTask( UWorld* World, FAsyncTask<class FFGAsyncCliffGrassBuilderTask>* inAsyncTask, AFGCliffActor* inActor );

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TArray<FGCliffActorTask> mTasks;

	static AFGCliffActorManager* mStaticManager;
};

UCLASS()
class FACTORYGAME_API AFGCliffActor : public AActor, public IFGSignificanceInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGCliffActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override;

	/* Started on significance gain running on a timer.*/
	//UFUNCTION()
	//void CheckOnAsyncTasks();
	
public:
	FORCEINLINE UStaticMesh* GetStaticMesh() const { return mStaticMesh; }
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return mMeshComponent; }
	FORCEINLINE bool IsSignificant() const { return mIsSignificant; }
	
private:
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mMeshComponent;
	
	//TArray<FAsyncTask<class FFGAsyncCliffGrassBuilderTask>*> mAsyncTasks;

	bool mIsSignificant;

	//FTimerHandle mAsyncCheckHandle;

protected:
	/* Components generated on gain significance. */
	UPROPERTY( Transient, VisibleAnywhere )
	TArray< class UGrassInstancedStaticMeshComponent* > mGeneratedMeshComponent;

public:
	UPROPERTY( EditInstanceOnly, Category = "Setting" )
	UStaticMesh* mStaticMesh;
	
	UPROPERTY( EditInstanceOnly, Category = "Setting" )
	TArray< UFoliageType* > mFoliageTypes;

	UPROPERTY( EditInstanceOnly, Category = "Setting" )
	TMap< UFoliageType*, float > mFoliageTypesDensityMultiplier;
	
	/* Range multiplier for significance */
	UPROPERTY( EditInstanceOnly, Category = "Setting" )
	float mSignificanceRangeMultiplier;
	
#if WITH_EDITOR
	UFUNCTION( BlueprintCallable )
	static void ConvertStaticMeshActorToOnTopMesh( AActor* SelectedActor, FString& ResultMsg );

	UFUNCTION( BlueprintCallable )
	static void UpdateAssociatedCliffActorsAndReParent();

	UFUNCTION( CallInEditor, Category = "Debug")
	void DebugSpawn();

	UFUNCTION( CallInEditor, Category = "Debug")
	void ClearDebugSpawn();

	UFUNCTION( CallInEditor, Category = "Debug")
	void ForceUpdateMeshCPUAccess();	

	UFUNCTION( CallInEditor,Category = "Debug")
	void DebugDrawSignificanceRange();
	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif	
};

struct FFGCliffGrassWorker
{
	FFGCliffGrassWorker()
	{
		
	}
	
	FFGCliffGrassWorker(AFGCliffActor* inCliffActor, UFoliageType* inType,float inMultiplier, UGrassInstancedStaticMeshComponent* inHISMComponent );

	/* Input */
	TWeakObjectPtr<AFGCliffActor> mCliffActor;
	UFoliageType* mFoliageType;
	TWeakObjectPtr<class UGrassInstancedStaticMeshComponent> mInstanceComponent;
	TArray<uint32> mCachedIndices;
	TArray<FVector3f> mCachedVerts;
	float mFoliageTypesDensityMultiplier;
	TArray<FInstancedStaticMeshInstanceData> mInstanceData;
	/* Output */
	FStaticMeshInstanceData InstanceBuffer;
	TArray<struct FClusterNode> ClusterTree;
	int32 OutOcclusionLayerNum;
	
	void DoWork();
};



class FFGAsyncCliffGrassBuilderTask : public FNonAbandonableTask
{
public:
	FFGAsyncCliffGrassBuilderTask( FFGCliffGrassWorker* InWorker )
	{
		Builder = InWorker;
	}
	
	FFGCliffGrassWorker* Builder;
	
	void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT( FFGAsyncCliffGrassBuilderTask, STATGROUP_ThreadPoolAsyncTasks )		
    }
	~FFGAsyncCliffGrassBuilderTask();
};


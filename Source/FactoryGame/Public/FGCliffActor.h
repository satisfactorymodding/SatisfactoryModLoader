// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "FGSignificanceInterface.h"
#include "FoliageType.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "FGCliffActor.generated.h"

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
	UFUNCTION()
	void CheckOnAsyncTasks();
	
public:
	FORCEINLINE UStaticMesh* GetStaticMesh() const { return mStaticMesh; }
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return mMeshComponent; }
	
private:
	UPROPERTY()
	UStaticMeshComponent* mMeshComponent;
	
	TArray<FAsyncTask<class FFGAsyncCliffGrassBuilderTask>*> mAsyncTasks;

	bool mIsSignificant;

	FTimerHandle mAsyncCheckHandle;

protected:
	/* Components generated on gain significance. */
	UPROPERTY( Transient )
	TArray< class UHierarchicalInstancedStaticMeshComponent* > mGeneratedMeshComponent;

public:
	UPROPERTY( EditInstanceOnly, Category = "Setting" )
	UStaticMesh* mStaticMesh;
	
	UPROPERTY( EditInstanceOnly, Category = "Setting" )
	TArray< UFoliageType* > mFoliageTypes;

	/* Range multiplier for significance */
	UPROPERTY( EditInstanceOnly, Category = "Setting" )
	float mSignificanceRangeMultiplier;
	
#if WITH_EDITOR
	UFUNCTION( BlueprintCallable )
	static void ConvertStaticMeshActorToOnTopMesh( AActor* SelectedActor, FString& ResultMsg );
#endif	
};

struct FFGCliffGrassWorker
{
	FFGCliffGrassWorker()
	{
		
	}
	
	FFGCliffGrassWorker(AFGCliffActor* inCliffActor, UFoliageType* inType, UHierarchicalInstancedStaticMeshComponent* inHISMComponent ) :
	mCliffActor(inCliffActor),
	mFoliageType(inType),
	mInstanceComponent( inHISMComponent ),
	InstanceBuffer(GVertexElementTypeSupport.IsSupported(VET_Half2))
	{
	}
	
	/* Input */
	TWeakObjectPtr<AFGCliffActor> mCliffActor;
	UFoliageType* mFoliageType;
	TWeakObjectPtr<class UHierarchicalInstancedStaticMeshComponent> mInstanceComponent;

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


// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "FactoryGame.h"
#include "Components/SceneComponent.h"
#include "FGFactoryColoringTypes.h"
#include "FGOptimizationSettings.h"
#include "FGFactoryColoringTypes.h"
#include "FGFactoryLegInstanceManager.generated.h"


/**
 * Handles buildings legs instancing. Based on how the FGColorableInstanceManager works
 */
UCLASS( ClassGroup = FactoryGame )
class FACTORYGAME_API UFGFactoryLegInstanceManager : public USceneComponent
{
	GENERATED_BODY()
public:

	struct FInstanceHandle
	{
		FORCEINLINE bool IsInstanced() const
		{
			return HandleID >= 0;
		}

	private:
		friend UFGFactoryLegInstanceManager;

		int32 HandleID = INDEX_NONE;
	};


	// Begin AActorComponent interface
	virtual bool RequiresGameThreadEndOfFrameRecreate() const override { return true; }
	// End AActorComponent interface

	// Setup the necessary instance lists on our outer. Component must be registered before this is called.
	void SetupInstanceList( UStaticMesh* staticMesh, bool useAsOccluder = false, EDistanceCullCategory CullCategory = EDistanceCullCategory::FGDDC_NEVERCULL );

	// Functions to manage the instances handled by this class, setup must be called prior to using these.
	void ClearInstances();
	void AddInstance( const FTransform& transform, FInstanceHandle& handle );
	void RemoveInstance( FInstanceHandle& handle );

	FORCEINLINE EDistanceCullCategory GetCullCategory() { return mCullCategory; }

private:
	class UHierarchicalInstancedStaticMeshComponent* CreateHierarchicalInstancingComponent( class UStaticMesh* staticMesh, bool useAsOccluder, FVector2D& minMaxCullDistance );

private:
	UPROPERTY( EditAnywhere, Category = "UFGFactoryLegInstanceManager")
	class UHierarchicalInstancedStaticMeshComponent* mInstanceComponent;

	/** Handles from all the managed instances. */
	TArray< FInstanceHandle* > mHandles;

	EDistanceCullCategory mCullCategory;
};

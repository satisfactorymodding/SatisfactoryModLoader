// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "FactoryGame.h"
#include "Components/SceneComponent.h"
#include "BuildableColorSlotBase.h"
#include "FGOptimizationSettings.h"
#include "FGColoredInstanceManager.generated.h"


/**
 * Handles building instancing and coloring.
 */
UCLASS( ClassGroup = FactoryGame )
class FACTORYGAME_API UFGColoredInstanceManager : public USceneComponent
{
	GENERATED_BODY()
public:
	struct InstanceHandle
	{
		FORCEINLINE bool IsInstanced() const
		{
			return HandleID >= 0;
		}
	private:
		friend UFGColoredInstanceManager;

		int32 HandleID = INDEX_NONE;
		uint8 ColorIndex = UINT8_MAX;
	};

	// Begin AActorComponent interface
	virtual bool RequiresGameThreadEndOfFrameRecreate() const override { return true; }
	// End AActorComponent interface

	// Setup the necessary instance lists on our outer. Component must be registered before this is called.
	void SetupInstanceLists( UStaticMesh* staticMesh, bool makeSingleColor = false, bool useAsOccluder = false, EDistanceCullCategory CullCategory = EDistanceCullCategory::FGDDC_NEVERCULL );

	// Functions to manage the instances handled by this class, setup must be called prior to using these.
	void ClearInstances();
	void AddInstance( const FTransform& transform, InstanceHandle& handle, uint8 colorIndex );
	void RemoveInstance( InstanceHandle& handle );
	void MoveInstance( const FTransform& transform, InstanceHandle& handle, uint8 newColorIndex );

	FORCEINLINE EDistanceCullCategory GetCullCategory() { return mCullCategory; }

private:
	void UpdateMaterialColors();
	class UHierarchicalInstancedStaticMeshComponent* CreateHierarchicalInstancingComponent( class UStaticMesh* staticMesh, bool useAsOccluder, FVector2D& minMaxCullDistance );

private:
	/** If we are only using a single color we can skip creating a HISM for every color. */
	bool mSingleColorOnly = false;

	/**
	 * All instances managed, one instance list per indicator status.
	 * Since these need to be attached to an actor to be rendered, our outer is used for this purpose.
	 */
	UPROPERTY()
	class UHierarchicalInstancedStaticMeshComponent* mInstanceComponents[ BUILDABLE_COLORS_MAX_SLOTS ];

	/** Handles from all the managed indicators. */
	TArray< InstanceHandle* > mHandles[ BUILDABLE_COLORS_MAX_SLOTS ];

	EDistanceCullCategory mCullCategory;
};

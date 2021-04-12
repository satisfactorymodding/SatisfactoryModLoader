// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Buildables/FGBuildableFactory.h"
#include "Components/SceneComponent.h" //MODDING EDIT
#include "FGProductionIndicatorInstanceManager.generated.h"


/**
 * Instanced production indicator, used on factories to display their status.
 */
UCLASS( ClassGroup = FactoryGame )
class FACTORYGAME_API UFGProductionIndicatorInstanceManager : public USceneComponent
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
		friend UFGProductionIndicatorInstanceManager;

		int32 HandleID = INDEX_NONE;
		EProductionStatus Status = EProductionStatus::IS_NONE;
	};

	// Begin AActorComponent interface
	virtual bool RequiresGameThreadEndOfFrameRecreate() const override { return true; }
	// End AActorComponent interface

	// Setup the necessary instance lists on our outer. Component must be registered before this is called.
	void SetupInstanceLists( UStaticMesh* staticMesh );

	// Functions to manage the instances handled by this class, setup must be called prior to using these.
	void ClearInstances();
	void AddInstance( const FTransform& transform, InstanceHandle& handle, EProductionStatus status );
	void RemoveInstance( InstanceHandle& handle );
	void MoveInstance( const FTransform& transform, InstanceHandle& handle, EProductionStatus moveTo );
private:
	/**
	 * All instances managed, one instance list per indicator status.
	 * Since these need to be attached to an actor to be rendered, our outer is used for this purpose.
	 */
	//MODDING EDIT: cast enum classes to underlying types because it is an syntax error on everything except MSVC
	UPROPERTY()
	UHierarchicalInstancedStaticMeshComponent* mInstanceComponents[ (uint8) EProductionStatus::IS_MAX ];

	//MODDING EDIT: cast enum classes to underlying types because it is an syntax error on everything except MSVC
	/** Handles from all the managed indicators. */
	TArray< InstanceHandle* > mHandles[ (uint8) EProductionStatus::IS_MAX ];
};

//</CSS>

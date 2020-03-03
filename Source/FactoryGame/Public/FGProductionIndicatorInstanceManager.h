#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "UObject/Class.h"
//<CSS>
// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.


#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGProductionIndicatorInstanceManager.generated.h"


/**
* 
*/
UCLASS( ClassGroup = FactoryGame )
class FACTORYGAME_API UFGProductionIndicatorInstanceManager : public USceneComponent
{
	GENERATED_BODY()
public:

	struct InstanceHandle
	{
		FORCEINLINE bool isInstanced() const
		{
			return handleID >= 0;
		}
	private:
		int32 handleID = INDEX_NONE;
		EProductionStatus status = EProductionStatus::IS_NONE;
		friend UFGProductionIndicatorInstanceManager;
	};

	UFGProductionIndicatorInstanceManager();


	virtual void OnUnregister() override;
	virtual void OnRegister() override;

	void ClearInstances();

	void AddInstance( const FTransform& transform, InstanceHandle& handle, EProductionStatus status );
	void RemoveInstance( InstanceHandle& handle );
	void MoveInstance( const FTransform& transform, InstanceHandle& handle, EProductionStatus moveTo ); //[DavalliusA:Fri/15-02-2019] wish we could remove the need to send the transform, but didn't find a way to read it from the current instance, so let's send it for now. In worst case we can store it in the handle later... or something.

	//virtual bool RequiresGameThreadEndOfFrameUpdates() const override { return true; }
	virtual bool RequiresGameThreadEndOfFrameRecreate() const override { return true; }

	void SetupInstanceLists( UStaticMesh* staticMesh );
private:

	UPROPERTY()
	UHierarchicalInstancedStaticMeshComponent* mInstanceComponents[ EProductionStatus::IS_MAX ];
	TArray< InstanceHandle* > mHandles[ EProductionStatus::IS_MAX ];


public:
	FORCEINLINE ~UFGProductionIndicatorInstanceManager() = default;
};

//</CSS>
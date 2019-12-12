#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "UObject/Class.h"
//<CSS>
// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.


#include "FactoryGame.h"
#include "Components/SceneComponent.h"
#include "BuildableColorSlotBase.h"
#include "FGColoredInstanceManager.generated.h"

class UHierarchicalInstancedStaticMeshComponent;
class AFGBuildableSubsystem;

/**
*
*/
UCLASS( ClassGroup = FactoryGame )
class FACTORYGAME_API UFGColoredInstanceManager : public USceneComponent
{
	GENERATED_BODY()
public:
	UFGColoredInstanceManager();

	struct InstanceHandle
	{
		FORCEINLINE bool IsInstanced() const
		{
			return handleID >= 0;
		}
	private:
		int32 handleID = INDEX_NONE;
		uint8 colorIndex = UINT8_MAX;
		friend UFGColoredInstanceManager;
	};

	virtual void OnUnregister() override;
	virtual void OnRegister() override;

	void ClearInstances();

	void AddInstance( const FTransform& transform, InstanceHandle& handle, uint8 colorIndex );
	void RemoveInstance( InstanceHandle& handle );
	void MoveInstance( const FTransform& transform, InstanceHandle& handle, uint8 newColorIndex ); //[DavalliusA:Fri/15-02-2019] wish we could remove the need to send the transform, but didn't find a way to read it from the current instance, so let's send it for now. In worst case we can store it in the handle later... or something.

	virtual bool RequiresGameThreadEndOfFrameRecreate() const override { return true; }

	void SetupInstanceLists( UStaticMesh* staticMesh, bool makeCingleColor = false );

	void UpdateMaterialColors();

	UHierarchicalInstancedStaticMeshComponent* GetHierarchicalMesh( uint8 colorIndex );

	bool IsSingleColorOnly() { return mSingleColorOnly; }

	//[DavalliusA:Fri/22-02-2019] olny used for local quick reference. Don't need to be a property. Will be fetching color slot data from it when updating color slots.
	AFGBuildableSubsystem* mBuildableSubSystem = nullptr;
private:

	bool mSingleColorOnly = false;

	UPROPERTY()
	UHierarchicalInstancedStaticMeshComponent* mInstanceComponents[ BUILDABLE_COLORS_MAX_SLOTS ];

	TArray< InstanceHandle* > mHandles[ BUILDABLE_COLORS_MAX_SLOTS ];

};

//</CSS>
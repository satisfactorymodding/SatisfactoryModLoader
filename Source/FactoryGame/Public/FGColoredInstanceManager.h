// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "FactoryGame.h"
#include "Components/SceneComponent.h"
#include "FGFactoryColoringTypes.h"
#include "FGOptimizationSettings.h"
#include "FGFactoryColoringTypes.h"
#include "FGColoredInstanceManager.generated.h"





/**
 * Handles building instancing and coloring.
 */
UCLASS( ClassGroup = FactoryGame )
class FACTORYGAME_API UFGColoredInstanceManager : public USceneComponent
{
	GENERATED_BODY()
public:

	struct FInstanceHandle
	{
		FORCEINLINE bool IsInstanced() const
		{
			return HandleID >= 0;
		}

		FORCEINLINE int32 GetHandleID() const { return HandleID; }
		
		FORCEINLINE uint8 GetColorIndex( ) { return ColorIndex; }
		FORCEINLINE void SetColorIndex( uint8 colorIndex ) { ColorIndex = colorIndex; }

		/* Set whole custom data for the component. */
		void SetCustomDataArray( const TArray<float>& colorDataArray )
		{
			CustomData.SetNumZeroed( 20 );
			for( int32 i = 0; i < colorDataArray.Num(); ++i )
			{
				CustomData[ i ] = colorDataArray[ i ];
			}
		}

		/* Set specific value by id. */
		void SetCustomDataById( const int32 id, float value )
		{
			CustomData[ id ] = value;
		}

		TArray<float> GetCustomData() const
		{
			return CustomData;
		}

	private:
		friend UFGColoredInstanceManager;

		TArray<float> CustomData;
		int32 HandleID = INDEX_NONE;
		uint8 ColorIndex = UINT8_MAX;
	};


	// Begin AActorComponent interface
	virtual bool RequiresGameThreadEndOfFrameRecreate() const override { return true; }
	// End AActorComponent interface

	// Setup the necessary instance lists on our outer. Component must be registered before this is called.
	void SetupInstanceList( UStaticMeshComponent* sourceStaticMeshComponent, uint8 numCustomDataFloats, bool useAsOccluder = false, EDistanceCullCategory CullCategory = EDistanceCullCategory::FGDDC_NEVERCULL );

	// Functions to manage the instances handled by this class, setup must be called prior to using these.
	void ClearInstances();
	void AddInstance( const FTransform& transform, FInstanceHandle& handle, uint8 colorIndex );
	void RemoveInstance( FInstanceHandle& handle );

	FORCEINLINE EDistanceCullCategory GetCullCategory() { return mCullCategory; }

	void UpdateTransformForInstance( const FTransform& newTransform, int32 handleId );

	/** Update the custom data for a single mesh instance */
	void UpdateColorForInstance( uint8 colorIndex, FInstanceHandle& handle );

	/** Sets the color data instance array on a handle. Will call update to actually apply the custom data after setting */
	void SetColorForInstanceFromDataArray( const TArray<float>& colorDataArray, FInstanceHandle& handle, bool updateColor = true );

	/** Set specifically defined data array. Useful for edge cases like signs where the colors are driven elsewhere */
	void SetUserDefinedData( TArray< float > userData, FInstanceHandle& handle );

	/** Specifically sets the Data for HasPower from the data array */
	void SetHasPowerData( float newHasPower, FInstanceHandle& handle );

	/** Update color from Custom Data Array actual logic */
	void UpdateColorForInstanceFromDataArray( FInstanceHandle& handle );

	/** Reapply all material custom data to each mesh instance */
	void UpdateMaterialColors();

private:

	//class UHierarchicalInstancedStaticMeshComponent* CreateHierarchicalInstancingComponent( class UStaticMesh* staticMesh, uint8 numCustomData, bool useAsOccluder, FVector2D& minMaxCullDistance );
	class UHierarchicalInstancedStaticMeshComponent* CreateHierarchicalInstancingComponent( class UStaticMesh* staticMesh,TArray<class UMaterialInterface*> overridenMaterials, uint8 numCustomData, bool useAsOccluder, FVector2D& minMaxCullDistance );
private:
	UPROPERTY( EditAnywhere, Category = "UFGColoredInstanceManager")
	class UHierarchicalInstancedStaticMeshComponent* mInstanceComponent;


	/** Handles from all the managed instances. */
	TArray< FInstanceHandle* > mHandles;

	EDistanceCullCategory mCullCategory;

	uint8 mCachedNumCustomData;
};

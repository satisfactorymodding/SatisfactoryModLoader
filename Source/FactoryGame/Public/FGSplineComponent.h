// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "FGInstancedSplineMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "Components/SplineMeshComponent.h"
#include "UObject/Class.h"

#include "Components/SplineComponent.h"
#include "FGSplineComponent.generated.h"


/**
 * A spline with spline meshes combined in the same component.
 * With this you can create a spline that automatically places meshes along itself.
 *
 * @note Only use the provided AddSplinePointFromData, RemoveSplinePointData and ClearSplinePointsData to add/remove points.
 */
UCLASS( ClassGroup = (Utility), ShowCategories = ( Collision ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGSplineComponent : public USplineComponent
{
	GENERATED_BODY()
	
public:
	UFGSplineComponent();

	/** Set the override material to use on the spline meshes, otherwise the default is used. */
	UFUNCTION( BlueprintCallable, Category = "Spline" )
	void SetOverrideMaterial( class UMaterialInterface* material );

	/** Update the spline meshes to fit on the spline. */
	UFUNCTION( BlueprintCallable, Category = "Spline" )
	void UpdateSplineMeshes();

	/** Draw the spline using debug lines. */
	UFUNCTION( BlueprintCallable, Category = "Debug" )
	void DrawDebugSpline( const FColor& color1, const FColor& color2, float thickness = 0.0f ) const;

	/** Get the number of segments this spline is made up of. */
	int32 GetNumberOfMeshes() const;

	/** @return The mesh at index; returns nullptr if this is instanced. */
	class USplineMeshComponent* GetMesh( int32 index ) const;

	/** @return The instanced mesh at index; returns nullptr if this is not instanced. */
	class UFGInstancedSplineMeshComponent* GetInstancedMesh() const;

	/** Gives you the meshes in this spline */
	void SetVectorParameterOnInstancedMeshMaterials( FName parameterName, FVector inVector );

	/** @return true if this spline uses instanced spline meshes. */
	FORCEINLINE bool UseInstancing() const { return mUseInstancing; }

	/** If we should try to use instancing or not when using spline meshes */
	void SetUseInstancing( bool useInstancing );

	/** If we set this to true, then we render our spline in a addition pass with custom depth */
	void SetAdditionalCustomDepthPass( bool enable );

	int32 GetNumberOfCollisionShapes() const { return mSplineCollisionComponents.Num(); }
	class UShapeComponent* GetCollisionShapeAt( int32 index ) const { return mSplineCollisionComponents[ index ]; }

private:
	/** Generate the box corresponding to collision index idx */
	void GenerateCollisionIdx( int32 idx, float splineLength, int32 numCollisions );

	/** Place box collisions along the spline. */
	void GenerateSplineCollisions();

	/** Create a basic setup of a UFGInstancedSplineMeshComponent that's shared between custom depth mesh and normal mesh */
	class UFGInstancedSplineMeshComponent* CreateInstancedSplineMeshComponent();

	/** Create a basic setup of a spline mesh component that's shared between custom depth mesh and normal mesh */
	class USplineMeshComponent* CreateSplineMeshComponent();

public:
	/** The mesh to repeat on curved sections. */
	UPROPERTY( EditDefaultsOnly, Category = "Mesh" )
	class UStaticMesh* mSplineMesh;

	/** The size of each spline mesh. */
	UPROPERTY( EditDefaultsOnly, Category = "Mesh" )
	float mSplineMeshLength;

	//@todo Rewrite collisions to use the spline collisions. These do not support instancing yet.
	//      Look at how epic cooks the collisions for spline meshes and make use of that for the instanced spline mesh
	//		to create the physx shapes for the whole spline.

	/** Spacing between the collision components. */
	UPROPERTY( EditDefaultsOnly, Category = "Collision|Generated" )
	bool mGenerateCollisions;

	/** Spacing between the collision components. */
	UPROPERTY( EditDefaultsOnly, Category = "Collision|Generated", meta = ( EditCondition = mGenerateCollisions ) )
	float mCollisionSpacing;

	/** Extent of the collision components. X is forward. */
	UPROPERTY( EditDefaultsOnly, Category = "Collision|Generated", meta = ( EditCondition = mGenerateCollisions ) )
	FVector mCollisionExtent;

	/** Offset of the collision components. X is forward. */
	UPROPERTY( EditDefaultsOnly, Category = "Collision|Generated", meta = ( EditCondition = mGenerateCollisions ) )
	FVector mCollisionOffset;

private:
	/** The cached material, we cache this as the number of meshes grow/shrink as we drag the conveyor belt. */
	UPROPERTY()
	class UMaterialInterface* mOverrideMaterial;

	/** Whether to use instancing or not. */
	UPROPERTY()
	bool mUseInstancing;

	/** If true, then we will render custom depth but not in main pass */
	bool mAdditionalCustomDepthPass;

	/** The meshes that make up the spline. */
	UPROPERTY()
	TArray< class USplineMeshComponent* > mSplineMeshComponents;
	
	/** If we have enabled custom depth pass, then we store the custom depth spline meshes here */
	UPROPERTY()
	TArray< class USplineMeshComponent* > mCustomDepthSplineMeshComponents;

	/** The meshes that make up the spline when instanced. */
	UPROPERTY()
	class UFGInstancedSplineMeshComponent* mSplineMeshInstances;
	
	/** If we have enabled custom depth pass, this will be non-null */
	UPROPERTY()
	class UFGInstancedSplineMeshComponent* mCustomDepthSplineMeshInstances;

	/** The collisions that make up the spline. */
	UPROPERTY()
	TArray< class UShapeComponent* > mSplineCollisionComponents;

public:
	FORCEINLINE ~UFGSplineComponent() = default;
};

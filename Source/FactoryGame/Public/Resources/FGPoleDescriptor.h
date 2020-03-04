// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildingDescriptor.h"
#include "FGPoleDescriptor.generated.h"

/**
 * Defines a pole height.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPoleHeightMesh
{
	GENERATED_BODY()
public:
	FPoleHeightMesh() : Mesh( nullptr ), Height( 0.0f ) {}
public:
	/** Mesh for the current pole height. */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* Mesh;

	/** Pole height for the current mesh. */
	UPROPERTY( EditDefaultsOnly )
	float Height;

public:
	FORCEINLINE ~FPoleHeightMesh() = default;
};

/**
 * Descriptors for poles defined by a set of meshes.
 */
UCLASS()
class FACTORYGAME_API UFGPoleDescriptor : public UFGBuildingDescriptor
{
	GENERATED_BODY()
public:
	/**
	 * Get the heights for this pole.
	 */
	UFUNCTION( BlueprintPure, Category = "Item|Building|Pole" )
	static void GetHeightMeshes( TSubclassOf< UFGPoleDescriptor > inClass, TArray< FPoleHeightMesh >& out_heightMeshes );

	/** Get the mesh for the given height (closest match). */
	static FPoleHeightMesh FindBestHeightMesh( TSubclassOf< UFGPoleDescriptor > inClass, float height );

	/** Get the number of heights this pole support. */
	static int32 NumHeightMeshes( TSubclassOf< UFGPoleDescriptor > inClass );

	/** Read only accessors */
	static FORCEINLINE const FName& GetPoleMeshComponentTag(){ return mPoleMeshComponentTag; }
	static FORCEINLINE const FName& GetPoleHeightComponentTag(){ return mPoleHeightComponentTag; }
	static FORCEINLINE const FName& GetPoleTopMeshComponentTag(){ return mPoleTopMeshComponentTag; } //[DavalliusA:Wed/27-11-2019] used for when the top part of the pole is separate from the bottom
protected:
	/** Array with meshes and their heights for the pole. */
	UPROPERTY( EditDefaultsOnly, Category = "Pole", Meta = (NoAutoJSON = true) )
	TArray< FPoleHeightMesh > mHeightMeshes;
private:
	/** Helper to find the pole mesh component. */
	static FName mPoleMeshComponentTag;

	/** Helper to find the pole mesh component. */
	static FName mPoleHeightComponentTag;

	/** Helper to find the pole top mesh component. */
	static FName mPoleTopMeshComponentTag;

public:
	FORCEINLINE ~UFGPoleDescriptor() = default;
};

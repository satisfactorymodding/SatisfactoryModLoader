// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "FGConveyorItemRenderTargetWriter.generated.h"

UCLASS()
class FACTORYGAME_API UFGConveyorItemInstanceComponent : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

	virtual FBoxSphereBounds CalcBounds(const FTransform& BoundTransform) const override;
	virtual bool ShouldCreatePhysicsState() const override 	{ return false; }
	
public:
	void UpdateCustomBounds( const TArray<FTransform>& InstanceLocations, int32 StartIndex, int32 EndIndex ); 	

	void UpdateRenderState_internal();

	bool ShouldUpdateRenderState() const { return bShouldUpdateRenderState; }

	/* Getter needed for debug drawing. */
	FBoxSphereBounds GetCustomBounds() const {return mCustomBounds; }
	
private:
	FBoxSphereBounds mCustomBounds;

	bool bShouldUpdateRenderState;
};


/* Class holding helper functions for writing the texture instance buffers for the conveyor renderer systems. */
class FACTORYGAME_API FGConveyorItemRendererWriter
{
public:
	static void SetupBuffer( UTexture2D*& OutBufferTexture, TArray<uint8>& CPUDataBuffer, EPixelFormat Format, int32 SizeX, int32 SizeY, FName BufferName );

	static void ResizeBuffer( UTexture2D*& OutBufferTexture, TArray<uint8>& CPUDataBuffer, int32 SizeX, int32 SizeY, FName BufferName );

	static void FlushBuffer( UTexture2D*& OutBufferTexture, TArray<uint8>& CPUDataBuffer, FVector4 DefaultValue, bool bWriteToTexture2D );
	
	static SIZE_T GetBPPSize( EPixelFormat Format )
	{
		switch (Format)
		{
		case EPixelFormat::PF_B8G8R8A8:
			return sizeof( UINT8 );

		case EPixelFormat::PF_A16B16G16R16:
			return sizeof( UINT16 );

		case EPixelFormat::PF_A32B32G32R32F:
			return sizeof( float );

		default:
			// UNSUPPORTED
			check(false);
			return -1;
		} 
	}
	
	/* Pack values in to the assigned buffer, texture result depends on pixel format
	* @Param-in float valueX - 					Value for channel
	* @Param-in float valueY - 					Value for channel
	* @Param-in float valueZ - 					Value for channel
	* @Param-in float valueW - 					Value for channel
	* @Param-in TArray<uint8> &TargetBuffer - 	Target array
	* @Param-in int32 index - 					Target index in the buffer array.
	* @Param-in int32 components - 				The number of components the pixel format uses,
	* 											4 : 8 bits, 8 : 16 bits etc. */
	static void PackValue( float valueX, float valueY, float valueZ, float valueW, TArray< uint8 > &TargetBuffer, int32 index, int32 components );

	static int32 GetNumComponentsByFormat( EPixelFormat Format )
	{
		switch (Format)
		{
			case EPixelFormat::PF_B8G8R8A8:
				return 4;

			case EPixelFormat::PF_A16B16G16R16:
				return 8;

			case EPixelFormat::PF_A32B32G32R32F:
				return 16;

			default:
				// UNSUPPORTED
				check(false);
				return -1;
		}
	}	
};


/*	Holds the material instance that has the static flag enabled for texture based conveyor instancing */
UCLASS()
class FACTORYGAME_API UFGConveyorItemUserData : public UAssetUserData
{
	GENERATED_BODY()
public:
	UMaterialInterface* GetConveyorInstance() const 	{ return mConveyorInstance; }
	UMaterialInterface* GetMidConveyorInstance() const 	{ return mMidConveyorInstance; }
	UMaterialInterface* GetFarConveyorInstance() const 	{ return mFarConveyorInstance; }

private:
	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mConveyorInstance;

	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mMidConveyorInstance;

	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mFarConveyorInstance;
};
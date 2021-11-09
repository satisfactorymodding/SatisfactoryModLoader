// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildableSignBase.h"
#include "FGSignPixelInstanceManager.h"
#include "FGBuildablePixelSign.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePixelSign : public AFGBuildableSignBase
{
	GENERATED_BODY()

public:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End AActor Interface

	virtual bool IsColorApplicationDeferred() override { return true; }
	virtual bool CanApplyDeferredColorToBuildable( FVector hitLocation, FVector hitNormal, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController );
	virtual void ApplyDeferredColorToBuildable( FVector hitLocation, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController );

	FORCEINLINE FVector2D GetPixelDimensions() const { return mPixelDimensions; }
	FORCEINLINE float GetPixelSize() const { return mPixelSize; }
	FORCEINLINE UStaticMesh* GetPixelMesh() const { return mPixelMesh; }
	FORCEINLINE int32 GetLinearSize() const {return mPixelDimensions.X * mPixelDimensions.Y; }

	bool ShouldSave_Implementation() const override;

 private:
	int32 GetIndexOfHitPixel( FVector hitLocation );
	void SetPixelColor( int32 pixelIndex, FLinearColor& color );
	FLinearColor GetColorOfPixel( int32 pixelIndex );

protected:
	friend class AFGSignSubsystem;
	friend class UFGSignPixelInstanceManager;

	UFGSignPixelInstanceManager::FSignHandle mSignHandle;

	UPROPERTY()
	UFGSignPixelInstanceManager* mPixelInstanceManager;

	UPROPERTY( SaveGame )
	TArray< uint8 > mColorArray;

	// The number of pixels X/Y on this pixel sign
	UPROPERTY( EditDefaultsOnly, Category = "Pixel Sign" )
	FVector2D mPixelDimensions;

	// Sqaure size of the Pixel in World Units
	UPROPERTY( EditDefaultsOnly, Category = "Pixel Sign" )
	float mPixelSize;

	// The Mesh to be used as the pixel (origin should be at the center of the mesh)
	UPROPERTY( EditDefaultsOnly, Category = "Pixel Sign" )
	UStaticMesh* mPixelMesh;

	
};

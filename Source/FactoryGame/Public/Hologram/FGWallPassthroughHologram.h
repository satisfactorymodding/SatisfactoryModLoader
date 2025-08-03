// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGWallPassthroughHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGWallPassthroughHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGWallPassthroughHologram();
	
	virtual void BeginPlay() override;

	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void PostHologramPlacement( const FHitResult& hitResult, bool callForChildren ) override;
	virtual void InitializeClearanceData() override;
	virtual void GetClearanceData( TArray<const FFGClearanceData*>& out_ClearanceData ) const override;

	virtual void ConfigureActor( AFGBuildable* inBuildable ) const override;

private:
	float mSnappedDepth;

	float mConnectionDepthOffset;

	UPROPERTY()
	UStaticMeshComponent* mConnectionMeshes[ 2 ];

	FFGClearanceData mConnectionMeshClearanceData[ 2 ];
};

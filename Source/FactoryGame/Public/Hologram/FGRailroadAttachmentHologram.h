// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
#include "FGRailroadAttachmentHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGRailroadAttachmentHologram : public AFGBuildableHologram
{
	GENERATED_BODY()

public:
	AFGRailroadAttachmentHologram();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void PostHologramPlacement( const FHitResult& hitResult, bool callForChildren ) override;
	virtual void ConfigureComponents( AFGBuildable* inBuildable ) const override;
	virtual void GetIgnoredClearanceActors( TSet< AActor* >& ignoredActors ) const override;
	// End AFGHologram Interface

private:
	UPROPERTY( CustomSerialization )
	class UFGRailroadTrackConnectionComponent* mConnection;
	
	UPROPERTY( CustomSerialization )
	class UFGRailroadTrackConnectionComponent* mSnappedConnection;

	FTransform mRelativeConnectionTransform;

	UPROPERTY( EditDefaultsOnly, Category = "Railroad Attachment" )
	bool mMustSnap;
};

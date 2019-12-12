// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGConveyorAttachmentHologram.h"
#include "FGAttachmentSplitterHologram.generated.h"

/**
 * Adds up/downgrade for splitters.
 */
UCLASS()
class FACTORYGAME_API AFGAttachmentSplitterHologram : public AFGConveyorAttachmentHologram
{
	GENERATED_BODY()
public:
	AFGAttachmentSplitterHologram();

	// Begin AFGHologram Interface
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual bool MultiStepPlacement() override;
	virtual AActor* GetUpgradedActor() const override;
	// End AFGHologram Interface

protected:
	// Begin AFGBuildableHologram Interface
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram Interface

private:
	/** If we're upgrading another actor. */
	UPROPERTY()
	class AFGBuildableAttachmentSplitter* mUpgradedSplitter;

	/** Used when upgrading. */
	UPROPERTY()
	TArray< UFGFactoryConnectionComponent* > mSnappedConnectionComponents;
};

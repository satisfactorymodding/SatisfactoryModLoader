// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGPassthroughHologram.h"
#include "FGPassthroughPipeBaseHologram.generated.h"


UCLASS()
class FACTORYGAME_API AFGPassthroughPipeBaseHologram : public AFGPassthroughHologram
{
	GENERATED_BODY()
public:
	AFGPassthroughPipeBaseHologram();
	
	// Begin AFGHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGHologram interface
protected:
	virtual void RebuildMeshesAndUpdateClearance() override;
};

UCLASS()
class FACTORYGAME_API AFGPassthroughPipeHyperHologram : public AFGPassthroughPipeBaseHologram
{
	GENERATED_BODY()
};

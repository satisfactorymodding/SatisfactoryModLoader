#pragma once
#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGPipeAttachmentHologram.h"
#include "FGPipeHyperAttachmentHologram.generated.h"

UCLASS( Blueprintable )
class FACTORYGAME_API AFGPipeHyperAttachmentHologram : public AFGPipeAttachmentHologram
{
	GENERATED_BODY()
public:
	AFGPipeHyperAttachmentHologram();
	
	//Begin AFGHologram
	virtual void ConfigureComponents(AFGBuildable* inBuildable) const override;
	virtual void CheckValidPlacement() override;
	//End AFGHologram

protected:
	/** Length of the pipe split to make to accomodate for this attachment */
	UPROPERTY(EditDefaultsOnly, Category = "Pipe Attachment")
	float mPipeSpliceLength;

	/** Minimum length of the remnant pipe piece after the pipeline has been split */
	UPROPERTY(EditDefaultsOnly, Category = "Pipe Attachment")
	float mMinimumPipeSplitRemnantLength;
};
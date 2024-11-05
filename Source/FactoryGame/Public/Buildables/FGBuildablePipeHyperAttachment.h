#pragma once
#include "CoreMinimal.h"
#include "FGBuildableFactory.h"
#include "FGPipeHyperAttachmentSnapTargetInterface.h"
#include "FGBuildablePipeHyperAttachment.generated.h"

class UFGPipeConnectionComponentBase;

UCLASS( Abstract )
class FACTORYGAME_API AFGBuildablePipeHyperAttachment : public AFGBuildableFactory, public IFGPipeHyperAttachmentSnapTargetInterface
{
	GENERATED_BODY()
public:
	AFGBuildablePipeHyperAttachment();

	//Begin AFGBuildable
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled ) const override;
	//End AFGBuildable
protected:
	/** Length of the attachment across Connection0 and Connection1, used for slicing logic and returns calculation */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Pipe Hyper" )
	float mAttachmentLength;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Pipe Hyper" )
	UFGPipeConnectionComponentBase* mConnection0;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Pipe Hyper" )
	UFGPipeConnectionComponentBase* mConnection1;

	UPROPERTY( VisibleAnywhere, SaveGame, Category = "Pipe Hyper" )
	TSubclassOf<UFGRecipe> mBuiltWithPipelineRecipe;

	UPROPERTY( VisibleAnywhere, SaveGame, Category = "Pipe Hyper" )
	int32 mBuiltWithPipelineCostMultiplier;
public:
	FORCEINLINE float GetAttachmentLength() const { return mAttachmentLength; }
	
	/** @return The connections, safe to assume its always valid. */
	FORCEINLINE UFGPipeConnectionComponentBase* GetConnection0() const { return mConnection0; }
	FORCEINLINE UFGPipeConnectionComponentBase* GetConnection1() const { return mConnection1; }

	/** @return the recipe that the replaced pipeline segment had, if valid the resources for it will be returned upon dismantle */
	FORCEINLINE TSubclassOf<UFGRecipe> GetBuiltWithPipelineRecipe() const { return mBuiltWithPipelineRecipe; }
	FORCEINLINE void SetBuiltWithPipelineRecipe(TSubclassOf<UFGRecipe> newRecipe) { mBuiltWithPipelineRecipe = newRecipe; }

	FORCEINLINE int32 GetBuiltWithPipelineCostMultiplier() const { return mBuiltWithPipelineCostMultiplier; }
	FORCEINLINE void SetBuiltWithPipelineCostMultiplier(int32 newMultiplier) { mBuiltWithPipelineCostMultiplier = newMultiplier; }
};

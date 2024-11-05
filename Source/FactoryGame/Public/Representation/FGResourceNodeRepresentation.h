// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGActorRepresentation.h"
#include "FGResourceNodeRepresentation.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGResourceNodeRepresentation : public UFGActorRepresentation
{
	GENERATED_BODY()
public:
	UFGResourceNodeRepresentation();

	// Begin UFGActorRepresentation interface
	virtual void SetupActorRepresentation( AActor* realActor, bool isLocal, float lifeSpan ) override;
	virtual UMaterialInterface* GetRepresentationCompassMaterial() const override;
	virtual float GetCompassHeightAlignment() const override;
	virtual bool NeedsDynamicCompassRepresentationText() const override;
	virtual FText GetDynamicCompassRepresentationText(APlayerController* ownerPlayerController, float distanceToPlayer) const override;
	virtual bool NeedsDynamicCompassRepresentationScale() const override;
	virtual float CalculateCompassRepresentationScale(APlayerController* ownerPlayerController, float distanceToPlayer) const override;
	virtual void UpdateRepresentationCompassMaterial(UMaterialInstanceDynamic* compassMaterialInstance, APlayerController* ownerPlayerController) const override;
	virtual UMaterialInterface* GetRepresentationCompassEffectMaterial() const override;
	virtual FVector2f GetRepresentationCompassEffectSize() const override;
	virtual bool UpdateRepresentationCompassEffectMaterial(UMaterialInstanceDynamic* compassMaterialInstance, APlayerController* ownerPlayerController, float distanceToPlayer, float totalTime) override;
	virtual bool IsImportantCompassRepresentation() const override;
	virtual bool GetShouldShowOnMap() const override;
	// End UFGActorRepresentation interface
	
	void SetupResourceNodeRepresentation( class AFGResourceNodeBase* resourceNode );

	UFUNCTION( BlueprintPure, Category=Representation )
	class AFGResourceNodeBase* GetResourceNode() const { return mResourceNode; }

	UFUNCTION( BlueprintPure, Category=Representation )
	bool IsCluster() const;
	
	UFUNCTION( BlueprintPure, Category=Representation )
	bool IsOccupied() const;

	UPROPERTY()
	class AFGResourceNodeBase* mResourceNode;

	/** How many times have an actor representation with the underlying resource node been added by a radar scan. Used to keep track of when we can remove this representation */
	int32 mScanCount{0};
	/** Is this representating a cluster of nodes */ 
	bool mIsCluster{false};
	/** Is the node or cluster this represents claimed or not. Only used on compass when mResourceNode is invalid */ 
	bool mIsOccupied{false};
	/** True if this resource node representation was created by the resource scanner */
	bool mIsScannerOwned{false};
};

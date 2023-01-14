// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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

	virtual void SetupActorRepresentation( AActor* realActor, bool isLocal, float lifeSpan ) override;
	
	void SetupResourceNodeRepresentation( class AFGResourceNodeBase* resourceNode );

	/* We don't want to replicate this. The information is replicated somewhere else and then the representation is added locally */
	virtual bool IsSupportedForNetworking() const override { return false; }

	UFUNCTION( BlueprintPure, Category=Representation )
	class AFGResourceNodeBase* GetResourceNode() const { return mResourceNode; }

	UFUNCTION( BlueprintPure, Category=Representation )
	bool IsCluster() const;
	
	UFUNCTION( BlueprintPure, Category=Representation )
	bool IsOccupied() const;

	UPROPERTY()
	class AFGResourceNodeBase* mResourceNode;

	/** How many times have an actor representation with the underlying resource node been added by a radar scan. Used to keep track of when we can remove this representation */
	int32 mScanCount = 0;

	/** Is this representating a cluster of nodes */ 
	bool mIsCluster = false;

	/** Is the node or cluster this represents claimed or not. Only used on compass when mResourceNode is invalid */ 
	bool mIsOccupied = false;
};

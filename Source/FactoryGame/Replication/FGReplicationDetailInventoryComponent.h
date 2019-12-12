// Copyright 2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "Components/ActorComponent.h"
#include "FGReplicationDetailInventoryComponent.generated.h"

/**
* @todo: snutt write documentation you lazy piece of shit [<+1 Upvote> (Username: Dylan)]
**/
UCLASS()
class FACTORYGAME_API UFGReplicationDetailInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFGReplicationDetailInventoryComponent();

	void SetMainInventoryComponent( class UFGInventoryComponent* inventoryComponent );
	void SetReplicationInventoryComponent( class UFGInventoryComponent* inventoryComponent );

	/** Returns the active inventory component */
	FORCEINLINE class UFGInventoryComponent* GetActiveInventoryComponent() const { return mActiveInventoryComponent; }

protected:
	class UFGInventoryComponent* mActiveInventoryComponent;

	class UFGInventoryComponent* mMainInventoryComponent;
	class UFGInventoryComponent* mReplicationInventoryComponent;

	class AFGReplicationDetailActor* mReplicationDetailActor;
};

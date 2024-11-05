// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGBuildableCheatItemSpawner.generated.h"

UCLASS()
class FACTORYGAME_API AFGBuildableCheatItemSpawner : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildableCheatItemSpawner();
	
	// Begin AActor
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	// End AActor

	// Begin AFGBuildable
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual void Factory_Tick(float dt) override;
	virtual bool Factory_PeekOutput_Implementation(const UFGFactoryConnectionComponent* connection, TArray<FInventoryItem>& out_items, TSubclassOf<UFGItemDescriptor> type) const override;
	virtual bool Factory_GrabOutput_Implementation(UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf<UFGItemDescriptor> type) override;
	// End AFGBuildable

	/** Returns the current item rate (items/s produced) over the last period */
	UFUNCTION( BlueprintPure, Category = "Cheat Item Spawner" )
	FORCEINLINE float GetCurrentItemRate() const { return mCurrentItemRate; }

	/** Returns the total amount of items spawned */
	UFUNCTION( BlueprintPure, Category = "Cheat Item Spawner" )
	FORCEINLINE int32 GetTotalItemsSpawned() const { return mTotalItemsSpawned; }

	/** Returns the item descriptor currently set to be spawned */
	UFUNCTION( BlueprintPure, Category = "Cheat Item Spawner" )
	FORCEINLINE TSubclassOf<UFGItemDescriptor> GetItemDescriptor() const { return mItemDescriptor; }

	/** Returns the current item rate limit. */
	UFUNCTION( BlueprintPure, Category = "Cheat Item Spawner" )
	FORCEINLINE float GetItemRateLimit() const { return mItemRateLimit; }
	
	/** Updates the item descriptor class produced by this buildable */
	UFUNCTION( BlueprintCallable, Category = "Cheat Item Spawner" )
	void SetItemDescriptor( TSubclassOf<UFGItemDescriptor> itemDescriptor );

	/** Updates the item rate limit on the spawner. */
	UFUNCTION( BlueprintCallable, Category = "Cheat Item Spawner" )
	void SetItemRateLimit( float newItemRateLimit );

protected:
	/** Time interval for a single period of history */
	UPROPERTY( EditDefaultsOnly, Category = "Cheat Item Spawner" )
	float mItemRatePeriod;

	/** Max items to output per minute. */
	UPROPERTY( SaveGame, Replicated )
	float mItemRateLimit;

	/** Item descriptor that we are spawning */
	UPROPERTY( SaveGame, Replicated )
	TSubclassOf<UFGItemDescriptor> mItemDescriptor;

	/** Total amount of items spawned */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	int32 mTotalItemsSpawned;
	
	/** Current item rate */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mCurrentItemRate;

	/** Items spawned since this history entry began */
	UPROPERTY( SaveGame )
	int32 mItemsSpawned;

	/** Current time since the history entry began */
	UPROPERTY( SaveGame )
	float mCurrentPeriodTime;

	/** Timer used for rate limiting. */
	UPROPERTY( SaveGame )
	float mTimeSinceLastItemSpawn;
};
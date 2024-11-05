// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGBuildableCheatItemSink.generated.h"

UCLASS()
class FACTORYGAME_API AFGBuildableCheatItemSink : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildableCheatItemSink();
	
	// Begin AActor
	virtual void BeginPlay() override;
	// End AActor

	// Begin AFGBuildable
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual void Factory_Tick(float dt) override;
	virtual void Factory_CollectInput_Implementation() override;
	// End AFGBuildable

	/** Returns the total amount of items removed */
	UFUNCTION( BlueprintPure, Category = "Cheat Item Sink" )
	FORCEINLINE int32 GetTotalItemsSunk() const { return mTotalItemsSunk; }

	/** Returns the current rate (items/s) of this buildable sinking items */
	UFUNCTION( BlueprintPure, Category = "Cheat Item Sink" )
	FORCEINLINE float GetItemSinkRate() const { return mCurrentItemRate; }
	
protected:
	/** Time interval for a single period of history */
	UPROPERTY( EditDefaultsOnly, Category = "Cheat Item Spawner" )
	float mItemRatePeriod;

	/** Total amount of items sunk into our inventory and voided */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	int32 mTotalItemsSunk;
	
	/** Current item rate */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mCurrentItemRate;

	/** Items removed since this history entry began */
	UPROPERTY( SaveGame )
	int32 mItemsRemoved;

	/** Current time since the history entry began */
	UPROPERTY( SaveGame )
	float mCurrentPeriodTime;

	UPROPERTY( Transient )
	TArray<UFGFactoryConnectionComponent*> mInputConnections;
};
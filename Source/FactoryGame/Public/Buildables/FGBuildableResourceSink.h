// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGBuildableResourceSink.generated.h"

/**
 * Building that you can sink items into to get points
 */
UCLASS()
class FACTORYGAME_API AFGBuildableResourceSink : public AFGBuildableFactory
{
	GENERATED_BODY()

public:
	AFGBuildableResourceSink();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

	// Begin BuildableFactoryInterface
	virtual void Factory_CollectInput_Implementation() override;
	bool CanProduce_Implementation() const override;
	// End BuildableFactoryInterface

	/** Get the inventory where we store coupons for this resource sink */
	UFUNCTION( BlueprintPure, Category = "Resource Sink" )
	FORCEINLINE class UFGInventoryComponent* GetCouponInventory() const { return mCouponInventory; }

	/** 
	* Claims the given number of coupons. If less coupons than the given num is available it will claim the maximum amount available. 
	* Returns number of claimed coupons
	*/
	UFUNCTION( BlueprintCallable, Category = "Resource Sink" )
	int32 ClaimCoupons( int32 numCoupons );

	/** Coupons that's still in the sink inventory will be removed from the inventory and given back to the resource sink subsystem */
	UFUNCTION( BlueprintCallable, Category = "Resource Sink" )
	void ReturnUnclaimedCoupons();


private:
	/** Used to start the producing timer from non-game thread */
	UFUNCTION()
	void StartProducingTimer();

private:
	UPROPERTY( VisibleDefaultsOnly, SaveGame, Replicated, Category = "Resource Sink" )
	class UFGInventoryComponent* mCouponInventory;

	/** Cached factory input connections */
	UPROPERTY( Transient )
	TArray<class UFGFactoryConnectionComponent*> mFactoryInputConnections;
	
	/** Cached resource sink subsystem */
	UPROPERTY( Transient )
	class AFGResourceSinkSubsystem* mResourceSinkSubsystem;

	/** The item descriptor that should be used as a coupon */
	UPROPERTY( Transient )
	TSubclassOf< class UFGItemDescriptor > mCouponClass;

	/** How long after the last sunk item should we stop producing */
	UPROPERTY( EditDefaultsOnly )
	float mProcessingTime;

	/** How long we have left on the timer when saving the game */
	UPROPERTY( EditDefaultsOnly, SaveGame )
	float mSavedProducingTimer;
	
	/** Used to know when we should stop producing. Since the sink just sinks at belt speed we don't have anything to look at to know if we are producing
	* so whenever we sink an item we reset the timer. If the timer is active we are producing. Used to avoid choppy triggers for animation/vfx/sound.
	* If we ever have the need for tick in this class we can move this functionality there with our own timer based on a float or similar.
	*/
	FTimerHandle mProducingTimer;

public:
	FORCEINLINE ~AFGBuildableResourceSink() = default;
};

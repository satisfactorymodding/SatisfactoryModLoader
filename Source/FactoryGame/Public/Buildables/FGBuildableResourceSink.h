// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	virtual void Tick( float dt ) override;
	virtual void Destroyed() override;
	// End AActor interface

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

	/** Used to know when we should stop producing. Since the sink just sinks at belt speed we don't have anything to look at to know if we are producing
	* so whenever we sink an item we reset the timer. If the timer is active we are producing. Used to avoid choppy triggers for animation/vfx/sound.
	* This will only count down if we have significance. So if we go out of significance while producing we will still return true for producing until we get significance back. 
	* @todok2 Look into if this is a problem. The only thing I can think of now is that animations/vfx/sound depending on this state might be starting when getting significance back 
	* when in fact we aren't producing
	*/
	UPROPERTY( SaveGame )
	float mProducingTimer;
	
};

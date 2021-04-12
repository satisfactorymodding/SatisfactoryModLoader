// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGEventSubsystem.h"
#include "FGBuildableFactorySimpleProducer.generated.h"

/**
 * A factory building that allow for simple production of a single item. Production rate and ItemType can be set via blueprint
 */
UCLASS()
class FACTORYGAME_API AFGBuildableFactorySimpleProducer : public AFGBuildableFactory
{
	GENERATED_BODY()

public:
	// Begin AActor
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor

	// Begin Factory Interface
	virtual void Factory_Tick( float dt ) override;
	virtual bool Factory_PeekOutput_Implementation( const class UFGFactoryConnectionComponent* connection, TArray< FInventoryItem >& out_items, TSubclassOf< UFGItemDescriptor > type ) const override;
	virtual bool Factory_GrabOutput_Implementation( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type ) override;
	// End Factory Interface

	bool IsEventValid() const;

protected:
	UPROPERTY( EditDefaultsOnly, Category = "Factory Simple Producer" )
	TSubclassOf<class UFGItemDescriptor> mItemType;

	UPROPERTY( EditDefaultsOnly, Category = "Factory Simple Producer" )
	float mTimeToProduceItem;

	UPROPERTY( EditDefaultsOnly, Category = "Factory Simple Producer", meta=(EditCondition=mUsesEventData) )
	EEvents mEventType;

private:
	float mTimeSinceLastGrab;

};

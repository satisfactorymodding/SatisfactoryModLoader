// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGOptimizationSettings.h"
#include "FGColoredInstanceManager.h"
#include "Components/StaticMeshComponent.h"
#include "FGColoredInstanceMeshProxy.generated.h"


/**
 * Proxy placed in buildings to be replaced with an instance on creation, supports coloring.
 */
UCLASS( Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGColoredInstanceMeshProxy : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFGColoredInstanceMeshProxy();

	// Begin AActorComponent interface
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	// End AActorComponent interface

	void SetColorSlot( uint8 colorSlotIndex );

	FORCEINLINE void SetOptimizationCategory( EDistanceCullCategory NewType ) { mOptimizationCategory = NewType; }

	void SetInstanced( bool setToInstanced );

protected:
	// Begin AActorComponent interface
	virtual void OnHiddenInGameChanged() override;	
public:
	virtual bool ShouldCreateRenderState() const override;
	// End AActorComponent interface

private:
	void InstantiateInternal();

public:
	UPROPERTY( EditDefaultsOnly )
	bool mCanBecolored = true;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	bool mBlockInstancing = false;

	/** Only used for holding info about where the instance is located, for quicker changes.*/
	UFGColoredInstanceManager::InstanceHandle mInstanceHandle;

	/*Don't need to be a UPROPERTY as it's only meant as a shortcut to an object that is already managed elsewhere and guaranteed to live longer than this component*/
	UFGColoredInstanceManager* mInstanceManager;

	/* Category that will be used based on optimization settings. */
	UPROPERTY( EditDefaultsOnly )
	EDistanceCullCategory mOptimizationCategory;
};

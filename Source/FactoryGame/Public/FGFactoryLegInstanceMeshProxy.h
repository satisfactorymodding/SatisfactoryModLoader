// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGOptimizationSettings.h"
#include "FGFactoryLegInstanceManager.h"
#include "Components/StaticMeshComponent.h"
#include "FGFactoryLegInstanceMeshProxy.generated.h"


/**
 * Proxy placed in buildings to be replaced with an instance on creation, supports coloring.
 */
UCLASS( Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGFactoryLegInstanceMeshProxy : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFGFactoryLegInstanceMeshProxy();

	// Begin AActorComponent interface
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	// End AActorComponent interface

	FORCEINLINE void SetOptimizationCategory( EDistanceCullCategory NewType ) { mOptimizationCategory = NewType; }

	void SetInstanced( bool setToInstanced );

protected:
	// Begin AActorComponent interface
	virtual void OnHiddenInGameChanged() override;
	// End AActorComponent interface

private:
	void InstantiateInternal();

public:

	/** Only used for holding info about where the instance is located, for quicker changes.*/
	UFGFactoryLegInstanceManager::FInstanceHandle mInstanceHandle;

	/*Don't need to be a UPROPERTY as it's only meant as a shortcut to an object that is already managed elsewhere and guaranteed to live longer than this component*/
	UFGFactoryLegInstanceManager* mInstanceManager;

	/** Used to keep track of our instance ID in the HISM */
	int32 InstanceID;

	/* Category that will be used based on optimization settings. */
	UPROPERTY( EditDefaultsOnly )
	EDistanceCullCategory mOptimizationCategory;

};

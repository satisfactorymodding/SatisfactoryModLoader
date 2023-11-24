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

	void SetCustomizationData( const FFactoryCustomizationData& customizationData );
	void SetHasPowerData( float newHasPower );
	void SetUserDefinedData( TArray<float> userData );

	FORCEINLINE void SetOptimizationCategory( EDistanceCullCategory NewType ) { mOptimizationCategory = NewType; }

	void SetInstanced( bool setToInstanced );

	UFUNCTION( BlueprintPure, Category = "Colored Mesh Proxy")
	FORCEINLINE uint8 GetNumCustomDataFloats() const { return mNumCustomDataFloats; }

protected:
	// Begin USceneComponent interface
	virtual void OnUpdateTransform( EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport ) override;
	// End USceneComponent interface
	
	// Begin AActorComponent interface
	virtual void OnHiddenInGameChanged() override;	
public:
	virtual bool ShouldCreateRenderState() const override;
	// End AActorComponent interface
	virtual bool ShouldBlockInstancing() const;

private:
	void InstantiateInternal();
	virtual void PostLoad() override;
public:

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	bool mBlockInstancing = false;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	bool mBlockInstancingWithLumen = false;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	bool mBlockColoring = false;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	bool mHasScalabilityMaterial = false;
	
	/** Only used for holding info about where the instance is located, for quicker changes.*/
	UFGColoredInstanceManager::FInstanceHandle mInstanceHandle;

	/** Used to keep track of our instance ID in the HISM */
	int32 InstanceID;

	/*Don't need to be a UPROPERTY as it's only meant as a shortcut to an object that is already managed elsewhere and guaranteed to live longer than this component*/
	UFGColoredInstanceManager* mInstanceManager;

	/* Category that will be used based on optimization settings. */
	UPROPERTY( EditDefaultsOnly )
	EDistanceCullCategory mOptimizationCategory;

protected:
	UPROPERTY( EditDefaultsOnly )
	uint8 mNumCustomDataFloats;

};

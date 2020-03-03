// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "UObject/Class.h"

#include "Buildables/FGBuildableFactory.h"
#include "Components/SceneComponent.h"
#include "FGProductionIndicatorInstanceManager.h"
#include "FGProductionIndicatorInstanceComponent.generated.h"


/**
 * Instanced production indicator, used on factories instead of the old non instanced variant.
 */
UCLASS( Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGProductionIndicatorInstanceComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFGProductionIndicatorInstanceComponent();

	//Begin AActor
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	//End AActor

	void SetInstanceManager( UFGProductionIndicatorInstanceManager* manager );
	void SetInstanced( bool isInstanced );

	/** Called when the buildings indicator status changes. */
	void OnProductionStatusChanged( EProductionStatus newStatus );

	/** This sets the cached status to IS_NONE so that an update is forced next frame */
	void ResetIndicatorStatus();

protected:
	// Begin SceneComponent interface
	virtual void OnHiddenInGameChanged() override;
	// End SceneComponent interface

private:
	/** The outer factory we should display the state for. */
	class AFGBuildableFactory* mOuterFactory;

	/** Save the state of the factory so that we don't change material excessively. */
	EProductionStatus mCachedIndicatorStatus;
	
	/** Only used for holding info about where the instance is located, for quicker changes.*/
	UFGProductionIndicatorInstanceManager::InstanceHandle mInstanceHandle;

	/* Don't need to be a UPROPERTY as it's only meant as a shortcut to an object that is already managed elsewhere and guaranteed to live longer than this component. */
	UFGProductionIndicatorInstanceManager* mInstanceManager;

public:
	FORCEINLINE ~UFGProductionIndicatorInstanceComponent() = default;
};

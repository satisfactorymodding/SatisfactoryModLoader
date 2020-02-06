// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "UObject/Class.h"

#include "Buildables/FGBuildableFactory.h"
#include "Components/SceneComponent.h"
#include "FGProductionIndicatorInstanceManager.h"
#include "FGProductionIndicatorInstanceComponent.generated.h"


/**
*
*/
UCLASS( Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGProductionIndicatorInstanceComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFGProductionIndicatorInstanceComponent();

		
	void OnProductionStatusChanged( EProductionStatus status );

	/** This sets the cacehd status to IS_NONE so that an update is forced next frame */
	void ResetIndicatorStatus();


	/** Only used for holding info about where the instance is located, for quicker changes.*/
	UFGProductionIndicatorInstanceManager::InstanceHandle mInstanceHandle;

	/*Dont'n eed to be a UPROPERTY as it's only meant as a shortcut to an object that is already managed elsewhere and guaranteed to live longer than this component*/
	UFGProductionIndicatorInstanceManager* mInstanceManager = nullptr;

	/** Save the state of the factory so that we don't change material excessively. */
	EProductionStatus mCachedIndicatorStatus = EProductionStatus::IS_MAX;


	virtual void BeginPlay() override;


	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;



	void SetInstanced( bool setToInstanced );

private:
	/** The outer factory we should display the state for. */
	class AFGBuildableFactory* mOuterFactory;



	virtual void OnHiddenInGameChanged() override;

};

// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "Buildables/FGBuildableFactory.h"
#include "FGProductionIndicatorComponent.generated.h"


/**
*
*/
UCLASS( Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGProductionIndicatorComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGProductionIndicatorComponent();

	virtual void OnUnregister() override;
	virtual void OnRegister() override;
		
	virtual void TickComponent( float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction ) override;

	/** This sets the cacehd status to IS_NONE so that an update is forced next frame */
	void ResetIndicatorStatus();

private:
	/** The outer factory we should display the state for. */
	class AFGBuildableFactory* mOuterFactory;

	/** Save the state of the factory so that we don't change material excessively. */
	EProductionStatus mCachedIndicatorStatus;
	/** Save the power state of the factory */
	bool mCachedHasPower;

	/** Dynamic instance of the material */
	UPROPERTY()
	class UMaterialInstanceDynamic* mIndicatorMaterial;

	/** Not UPROPERTY as this will never live longer than it's outer, cached version of it's main meshes */
	TArray< UMeshComponent* > mCachedMainMeshes;

public:
	FORCEINLINE ~UFGProductionIndicatorComponent() = default;
};

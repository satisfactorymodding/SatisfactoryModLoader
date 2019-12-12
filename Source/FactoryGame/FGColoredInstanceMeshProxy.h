// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "UObject/Class.h"

#include "FactoryGame.h"
#include "FGColoredInstanceManager.h"
#include "Components/StaticMeshComponent.h"
#include "FGColoredInstanceMeshProxy.generated.h"


/**
*
*/
UCLASS( Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGColoredInstanceMeshProxy : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFGColoredInstanceMeshProxy();

	virtual void OnUnregister() override;
	virtual void OnRegister() override;
		
	void SetColorSlot( uint8 colorSlotIndex );


	/** Only used for holding info about where the instance is located, for quicker changes.*/
	UFGColoredInstanceManager::InstanceHandle mInstanceHandle;

	/*Don't need to be a UPROPERTY as it's only meant as a shortcut to an object that is already managed elsewhere and guaranteed to live longer than this component*/
	UFGColoredInstanceManager* mInstanceManager = nullptr;

	virtual void BeginPlay() override;

	void InstantiateInternal();

	UPROPERTY( EditDefaultsOnly )
	bool mCanBecolored = true;
	UPROPERTY( BlueprintReadWrite )
	bool mBlockInstancing = false;

	void SetInstanced( bool setToInstanced );

protected:
	virtual void CreateRenderState_Concurrent() override;

	virtual void OnHiddenInGameChanged() override;

private:
	/** The outer factory we should display the state for. */
	//class AFGBuildableFactory* mOuterFactory; //[DavalliusA:Sat/23-02-2019] consider fetching tihs to be able to read color slot from it... but we only need that in rare cases, so it's probably not worth keeping


};

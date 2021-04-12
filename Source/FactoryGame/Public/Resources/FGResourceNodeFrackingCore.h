// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGResourceNodeBase.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "FGResourceNodeFrackingCore.generated.h"

/**
 * A node whose purpose is to let a AFGBuildableFrackingActivator activate a group of AFGResourceNodeFrackingSatellite nodes.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGResourceNodeFrackingCore : public AFGResourceNodeBase
{
	GENERATED_BODY()
	
public:
	AFGResourceNodeFrackingCore();
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor interface

	// Begin IFGExtractableResourceInterface
	virtual bool CanPlaceResourceExtractor() const override { return true; }
	// End IFGExtractableResourceInterface

	/** Register a satellite node as dependent of this core */
	void RegisterSatellite( TWeakObjectPtr< class AFGResourceNodeFrackingSatellite > satellite );

	/** Activate all the nodes that was registered by RegisterSatellite */
	void Factory_SetSatellitesActive( bool isActive );

	void SetActivator( TWeakObjectPtr< class AFGBuildableFrackingActivator > activator ) { mActivator = activator; }

	/** @returns the extractor connected to this node, nullptr if there is no such extractor */
	TWeakObjectPtr< class AFGBuildableFrackingActivator > GetActivator() { return mActivator; }

	/** @returns the satellites connected to this core node */
	TArray< TWeakObjectPtr< class AFGResourceNodeFrackingSatellite > >& GetSatellites() { return mSatellites; }

private:
	TArray< TWeakObjectPtr< class AFGResourceNodeFrackingSatellite > > mSatellites;

	TWeakObjectPtr< class AFGBuildableFrackingActivator > mActivator;
};

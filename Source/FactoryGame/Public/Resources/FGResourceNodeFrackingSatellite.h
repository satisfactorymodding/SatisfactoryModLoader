// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGResourceNodeFrackingCore.h" // MODDING EDIT
#include "Resources/FGResourceNode.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "FGResourceNodeFrackingSatellite.generated.h"

UENUM( BlueprintType )
enum class EFrackingSatelliteState : uint8
{
	FSS_Untouched		UMETA( DisplayName = "Untouched" ),
	FSS_Active			UMETA( DisplayName = "Active" ),
	FSS_Inactive		UMETA( DisplayName = "Inactive" )
};

/**
 * A node that must be activated through an AFGResourceNodeFrackingCore node before is can be mined by an AFGBuildableFrackingExtractor.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGResourceNodeFrackingSatellite : public AFGResourceNode
{
	GENERATED_BODY()

public:
	AFGResourceNodeFrackingSatellite();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void OnConstruction( const FTransform& Transform ) override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin IFGExtractableResourceInterface
	virtual void SetIsOccupied( bool occupied ) override;
	virtual bool CanPlaceResourceExtractor() const override;
	// End IFGExtractableResourceInterface

	/** Will dispatch a call of SetActive on the game thread */
	void Factory_SetActive( bool isActive );

	/** @param isActive if true, will set mState to Active, if false will set mState to Passive */
	void SetActive( bool isActive );
	
	/** @returns the current state of this satellite */
	UFUNCTION( BlueprintPure, Category = "Fracking" )
	EFrackingSatelliteState GetState() const { return mState; }

	/** @param extractor the extractor connected to this node */
	void SetExtractor( TWeakObjectPtr< class AFGBuildableFrackingExtractor > extractor );

	/** @returns the extractor connected to this node. nullptr if there is no such extractor */
	TWeakObjectPtr< class AFGBuildableFrackingExtractor > GetExtractor() { return mExtractor; }
	
	/** @returns the core connected to this satellite. nullptr means this asset is not properly configured */
	TWeakObjectPtr< class AFGResourceNodeFrackingCore > GetCore() { return mCore; }

protected:
	UFUNCTION( BlueprintImplementableEvent, Category="Fracking" )
	void OnStateChanged( EFrackingSatelliteState state, bool isFirstTimeActivated );

private:
	UFUNCTION()
	void OnRep_State();

	void OnStateChanged_Native( EFrackingSatelliteState state, bool isFirstTimeActivated );

private:
	/** The fracking core node through which this satellite node is activated */
	UPROPERTY( EditInstanceOnly, Category = "Resources" )
	class AFGResourceNodeFrackingCore* mCore;

	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_State )
	EFrackingSatelliteState mState;

	EFrackingSatelliteState mPreviousState;

	TWeakObjectPtr< class AFGBuildableFrackingExtractor > mExtractor;
};

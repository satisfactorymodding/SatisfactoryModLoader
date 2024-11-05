// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGRailroadVehicle.h"
#include "GameFramework/Actor.h"
#include "FGUseableInterface.h"
#include "FGSaveInterface.h"
#include "FGRailroadVehicleRerailHologram.generated.h"


/**
 * Derail hologram shown when a train has derailed and all its cars have scattered too far from the point of derailment.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadVehicleRerailHologram : public AActor, public IFGUseableInterface, public IFGSaveInterface
{
	GENERATED_BODY()
public:	
	AFGRailroadVehicleRerailHologram();

	// Begin AActor
	virtual void Tick( float dt ) override;
	// End AActor

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state  ) override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	//~ End IFGUseableInterface
	
	/**
	 * Call this directly after BeginPlay to setup the hologram.
	 */
	void Setup( class AFGRailroadVehicle* owner, class UStaticMesh* mesh );

private:
	// Owner that spawned this hologram.
	TWeakObjectPtr< class AFGRailroadVehicle > mOwner;
};

// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableFactory.h"
#include "../FGUseableInterface.h"
#include "FGBuildableRailroadSwitchControl.generated.h"

/**
 * A component for controlling a switch's position.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGBuildableRailroadSwitchControl : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Ctor */
	AFGBuildableRailroadSwitchControl();

	// Begin AActor interface
	virtual void Tick( float dt ) override;
	// End AActor interface

	// Begin IFGDismantleInterface
	virtual bool CanDismantle_Implementation() const override;
	// End IFGDismantleInterface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	// End IFGUseableInterface

	/** Get the current switch location. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Switch" )
	FORCEINLINE int32 GetSwitchPosition() const { return mSwitchPosition; }

	/** Toggle the switch position to the next track. */
	void ToggleSwitchPosition();

private:
	friend class AFGRailroadTrackHologram;

	/** Connection we control. */
	UPROPERTY( SaveGame )
	class UFGRailroadTrackConnectionComponent* mControlledConnection;

	/** Current switch position read from the controlled connection, polled each tick. */
	UPROPERTY( Replicated, Meta = (NoAutoJson = true) )
	int32 mSwitchPosition;
};

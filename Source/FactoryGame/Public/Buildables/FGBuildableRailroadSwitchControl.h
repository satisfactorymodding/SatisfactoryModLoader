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
	AFGBuildableRailroadSwitchControl();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin IFGDismantleInterface
	virtual bool CanDismantle_Implementation() const override;
	// End IFGDismantleInterface

	//~ Begin AFGBuildable interface
	virtual bool CanBeSampled_Implementation() const{ return false; }
	//~ End AFGBuildable interface

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

	/** Called when switch changes position, server only */
	UFUNCTION()
	void OnSwitchPositionChanged( int32 newPosition );

	/** Let blueprint get a chance to update the visuals after the switch  */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "FactoryGame|Railroad|Switch" )
	void UpdateSwitchPositionVisuals();
protected:
	UFUNCTION()
	void OnRep_SwitchPosition();
private:
	friend class AFGRailroadTrackHologram;

	/** Connection we control. */
	UPROPERTY( SaveGame )
	class UFGRailroadTrackConnectionComponent* mControlledConnection;

	/** Current switch position read from the controlled connection, polled each tick. */
	UPROPERTY( ReplicatedUsing = OnRep_SwitchPosition, Meta = (NoAutoJson = true) )
	int32 mSwitchPosition;

public:
	FORCEINLINE ~AFGBuildableRailroadSwitchControl() = default;
};

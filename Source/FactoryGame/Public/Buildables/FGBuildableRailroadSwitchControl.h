// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableFactory.h"
#include "FGUseableInterface.h"
#include "FGBuildableRailroadSwitchControl.generated.h"

/**
 * Struct containing packaged switch data so we can get an OnRep for them as a group.
 */
USTRUCT()
struct FSwitchData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	uint8 Position = 0;
	UPROPERTY()
	uint8 NumPositions = 1;
};

/**
 * A component for controlling a switch's position.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGBuildableRailroadSwitchControl : public AFGBuildable, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGBuildableRailroadSwitchControl();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor interface

	// Begin FGBuildable
	virtual void OnBuildEffectFinished() override;
	virtual void OnBuildEffectActorFinished() override;
	// End FGBuildable

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual	void SetupForSignificance() override;
	//End IFGSignificanceInterface
	
	// Begin IFGDismantleInterface
	virtual bool ShouldBlockDismantleSample_Implementation() const override;
	virtual bool CanDismantle_Implementation() const override;
	// End IFGDismantleInterface

	//~ Begin AFGBuildable interface
	virtual bool CanBeSampled_Implementation() const{ return false; }
	virtual bool ShouldBeConsideredForBase_Implementation() override { return false; }
	virtual void Dismantle_Implementation() override;
	//~ End AFGBuildable interface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	// End IFGUseableInterface

	/** Get the current switch position. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Switch" )
	FORCEINLINE int32 GetSwitchPosition() const { return mSwitchData.Position; }

	/** Get the total number of switch position. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Switch" )
	FORCEINLINE int32 GetNumSwitchPositions() const { return mSwitchData.NumPositions; }

	/** Toggle the switch position to the next track. */
	void ToggleSwitchPosition();

	/** Called when switch changes position, server only */
	UFUNCTION()
	void OnSwitchPositionChanged( int32 newPosition, int32 numPositions );

	/** @return If this is significant. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Signal" )
	bool IsSignificant() const { return mIsSignificant; }
	
	/**
	 * Sets the controlled connection when this switch is constructed.
	 * Note that the track the controlled connection belongs to and its connected components track must have had its begin play called.
	 * Must be called, prior to this actors BeginPlay.
	 */
	void SetControlledConnection( class UFGRailroadTrackConnectionComponent* controlledConnection );

protected:
	UFUNCTION()
	void OnRep_ControlledConnection();
	
	UFUNCTION()
	void OnRep_VisualState();

private:
	/** Updates the material parameters of this switch. */
	void UpdateVisuals();
	void ApplyVisualState( int16 state );

protected:
	/** Mesh for this switch, must be using the signal factory material for it to work. */
	UPROPERTY( VisibleAnywhere )
	class UFGColoredInstanceMeshProxy* mSwitchComponent;
	
private:
	/** Connection we control, might become null if the track is removed but not the control (mods and save game editing). */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_ControlledConnection )
	class UFGRailroadTrackConnectionComponent* mControlledConnection;

	/** Current switch position read from the controlled connection. */
	UPROPERTY( Replicated, Meta = (NoAutoJson = true) )
	FSwitchData mSwitchData;

	/** Stored custom data for the switch material. */
	UPROPERTY( ReplicatedUsing = OnRep_VisualState )
	int16 mVisualState;

	/** Indicates if the factory is within significance distance */
	bool mIsSignificant;

	/** The range to keep the buildable in significance */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceRange;
};

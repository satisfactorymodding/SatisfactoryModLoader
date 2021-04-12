// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGBackgroundThread.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableLightSource.generated.h"

/**
 * The light parameters that can be controlled from the light control panel.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FLightSourceControlData
{
	GENERATED_BODY()
	
	/** Slot index representing a color in the buildable light color slots */
	UPROPERTY( SaveGame, EditAnywhere, BlueprintReadWrite, Category = "Light" )
	int32 ColorSlotIndex = 0;
	/** Intensity of the light */
	UPROPERTY( SaveGame, EditAnywhere, BlueprintReadWrite, Category = "Light" )
	float Intensity = 1.f;
	/** Should it only light up during the night? or always! */
	UPROPERTY( SaveGame, EditAnywhere, BlueprintReadWrite, Category = "Light" )
	bool IsTimeOfDayAware = false;
};

/**
 * Base class for buildable light sources in the game.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableLightSource : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableLightSource();

	// Begin Actor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End Actor Interface

	// Begin AFGBuildable interface
	virtual bool GetPoolHandleInitialState() const override;
	// End AFGBuildable interface

	/** Turn this light on or off */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "FactoryGame|Buildable|Light" )
    void SetLightEnabled( bool isEnabled );
	
	/** Set the control data for this light in one go, prefer this to multiple call to the specific parameters. */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "FactoryGame|Buildable|Light" )
    void SetLightControlData( FLightSourceControlData data );

	/** Is this light on or off, valid on client. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Buildable|Light" )
    bool IsLightEnabled() const;

	/** Get the control data of this light, valid on client. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Buildable|Light" )
    FLightSourceControlData GetLightControlData() const;

	/** Get the currently set color of this light */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Buildable|Light" )
	FORCEINLINE FLinearColor GetCurrentLightColor() const { return mCurrentLightColor; }

	/** Do we have power, valid on client. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Buildable|Light" )
    bool HasPower() const { return mHasPower; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Buildable|Light" )
	float GetDefaultPowerConsumption() const { return mPowerConsumption; }

	/** Called when light color slots have been updated */
	void OnLightColorSlotsUpdated( const TArray< FLinearColor >& colors );

protected:
	/** Called when the time of day changes. */
	UFUNCTION( BlueprintImplementableEvent,Category = "FactoryGame|Buildable|Light" )
    void OnTimeOfDayChangedEvent( bool isDay );
	
	/** Called when the data has been set. */
	UFUNCTION( BlueprintImplementableEvent,Category = "FactoryGame|Buildable|Light" )
    void OnLightControlDataSet( FLightSourceControlData data );

	/** Called when state goes from on to off or other way around.*/
	UFUNCTION( BlueprintImplementableEvent )
    void OnUpdateMeshInfo( bool isEnabled );
	
private:
	// External delegates.
	UFUNCTION()
	void OnTimeOfDayChanged( bool isDay );
	void OnHasPowerChanged( class UFGPowerInfoComponent* info );

	// On reps.
	UFUNCTION()
	void OnRep_IsEnabled();
	UFUNCTION()
	void OnRep_LightControlData();
	UFUNCTION()
    void OnRep_HasPower();
	UFUNCTION()
	void OnRep_IsDay();

	// Called to update the light state in the world when some data has changed.
	void UpdateMeshDataAndHandles();
	
	// Update current light color by fetching the color that corresponds to the current light control data slot index
	void UpdateCurrentLightColor();

	// Update the power consumption of the light.
	void UpdatePowerConsumption();
	
private:
	/** Is the light on or off. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsEnabled )
	bool mIsEnabled;
	
	/** The parameters for the light output. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_LightControlData )
	FLightSourceControlData mLightControlData;

	/** The current set color that this light should use. This value is updated locally on both server and client but not directly replicated */
	UPROPERTY( Transient )
	FLinearColor mCurrentLightColor;
	
	/** Power consumption for this light. */
	UPROPERTY( EditDefaultsOnly, Category = "Light" )
	float mPowerConsumption;
	
	/** The power info for this light so it can consume power. */
	UPROPERTY()
	class UFGPowerInfoComponent* mPowerInfo;

	/** Locally cached has power. */
	UPROPERTY( ReplicatedUsing = OnRep_HasPower )
	bool mHasPower;

	/** Locally cached day status. */
	UPROPERTY( ReplicatedUsing = OnRep_IsDay )
	bool mIsDay;
};

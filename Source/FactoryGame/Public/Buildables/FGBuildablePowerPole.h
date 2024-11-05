// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildable.h"
#include "FGBuildablePowerPole.generated.h"

UENUM( BlueprintType )
enum class EPowerPoleType : uint8
{
	PPT_POLE 			UMETA( DisplayName = "Pole" ),
	PPT_WALL 			UMETA( DisplayName = "Wall Plug" ),
	PPT_WALL_DOUBLE 	UMETA( DisplayName = "Wall Plug Double" ),
	PPT_TOWER			UMETA( DisplayName = "Power Tower" )
};

/**
 * Base class for all power poles.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildablePowerPole : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildablePowerPole();

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	virtual void StartIsLookedAtForConnection( class AFGCharacterPlayer* byCharacter, class UFGCircuitConnectionComponent* overlappingConnection ) override;
	virtual void StopIsLookedAtForConnection( class AFGCharacterPlayer* byCharacter ) override;

	void ShowConnectionFeedback( class UFGCircuitConnectionComponent* overlappingConnection );
	void HideConnectionFeedback();

	virtual void Dismantle_Implementation() override;
	virtual bool ShouldBeConsideredForBase_Implementation() override;

	virtual void OnBuildEffectFinished() override;

	/**
	 * @return The power circuit this pole is connected to; nullptr if not connected.
	 */
	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	class UFGPowerCircuit* GetPowerCircuit() const;

	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	EPowerPoleType GetPowerPoleType() const { return mPowerPoleType; }

	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	class UFGPowerConnectionComponent* GetPowerConnection(int32 index) const { return mPowerConnections[index]; }

	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	const TArray< class UFGPowerConnectionComponent* >& GetPowerConnections() const { return mPowerConnections; }

	void OnPowerConnectionChanged(class UFGCircuitConnectionComponent* connection);

	/** Updates the cached number of connections this power pole currently have. */
	void MarkConnectionsDirty();
	
	/** @returns true if the power production in the circuit connected to this pole is above zero, false otherwise. */
	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	bool HasPower() const { return mHasPower; }

	/** Event that will be fired whenever mHasPower has changed */
	UFUNCTION( BlueprintImplementableEvent, Category = "PowerPole" )
	void OnHasPowerChanged( bool hasPower ) const;

	/** Gets the max length a wire is allowed to be when connecting this power tower to another power tower. */
	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	float GetPowerTowerWireMaxLength() const { return mPowerTowerWireMaxLength; }

private:
	void SetHasPower( bool hasPower );
	void OnConnectionHasPowerChanged( bool hasPower );

	UFUNCTION()
	void OnRep_HasPower() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PowerPole")
	class UWidgetComponent* mConnectionsWidgetComponent;

	UPROPERTY( EditDefaultsOnly, Category = "PowerPole")
	TSubclassOf<class UFGPoleConnectionsWidget> mConnectionWidgetClass;

private:
	/** The connection on this pole. */
	UPROPERTY( VisibleAnywhere, Category = "PowerPole" )
	TArray<class UFGPowerConnectionComponent*> mPowerConnections;

	/** The mesh component for this pole. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") )
	class UFGColoredInstanceMeshProxy* mMeshComponentProxy = nullptr;

	/** What kind of power pole this is. */
	UPROPERTY( EditDefaultsOnly, Category = "PowerPole" )
	EPowerPoleType mPowerPoleType;

	/** When connecting a wire from this power tower to another power tower, this is the max length the wire is allowed to be. */
	UPROPERTY( EditDefaultsOnly, Category = "PowerPole" )
	float mPowerTowerWireMaxLength;

	bool mIsDismantled;
	bool mIsShowingDismantleOutline;
	bool mIsShowingConnectionOutline;

	UPROPERTY( ReplicatedUsing = OnRep_HasPower )
	bool mHasPower;
};

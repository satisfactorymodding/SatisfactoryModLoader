// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "Array.h"
#include "UObject/Class.h"

#include "FGBuildable.h"
#include "FGBuildablePowerPole.generated.h"

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

	virtual void OnBuildEffectFinished() override;

	/**
	 * @return The power circuit this pole is connected to; nullptr if not connected.
	 */
	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	class UFGPowerCircuit* GetPowerCircuit() const;

	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	class UFGPowerConnectionComponent* GetPowerConnection(int32 index) const { return mPowerConnections[index]; }

	void OnPowerConnectionChanged(class UFGCircuitConnectionComponent* connection);

	/** Updates the cached number of connections this power pole currently have. */
	void MarkConnectionsDirty();

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
	UPROPERTY( VisibleAnywhere )
	class UFGColoredInstanceMeshProxy* mMeshComponentProxy = nullptr;

	bool mIsDismantled;
	bool mIsShowingDismantleOutline;
	bool mIsShowingConnectionOutline;

public:
	FORCEINLINE ~AFGBuildablePowerPole() = default;
};

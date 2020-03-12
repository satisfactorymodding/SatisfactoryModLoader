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

	virtual void StartIsLookedAtForConnection( class AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForConnection( class AFGCharacterPlayer* byCharacter ) override;

	void ShowConnectionFeedback();
	void HideConnectionFeedback();

	virtual void Dismantle_Implementation() override;

	virtual void OnBuildEffectFinished() override;

	/**
	 * @return The power circuit this pole is connected to; nullptr if not connected.
	 */
	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	class UFGPowerCircuit* GetPowerCircuit() const;

	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	class UFGPowerConnectionComponent* GetPowerConnection() const { return mPowerConnection; }

	/** Faster way to query how many connections this power pole currently have connected to it */
	UFUNCTION( BlueprintPure, Category = "PowerPole" )
	FORCEINLINE int32 GetCachedNumConnections() { return mCachedNumConnectionsToPole; }

	UFUNCTION( BlueprintImplementableEvent, Category = "PowerPole")
	void OnShowConnectionFeedback();

	void OnPowerConnectionChanged(class UFGCircuitConnectionComponent* connection);

	/** Updates the cached number of connections this power pole currently have. */
	void MarkConnectionsDirty();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PowerPole")
	class UWidgetComponent* mConnectionsWidgetComponent;

	UPROPERTY( EditDefaultsOnly, Category = "PowerPole")
	TSubclassOf<class UUserWidget> mConnectionWidgetClass;

private:
	/** The connection on this pole. */
	UPROPERTY( Replicated, VisibleAnywhere, Category = "PowerPole" )
	class UFGPowerConnectionComponent* mPowerConnection;

	/** The mesh component for this pole. */
	UPROPERTY( VisibleAnywhere )
	class UFGColoredInstanceMeshProxy* mMeshComponentProxy = nullptr;

	UPROPERTY( Replicated, meta = (NoAutoJson = true)  )
	int32 mCachedNumConnectionsToPole;

	bool mIsDismantled;
	bool mIsShowingDismantleOutline;
	bool mIsShowingConnectionOutline;

public:
	FORCEINLINE ~AFGBuildablePowerPole() = default;
};

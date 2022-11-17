// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Info.h"
#include "FGPriorityPowerSwitchInfo.generated.h"

/**
 * Identifier for a train station that is always available on server and clients.
 */
UCLASS()
class FACTORYGAME_API AFGPriorityPowerSwitchInfo : public AInfo
{
	GENERATED_BODY()
public:
	AFGPriorityPowerSwitchInfo();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor Interface
	
	void Init( class AFGBuildablePriorityPowerSwitch* prioritySwitch );
	
	/** Get the name of this switch. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Power|PrioritySwitchIdentifier" )
	FString GetSwitchName() const { return mSwitchName; }
	
	/** Get the priority for this switch. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Power|PrioritySwitchIdentifier" )
	int32 GetPriority() const { return mSwitchPriority; }

	/** Get if this switch is on or off. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Power|PrioritySwitchIdentifier" )
	bool IsSwitchOn() const { return mIsSwitchOn; }
	
	/** Set the priority for this switch. Only call this on the server, does nothing on client. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Power|PrioritySwitchIdentifier" )
	void SetPriority( int32 priority );

	/** Turn this switch on or off. Only call this on the server, does nothing on client. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Power|PrioritySwitchIdentifier" )
	void SetSwitchOn( bool on );
	
private:
	/** Callbacks from the switch. */
	UFUNCTION()
	void OnSwitchBuildingTagChanged( bool hasTag, const FString& tag );
	UFUNCTION()
	void OnIsSwitchOnChanged();
	UFUNCTION()
	void OnSwitchPriorityChanged( int32 priority );
	
public:
	/** The switch this info represents. */
	TWeakObjectPtr< class AFGBuildablePriorityPowerSwitch > mSwitch;
	
	/** Cached from the buildable. */
	UPROPERTY( Replicated )
	FString mSwitchName;

	/** Cached from the buildable. */
	UPROPERTY( Replicated )
	int32 mSwitchPriority;
	
	/** Cached from the buildable. */
	UPROPERTY( Replicated )
	bool mIsSwitchOn;
};

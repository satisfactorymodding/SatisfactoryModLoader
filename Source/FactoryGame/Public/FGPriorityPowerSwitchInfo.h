// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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

	/** @return Get the circuit group ID we belong to at our first connection, -1 if disconnected. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Power|PrioritySwitchIdentifier" )
	int32 GetCircuitGroupID0() const { return mCircuitGroupID0; }

	/** @return Get the circuit group ID we belong to at our second connection, -1 if disconnected. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Power|PrioritySwitchIdentifier" )
	int32 GetCircuitGroupID1() const { return mCircuitGroupID1; }
	
	/** Set the priority for this switch. Only call this on the server, does nothing on client. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Power|PrioritySwitchIdentifier" )
	void SetPriority( int32 priority );

	/** Turn this switch on or off. Only call this on the server, does nothing on client. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Power|PrioritySwitchIdentifier" )
	void SetSwitchOn( bool on );

	/** Called from the circuit subsystem when this info is removed. Both on server and client. */
	void OnRemoved() const;
	
private:
	/** Callbacks from the switch. */
	UFUNCTION()
	void OnSwitchBuildingTagChanged( bool hasTag, const FString& tag );
	UFUNCTION()
	void OnIsSwitchOnChanged();
	UFUNCTION()
	void OnSwitchPriorityChanged( int32 priority );
	UFUNCTION()
	void OnCircuitsChanged();

	/** OnReps for client delegates. */
	UFUNCTION()
	void OnRep_SwitchName() const;
	UFUNCTION()
	void OnRep_SwitchPriority() const;
	UFUNCTION()
	void OnRep_IsSwitchOn() const;
	UFUNCTION()
	void OnRep_GroupIDX() const;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSwitchNameChanged, const FString&, name );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnIsSwitchOnChanged, bool, isSwitchOn );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSwitchPriorityChanged, int32, priority );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnCircuitsChanged, int32, circuitID0, int32, circuitID1 );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSwitchRemoved );
	
	/** Called when the name changes, on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "Delegates" )
	FOnSwitchNameChanged mOnSwitchNameChangedDelegate;
	/** Called when the switch is turned on or off, on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "Delegates" )
	FOnIsSwitchOnChanged mOnIsSwitchOnChangedDelegate;
	/** Called when the priority changes, on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "Delegates" )
	FOnSwitchPriorityChanged mOnSwitchPriorityChangedDelegate;
	/** Called when any of the two circuits connected changes, on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "Delegates" )
	FOnCircuitsChanged mOnCircuitsChangedDelegate;
	/** Called when the switch is about to be removed, on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "Delegates" )
	FOnSwitchRemoved mOnSwitchRemovedDelegate;
	
private:
	/** The switch this info represents. */
	TWeakObjectPtr< class AFGBuildablePriorityPowerSwitch > mSwitch;
	
	/** Cached from the buildable. */
	UPROPERTY( ReplicatedUsing = OnRep_SwitchName )
	FString mSwitchName;

	/** Cached from the buildable. */
	UPROPERTY( ReplicatedUsing = OnRep_SwitchPriority )
	int32 mSwitchPriority;
	
	/** Cached from the buildable. */
	UPROPERTY( ReplicatedUsing = OnRep_IsSwitchOn )
	bool mIsSwitchOn;

	/**
	 * Which circuits do we belong to.
	 * Can be -1 if not connected.
	 * Can also be equal.
	 */
	UPROPERTY( ReplicatedUsing = OnRep_GroupIDX )
	int32 mCircuitGroupID0 = INDEX_NONE;
	UPROPERTY( ReplicatedUsing = OnRep_GroupIDX )
	int32 mCircuitGroupID1 = INDEX_NONE;
};

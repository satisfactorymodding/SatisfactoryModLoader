#pragma once

#include "FactoryGame.h"
#include "FGBuildable.h"
#include "FGElevatorTypes.h"
#include "FGSignificanceInterface.h"
#include "FGBuildableElevatorFloorStop.generated.h"


UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableElevatorFloorStop : public AFGBuildable, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGBuildableElevatorFloorStop();


	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// End AActor Interface

	// Begin Buildable Interface
	virtual void SetBuildableHiddenInGame(bool hide, bool disableCollisionOnHide) override;
	// End Buildable Interface
	
	// Begin IFGDistmantleInterface
	virtual bool CanDismantle_Implementation() const override;
	virtual void GetDismantleDisqualifiers_Implementation(TArray<TSubclassOf<UFGConstructDisqualifier>>& out_dismantleDisqualifiers, const TArray<AActor*>& allSelectedActors) const override;
	virtual bool SupportsDismantleDisqualifiers_Implementation() const override { return true; }
	virtual void GetChildDismantleActors_Implementation(TArray<AActor*>& out_ChildDismantleActors) const override;
	// End IFGDismantleinterface

	// Begin Useable Interface
	virtual bool IsUseable_Implementation() const override;
	virtual void UpdateUseState_Implementation(AFGCharacterPlayer* byCharacter, const FVector& atLocation, UPrimitiveComponent* componentHit, FUseState& out_useState) override;
	virtual void OnUse_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	virtual void StartIsLookedAt_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	virtual void StopIsLookedAt_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) override;
	virtual FText GetLookAtDecription_Implementation(AFGCharacterPlayer* byCharacter, const FUseState& state) const override;
	// End Useable Interface

	// Begin significance Interface.
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	// End
	// Assigns the Elevator that owns this stop. Occurs in PostLoadGame if coming from a save
	void SetOwningElevator( class AFGBuildableElevator* elevator );

	// Gets the elevator this Floor stop belongs to
	UFUNCTION( BlueprintPure, Category="FactoryGame|Buildable|ElevatorFloorStop" )
	class AFGBuildableElevator* GetOwningElevator() { return mElevator; }

	void ElevatorUpdateStateAtThisStop( EElevatorState newState );

	UFUNCTION()
	void OnRep_FloorRelevantElevatorState();

	UFUNCTION()
	void OnRep_Elevator();

	// When an elevator cabin is positioned at this stop the elevator broadcasts updates about the current state (Arrived/Doors Opening/Doors Closing etc.)
	UFUNCTION( BlueprintImplementableEvent )
	void OnElevatorUpdateStateAtThisStop( EElevatorState newState );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void OnPlayerUseFloorStopButton( bool becameSelected );

	// Notify from the owning elevator the Floor Info Has changed
	void NotifyFloorStopInfoHasChanged( const FElevatorFloorStopInfo& floorStopInfo );

	UFUNCTION(BlueprintImplementableEvent, Category="FactoryGame|Buildable|ElevatorFloorStop" )
	void OnFloorStopInfoChanged( const FElevatorFloorStopInfo& newFloorStopInfo );
	
	// Called by the owning elevator to notify of power status changes
	UFUNCTION()
	void NotifyPowerStatusChanged( bool hasPower );
	
	UFUNCTION(BlueprintImplementableEvent, Category="FactoryGame|Buildable|ElevatorFloorStop" )
	void OnPowerStatusChanged( bool hasPower );

	// Notify this floor stop of its queued status
	void NotifyQueuedStatus( EElevatorFloorStopQueuedStatus status );

	void UpdateButton( EElevatorFloorStopQueuedStatus status);
	
public:
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	class UFGColoredInstanceMeshProxy* mMesh;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	TObjectPtr< UFGColoredInstanceMeshProxy > mButtonMesh;

protected:
	UPROPERTY(EditDefaultsOnly)
   	float mSignificanceRange = 12000;

private:
	friend class AFGElevatorFloorStopHologram;

	UPROPERTY( ReplicatedUsing=OnRep_FloorRelevantElevatorState )
	EElevatorState mFloorRelevantElevatorState;
	
	// The owning elevator of this floor stop
	UPROPERTY( ReplicatedUsing=OnRep_Elevator )
	TObjectPtr< class AFGBuildableElevator > mElevator;

	UPROPERTY()
	EElevatorFloorStopQueuedStatus mCachedQueuedStatus;

	UPROPERTY()
	FElevatorFloorStopInfo mCachedFloorStopInfo;

	bool mIsBlockingOutlineCharacterOccupying;
	bool mIsOutlined;
	bool mLastUseStateHasPower;
	
};
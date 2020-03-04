#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGDropPodSettings.h"
#include "FGSaveInterface.h"
#include "FGUseableInterface.h"
#include "GameFramework/Actor.h"
#include "FGSchematic.h"
#include "FGSignificanceInterface.h"
#include "FGDropPod.generated.h"


UCLASS()
class FACTORYGAME_API AFGDropPod : public AActor, public IFGUseableInterface, public IFGSaveInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGDropPod();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PostLoad() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Tick( float DeltaSeconds ) override;
	// End AActor interface

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	//End IFGSignificanceInterface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin IFGUseableInterface
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	// End IFGUseableInterface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state  ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	// End IFGUseableInterface

	/** @return true if this has been opened. */
	UFUNCTION( BlueprintPure, Category = "Drop Pod" )
	FORCEINLINE bool HasBeenOpened() const { return mHasBeenOpened; }

	/** @return The inventory containing possible loot */
	UFUNCTION( BlueprintPure, Category = "Drop Pod" )
	FORCEINLINE class UFGInventoryComponent* GetLootInventory() const { return mInventory; }

	UFUNCTION( BlueprintPure, Category = "Drop Pod")
	FORCEINLINE bool GetHasPower() const { return mHasPower; }
	
protected:
	/** Open the drop pod. */
	UFUNCTION( BlueprintCallable, Category = "Drop Pod" )
	void Open();

	/** Called on server, rolls the loot for the drop pod. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drop Pod" )
	void OnOpened();

	/** Called on server, rolls the loot for the drop pod. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drop Pod" )
	void RollLoot();

	/** Event called when player tries to repair the drop-pod.*/
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Drop Pod")
	void OnRepair(class AFGCharacterPlayer* InteractingCharacter);

	/** Necessary to add for optimization reasons. We don't want to tick drop pods that don't require power but this is only set in blueprint. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Drop Pod")
	bool RequiresPowerToOpen() const;

	//[Snutt:Thu/20-02-2020] I added this because setting up a new connection component caused issues when loading
	/** Gets the power connection that's been assigned to the drop pod via blueprint */
	UFUNCTION( BlueprintImplementableEvent, Category = "Drop Pod" )
	class UFGPowerConnectionComponent* GetPowerConnection();

	/** Roll a package to drop and adds the items to the loot inventory. Call this on server only. */
	UFUNCTION( BlueprintCallable, Category = "Drop Pod" )
	FDropPackage RollDropPackage( /*bool excludeItems, */ TArray<TSubclassOf<class UFGItemDescriptor>> includedItems );

	UFUNCTION( BlueprintCallable, Category = "Drop Pod" )
	void GenerateDropPodInventory( TArray<TSubclassOf<class UFGItemDescriptor>> includedItems, int32 numItemsCreated );

	/** The amount of available inventory slots for the drop pod */
	UPROPERTY( EditDefaultsOnly, Category = "Drop Pod" )
	int32 mAmountOfInventorySlots;

	
protected:
	UPROPERTY( Replicated, BlueprintReadOnly )
	class UFGPowerInfoComponent* mPowerInfo;

	UPROPERTY( Replicated, BlueprintReadOnly )
	bool mHasPower;

private:
	UFUNCTION()
	void OnRep_HasBeenOpened();

	void OnPowerConnectionChanged( class UFGCircuitConnectionComponent* connection );

private:
	/** True when this has been opened */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_HasBeenOpened )
	bool mHasBeenOpened;

	/** Contains the loot if any */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mInventory;

public:
	FORCEINLINE ~AFGDropPod() = default;
};

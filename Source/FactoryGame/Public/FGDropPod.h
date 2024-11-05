// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGDismantleInterface.h"
#include "FGDropPodSettings.h"
#include "FGSaveInterface.h"
#include "FGUseableInterface.h"
#include "GameFramework/Actor.h"
#include "FGSchematic.h"
#include "FGSignificanceInterface.h"
#include "UObject/SoftObjectPtr.h"
#include "FGDropPod.generated.h"

class AFGBuildableWire;
class AFGItemPickup_Spawnable;
class UFGPowerInfoComponent;
class UFGPowerConnectionComponent;
class UFGMaterialEffect_Build;
class UFGInteractWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FFGOnDropPodOpenedDelegate );

/** Possible types of the unlock cost */
UENUM( BlueprintType )
enum class EFGDropPodUnlockCostType : uint8
{
	/** Drop pod can be unlocked without any cost */
	None,
	/** Unlocking the drop pod requires the provided item in the provided amounts */
	Item,
	/** Unlocking the drop pod requires a constantly supply of power */
	Power
};

/** A single unlock cost entry for the drop pod */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGDropPodUnlockCost
{
	GENERATED_BODY()

	/** Type of the unlock cost */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Unlock Cost" )
	EFGDropPodUnlockCostType CostType;

	/** Item cost of unlocking the drop pod */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Unlock Cost", meta = ( EditCondition = "CostType == EFGDropPodUnlockCostType::Item", EditConditionHides ) )
	FItemAmount ItemCost;

	/** Power consumption of the drop pod */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Unlock Cost", meta = ( EditCondition = "CostType == EFGDropPodUnlockCostType::Power", EditConditionHides ) )
	float PowerConsumption{};
};

/** Used to cache wires connected to the drop pod so it can be unloaded when it is no longer significant */
USTRUCT()
struct FACTORYGAME_API FFGCachedConnectedWire
{
	GENERATED_BODY()
	
	UPROPERTY( EditAnywhere, Category = "Wire", SaveGame )
	class AFGBuildableWire* mConnectedWire{};

	UPROPERTY( EditAnywhere, Category = "Wire", SaveGame )
	class UFGCircuitConnectionComponent* mOtherConnection{};
};

UCLASS()
class FACTORYGAME_API AFGDropPod : public AActor, public IFGUseableInterface, public IFGSaveInterface, public IFGSignificanceInterface, public IFGConditionalReplicationInterface
{
	GENERATED_BODY()
public:
	AFGDropPod();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	// End AActor interface

#if WITH_EDITOR
	// Begin UObject interface
	virtual void PostLoad() override;
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	// End UObject interface
#endif

	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	// End IFGSignificanceInterface

	// Begin IFGConditionalReplicationInterface
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual bool IsPropertyRelevantForConnection(UNetConnection* netConnection, const FProperty* property) const override;
	// End IFGConditionalReplicationInterface

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
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	// End IFGUseableInterface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
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

	/** Returns true if this has been opened and also looted (e.g. it's reward has been removed from the inventory) */
	UFUNCTION( BlueprintPure, Category = "Drop Pod" )
	bool HasBeenLooted() const;

	/** Returns the GUID of the drop pod actor. This is used in runtime to address drop pods that are not streamed in yet */
	FORCEINLINE FGuid GetDropPodGuid() const { return mDropPodGuid; }
	
	/** Returns the inventory containing possible loot */
	UFUNCTION( BlueprintPure, Category = "Drop Pod" )
	FORCEINLINE UFGInventoryComponent* GetLootInventory() const { return mInventoryComponent; }

	/** Returns the power info for this drop pod. */
	UFUNCTION( BlueprintPure, Category = "Drop Pod" )
	FORCEINLINE UFGPowerInfoComponent* GetPowerInfo() const { return mPowerInfoComponent; }

	/** Returns true if the drop pod has a power connected to it */
	UFUNCTION( BlueprintPure, Category = "Drop Pod", meta = ( DeprecatedFunction, DeprecationMessage = "Use GetPowerInfo and then check HasPower instead" ) )
	bool GetHasPower() const;

	/** Returns true if the provided player can unlock this drop pod. If the drop pod is already unlocked, returns false. */
	UFUNCTION( BlueprintPure, Category = "Drop Pod" )
	bool CanPlayerOpen( const AFGCharacterPlayer* player ) const;

	/** Attempts to open the drop pod using the resources from the inventory of the provided player */
	UFUNCTION( BlueprintCallable, Category = "Drop Pod" )
	bool OpenDropPod( AFGCharacterPlayer* player );

	/** Returns unlock cost for this drop pod */
	UFUNCTION( BlueprintPure, Category = "Drop Pod" )
	FORCEINLINE FFGDropPodUnlockCost GetUnlockCost() const { return mUnlockCost; }

	/** Returns the crash site debris actor linked with this drop pod */
	UFUNCTION( BlueprintPure, Category = "Drop Pod" )
	class AFGCrashSiteDebris* GetCrashSiteDebrisActor() const;

	UFUNCTION( BlueprintPure, Category = "Drop Pod" )
	FORCEINLINE TSubclassOf<UFGItemDescriptor> GetUnlockRewardClass() const { return mUnlockRewardClass; }

	UPROPERTY(EditDefaultsOnly,Category="Significance")
	float mSignificanceRange = 15000;
	
protected:
	UFUNCTION()
	void OnInventoryItemRemoved( TSubclassOf< UFGItemDescriptor > itemClass, const int32 numRemoved, UFGInventoryComponent* targetInventory = nullptr );
	
	/** Spawn the debris around the drop pod at the pre-specified locations */
	void SpawnDebrisAroundDropPod();

	void CacheAndDisconnectWires();

	void ReconnectCachedWires();

	/** Consumes the resources required to open the drop pod from the player inventory */
	void ConsumeOpenCost( AFGCharacterPlayer* player ) const;

	/** Returns a total number of players currently interacting with the drop pod and preventing it from being dismantled */
	int32 GetNumInteractingPlayers() const;
public:
	/** Called on the authority and replicated side when the drop pod has been opened */
	UPROPERTY( BlueprintAssignable, Category = "Drop Pod" )
	FFGOnDropPodOpenedDelegate mOnDropPodOpened;

	/** Crash site debris actor linked to this crash site */
	UPROPERTY( EditInstanceOnly, Category = "Drop Pod" )
	TSoftObjectPtr<class AFGCrashSiteDebris> mLinkedCrashSiteDebris;
	
protected:
	/** Name of the drop pod as visible when dismantling it */
	UPROPERTY( EditDefaultsOnly, Category = "Drop Pod" )
	FText mDisplayName;
	
	/** Reward to give the player upon unlocking the drop pod */
	UPROPERTY( EditAnywhere, Category = "Drop Pod" )
	TSubclassOf<UFGItemDescriptor> mUnlockRewardClass;

	/** Tier of the debris to spawn around the drop pod. */
	UPROPERTY( EditAnywhere, Category = "Drop Pod", DisplayName = "Item Tier" )
	int32 mDebrisTier;

	/** Allows overriding the amount of items of the provided rarity for this drop pod */
	UPROPERTY( EditAnywhere, Category = "Drop Pod", DisplayName = "Item Count Per Rarity Override" )
	TMap<EFGDropPodDebrisRarity, int32> mDebrisRarityOverrides;

	/** Cost of unlocking this drop pod */
	UPROPERTY( EditAnywhere, Category = "Drop Pod" )
	FFGDropPodUnlockCost mUnlockCost;

	/** Build effect to play on the actor when dismantling it */
	UPROPERTY( EditDefaultsOnly, Category = "Drop Pod" )
	TSoftClassPtr<UFGMaterialEffect_Build> mDismantleBuildEffect;

	/** The UI that will be open when interacting with a drop pod */
	UPROPERTY( EditDefaultsOnly, Category = "Drop Pod" )
	TSoftClassPtr<UFGInteractWidget> mInteractWidgetClass;

	UFUNCTION()
	void OnRep_HasBeenOpened();
	
	/** Power connection for this drop pod */
	UPROPERTY( EditDefaultsOnly, Category = "Drop Pod" )
	UFGPowerConnectionComponent* mPowerConnectionComponent;

	/** Power info for this drop pod */
	UPROPERTY( EditDefaultsOnly, Category = "Drop Pod" )
	UFGPowerInfoComponent* mPowerInfoComponent;

	/** Inventory component containing the reward */
	UPROPERTY( EditDefaultsOnly, Category = "Drop Pod" )
	UFGInventoryComponent* mInventoryComponent;

	/** True if we have already spawned the debris around the drop pod, false otherwise */
	UPROPERTY( VisibleInstanceOnly, Category = "Drop Pod", SaveGame )
	bool mSpawnedDebris;

	UPROPERTY( Replicated, Transient, meta = ( FGPropertyReplicator ) )
	FFGConditionalPropertyReplicator mPropertyReplicator;

	/** True if this crash site has been opened, e.g. the loot inventory has been populated with a reward. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_HasBeenOpened )
	bool mHasBeenOpened;

	/** Players currently interacting with the drop pod */
	UPROPERTY( VisibleInstanceOnly, Category = "Drop Pod" )
	TArray<AFGCharacterPlayer*> mInteractingPlayers;

	UPROPERTY( VisibleInstanceOnly, Category = "Drop Pod", SaveGame )
	TArray<AFGItemPickup_Spawnable*> mSpawnedPickups;

	/** Cached on lost significance when we disconnect the cables from the drop pod */
	UPROPERTY( VisibleInstanceOnly, Category = "Drop Pod", SaveGame )
	TArray<FFGCachedConnectedWire> mCachedConnectedWires;

	/** True if we have been dismantled and should be removed after finishing the dismantle effect */
	UPROPERTY( SaveGame )
	bool mIsDismantled;
	
	UPROPERTY( SaveGame )
	bool mHasBeenLooted = false;

	/** Actor ID cached during the cook to be able to identify this actor in runtime */
	UPROPERTY()
	FGuid mDropPodGuid;
};

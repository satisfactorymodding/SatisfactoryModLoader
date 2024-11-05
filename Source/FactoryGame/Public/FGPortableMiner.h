// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGClearanceInterface.h"
#include "GameFramework/Actor.h"
#include "FGUseableInterface.h"
#include "FGSaveInterface.h"
#include "FGInventoryComponent.h"
#include "FGPortableMiner.generated.h"

UCLASS( meta = (AutoJson = true) )
class FACTORYGAME_API AFGPortableMiner : public AActor, public IFGUseableInterface, public IFGSaveInterface, public IFGClearanceInterface
{
	GENERATED_BODY()
public:
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Ctor */
	AFGPortableMiner();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	//@optimize Are the portable miners optimized and turned of at a distance?
	/** Called when we produce something. */
	void TickProducing( float dt );

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state  ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	//~ End IFGUseableInterface

	// Begin IFGClearanceInterface
	virtual void GetClearanceData_Implementation(TArray<FFGClearanceData>& out_data) const override;
	// End IFGClearanceInterface

	/**
	 * Are we producing?
	 *
	 * @return - true if producing; otherwise false.
	 */
	UFUNCTION( BlueprintPure, Category = "Production" )
	bool IsProducing() const;

	/**
	 * Can we start production i.e. do we have the items needed for assembly etc.
	 *
	 * @return - true if we can start production; otherwise false.
	 */
	UFUNCTION( BlueprintPure, Category = "Production" )
	bool CanProduce() const;

	/**
	 * Start the production, client get this call replicated after the server
	 */
	void StartProducing();

	/**
	 * Stops the production, client get this call replicated after the server
	 */
	void StopProducing();

	/** @return The miners output inventory */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetOutputInventory() const { return mOutputInventory; }

	/** What do we get back when dismantling this */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	TArray< FInventoryStack > GetDismantleInventoryReturns() const;  

	/** @return Get the progress for the current bit of ore. */
	UFUNCTION( BlueprintPure, Category = "Production" )
	FORCEINLINE float GetExtractionProgress() const { return mCurrentExtractProgress; }

	/** @return Get the ExtractCycleTime. */
	UFUNCTION( BlueprintPure, Category = "Production" )
    FORCEINLINE float GetExtractCycleTime() const { return mExtractCycleTime; }

	void SetOwningPlayerState( class AFGPlayerState* playerState );

private:
	/** Calls Start/Stop Producing on client */
	UFUNCTION()
	void OnRep_IsProducing();

	UFUNCTION()
	void OnRep_OwningPlayerState( class AFGPlayerState* previousPlayerState );

	UFUNCTION()
	void OnPlayerCustomizationDataChanged( const struct FPlayerCustomizationData& newCustomizationData );
	
	void UpdateCustomizationData();

public:
	/** How fast we mine expressed as 1.0f / ( mExtractCycleTime * resourceSpeedMultiplier ) * dt. */
	UPROPERTY( EditDefaultsOnly, Category="Resource" )
	float mExtractCycleTime;

	/** The resource node we want to extract from */
	UPROPERTY( SaveGame, Replicated, BlueprintReadOnly, Category = "Resource" )
	class AFGResourceNode* mExtractResourceNode;

	/** The inventory of the factory node */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mOutputInventory;

	/** Current extract progress in the range [0, 1] */
	UPROPERTY( Replicated, meta = (NoAutoJson = true) )
	float mCurrentExtractProgress;

	/** The widget that will present our UI. */
	UPROPERTY( EditDefaultsOnly, Category = "Interaction" )
	TSubclassOf< class UFGInteractWidget > mInteractWidgetClass;

	/** How many slots is the inventory */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mInventorySize;

	/** The player state that "owns" this miner. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_OwningPlayerState )
	class AFGPlayerState* mOwningPlayerState;
private:
	/** Are we producing? */
	UPROPERTY( ReplicatedUsing = OnRep_IsProducing, meta = (NoAutoJson = true) )
	bool mIsProducing;

	/** Clearance box information for the portable miner */
	UPROPERTY( EditDefaultsOnly, Category = "Clearance" )
	FFGClearanceData mClearanceData;
};

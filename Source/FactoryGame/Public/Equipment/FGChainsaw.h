// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGEquipment.h"
#include "FGFoliageRemovalSubsystem.h"
#include "FGInventoryComponent.h"
#include "FGChainsaw.generated.h"


class IFGChainsawableInterface;

USTRUCT()
struct FACTORYGAME_API FPickedUpInstance
{
	GENERATED_BODY()

	FPickedUpInstance() :
		InstanceMesh( NULL ),
		Location( FVector::ZeroVector )
	{
	}

	FPickedUpInstance( UStaticMesh* instanceMesh, FVector location ) :
		InstanceMesh( instanceMesh ),
		Location( location )
	{
	}

	UPROPERTY()
	class UStaticMesh* InstanceMesh;

	UPROPERTY()
	FVector Location;
};

UENUM( BlueprintType )
enum class EFGChainsawState : uint8
{
	None,
	SpinningUp,
	Idle,
	Engaged,
	Sawing
};

/** Item state struct for the chainsaw */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGChainsawItemState
{
	GENERATED_BODY()
	
	/** How much energy do we have stored left in the chainsaw **/
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "ItemState|Chainsaw" )
	float EnergyStored{};
};

UCLASS()
class FACTORYGAME_API AFGChainsaw : public AFGEquipment
{
	GENERATED_BODY()
public:
	// Ctor
	AFGChainsaw();

	//~ Begin AActor interface
	virtual void Tick( float dt ) override;
	//~ End AActor interface

	// Begin AFGEquipment interface
	virtual void LoadFromItemState_Implementation(const FFGDynamicStruct& itemState) override;
	virtual FFGDynamicStruct SaveToItemState_Implementation() const override;
	virtual void DisableEquipment() override;
	virtual void Equip(AFGCharacterPlayer* character) override;
	virtual void UnEquip() override;
	virtual void AddEquipmentActionBindings() override;
	// End

	// Replication
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** @return the state the chainsaw is currently in. */
	UFUNCTION( BlueprintPure, Category = "Chainsaw" )
	FORCEINLINE EFGChainsawState GetChainsawState() const { return mChainsawState; }
	
	/** @return true if the player is actively trying to chainsaw, but no valid foliage exists for that */
	UFUNCTION( BlueprintPure, Category="Chainsaw" )
	bool IsSawEngaged() const;

	/** @return true if we are sawing AND we have a valid saw component */
	UFUNCTION( BlueprintPure, Category = "Chainsaw" )
	bool IsSawing() const;

	/** @return true if we are currently spinning the chainsaw up */
	UFUNCTION( BlueprintPure, Category = "Chainsaw" )
	bool IsSpinningUp() const;

	/** In percent, how long into our progress have we gone into sawing down our current tree */
	UFUNCTION( BlueprintPure, Category = "Chainsaw" )
	FORCEINLINE float SawProgress() const{ return mSawingProgress / mSawDownTreeTime; }

	/** returns true if the specified player has a chainsaw equipped */
	static bool DoesPlayerHaveChainsawEquipped( class AFGCharacterPlayer* player );

	UFUNCTION( BlueprintImplementableEvent, Category = "Chainsaw" )
	void CreatePhysicsFromFoliage( UStaticMesh* inMesh, FTransform inTransform );
	
	/** Return true we have any energy stored or if our owner has any fuel */
	UFUNCTION( BlueprintPure,  Category = "Chainsaw" )
	bool HasAnyFuel() const;
	
protected:
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;

	/** @return true if the "spinning up" animation has been finished and we should transition to the idle state now */
	UFUNCTION( BlueprintNativeEvent, Category = "Chainsaw" )
	bool IsSpinningUpTransitionFinished() const;

	/** Called to notify the blueprint of the chainsaw state transition */
	UFUNCTION( BlueprintNativeEvent, Category = "Chainsaw" )
	void OnChainsawStateTransition( const EFGChainsawState oldState );
	
	/**
	 * Consumes fuel, returns false if we are out of fuel
	 */
	bool ConsumeFuel( float dt );

	/**
	 * Start sawing, does no logic check if it's valid, caller is assumed to do so
	 * If client, calls server
	 */
	void StartSawing();

	/**
	 * Calls StartSawing on server
	 */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_StartSawing();
	
	/**
	 * Calls ToggleAOE on server
	 */
	UFUNCTION( BlueprintCallable, Reliable, Server )
	void Server_ToggleAOE( const bool isAOEOn );
	
	/**
	 * Stops sawing, does no logic check if it's valid, caller is assumed to do so
	 * If client, calls server
	 */
	void StopSawing();

	/** 
	 * Removes the foliage we just cut down
	 */
	UFUNCTION( Reliable, Server )
	void Server_RemoveFoliageInstance( const struct FFoliageInstanceStableId& stableId, const FVector& effectLocation, const FTransform& instanceTransform );

	void RemoveFoliageInstance( const struct FFoliageInstanceStableId& stableId, const FVector& effectLocation, const FTransform& instanceTransform );

	UFUNCTION( Reliable, Server )
	void Server_RemoveChainsawableObject(const TScriptInterface<IFGChainsawableInterface> &chainsawableObject);
	void RemoveChainsawableObject(TScriptInterface<IFGChainsawableInterface> chainsawableObject);

	/**
	 * Removes surrounding foliage around the chainsawedObject and picks it up the within the Collateral pick-up radius
	*/
	void RemoveCollateralFoliage( class AFGFoliageRemovalSubsystem* removalSubsystem, const FVector& location );

	UFUNCTION( NetMulticast, Unreliable )
	void BroadcastPickup( const TArray<FPickedUpInstance>& pickups, class AFGFoliagePickup* instigatorPlayer );

	/**
	 * Calls StopSawing on server
	 */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_StopSawing();
	

	/** Returns the current fuel class used for the chainsaw */
	UFUNCTION(BlueprintPure, Category = "Chainsaw")
	FORCEINLINE TSubclassOf<class UFGItemDescriptor> GetFuelClass() { return mFuelClass; }

	/** Start sawing on a new tree */
	void StartNewSawing( class USceneComponent* sawingComponent, int32 newIndex );

	/** Is it valid to saw on this component.
	 * @param newIndex: must be set to the corresponding index if sawingComponent is a UHierarchicalInstancedStaticMeshComponent
	 */
	bool IsValidSawing( class USceneComponent* sawingComponent, int32 newIndex ) const;
	
	bool CanPlayerPickupFoliageResourceForSeeds( class UHierarchicalInstancedStaticMeshComponent* meshComponent, const TArrayView< uint32 > seeds, TArray<FInventoryStack>& out_validStacks );

	/** returns the static mesh of whatever the hell it is this is i hate this */
	UStaticMesh* GetStaticMesh( USceneComponent* sawingComponent );

	/** returns true if actor is a chainsawable actor, duh */
	bool IsChainsawableObject(UObject* object) const;

	/** Transitions the chainsaw to the new state */
	void TransitionToNewState( const EFGChainsawState newState );

	/** Asks the server to transition to the new state */
	UFUNCTION( Server, Reliable )
	void Server_TransitionToNewState( EFGChainsawState newState );

	UFUNCTION()
	void OnRep_ChainsawState( EFGChainsawState oldState );

	void Input_Toggle( const FInputActionValue& actionValue );

protected:
	/** The fuel we want to be able to use with the chainsaw */
	UPROPERTY( EditDefaultsOnly, Category="Chainsaw|Fuel" )
	TSubclassOf<class UFGItemDescriptor> mFuelClass;

	/** How much energy the chainsaw consumes. In megawatt seconds (MWs) */
	UPROPERTY( EditDefaultsOnly, Category = "Chainsaw|Fuel" )
	float mEnergyConsumption;

	/** How many seconds should it take to saw down a tree */
	UPROPERTY( EditDefaultsOnly, Category = "Chainsaw" )
	float mSawDownTreeTime;

	/** How large radius of automatic pick up of foliage is when using chainsaw */
	UPROPERTY( EditDefaultsOnly, Category = "Chainsaw|Collateral" )
	float mCollateralPickupRadius;

	/** If collateral pickups should exclude chainsawable foliage when using chainsaw */
	UPROPERTY( Replicated, SaveGame, BlueprintReadWrite, Category = "Chainsaw|Collateral" )
	bool mIsAOEOn = false;

	/** The noise to make when using the chainsaw. */
	UPROPERTY( EditDefaultsOnly, Category = "Chainsaw" )
	TSubclassOf< class UFGNoise > mChainsawNoise;

	/**
	 * How much energy do we have stored left in the chainsaw (when we consume fuel from owners inventory
	 * then this is the energy stored here)
	 **/
	UPROPERTY( SaveGame, Replicated )
	float mEnergyStored;

	/** How much progress we have done when sawing on a tree. Locally simulated. */
	UPROPERTY()
	float mSawingProgress;

	/** Instance we are currently sawing on */
	int32 mSawingInstance;

	/** Component we are currently sawing on */
	UPROPERTY( Transient )
	class USceneComponent* mSawingComponent;

	/** Current state of the chainsaw, server controlled */
	UPROPERTY( ReplicatedUsing = OnRep_ChainsawState )
	EFGChainsawState mChainsawState;
}; 

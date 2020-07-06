// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGEquipment.h"
#include "../FGRecipeProducerInterface.h"
#include "FGEquipmentAttachment.h"
#include "../Inventory.h"
#include "FGBuildGun.generated.h"

 /**
  * States the build gun can be in.
  */
UENUM( BlueprintType )
enum class EBuildGunState : uint8
{
	BGS_NONE		= 0		UMETA( DisplayName = "None" ),
	BGS_MENU		= 1		UMETA( DisplayName = "Menu" ),
	BGS_BUILD		= 2		UMETA( DisplayName = "Build" ),
	BGS_DISMANTLE	= 3		UMETA( DisplayName = "Dismantle" ),
	BGS_MAX			= 4		UMETA( Hidden )
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildGunStateChanged, EBuildGunState, newState );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildGunRecipeChanged, TSubclassOf< class UFGRecipe >, newRecipe );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnRecipeSampled, TSubclassOf< class UFGRecipe >, newRecipe );


/**
 * Represents a state in the build gun, e.g. build, dismantle etc.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGBuildGunState : public UObject
{
	GENERATED_BODY()

public:
	UFGBuildGunState();

	/** For replicating more complicated objects. */
	virtual bool ReplicateSubobjects( class UActorChannel* channel, class FOutBunch* bunch, FReplicationFlags* repFlags );

	/** Mark this class as supported for networking */
	virtual bool IsSupportedForNetworking() const override;

	/** This is overloaded so that we can call Server/Client functions in this object by using the Callspace of the outer BuildGun. */
	int32 GetFunctionCallspace( UFunction* Function, void* Parameters, FFrame* Stack ) override;

	/** This is overloaded so that we can call Server/Client functions in this object by using the NetDriver of the outer BuildGun.*/
	bool CallRemoteFunction( UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack ) override;

	/** Checks if the outer build gun has authority. */
	UFUNCTION( BlueprintPure, Category = "BuildGunState" )
	bool HasAuthority() const;

	/** Get the build guns world. */
	virtual UWorld* GetWorld() const override;

	/** Enter this state. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void BeginState();

	/** Exit this state. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void EndState();

	/** Tick this state. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void TickState( float deltaTime );

	/** Is this state active. */
	UFUNCTION( BlueprintPure, Category = "BuildGunState" )
	FORCEINLINE bool IsActive() const{ return mIsActive; }

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void PrimaryFire();

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void PrimaryFireRelease();

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void SecondaryFire();

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void ModeSelectPressed();

		/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void ModeSelectRelease();


	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void BuildSamplePressed();

	/** If true, then the building is valid to sample in this state */
	virtual bool IsValidBuildingSample( class AFGBuildable* buildable ) const;

	/**
	 * We have sampled a new recipe
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState|Build" )
	void OnRecipeSampled( TSubclassOf<class UFGRecipe> recipe );

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void BuildSampleRelease();

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void ScrollDown();

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void ScrollUp();

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void ChangeScrollMode();

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void ChangeNoSnapMode();

	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void ChangeGuideLinesSnapMode( bool enabled );

	/**
	 * Get the owning build gun.
	 * @return A valid build gun.
	 */
	UFUNCTION( BlueprintPure, Category = "BuildGunState" )
	class AFGBuildGun* GetBuildGun() const;

	/** 
	 * Get's current percentage of Build delay progress. 
	 * @return Returns between 0-1. Returns 0 if no build is in progress 
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGunState" )
	float GetBuildGunDelayPercentage() const;

	/**
	 * Overrideable function that will test if the basic requirements
	 * for the current build state to perform its action is met.
	 * @return true if the conditions required to use the build gun are met.
	 */
	virtual bool CanBeginBuildGunDelay() const { return true; }

	/** 
	 * Get's the build delay message
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGunState" )
	FText GetBuildGunDelayMessage() const { return mActionMessage; }

	UFUNCTION( Category = "BuildGunState" )
	virtual void BeginBuildGunDelay();

	/** sets mActionStartTime to 0 */
	UFUNCTION( Category = "BuildGunState" )
	virtual void ResetBuildGunDelay();

	/** @return true if the build gun delay is complete, or is 0 (ie. always complete) */
	UFUNCTION( Category = "BuildGunState" )
	bool BuildGunDelayIsComplete();

	/** @return true if there is an delay on this state. */
	UFUNCTION( Category = "BuildGunState" )
	bool HasBuildGunDelay();
protected:
	/** If true, then we can sample buildings in this state */
	bool mCanSampleBuildingsInState;
private:
	/** Time (in seconds) it takes for the action (eg. Build, dismantle) */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGunState" )
	float mActionDelay;

	/** internal time for when action has begun (eg. Build, dismantle). if 0, ignore. */
	float mActionStartTime;

	/** Text to show while action is in progress */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGunState" )
	FText mActionMessage;

	/** Is this state active? */
	bool mIsActive;

public:
	FORCEINLINE ~UFGBuildGunState() = default;
};

/**
 * The latest iteration of a pink box with a red button.
 */
UCLASS()
class FACTORYGAME_API AFGBuildGun : public AFGEquipment, public IFGRecipeProducerInterface
{
	GENERATED_BODY()

public:
	AFGBuildGun();

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual bool ReplicateSubobjects( class UActorChannel* channel, class FOutBunch* bunch, FReplicationFlags* repFlags ) override;
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;

	// Begin AFGEquipment interface
	virtual bool ShouldSaveState() const override;
	virtual void Equip( class AFGCharacterPlayer* character );
	virtual void UnEquip();
	// End AFGEquipment interface

	/** @return The FHitResult of this build gun. */
	FORCEINLINE FHitResult& GetHitResult(){ return mHitResult; }

	/**
	 * Gets all the recipes that can be built using this build gun.
	 * @note This is an expensive operation so cache the result.
	 * @param out_recipes Returns all recipes available to this build gun.
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGun|Recipe" )
	void GetAvailableRecipes( TArray< TSubclassOf< class UFGRecipe > >& out_recipes ) const;

	/** Convenience function to get the cost for a recipe. */
	UFUNCTION( BlueprintCallable, Category = "BuildGun|Recipe" )
	TArray< FItemAmount > GetCostForRecipe( TSubclassOf< class UFGRecipe > recipe ) const;

	/** Get the inventory to charge when building and refunding when dismantling. */
	UFUNCTION( BlueprintPure, Category = "BuildGun|Inventory" )
	class UFGInventoryComponent* GetInventory() const;
	
	/** Gets BuildGunState depending on the enum passed */
	UFUNCTION( BlueprintPure, Category = "BuildGun|State" )
	FORCEINLINE class UFGBuildGunState* GetBuildGunStateFor( EBuildGunState gunState ) const { return mStates[ (uint8)gunState ]; }

	/** Gets the build gun delay progress from current state as a percentage between 0-1 */
	UFUNCTION( BlueprintPure, Category = "BuildGun|State" )
	float GetCurrentBuildGunDelayPercentage() const;

	/** Gets the build gun delay message from current state */
	UFUNCTION( BlueprintPure, Category = "BuildGun|State" )
	FText GetCurrentBuildGunDelayMessage() const;

	/** @return true if the produce the same buildable; false if not. */
	UFUNCTION( BlueprintCallable, Category = "BuildGun|Recipe" )
	bool CompareActiveRecipeTo( TSubclassOf< class UFGRecipe > recipe );

	/** Checks if the buildgun is in the state we send in  */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	bool IsInState( EBuildGunState inState );

	/**
	 * Only the server is allowed to build stuff so all the actions are executed on the server but may be simulated on the client.
	 * Simulations may be sounds and the brrrrrrrring progress bar when selling.
	 *****************************************************************************/
	void OnPrimaryFirePressed();
	void OnPrimaryFireReleased();
	void OnSecondaryFirePressed();
	void OnSecondaryFireReleased();
	void OnModeSelectPressed();
	void OnModeSelectReleased();
	void OnScrollDownPressed();
	void OnScrollUpPressed();
	void OnScrollModePressed();
	void OnNoSnapModePressed();
	void OnSnapToGuideLinesPressed();
	void OnSnapToGuideLinesReleased();
	void OnDismantleToggleMultiSelectStatePressed();
	void OnDismantleToggleMultiSelectStateReleased();
	void OnBuildSamplePressed();
	void OnBuildSampleReleased();

	/**
	 * Only the client handles categories, recipes.
	 * This enables faster menu feedback and that the menus can be completely separated from the build gun implementation.
	 * The client knows about every recipe available and their category and may organize them however it wants to.
	 * When it want to set a recipe to active it tells the server to change the active recipe, hence no need for the server to handle the categories.
	 *****************************************************************************/

	/**
	 * (Simulated)
	 * Set the build gun in dismantling mode.
	 * @note Must be called on the local player.
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	void GotoMenuState();

	/**
	 * (Simulated)
	 * Set the build gun in building mode and activates the given recipe.
	 * @note Must be called on the local player.
	 *
	 * @param recipe The recipe to set as active. This may be nullptr, e.g. to hide hologram.
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	void GotoBuildState( TSubclassOf< class UFGRecipe > recipe );

	/**
	 * (Simulated)
	 * Set the build gun in dismantling mode.
	 * @note Must be called on the local player.
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	void GotoDismantleState();

	void SetAllowRayCleranceHit( bool allow );
protected:
	/** Add custom bindings for this equipment */
	virtual void AddEquipmentActionBindings() override;
private:
	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_PrimaryFire();

	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SecondaryFire();

	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_ScrollDown();

	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_ScrollUp();

	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_ScrollMode();

	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_NoSnapMode();

	/** Lets the server switch to build state. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_GotoBuildState( TSubclassOf< class UFGRecipe > recipe );

	/**
	 * (Simulated)
	 * Set the build gun in the given state.
	 * Some states may require additional parameters so use the GotoXyzState helper functions.
	 * @note Must be called on the local player.
	 */
	void GotoState( EBuildGunState state );

	/** Lets the server switch state. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_GotoState( EBuildGunState state );

	/** Switch the current state */
	void GotoStateInternal( EBuildGunState state );

private:
	FORCEINLINE UFGBuildGunState* GetState( EBuildGunState state ) const { return mStates[ ( uint8 )state ]; }
	template< class C > FORCEINLINE C* GetState( EBuildGunState state ) const { return CastChecked< C >( GetState( state ) ); }

public:
	/** Called when the build gun state changes. */
	UPROPERTY( BlueprintAssignable, Category = "BuildGun|State" )
	FOnBuildGunStateChanged mOnStateChanged;

	/** Called when the build gun build state receives a new recipe. This May be called prior to OnStateChanged. */
	UPROPERTY( BlueprintAssignable, Category = "BuildGun|Recipe" )
	FOnBuildGunRecipeChanged mOnRecipeChanged;

	/** Called when the build gun have sampled a new recipe. */
	UPROPERTY( BlueprintAssignable, Category = "BuildGun|Recipe" )
	FOnRecipeSampled mOnRecipeSampled;

protected:
	/** Trace distance for this build gun when building and dismantling. */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGun" )
	float mBuildDistanceMax;

	/** The state to use when operating the menus. */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGun|State" )
	TSubclassOf< class UFGBuildGunState > mMenuStateClass;

	/** The state to use when building. */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGun|State" )
	TSubclassOf< class UFGBuildGunStateBuild > mBuildStateClass;

	/** The state to use when dismantling. */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGun|State" )
	TSubclassOf< class UFGBuildGunStateDismantle > mDismantleStateClass;

	bool mAllowCleranceRayHits = false;

private:
	/** All the states. */
	UPROPERTY( Replicated )
	UFGBuildGunState* mStates[ ( uint8 )EBuildGunState::BGS_MAX ];

	/** State to enter on the next equip. */
	EBuildGunState mPendingEntryState;

	/** Result of the latest trace. */
	UPROPERTY()
	FHitResult mHitResult;

	/**
	 * (Simulated)
	 * Current build gun state.
	 * The client sets this locally and tells the server I want this state.
	 */
	UPROPERTY()
	EBuildGunState mCurrentStateEnum;

	/** @see mCurrentStateIndex. */
	UPROPERTY()
	UFGBuildGunState* mCurrentState;

	/** wait for primary fire release event before re-initiating another build gun fire. Does not affect click+hold. */
	bool mWaitingForPrimaryFireRelease;

	bool mHasHookedUpBuildStateUserSettings = false; //[DavalliusA:Thu/23-01-2020] not happy with this, but didn't find a function that is only called once and where we know we have a local instagator or not 

public:
	FORCEINLINE ~AFGBuildGun() = default;
};

/**
 * Attachment for the build gun.
 */
UCLASS()
class FACTORYGAME_API AFGBuildGunAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()

public:
	FORCEINLINE ~AFGBuildGunAttachment() = default;
};

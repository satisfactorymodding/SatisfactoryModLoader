// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "Interfaces/Interface_ActorSubobject.h"
#include "FGHotbarShortcut.generated.h"

class UFGHotbarShortcut;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnShortcutActiveStatusChanged, UFGHotbarShortcut*, shortcut );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnShortcutBound, UFGHotbarShortcut*, shortcut );


/**
 * Base class for items that can be put in the players hotbar, e.g. recipe shortcuts.
 */
UCLASS( Abstract, Blueprintable )
class FACTORYGAME_API UFGHotbarShortcut : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	/** Mark this class as supported for networking */
	virtual bool IsSupportedForNetworking() const override{ return true; }
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;
	virtual bool CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack) override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin UObject interface
	virtual UWorld* GetWorld() const override;
	// End UObject interface
	
	/** Executes this shortcut for the given player controller */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category= "Shortcut" )
	void Execute( class AFGPlayerController* owner );
	
	/**
	 * Called every frame on the active hotbar to refresh whenever this shortcut is active.
	 * This is much more flexible when having delegates for various shortcut types and
	 * does not add much overhead as all IsActive calls are extremely lightweight.
	 */
	virtual void UpdateActiveShortcut( class AFGPlayerController* owner );
	
	UFUNCTION( BlueprintPure, BlueprintNativeEvent, Category = "Shortcut" )
	bool IsValidShortcut( class AFGPlayerController* owner ) const;

	UFUNCTION( BlueprintPure, BlueprintNativeEvent, Category = "Shortcut" )
	UTexture2D* GetDisplayImage() const;

	UFUNCTION( BlueprintPure, BlueprintNativeEvent, Category = "Shortcut" )
	bool IsActive( class AFGPlayerController* owner ) const;

	/** @return true if this shortcut is exactly the same as the provided one */
	UFUNCTION( BlueprintPure, BlueprintNativeEvent, Category = "Shortcut" )
	bool IsSame( UFGHotbarShortcut* shortcut) const;

	/** Describe the contents of this shortcut, e.g. a recipe or emote it holds */
	UFUNCTION( BlueprintPure, BlueprintNativeEvent, Category = "Shortcut" )
	FString DescribeShortcut() const;

	/** Returns the index of this shortcut in the hotbar, never changes for a given shortcut object */
	FORCEINLINE int32 GetShortcutIndex() const { return mShortcutIndex; }
	
	/** Returns true if the shortcut is active. Uses the cached value only computed for the current hotbar */
	FORCEINLINE bool IsActiveShortcutCached() const { return mIsShortcutActiveCached; }

	/** Notifies the owning hotbar that the shortcut has been changed and needs to be updated */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void NotifyShortcutChanged();
private:
	void Internal_TryInitializeShortcut();
	void Internal_ConditionalDestroyShortcut();
	
protected:
	
	/** Initialize this shortcut by binding to the relevant delegates or using data available in the world. */
	UFUNCTION( BlueprintNativeEvent, Category = "Shortcut" )
	void InitializeShortcut();

	/** Destroy the shortcut by unsubscribing from all of the delegates */
	UFUNCTION( BlueprintNativeEvent, Category = "Shortcut" )
	void DestroyShortcut();

	/** Called when the subsystems are available to be subscribed to on the current side */
	UFUNCTION()
	virtual void OnClientSubsystemsValid();

	/** Attempts to initialize with the game state if we have one, otherwise it will try again next tick */
	void TryInitializeWithGameState();
public:
	/** Called when the shortcut changes the status from being inactive to being active or vice versa */
	UPROPERTY( BlueprintAssignable, Category = "Shortcut" )
	FFGOnShortcutActiveStatusChanged mOnActiveStatusChanged;

	UPROPERTY( BlueprintAssignable, Category = "Shortcut" )
	FFGOnShortcutBound mOnShortcutBound;
protected:
	friend class UFGPlayerHotbar;

	UFUNCTION()
	void OnRep_ShortcutBound();

	/** Resets mShortcutJustBound, indicating that we have played the "Shortcut Bound" notification on the client */
	UFUNCTION( Client, Unreliable )
	void Client_ResetShortcutJustBound();
	
	/** Get the buildgun from a controller */
	class AFGBuildGun* GetBuildGun( class AFGPlayerController* playerController ) const;

	/** Get a valid player that can use the shortcut, will be null if it's not allowed for some reason */
	class AFGCharacterPlayer* GetValidPlayerCharacter( class AFGPlayerController* playerController ) const;

	/** Marks the shortcut as "Just Bound" */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void SetShortcutJustBound();

	/** Called to fire the delegate if the shortcut has just been bound */
	void TryFireShortcutBoundDelegate();

	/**
	 * Index of the shortcut in the hotbar.
	 * Used to be able to dispatch shortcut events when the object is destroyed by the replication.
	 * We do not need a RepNotify for it as the object should always receive it by the end object is killed by replication.
	 */
	UPROPERTY( SaveGame, Replicated )
	int32 mShortcutIndex;

	/** True if the shortcut has just been bound, e.g. has recently changed it's recipe or is a completely new shortcut. Used to dispatch a "Bound to Hotbar" notification on the client */
	UPROPERTY( ReplicatedUsing=OnRep_ShortcutBound )
	bool mShortcutJustBound;
	
	/** True if the shortcut is currently active */
	uint8 mIsShortcutActiveCached : 1;
	/** True if we have somebody listening to mOnShortcutBound and can fire it */
	uint8 mHasOnShortcutBound: 1;
	/** True if the shortcut has been initialized already */
	uint8 mIsShortcutInitialized : 1;
	/** True if we have subscribed to the game state already */
	uint8 mInitializedWithGameState : 1;
};

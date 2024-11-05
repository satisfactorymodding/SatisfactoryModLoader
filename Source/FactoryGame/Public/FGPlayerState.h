//Copyright 2016 Coffee Stain Studios.All Rights Reserved.

#pragma once

#include "FGActorRepresentation.h"
#include "FGCharacterPlayer.h"
#include "FGCreatureSubsystem.h"
#include "FGFactoryColoringTypes.h"
#include "FGHotbarShortcut.h"
#include "FGInventoryToRespawnWith.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/Interface_ActorSubobject.h"
#include "Online/ClientIdentification.h"
#include "PlayerCustomizationData.h"
#include "ShoppingList/FGShoppingListComponent.h"
#include "UI/Message/FGMessageBase.h"
#include "FGPlayerState.generated.h"

class UFGPlayerHotbar;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildableConstructedNew, TSubclassOf< class UFGItemDescriptor >, itemDesc );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnHotbarUpdatedForMaterialDescriptor, TSubclassOf< class UFGFactoryCustomizationDescriptor_Material >, materialDesc );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnPublicTodoListUpdated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSlotDataUpdated, class AFGPlayerState*, playerState  );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FFGOnHotbarSlotUpdated, UFGPlayerHotbar*, hotbar, int32, index );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FFGOnActiveHotbarIndexChanged, UFGPlayerHotbar*, hotbar, int32, hotbarIndex );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FFGOnHotbarsAvailable );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnHotbarSlotUnbound, int32, slotIndex );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnAdminStateChanged, AFGPlayerState*, playerState, bool, isAdmin );

/**
 * The color data for a player
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPlayerColorData
{
	GENERATED_BODY();

	/** The color of the players ping */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Color")
	FLinearColor PingColor;

	/** The color of the players nametag above their head, and in the UI */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Color")
	FLinearColor NametagColor;

	FORCEINLINE bool operator==( const FPlayerColorData& other ) const{
		return other.PingColor == PingColor && other.NametagColor == NametagColor;
	}
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPlayerCustomizationDataChanged, const FPlayerCustomizationData&, CustomizationData );

/** Represents the hotbar of the player, with various shortcuts attached to it's slots */
UCLASS( BlueprintType, Within = FGPlayerState )
class FACTORYGAME_API UFGPlayerHotbar : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	UFGPlayerHotbar();

	// Begin UObject interface
	virtual void PostInitProperties() override;
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual UWorld* GetWorld() const override;
	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;
	virtual bool CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack) override;
	// End UObject interface
	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Returns the hotbar shortcut at the specified index */
	UFUNCTION( BlueprintPure, Category = "Hotbar" )
	UFGHotbarShortcut* GetShortcutAtIndex( int32 index ) const;

	/** Creates the shortcut of the specified type and sets it to the provided index */
	UFUNCTION( BlueprintCallable, Category = "Hotbar", DisplayName = "CreateShortcutAtIndex", meta = ( DeterminesOutputType = "inClass" ) )
	UFGHotbarShortcut* K2_CreateShortcutAtIndex( int32 index, TSubclassOf<UFGHotbarShortcut> inClass, bool silent = false );

	/** Removes the shortcut at the index, leaving a blank space */
	UFUNCTION( BlueprintCallable, Category = "Hotbar" )
	void RemoveShortcutAtIndex( int32 index, bool silent = false );

	/** Collapses duplicate shortcuts into the specified shortcut index, leaving empty slots behind */
	UFUNCTION( BlueprintCallable, Category = "Hotbar" )
	void CollapseDuplicateShortcuts( int32 index );

	/** Attempts to copy either the entire hotbar or the shortcut at the specified index into this hotbar */
	UFUNCTION( BlueprintCallable, Category = "Hotbar" )
	void CopyFromHotbar( const UFGPlayerHotbar* otherHotbar, int32 filterIndex = -1 );
	
	/**
	 * Convenient accessor for CreateShortcutAtIndex that automatically casts to the correct type
	 * Keep in mind that it is the shortcut implementation responsibility to notify the hotbar of it's changes via OnShortcutChanged
	 */
	template<typename T>
	FORCEINLINE T* CreateShortcutAtIndex( int32 index, TSubclassOf<T> inClass = T::StaticClass(), bool silent = false )
	{
		return Cast<T>( K2_CreateShortcutAtIndex( index, inClass, silent ) );
	}

	template<typename T>
	FORCEINLINE T* GetShortcutAtIndex( int32 index ) const
	{
		return Cast<T>( GetShortcutAtIndex( index ) );
	}

	/** @return the amount of shortcuts in the hotbar */
	UFUNCTION( BlueprintPure, Category = "Hotbar" )
	FORCEINLINE int32 GetNumShortcuts() const { return mShortcuts.Num(); }

	/** Sets the recipe at the specified hotbar index. */
	UFUNCTION( BlueprintCallable, Category = "Hotbar | Utility" )
	void SetRecipeShortcutAtIndex( int32 index, TSubclassOf<UFGRecipe> recipe, bool silent = false );

	/** Sets the factory customization at the specified hotbar index */
	UFUNCTION( BlueprintCallable, Category = "Hotbar | Utility" )
	void SetFactoryCustomizationShortcutAtIndex( int32 index, TSubclassOf<UFGCustomizationRecipe> customization, bool silent = false );

	/** Sets the blueprint shortcut at the specified index */
	UFUNCTION( BlueprintCallable, Category = "Hotbar | Utility" )
	void SetBlueprintAtIndex( int32 index, const FString& blueprintName, bool silent = false );

	/** Sets the emote shortcut at the specified index */
	UFUNCTION( BlueprintCallable, Category = "Hotbar | Utility" )
	void SetEmoteAtIndex( int32 index, TSubclassOf<UFGEmote> inEmote, bool silent = false );

	/** Called each tick to update the active status of the shortcuts in the active hotbar */
	void UpdateActiveHotbar( AFGPlayerController* owner );
	
	/** Loads data from the legacy hotbar */
	void Internal_LoadFromLegacyData( const struct FHotbar& inLegacyHotbar );

	/** Called when the state of the shortcut object changes */
	void OnShortcutChanged( UFGHotbarShortcut* shortcut );

	void GetAllShortcuts( TArray<UFGHotbarShortcut*>& out_shortcuts ) const;

	FORCEINLINE TArray<UFGHotbarShortcut*> GetAllShortcuts() const { return mShortcuts; }

protected:
	UFUNCTION()
	void OnRep_Shortcuts();

	/** Called to notify the client that we have unbound the shortcut */
	UFUNCTION( Client, Unreliable )
	void Client_NotifyShortcutUnbound( int32 shortcutIndex );
	
	void Internal_DestroyShortcutAtIndex( int32 shortcutIndex, bool silent );
	void Internal_InitializeShortcutAtIndex( int32 shortcutIndex, UFGHotbarShortcut* newShortcut, bool silent );
public:
	/** Called when the hotbar slot is updated */
	UPROPERTY( BlueprintAssignable, Category = "Hotbar" )
	FFGOnHotbarSlotUpdated mOnHotbarSlotUpdated;

	/** Called when the shortcut has been unbound from the hotbar, e.g. when the hotbar slot becomes empty */
	UPROPERTY( BlueprintAssignable, Category = "Hotbar" )
	FFGOnHotbarSlotUnbound mOnHotbarSlotUnbound;

	DECLARE_MULTICAST_DELEGATE_OneParam( FOnShortcutConstructed, UFGHotbarShortcut* shortcut );

	FOnShortcutConstructed mOnShortcutConstructed;
	FOnShortcutConstructed mOnShortcutDestroyed;
	
protected:
	/** Shortcuts that this hotbar has, fixed size and with potential null pointers. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_Shortcuts )
	TArray< UFGHotbarShortcut* > mShortcuts;
	
private:
	
	/** Last shortcuts we had, for correctly distinguishing changes in RepNotify */
	TArray<TWeakObjectPtr<UFGHotbarShortcut>> mLastShortcuts;
};

/** Legacy struct used to represent hotbars in the game */
USTRUCT()
struct FACTORYGAME_API FHotbar
{
	GENERATED_BODY();
	
	UPROPERTY( SaveGame )
	TArray< class UFGHotbarShortcut* > HotbarShortcuts;
};

USTRUCT()
struct FACTORYGAME_API FSubCategoryMaterialDefault
{
	GENERATED_BODY();

	FSubCategoryMaterialDefault() {}
	FSubCategoryMaterialDefault( const TSubclassOf< class UFGCategory > cat, const TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > desc ) 
	{
		Category = cat;
		MaterialDesc = desc;
	}

	UPROPERTY( SaveGame )
	TSubclassOf< class UFGCategory > Category;

	UPROPERTY( SaveGame )
	TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > MaterialDesc;
};

USTRUCT( BlueprintType )
struct FShoppingListSettings
{
	GENERATED_BODY()
	
	UPROPERTY( SaveGame, BlueprintReadWrite, EditAnywhere )
	bool PublicTodoListVisibilty = false;
	
	UPROPERTY( SaveGame, BlueprintReadWrite, EditAnywhere )
	bool PrivateTodoListVisibilty = false;

	UPROPERTY( SaveGame, BlueprintReadWrite, EditAnywhere )
	bool RecipeListVisibilty = false;
	
	UPROPERTY( SaveGame, BlueprintReadWrite, EditAnywhere )
	float Size = 0.f;
};

USTRUCT( BlueprintType )
struct FPlayerRules
{
	GENERATED_BODY()
	
	UPROPERTY( SaveGame )
	bool HasInitialized = false;
	
	UPROPERTY( SaveGame )
	bool NoBuildCost = false;

	UPROPERTY( SaveGame )
	bool FlightMode = false;

	UPROPERTY( SaveGame )
	bool GodMode = false;
	
	void GetDebugOverlayData( TArray<FString>& out_debugOverlayData ) const;
};

UCLASS()
class FACTORYGAME_API AFGPlayerState final : public APlayerState, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGPlayerState();

	// Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
	// End UObject Interface

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface
	
	// Begin APlayerState interface
	virtual void CopyProperties( APlayerState* playerState ) override;
	virtual void ClientInitialize(AController* C) override;
	virtual void RegisterPlayerWithSession(bool bWasFromInvite) override;
	virtual void UnregisterPlayerWithSession() override;
	// End APlayerState interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	void RegisterPlayerWithSessionRemote(bool bWasFromInvite);
	void RegisterPlayerWithSessionAuthoritative(bool bWasFromInvite);
	
	/** Set the pawn we controls (it should be the character, not a vehicle) */
	FORCEINLINE void SetOwnedPawn( class APawn* pawn ){ mOwnedPawn = pawn; }

	/** Get the character we control (not a vehicle) */
	FORCEINLINE class APawn* GetOwnedPawn() const{ return mOwnedPawn; }

	/** Return true if we have received our initial items */
	FORCEINLINE bool HasReceiveInitialItems() const { return mHasReceivedInitialItems; }

	/** Mark this character as it has received its initial items */
	FORCEINLINE void MarkAsReceivedInitialItems(){ mHasReceivedInitialItems = true; }
	FORCEINLINE void UnmarkAsReceivedInitialItems(){ mHasReceivedInitialItems = false; }

	/** Get the slot the player has claimed */
	UFUNCTION(BlueprintPure, Category = "FactoryGame|Slots" )
	FORCEINLINE int32 GetSlotNum() const{ return mSlotNum; }

	/** Set the slot number of this player */
	FORCEINLINE void SetSlotNum( const int32 slotNr ){ mSlotNum = slotNr; }
	
	/** Set the color data for this player */
	void SetPlayerColorData( FPlayerColorData slotData );

	/** get the color data for this player */
	FORCEINLINE FPlayerColorData GetSlotData() const { return mPlayerColorData; }

	/** Gets the player rules for this player. */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Rules" )
	const FPlayerRules& GetPlayerRules() const { return mPlayerRules; }
	
	/** Used to get the creature hostility against this player. */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Rules" )
	EPlayerKeepInventoryMode GetKeepInventoryMode() const { return mKeepInventoryMode; }

	/** Used to get the creature hostility against this player. */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Rules" )
	EPlayerHostilityMode GetCreatureHostility() const { return mCreatureHostilityMode; }
	
	/** Used to set the creature hostility against this player. */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Rules" )
	void SetCreatureHostility( EPlayerHostilityMode hostility );

	UFUNCTION( Server, Reliable )
	void Server_SetCreatureHostility( EPlayerHostilityMode hostility );

	/** Used to set Keep Inventory on this player. */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Rules" )
	void SetKeepInventory( const EPlayerKeepInventoryMode keepInventoryMode );

	UFUNCTION( Server, Reliable )
	void Server_SetKeepInventory( const EPlayerKeepInventoryMode keepInventoryMode );
	
	/** Get the unique ID of the user from the online subsystem */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Networking" )
	FString GetUserName() const;

	/** Get the unique ID of the user from the online subsystem */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Networking" )
	FString GetUserID() const;

	/** Get the unique ID of the user from the online subsystem */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Networking" )
	FUniqueNetIdRepl GetUniqueNetId() const;

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Message" )
	TArray< class UFGMessage* > GetPlayedMessages() const { return mPlayedMessages; }
	bool HasMessageBeenPlayed( class UFGMessage* message ) const;
	void MarkMessageAsPlayed( class UFGMessage* message );
	UFUNCTION( Server, Reliable )
	void Server_MarkMessageAsPlayed( class UFGMessage* message );
	/** Retrieves all important messages played so far and marks them as played. Useful for players who join mid-game */
	void FetchImportantMessages();

	/**
	 * Updates the index of the currently selected hotbar for this player
	 * Will sync it back to the client and fire the change delegate to notify the listeners such as player controller
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Hotbar" )
	void SetHotbarIndex( int32 newHotbarIndex );
	
	/** Returns the currently selected hotbar */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Hotbar" )
	UFGPlayerHotbar* GetActiveHotbar() const;

	/** Returns the currently selected hotbar index */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Hotbar" )
	FORCEINLINE int32 GetActiveHotbarIndex() const { return mCurrentHotbarIndex; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Hotbar" )
	FORCEINLINE int32 GetNumHotbars() const { return mPlayerHotbars.Num(); }

	/** Returns the hotbar at index */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Hotbar" )
	UFGPlayerHotbar* GetHotbarAtIndex( int32 hotbarIndex ) const;

	/** Returns the index matching the provided hotbar object, or INDEX_NONE if it does not belong to this player state */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Hotbar" )
	int32 FindHotbarIndex( UFGPlayerHotbar* hotbar ) const;

	/** Returns all hotbars that the player has. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Hotbar" )
	void GetAllHotbars( TArray<UFGPlayerHotbar*>& out_hotbars ) const;
	
	bool GetAndSetFirstTimeEquipped( class AFGEquipment* equipment );
	
	/** Get the controller owning this player state */
	class AFGPlayerController* GetOwningController() const;

	/** Get the HUD from the controller owning this player state */
	class AFGHUD* GetHUD() const;

	/** Get the Game UI from the controller owning this player state */
	class UFGGameUI* GetGameUI() const;

	/** Adds a new recipe to the list of new recipes. This is only for UI feedback and does not give the player the actual ability to use the recipe */
	void AddNewRecipe( TSubclassOf< UFGRecipe > recipe );

	/** Get all recipes that are new to the player. This is only for UI feedback */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Recipes" )
	void GetNewRecipes( TArray<TSubclassOf<class UFGRecipe>>& out_newRecipes ) const;

	/** Removes a recipe from the list of new recipes. This is only for UI feedback and does not remove the players ability to use the recipe */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipes" )
	void RemoveRecipe( TSubclassOf< UFGRecipe > recipe );

	/** Lets the server remove a recipe from the list of new recipes */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_RemoveRecipe( TSubclassOf< UFGRecipe > recipe );

	/** Gets number of slots for arm equipment */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Equipment" )
	FORCEINLINE int32 GetNumArmSlots() const { return mNumArmSlots; }

	/** Adds more arm slots ( can also be a negative number to decrease number of slots ) */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Equipment" )
	void AddArmSlots( int32 slotsToAdd );

	/** Get if we only should show affordable recipes in manufacturing widgets */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipes" )
	FORCEINLINE bool GetOnlyShowAffordableRecipes() const { return mOnlyShowAffordableRecipes; }

	/** Set if we only should show affordable recipes in manufacturing widgets */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipes" )
	void SetOnlyShowAffordableRecipes( bool enabled );

	/** Let server set if we only should show affordable recipes in manufacturing widgets */
	UFUNCTION( Server, Reliable, WithValidation, Category = "FactoryGame|Recipes" )
	void Server_SetOnlyShowAffordableRecipes( bool enabled );

	/** Get if we should we try to take items from inventory before central storage when building or crafting */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|CentralStorage" )
	FORCEINLINE bool GetTakeFromInventoryBeforeCentralStorage() const { return mTakeFromInventoryBeforeCentralStorage; }

	/** Set if we should we try to take items from inventory before central storage when building or crafting */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|CentralStorage" )
	void SetTakeFromInventoryBeforeCentralStorage( bool takeFromInventoryBeforeCentralStorage );

	/** Let server set if we should we try to take items from inventory before central storage when building or crafting  */
	UFUNCTION( Server, Reliable, Category = "FactoryGame|CentralStorage" )
	void Server_SetTakeFromInventoryBeforeCentralStorage( bool takeFromInventoryBeforeCentralStorage );
	
	/** Get if the central storage widget is expanded in the player inventory widget */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|CentralStorage" )
	FORCEINLINE bool IsCentralStorageInventoryWidgetExpanded() { return mCentralStorageInventoryWidgetExpanded; }

	/** Set if the central storage widget is expanded in the player inventory widget */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|CentralStorage" )
	void SetCentralStorageInventoryWidgetExpanded( bool centralStorageInventoryWidgetExpanded );

	/** Let server set if the central storage widget is expanded in the player inventory widget   */
	UFUNCTION( Server, Reliable, Category = "FactoryGame|CentralStorage" )
	void Server_SetCentralStorageInventoryWidgetExpanded( bool centralStorageInventoryWidgetExpanded );

	/** Get the item categories that the user have collapsed in manufacturing widgets  */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ItemCategory" )
	FORCEINLINE TArray< TSubclassOf< class UFGItemCategory > > GetCollapsedItemCategories() { return mCollapsedItemCategories; }

	/** Set if an item category is collapsed in manufacturing widgets  */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|ItemCategory" )
	void SetItemCategoryCollapsed( TSubclassOf< class UFGItemCategory > itemCategory, bool collapsed );

	/** Let server set if an item category is collapsed in manufacturing widgets  */
	UFUNCTION( Server, Reliable, WithValidation, Category = "FactoryGame|ItemCategory" )
	void Server_SetItemCategoryCollapsed( TSubclassOf< class UFGItemCategory > itemCategory, bool collapsed );
	
	/** Gets the filter for map representations */
	FORCEINLINE TArray< ERepresentationType > GetFilteredOutMapTypes() { return mFilteredOutMapTypes; }

	/** Gets the filter for compass representations */
	FORCEINLINE TArray< ERepresentationType > GetFilteredOutCompassTypes() { return mFilteredOutCompassTypes; }

	/** Sets the map filter visibility for the given representation */
	void SetMapFilter( ERepresentationType representationType, bool visible );

	/** Let server set the map filter visibility for the given representation */
	UFUNCTION( Server, Reliable, WithValidation, Category = "FactoryGame|Representation" )
	void Server_SetMapFilter( ERepresentationType representationType, bool visible );

	/** Sets the compass filter visibility for the given representation */
	void SetCompassFilter( ERepresentationType representationType, bool visible );
	
	/** Let server set the compass filter visibility for the given representation */
	UFUNCTION( Server, Reliable, WithValidation, Category = "FactoryGame|Representation" )
	void Server_SetCompassFilter( ERepresentationType representationType, bool visible );

	/** Get the map categories that the user have collapsed in map widget */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Representation" )
	FORCEINLINE TArray< ERepresentationType > GetCollapsedMapCategories() const { return mCollapsedMapCategories; }
	
	/** Get if a map category is collapsed in the map widget */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Representation" )
	FORCEINLINE bool GetMapCategoryCollapsed( const ERepresentationType mapCategory ) const { return mCollapsedMapCategories.Contains( mapCategory ); }

	/** Set if a map category is collapsed in the map widget */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Representation" )
	void SetMapCategoryCollapsed( ERepresentationType mapCategory, bool collapsed );
	
	/** Let server set if a map category is collapsed in the map widget */
	UFUNCTION( Server, Reliable, Category = "FactoryGame|Representation" )
	void Server_SetMapCategoryCollapsed( ERepresentationType mapCategory, bool collapsed );
	
	/** Get the custom map categories that the user have collapsed in map widget */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Representation" )
	FORCEINLINE TArray< FString > GetCollapsedCustomMapCategories() const { return mCollapsedCustomMapCategories; }
	
	/** Get if a custom map category is collapsed in the map widget */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Representation" )
	FORCEINLINE bool GetCustomMapCategoryCollapsed( const FString& customMapCategory ) const { return mCollapsedCustomMapCategories.Contains( customMapCategory ); }

	/** Set if a map category is collapsed in the map widget */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Representation" )
	void SetCustomMapCategoryCollapsed( const FString& customMapCategory, bool collapsed );

	/** Let server set if a map category is collapsed in the map widget */
	UFUNCTION( Server, Reliable, Category = "FactoryGame|Representation" )
	void Server_SetCustomMapCategoryCollapsed( const FString& customMapCategory, bool collapsed );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Color" )
	FORCEINLINE FLinearColor GetPingColor() const { return mPlayerColorData.PingColor; }
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Color" )
	FORCEINLINE FLinearColor GetNametagColor() const { return mPlayerColorData.NametagColor; }

	void UpdateOwningPawnActorRepresentation() const;

	FORCEINLINE void SetIsServerAdmin( const bool isAdmin );
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Admin" )
	
	FORCEINLINE bool IsServerAdmin() const{ return mIsServerAdmin; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Schematic" )
	FORCEINLINE TSubclassOf<UFGSchematicCategory> GetLastSelectedResourceSinkShopCategory() const { return mLastSelectedResourceSinkShopCategory; }
	
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Schematic" )
	void SetLastSelectedResourceSinkShopCategory( const TSubclassOf<UFGSchematicCategory> selectedCategory ) { mLastSelectedResourceSinkShopCategory = selectedCategory; }

	// Debug command to show all hotbars
	void DumpHotbars();

	/** Returns how many inventory slots the player has observed that they have */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Inventory" )
	int32 GetNumObservedInventorySlots() const { return mNumObservedInventorySlots; }

	/** Update the number of observed slots to how many we have unlocked */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Inventory" )
	void UpdateNumObservedInventorySlots();

	/** Is this schematic saved as a favorite in the awesome shop */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Awesome Shop" )
	bool IsShopFavorite( TSubclassOf<class UFGSchematic> schematic ) const;

	/** Get all schematics saved as a favorite in the awesome shop */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Awesome Shop" )
	TArray<TSubclassOf<class UFGSchematic>> GetShopFavorites() const;

	/** Save this schematic as a favorite in the awesome shop */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Awesome Shop" )
	void SaveAsShopFavorite( TSubclassOf<class UFGSchematic> schematic );

	/** Remove this schematic as a favorite in the awesome shop */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Awesome Shop" )
	void RemoveAsShopFavorite( TSubclassOf<class UFGSchematic> schematic );

	/** Remove all favorite schematic in the awesome shop */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Awesome Shop" )
	void RemoveAllShopFavorites();

	/** Get all the schematics and number of that schematic the player has in their shopping cart in the awesome shop */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Awesome Shop" )
	TMap< TSubclassOf< class UFGSchematic >, int32 > GetShoppingCart() const;

	/** Sets all the schematics and number of that schematic the player has in their shopping cart in the awesome shop */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Awesome Shop" )
	void SetShoppingCart( TMap< TSubclassOf< class UFGSchematic >, int32 > shoppingCart );
	
	FORCEINLINE TArray< TSubclassOf< class UFGMapArea > >* GetPlayerVisitedAreas() { return &mVisitedAreas; };

	/** Get the Custom Color Data for this player */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Custom Color" )
	FORCEINLINE FFactoryCustomizationColorSlot GetCustomColorData() const { return mCustomColorData; }

	/** 
	 * Sets the local color customization data. This color data is used when assigning a color with slot index INDEX_CUSTOM_COLOR_DATA (255)
	 * Will remote call on server if called by non-authority 
	 */
	UFUNCTION( BlueprintCallable, Category = "FactorGame|Custom Color" )
	void SetPlayerCustomizationSlotData( FFactoryCustomizationColorSlot customColorData );

	/** Sets the user color data on the server. The server in turn will use this to color a building with the correct data when the player paints with their custom color */
	UFUNCTION( Server, Reliable, Category = "FactoryGame|Custom Color" )
	void Server_SetPlayerCustomizationSlotData( FFactoryCustomizationColorSlot customColorData );
	
	/** Returns the current customization data for the player */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Player Customization" )
	FORCEINLINE FPlayerCustomizationData const& GetPlayerCustomizationData() const { return mPlayerCustomizationData; }

	/** Updates the customization data for the player. Safe to call on the owning client. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Player Customization" )
	void SetPlayerCustomizationData( const FPlayerCustomizationData& NewCustomizationData );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Player Customization" )
	void SetPlayerEquipmentCustomizationData(TSubclassOf<AFGEquipment> EquipmentType,TSubclassOf<UFGPlayerEquipmentSkinCustomizationDesc> NewSkin );

	/* Can be null!*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Player Customization" )
	TSubclassOf<UFGPlayerEquipmentSkinCustomizationDesc> GetCurrentSkinDescForEquipment(TSubclassOf<AFGEquipment> EquipmentType) const;

	/** Get the Users saved default material desc for a given category (can return null) */
	UFUNCTION()
	TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > GetSavedMatDescForBuildableCategory( TSubclassOf< class UFGCategory > category, TSubclassOf< class UFGCategory > subCategory );

	/** Sets a players default material desc for a given category. If called by client will trigger a server call to set it remotely */
	UFUNCTION()
	void SetSavedMatDescForBuildableCategory( TSubclassOf< class UFGCategory > category, TSubclassOf< UFGFactoryCustomizationDescriptor_Material > materialDesc, bool skipRep = false );

	UFUNCTION( Server, Reliable )
	void Server_SetSavedMatDescForBuildableCategory( TSubclassOf< class UFGCategory > category, TSubclassOf< UFGFactoryCustomizationDescriptor_Material > materialDesc );

	/** Get the Users saved (global) default material desc for a given material category (can return null) */
	UFUNCTION()
	TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > GetSavedMatDescForMaterialCategory( TSubclassOf< class UFGCategory > category );

	/** Sets a players default material desc. If called by client will trigger a server call to set it remotely */
	UFUNCTION()
	void SetSavedMatDescForMaterialCategory( TSubclassOf< class UFGCategory > category, TSubclassOf< UFGFactoryCustomizationDescriptor_Material > materialDesc, bool updateHotbarShortcuts = false );

	UFUNCTION( Server, Reliable )
	void Server_SetSavedMatDescForMaterialCategory( TSubclassOf< class UFGCategory > category, TSubclassOf< UFGFactoryCustomizationDescriptor_Material > materialDesc );

	UFUNCTION()
	void UpdateHotbarShortcutsForMaterialDesc( TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > newDefaultMaterialDesc );

	UFUNCTION( BlueprintCallable, Category = "Todo List" )
	void SetPublicTodoList( const FString& newTodoList );
	
	UFUNCTION( Server, Reliable )
	void Server_SetPublicTodoList( const FString& newTodoList );
	
	UFUNCTION( Client, Reliable )
	void Client_UpdatePublicTodoList( const FString& updatedTodoList );
	
	UFUNCTION( BlueprintCallable, Category = "Todo List" )
	void SetPrivateTodoList( const FString& newTodoList );

	UFUNCTION( Server, Reliable )
	void Server_SetPrivateTodoList( const FString& newTodoList );

	UFUNCTION( BlueprintPure, Category = "Todo List" )
	FString GetPublicTodoList() const;
	UFUNCTION( BlueprintPure, Category = "Todo List" )
	FString GetPrivateTodoList() const { return mPrivateTodoList; }

	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	void SetShoppingListSettings( const FShoppingListSettings& newShoppingListSettings );

	UFUNCTION( Server, Reliable )
	void Server_SetShoppingListSettings( const FShoppingListSettings& newShoppingListSettings );
	
	UFUNCTION( BlueprintPure, Category = "Shopping List" )
	FORCEINLINE FShoppingListSettings GetShoppingListSettings() const { return mShoppingListSettings; }
	
	UFUNCTION( BlueprintCallable, Category = "Factory Clipboard" )
	void CopyFactoryClipboard( UObject* object );
	UFUNCTION( BlueprintCallable, Category = "Factory Clipboard" )
	void PasteFactoryClipboard( UObject* object );

	UFUNCTION( BlueprintPure, Category = "Widget" )
	UPARAM( DisplayName = "openedInThisSave" ) bool GetWidgetHasBeenOpened( TSubclassOf< class UUserWidget > widget, bool& openedThisSession );
	/** Set if a widget have been opened. If save is true it will persist between saves. Otherwise it's per session only */
	UFUNCTION( BlueprintCallable, Category = "Widget" )
	void SetWidgetHasBeenOpened( TSubclassOf< class UUserWidget > widget, bool save );
	UFUNCTION( Server, Reliable )
	void Server_SetWidgetHasBeenOpened( TSubclassOf< class UUserWidget > widget );

	UFUNCTION( BlueprintPure, Category = "Shopping List"  )
	UFGShoppingListComponent* GetShoppingListComponent() const { return mShoppingListComponent; }

	// On recipe constructed could mean both constructing buildings and crafting items
	UFUNCTION( Client, Reliable )
	void Client_OnRecipeConstructed( TSubclassOf< class UFGRecipe > recipe, int32 numConstructed );
	void Native_OnRecipeConstructed( TSubclassOf< class UFGRecipe > recipe, int32 numConstructed );
	void Native_OnBlueprintConstructed( const FString& blueprintName, int32 numConstructed );

	UFUNCTION()
	void Native_OnSchematicPurchased( TSubclassOf< class UFGSchematic > schematic );

	/** Get if an item are pinned for central storage UI */
	UFUNCTION( BlueprintPure, Category = "Central Storage" )
	bool IsCentralStorageItemPinned( TSubclassOf< UFGItemDescriptor > itemDescriptor ) const;
	/** Set if an item are pinned for central storage UI */
	UFUNCTION( BlueprintCallable, Category = "Central Storage" )
	void SetCentralStorageItemPinned( TSubclassOf< UFGItemDescriptor > itemDescriptor, bool pinned );
	UFUNCTION( Server, Reliable )
	void Server_SetCentralStorageItemPinned( TSubclassOf< UFGItemDescriptor > itemDescriptor, bool pinned );

	// Not the prettiest solution but handles when blueprints are removed. We should have an event in blueprint subsystem instead
	UFUNCTION( Server, Reliable, BlueprintCallable )
	void Server_OnBlueprintRemoved( const FString& blueprintName );
	UFUNCTION( Client, Reliable )
	void Client_OnBlueprintRemoved( const FString& blueprintName );

	// Only for migration purposes.
	UFUNCTION( BlueprintImplementableEvent )
	TArray< FShoppingListRecipeEntry > GetAndClearShoppingListForMigration();
	
	/** Checks if the player state is in the player array. Tried to use IsInactive but it's not updated when a player state is loaded and is inactive.
	 *  And I don't want to start changing that logic since other things might depend on it. -K2
	 */
	bool IsInPlayerArray();

	void SetFlightMode( const bool flightMode );
	UFUNCTION( Server, Reliable )
	void Server_SetFlightMode( const bool flightMode );

	void SetGodMode( const bool godMode );
	UFUNCTION( Server, Reliable )
	void Server_SetGodMode( const bool godMode );

	bool IsPlayerSpecificSchematicPurchased( TSubclassOf< class UFGSchematic > schematic );
	void GiveAccessToPlayerSpecificSchematic( TSubclassOf< class UFGSchematic > schematic );

	void SetClientIdentity(const FClientIdentityInfo& clientIdentity);
	const FClientIdentityInfo& GetClientIdentity() const;

protected:
	void Native_OnFactoryClipboardCopied( UObject* object, class UFGFactoryClipboardSettings* factoryClipboard );
	void Native_OnFactoryClipboardPasted( UObject* object, class UFGFactoryClipboardSettings* factoryClipboard );
	
	UFUNCTION()
	void OnRep_PlayerHotbars();

	UFUNCTION()
	void OnRep_CurrentHotbarIndex();
	
	UFUNCTION()
	void OnRep_PlayerColorData();

	UFUNCTION()
	void OnRep_PlayerRules();

	UFUNCTION()
	void OnRep_PlayerCustomizationData();

	UFUNCTION()
	void OnRep_IsServerAdmin();
	
	void CreateDefaultHotbars();

	/** Updates the recipe of the provided shortcut on the server side */
	UFUNCTION( Server, Reliable )
	void Server_UpdateRecipeShortcut( UFGPlayerHotbar* hotbar, int32 shortcutIndex, TSubclassOf<UFGRecipe> newRecipe );

	/** Called to propagate the customization data change to the server */
	UFUNCTION( Server, Reliable )
	void Server_SetPlayerCustomizationData( const FPlayerCustomizationData& NewCustomizationData );
private:
	/** Server function for updating number observed inventory slots */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_UpdateNumObservedInventorySlots();

	void Native_OnPlayerColorDataUpdated();

	void SetupPlayerSettings();

	void SetupPlayerRules();

	void PushPlayerRulesToAdvancedGameSettings();

	void OnCreatureHostilityModeUpdated( FString strId, FVariant value );
	void OnNoBuildCostUpdated( FString strId, FVariant value );
	void OnKeepInventoryUpdated( FString strId, FVariant value );
	void OnFlightModeUpdated( FString strId, FVariant value );
	void OnGodModeUpdated( FString strId, FVariant value );

	void SetNoBuildCost( const bool noBuildCost );
	UFUNCTION( Server, Reliable )
	void Server_SetNoBuildCost( const bool noBuildCost );

	UFUNCTION()
	void OnRep_PlayerSpecificSchematics( TArray< TSubclassOf< UFGSchematic > > previousPlayerSpecificSchematics );
	void ListenForSchematicPurchased();

	/** Called when either the active hotbar index or the object itself changes */
	void UpdateActiveHotbarState();
	
	void SubscribeToHotbar( UFGPlayerHotbar* hotbar );
	void UnsubscribeFromHotbar( UFGPlayerHotbar* hotbar );
	void OnShortcutConstructed( UFGHotbarShortcut* shortcut );
	void OnShortcutDestroyed( UFGHotbarShortcut* shortcut );
	
	friend class UFGPlayerHotbar;
public:
	/** Broadcast when a buildable or decor has been constructed. */
	UPROPERTY( BlueprintAssignable, Category = "Build", DisplayName = "OnBuildableConstructed" )
	FOnBuildableConstructedNew BuildableConstructedDelegate;

	/** Broadcast when a player sets a default material customization desc */
	UPROPERTY( BlueprintAssignable, Category = "Customization", DisplayName = "OnHotbarUpdatedForMaterialDescriptor" )
	FOnHotbarUpdatedForMaterialDescriptor mOnHotbarUpdatedForMaterialDescriptor;
	
	UPROPERTY( BlueprintAssignable, Category = "Todo List")
	FOnPublicTodoListUpdated mOnPublicTodoListUpdated;

	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Shopping List")
	FOnShoppingListUpdated mOnShoppingListUpdated;

	UPROPERTY( BlueprintAssignable, Category = "ColorData")
	FOnSlotDataUpdated mOnColorDataUpdated;

	/** Called when the active hotbar index changes */
	UPROPERTY( BlueprintAssignable, Category = "Hotbar" )
	FFGOnActiveHotbarIndexChanged mOnActiveHotbarIndexChanged;

	/** Called when the hotbars are populated on the server side (first join) or replicated to the client. Can be called multiple times on the client as subobjects replicate. */
	UPROPERTY( BlueprintAssignable, Category = "Hotbar" )
	FFGOnHotbarsAvailable mOnHotbarsAvailable;

	/** Called when the player customization data is updated */
	UPROPERTY( BlueprintAssignable, Category = "Player Customization" )
	FOnPlayerCustomizationDataChanged mOnPlayerCustomizationDataChanged;

	/** Called when the player is made admin */
	UPROPERTY( BlueprintAssignable, Category = "Player" )
	FOnAdminStateChanged mOnAdminStateChanged;

	/** Holds the item stacks that the player can get copied to their inventory on respawn. */
	UPROPERTY( SaveGame )
	FInventoryToRespawnWith mInventoryToRespawnWith;
private:
	/** Legacy hotbars in the game */
	UPROPERTY( SaveGame )
	TArray< FHotbar > mHotbars_DEPRECATED;

	/** Last hotbar that was considered active. Used for correctly dispatching the delegate on the client */
	UPROPERTY()
	TWeakObjectPtr<UFGPlayerHotbar> mLastActivePlayerHotbar;
protected:
	/** Hotbars that the player has, in the new format */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_PlayerHotbars )
	TArray< UFGPlayerHotbar* > mPlayerHotbars;
	
	/** The index of the current hotbar*/
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CurrentHotbarIndex )
	int32 mCurrentHotbarIndex;

	/** Array of all set buildable categories and their default material desc */
	UPROPERTY( SaveGame, Replicated )
	TArray< FSubCategoryMaterialDefault > mBuildableSubCategoryDefaultMatDesc;

	/** 
	 * Array of all set material categories and their default material desc. 
	 * This acts as a global set. When we change this, we also update the mBuildableSubcategoryDefaultMatDesc array  
	 */
	UPROPERTY( SaveGame, Replicated )
	TArray< FSubCategoryMaterialDefault > mMaterialSubCategoryDefaultMatDesc;

	/** Default recipes to have shortcuts to */
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	TArray< TSubclassOf< class UFGRecipe > > mDefaultRecipeShortcuts;
	
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	TSubclassOf< class UFGEmote > mDefaultEmoteShortcut;

	/** Recipes that are new to the player. This is only for UI feedback and does not affect the players ability to use the recipe  */
	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf< class UFGRecipe > > mNewRecipes;

	/** The slot num of this player state */
	UPROPERTY( Replicated )
	int32 mSlotNum;

	/** This players color container */
	UPROPERTY( ReplicatedUsing=OnRep_PlayerColorData )
	FPlayerColorData mPlayerColorData;

	/** Gameplay Rules set specifically for this player. */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_PlayerRules )
	FPlayerRules mPlayerRules;

	/** What kind of hostility creatures should have against this player.
	 *  Note: This is now in the option menu and isn't part of the mPlayerRules anymore
	 *  The default value for the option is PHM_Default but we default this value to passive and then after we joined we send the correct value by RPC if it's changed
	 *  This is to ensure you don't get attacked while joining 
	 */
	UPROPERTY( Transient )
	EPlayerHostilityMode mCreatureHostilityMode = EPlayerHostilityMode::PHM_Passive;

	/** Decides what items should be kept after death. */
	UPROPERTY( Transient )
	EPlayerKeepInventoryMode mKeepInventoryMode = EPlayerKeepInventoryMode::Keep_Equipment;

	/** Pawn we should take control of when rejoining game/loading game */
	UPROPERTY( SaveGame )
	class APawn* mOwnedPawn;

	/** Set to true after we have received our initial items */
	UPROPERTY( SaveGame )
	uint8 mHasReceivedInitialItems:1;

	/** If true, then we are server admin */
	UPROPERTY( ReplicatedUsing=OnRep_IsServerAdmin )
	uint8 mIsServerAdmin : 1;

	UPROPERTY(SaveGame, Replicated)
	TArray< TSubclassOf< class UFGMapArea > > mVisitedAreas;

	UPROPERTY( SaveGame, Replicated )
	FFactoryCustomizationColorSlot mCustomColorData;
	
	/** The settings for the players shopping list. Only replicated on initial send. Then RPCed back to server for saving. */
	UPROPERTY( EditDefaultsOnly, SaveGame, Replicated, Category = "Shopping List")
	FShoppingListSettings mShoppingListSettings;

	/** Data about the selected player customization */
	UPROPERTY( EditDefaultsOnly, SaveGame, ReplicatedUsing = OnRep_PlayerCustomizationData, Category = "Player Customization" )
	FPlayerCustomizationData mPlayerCustomizationData;

	UPROPERTY( SaveGame )
	FClientIdentityInfo mClientIdentityInfo;
	
private:
	/** All messages that have been played for this player */
	UPROPERTY( SaveGame, Replicated )
	TArray< class UFGMessage* > mPlayedMessages;

	/** List of equipment classes that have been equipped at least once. */
	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf< class AFGEquipment > > mRememberedFirstTimeEquipmentClasses;

	/** Total number of arm equipment slots for this player */
	UPROPERTY( SaveGame, Replicated )
	int32 mNumArmSlots;

	/** True if we only should show affordable recipes in manufacturing widgets  */
	UPROPERTY( SaveGame, Replicated )
	bool mOnlyShowAffordableRecipes;

	/** Should we try to take items from inventory before central storage when building or crafting */ 
	UPROPERTY( SaveGame, Replicated )
	bool mTakeFromInventoryBeforeCentralStorage;

	/** Is the central storage widget expanded in the player inventory widget */ 
	UPROPERTY( SaveGame, Replicated )
	bool mCentralStorageInventoryWidgetExpanded;

	/** The item categories that the user have collapsed in manufacturing widgets  */
	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf< class UFGItemCategory > > mCollapsedItemCategories;
	
	UPROPERTY( SaveGame, Replicated )
	TArray< ERepresentationType > mFilteredOutMapTypes;
	
	UPROPERTY( SaveGame, Replicated )
	TArray< ERepresentationType > mFilteredOutCompassTypes;

	/** The map categories that the user have collapsed in the map widget */
	UPROPERTY( SaveGame, Replicated )
	TArray< ERepresentationType > mCollapsedMapCategories;
	UPROPERTY( SaveGame, Replicated )
	TArray< FString > mCollapsedCustomMapCategories;

	/** The last selected category in the resource sink shop so we can open the shop at the same category later */
	UPROPERTY( Transient )
	TSubclassOf< UFGSchematicCategory > mLastSelectedResourceSinkShopCategory;

	/** How many inventory slots the player has observed that they have. Used to show when we have new available slots in the UI  */
	UPROPERTY( SaveGame, Replicated )
	int32 mNumObservedInventorySlots;

	/** The schematics the player has selected as their favorites in the awesome shop */
	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf< class UFGSchematic > > mFavoriteShopSchematics;
	
	/** The schematics and number of that schematic the player has in their shopping cart in the awesome shop  */
	UPROPERTY( Transient )
	TMap< TSubclassOf< class UFGSchematic >, int32 > mShoppingCart;

	/** The personal todolist. Only replicated on initial send. Then RPCed back to server for saving. */
	UPROPERTY( SaveGame, Replicated )
	FString mPrivateTodoList;
	
	UPROPERTY( SaveGame, Replicated )
	class UFGShoppingListComponent* mShoppingListComponent;

	/** The current factory clipboard. Used to copy and paste settings between buildings. Buildings with the same key use can copy/paste between each other.
	 *	The key is usually the most derived class for the building/object but can be changed by developers to share key with other buildings. Key could be any UObject subclass.
	 */
	UPROPERTY( Transient )
	TMap< TSubclassOf<UObject>, class UFGFactoryClipboardSettings* > mFactoryClipboard;

	/** Track whether or not we opened a widget */
	UPROPERTY( Transient ) 
	TArray< TSubclassOf< class UUserWidget > > mOpenedWidgetsThisSession;
	UPROPERTY( SaveGame, Replicated ) 
	TArray< TSubclassOf< class UUserWidget > > mOpenedWidgetsPersistent;

	/** The player specific schematics that this player have purchased */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_PlayerSpecificSchematics ) 
	TArray< TSubclassOf< class UFGSchematic > > mPlayerSpecificSchematics;

	/** Track if items are pinned for central storage UI. If they are in the array it means they are pinned */ 
	UPROPERTY( SaveGame, Replicated ) 
	TArray< TSubclassOf< UFGItemDescriptor > > mCentralStoragePinnedItems;
};

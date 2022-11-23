//Copyright 2016 Coffee Stain Studios.All Rights Reserved.

#pragma once

#include <type_traits>
#include "FactoryGame.h"
#include "GameFramework/PlayerState.h"
#include "FGCharacterPlayer.h"
#include "FGFactoryColoringTypes.h"
#include "UI/Message/FGMessageBase.h"
#include "FGActorRepresentation.h"
#include "FGHotbarShortcut.h"
#include "FGCreatureSubsystem.h"
#include "FGPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildableConstructedNew, TSubclassOf< class UFGItemDescriptor >, itemDesc );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnHotbarUpdatedForMaterialDescriptor, TSubclassOf< class UFGFactoryCustomizationDescriptor_Material >, materialDesc );
DECLARE_DELEGATE( FOnHotbarReplicated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnPublicTodoListUpdated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnShoppingListUpdated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSlotDataUpdated, class AFGPlayerState*, playerState  );


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

/**
* Data associated with a message
*/
USTRUCT( BlueprintType )
struct FACTORYGAME_API FMessageData
{
	GENERATED_BODY();

	FMessageData() : 
		WasRead( false ), 
		MessageClass( nullptr )
	{
	}

	/** Has message been read */
	UPROPERTY( SaveGame, EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	bool WasRead;

	/** What class is the message */
	UPROPERTY( SaveGame, EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > MessageClass;
};

/**
* A hotbar with a set of shortcuts that can be assigned and executed
*/
USTRUCT( BlueprintType )
struct FACTORYGAME_API FHotbar
{
	GENERATED_BODY();

	FHotbar(){}
	FHotbar( class AFGPlayerState* owningState, const FHotbar& hotbar );
	FHotbar( TArray< class UFGHotbarShortcut* > hotbarShortcuts );

	UPROPERTY( SaveGame, BlueprintReadOnly )
	TArray< class UFGHotbarShortcut* > HotbarShortcuts;
};

/**
* A preset represents a way for players to create pre made hotbars they can replace there current hotbar with
*/
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPresetHotbar
{
	GENERATED_BODY();

	FPresetHotbar(){}
	FPresetHotbar( class AFGPlayerState* owningState, const FPresetHotbar& presetHotbar );
	FPresetHotbar( FText presetName, uint8 iconIndex, FHotbar hotbar ) :
		PresetName( presetName ),
		IconIndex( iconIndex ),
		Hotbar( hotbar )
	{}

	UPROPERTY( SaveGame, BlueprintReadOnly )
	FText PresetName;

	/** The shortcut in the hotbar with this index will decide the icon for the preset */
	UPROPERTY( SaveGame, BlueprintReadOnly )
	uint8 IconIndex;

	/** The hotbar shortcuts for this preset */
	UPROPERTY( SaveGame, BlueprintReadOnly )
	FHotbar Hotbar;
};

USTRUCT()
struct FACTORYGAME_API FSubCategoryMaterialDefault
{
	GENERATED_BODY();

	FSubCategoryMaterialDefault() {}
	FSubCategoryMaterialDefault( TSubclassOf< class UFGCategory > cat, TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > desc ) 
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
	bool PublicTodoListVisibilty;
	
	UPROPERTY( SaveGame, BlueprintReadWrite, EditAnywhere )
	bool PrivateTodoListVisibilty;

	UPROPERTY( SaveGame, BlueprintReadWrite, EditAnywhere )
	bool RecipeListVisibilty;
	
	UPROPERTY( SaveGame, BlueprintReadWrite, EditAnywhere )
	float Size;
};

USTRUCT( BlueprintType )
struct FPlayerRules
{
	GENERATED_BODY()

	/** What kind of hostility creatures should have agaisnt this player. */
	UPROPERTY( SaveGame, BlueprintReadOnly )
	EPlayerHostilityMode CreatureHostilityMode;
};

USTRUCT()
struct FACTORYGAME_API FShoppingListBlueprintEntry
{
	GENERATED_BODY()

	FShoppingListBlueprintEntry( const FString& inBlueprintName, int32 inAmount ) :
		BlueprintName( inBlueprintName ),
		Amount( inAmount )
	{}

	FShoppingListBlueprintEntry(){}
	
	UPROPERTY( SaveGame )
	FString BlueprintName = "";
	
	UPROPERTY( SaveGame )
	int32 Amount = 0;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FShoppingListRecipeEntry
{
	GENERATED_BODY()

	FShoppingListRecipeEntry( TSubclassOf<class UFGRecipe> inRecipeClass, int32 inAmount ) :
		RecipeClass( inRecipeClass ),
		Amount( inAmount )
	{}

	FShoppingListRecipeEntry(){}
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	TSubclassOf<class UFGRecipe> RecipeClass = nullptr;
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	int32 Amount = 0;
};

UCLASS()
class FACTORYGAME_API AFGPlayerState : public APlayerState, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGPlayerState();

	// Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
	// End UObject Interface

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual bool ReplicateSubobjects( class UActorChannel* channel, class FOutBunch* bunch, FReplicationFlags* repFlags ) override;
	virtual void BeginPlay() override;
	// End AActor interface
	
	// Begin APlayerState interface
	virtual void CopyProperties( APlayerState* playerState ) override;
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

	/** Set the pawn we controls (it should be the character, not a vehicle) */
	FORCEINLINE void SetOwnedPawn( class APawn* pawn ){ mOwnedPawn = pawn; }

	/** Get the character we control (not a vehicle) */
	FORCEINLINE class APawn* GetOwnedPawn() const{ return mOwnedPawn; }

	/** Return true if we have received our initial items */
	FORCEINLINE bool HasReceiveInitialItems() const { return mHasReceivedInitialItems; }

	/** Mark this character as it has received its initial items */
	FORCEINLINE void MarkAsReceivedInitialItems(){ mHasReceivedInitialItems = true; }

	/** Get the slot the player has claimed */
	UFUNCTION(BlueprintPure, Category = "FactoryGame|Slots" )
	FORCEINLINE int32 GetSlotNum() const{ return mSlotNum; }

	/** Set the slot number of this player */
	FORCEINLINE void SetSlotNum( int32 slotNr ){ mSlotNum = slotNr; }
	
	/** Set the color data for this player */
	void SetPlayerColorData( FPlayerColorData slotData );

	/** get the color data for this player */
	FORCEINLINE FPlayerColorData GetSlotData() const { return mPlayerColorData; }

	/** Gets the player rules for this player. */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Rules" )
	const FPlayerRules& GetPlayerRules() const { return mPlayerRules; }

	/** Used to set the creature hostility against this player. */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Rules" )
	void SetCreatureHostility( EPlayerHostilityMode hostility );

	UFUNCTION( Server, Reliable )
	void Server_SetCreatureHostility( EPlayerHostilityMode hostility );

	/** Get the unique ID of the user from the online subsystem */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Networking" )
	FString GetUserName();

	/** Get the unique ID of the user from the online subsystem */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Networking" )
	FString GetUserID();

	/** Get the unique ID of the user from the online subsystem */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Networking" )
	FUniqueNetIdRepl GetUniqeNetId();

	/** @returns string representation of users SteamID */
	UE_DEPRECATED( 4.20, "GetSteamID has been replaced by GetUserID" )
	UFUNCTION( BlueprintPure, Category="Networking", meta=(DeprecatedFunction, DeprecationMessage="Please use GetUserID instead") )
	FString GetSteamID();

	/** Creates the tutorial system. */
	void CreateTutorialSubsystem();

	/** Gets the subsystem for BP usage */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Tutorial" )
	FORCEINLINE class UFGTutorialSubsystem* GetTutorialSubsystem(){ return mTutorialSubsystem; }

	/** Gets all messages we have received */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Message" )
	TArray< TSubclassOf< class UFGMessageBase > > GetAllMessages( EMessageType messageType = EMessageType::MT_UNDEFINED );

	/** Gets all messagedata from messages we have received */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Message" )
	FORCEINLINE TArray< FMessageData > GetAllMessageData() { return mMessageData; }

	/** Change read status of a message */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Message" )
	void ReadMessage( TSubclassOf< class UFGMessageBase > inMessage );

	UFUNCTION()
	void AddMessage( TSubclassOf< class UFGMessageBase > inMessage );

	/** Used primarily to reset tutorial flow, verifies it exists before attempting removal */
	UFUNCTION()
	void RemoveMessage( TSubclassOf< class UFGMessageBase > inMessage );

	/** Setup our default shortcuts */
	void SetupDefaultShortcuts();

	/** Create a shortcut of a specified class, only valid on server */
	UFUNCTION( BlueprintCallable, DisplayName = CreateShortcut, meta = ( DeterminesOutputType = shortcutClass ) )
	class UFGHotbarShortcut* CreateShortcut( TSubclassOf< class UFGHotbarShortcut > shortcutClass );

	/** Create a shortcut of a specified class and casts it to the specified class */
	template< typename T >
	T* CreateTypedShortcut( TSubclassOf<T> shortcutClass )
	{
		fgcheck( T::StaticClass()->IsChildOf( UFGHotbarShortcut::StaticClass() ) );
		return Cast< T >( CreateShortcut( shortcutClass ) );
	}

	/** Gets or Creates, replacing what is there, for a given index in a hotbar */
	template< typename T >
	T* GetOrCreateShortcutOnHotbar( TSubclassOf<T> shortcutClass, FHotbar& hotbar, int32 index ) 
	{ 
		fgcheck( T::StaticClass()->IsChildOf( UFGHotbarShortcut::StaticClass() ) ); 
		if( hotbar.HotbarShortcuts.IsValidIndex( index ) )
		{
			if( hotbar.HotbarShortcuts[ index ]->GetClass()->IsChildOf( shortcutClass ) )
			{
				return Cast<T>( hotbar.HotbarShortcuts[ index ] );
			}
			else
			{
				hotbar.HotbarShortcuts[ index ] = CreateTypedShortcut( shortcutClass );
				return Cast<T>( hotbar.HotbarShortcuts[ index ] );
			}
		}

		return nullptr;
	}
	

	/** Get current shortcuts */
	void GetCurrentShortcuts( TArray< class UFGHotbarShortcut* >& out_shortcuts );

	/** Get current shortcuts */
	UFGHotbarShortcut* GetShortcutFromCurrentHotbar( int32 shortcutIndex );

	/** Get preset shortcuts with the given index */
	void GetPresetShortcuts( int32 presetHotbarIndex, TArray< class UFGHotbarShortcut* >& out_shortcuts );

	/** Get all preset hotbars */
	void GetAllPresetHotbars( TArray<FPresetHotbar>& out_presetHotbars );

	int32 GetNumHotbars() const { return mHotbars.Num(); }
	
	int32 GetNumPresetHotbars() const { return mPresetHotbars.Num(); }

	int32 GetCurrentHotbarIndex() const { return mCurrentHotbarIndex; }

	void SetHotbarIndex( int32 val );

	/** Copy the current hotbar shortcuts to a new preset hotbar
	*	@return true if the copy was a success 
	*/
	bool CreatePresetFromCurrentHotbar( const FText& presetName, int32 iconIndex );
	
	/** Check if we can create a new preset */
	bool CanCreateNewPresetHotbar() const;

	/** Copy the current hotbar shortcuts to the preset hotbar with the given index */
	bool CopyCurrentHotbarToPresetHotbar( int32 presetHotbarIndex );

	/** Change the name of the preset hotbar at the given index */
	void ChangeNameOfPresetHotbar( int32 presetHotbarIndex, const FText& newName );
	
	/** Change the icon index of the preset hotbar at the given index */
	void ChangeIconIndexOfPresetHotbar( int32 presetHotbarIndex, int32 iconIndex );

	/** Remove the preset hotbar with the given index */
	bool RemovePresetHotbar( int32 presetHotbarIndex );

	/** Copy the shortcuts of the preset hotbar with the given index to the current hotbar
	*	@return true if the copy was a success 
	*/
	bool CopyPresetHotbarToCurrentHotbar( int32 presetHotbarIndex );

	/** Set the specified hotbar shortcut on the index if it's valid. Optionally pass the hotbar index to set a specific index on a specific hotbar. */
	void SetRecipeShortcutOnIndex( TSubclassOf< class UFGRecipe > recipe, int32 onIndex, int32 onHotbarIndex = -1 );

	/** Set the customization desc shortcut on the index if valid */
	void SetCustomizationShortcutOnIndex( TSubclassOf< class UFGCustomizationRecipe > customizationRecipe, int32 onIndex );

	/** Set the emote shortcut on the index if valid */
	void SetEmoteShortcutOnIndex( TSubclassOf< class UFGEmote > emote, int32 onIndex );

	/** Set the blueprint shortcut on the index if it's valid */
	void SetBlueprintShortcutOnIndex( const FString& blueprintName, int32 onIndex );

	/** Get the current value of first time equipped and then sets the value to false. */
	bool GetAndSetFirstTimeEquipped( class AFGEquipment* equipment );

	/** Get the controller owning this player state */
	class AFGPlayerController* GetOwningController() const;

	/** Get the HUD from the controller owning this player state */
	class AFGHUD* GetHUD() const;

	/** Get the Game UI from the controller owning this player state */
	class UFGGameUI* GetGameUI() const;

	/** Adds a new recipe to the list of new recipes. This is only for UI feedback and doesn't give the player the actual ability to use the recipe */
	void AddNewRecipe( TSubclassOf< UFGRecipe > recipe );

	/** Get all recipes that are new to the player. This is only for UI feedback */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Recipes" )
	void GetNewRecipes( TArray<TSubclassOf<class UFGRecipe>>& out_newRecipes ) const;

	/** Removes a recipe from the list of new recipes. This is only for UI feedback and doesn't remove the players ability to use the recipe */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipes" )
	void RemoveRecipe( TSubclassOf< UFGRecipe > recipe );

	/** Lets the server remove a recipe from the list of new recipes */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_RemoveRecipe( TSubclassOf< UFGRecipe > recipe );

	/** Gets number of slots for arm equipment */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Equipment" )
	FORCEINLINE int32 GetNumArmSlots() { return mNumArmSlots; }

	/** Adds more arm slots ( can also be a negative number to decrease number of slots ) */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Equipment" )
	void AddArmSlots( int32 slotsToAdd );

	/** Get if we only should show affordable recipes in manufacturing widgets */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipes" )
	FORCEINLINE bool GetOnlyShowAffordableRecipes() { return mOnlyShowAffordableRecipes; }

	/** Set if we only should show affordable recipes in manufacturing widgets */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipes" )
	void SetOnlyShowAffordableRecipes( bool enabled );

	/** Let server set if we only should show affordable recipes in manufacturing widgets */
	UFUNCTION( Server, Reliable, WithValidation, Category = "FactoryGame|Recipes" )
	void Server_SetOnlyShowAffordableRecipes( bool enabled );

	/** Get if we should we try to take items from inventory before central storage when building or crafting */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|CentralStorage" )
	FORCEINLINE bool GetTakeFromInventoryBeforeCentralStorage() { return true; }

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
	FORCEINLINE bool GetMapCategoryCollapsed( ERepresentationType mapCategory ) const { return mCollapsedMapCategories.Contains( mapCategory ); }

	/** Set if a map category is collapsed in the map widget */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Representation" )
	void SetMapCategoryCollapsed( ERepresentationType mapCategory, bool collapsed );

	/** Let server set if a map category is collapsed in the map widget */
	UFUNCTION( Server, Reliable, Category = "FactoryGame|Representation" )
	void Server_SetMapCategoryCollapsed( ERepresentationType mapCategory, bool collapsed );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Color" )
	FORCEINLINE FLinearColor GetPingColor() const { return mPlayerColorData.PingColor; }
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Color" )
	FORCEINLINE FLinearColor GetNametagColor() const { return mPlayerColorData.NametagColor; }

	void UpdateOwningPawnActorRepresentation() const;

	FORCEINLINE void SetIsServerAdmin( bool isAdmin ){ mIsServerAdmin = isAdmin; }
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Admin" )
	FORCEINLINE bool IsServerAdmin() const{ return mIsServerAdmin; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Schematic" )
	FORCEINLINE TSubclassOf<UFGSchematicCategory> GetLastSelectedResourceSinkShopCategory() const { return mLastSelectedResourceSinkShopCategory; }
	
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Schematic" )
	void SetLastSelectedResourceSinkShopCategory( TSubclassOf<UFGSchematicCategory> selectedCategory ) { mLastSelectedResourceSinkShopCategory = selectedCategory; }

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
	FORCEINLINE FFactoryCustomizationColorSlot GetCustomColorData() { return mCustomColorData; }

	/** 
	 * Sets the local color customization data. This color data is used when assigning a color with slot index INDEX_CUSTOM_COLOR_DATA (255)
	 * Will remote call on server if called by non-authority 
	 */
	UFUNCTION( BlueprintCallable, Category = "FactorGame|Custom Color" )
	void SetPlayerCustomizationSlotData( FFactoryCustomizationColorSlot customColorData );

	/** Sets the user color data on the server. The server in turn will use this to color a building with the correct data when the player paints with their custom color */
	UFUNCTION( Server, Reliable, Category = "FactoryGame|Custom Color" )
	void Server_SetPlayerCustomizationSlotData( FFactoryCustomizationColorSlot customColorData );

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

	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	void AddBlueprintToShoppingList( class UFGBlueprintDescriptor* blueprintDescriptor, int32 amount );
	UFUNCTION( Server, Reliable )
	void Server_AddBlueprintToShoppingList( const FString& blueprintName, int32 amount );
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	void RemoveBlueprintFromShoppingList( class UFGBlueprintDescriptor* blueprintDescriptor, int32 amount );
	UFUNCTION( Server, Reliable )
	void Server_RemoveBlueprintFromShoppingList( const FString& blueprintName, int32 amount );
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	void AddRecipeClassToShoppingList( TSubclassOf< class UFGRecipe > recipeClass, int32 amount );
	UFUNCTION( Server, Reliable )
	void Server_AddRecipeClassToShoppingList( TSubclassOf< class UFGRecipe > recipeClass, int32 amount );
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	void RemoveRecipeClassFromShoppingList( TSubclassOf< class UFGRecipe > recipeClass, int32 amount );
	UFUNCTION( Server, Reliable )
	void Server_RemoveClassRecipeFromShoppingList( TSubclassOf< class UFGRecipe > recipeClass, int32 amount );
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	void EmptyShoppingList();
	UFUNCTION( Server, Reliable )
	void Server_EmptyShoppingList();

	UFUNCTION( BlueprintCallable )
	TMap< FString, int32 > GetShoppingListItems();
	UFUNCTION( BlueprintCallable )
	TArray< FItemAmount > GetShoppingListCost() const;

	// On recipe constructed could mean both constructing buildings and crafting items
	UFUNCTION( Client, Reliable )
	void Client_OnRecipeConstructed( TSubclassOf< class UFGRecipe > recipe, int32 numConstructed );
	void Native_OnRecipeConstructed( TSubclassOf< class UFGRecipe > recipe, int32 numConstructed );
	void Native_OnBlueprintConstructed( const FString& blueprintName, int32 numConstructed );

	// Only for migration purposes.
	UFUNCTION( BlueprintImplementableEvent )
	TArray< FShoppingListRecipeEntry > GetAndClearShoppingListForMigration();
	
	/** Checks if the player state is in the player array. Tried to use IsInactive but it's not updated when a player state is loaded and is inactive.
	 *  And I don't want to start chancing that logic since other things might depend on it. -K2
	 */
	bool IsInPlayerArray();

protected:
	void Native_OnFactoryClipboardCopied( UObject* object, class UFGFactoryClipboardSettings* factoryClipboard );
	void Native_OnFactoryClipboardPasted( UObject* object, class UFGFactoryClipboardSettings* factoryClipboard );
	
	// Client get notified that the hotbar has changed
	UFUNCTION()
	void OnRep_HotbarShortcuts();

	// Client get notified that the hotbar index has changed
	UFUNCTION()
	void OnRep_CurrentHotbarIndex();
	
	UFUNCTION()
	void OnRep_PlayerColorData();

	UFUNCTION()
	void OnRep_PlayerRules();
	
	UFUNCTION()
	void OnRep_ShoppingListBlueprints();
	
	UFUNCTION()
	void OnRep_ShoppingListRecipes();

private:
	/** Server function for updating number observed inventory slots */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_UpdateNumObservedInventorySlots();

	void Native_OnPlayerColorDataUpdated();

	void SetupPlayerRules();

	void PushRulesToGameModesSubssytem();

	void OnCreatureHostilityModeUpdated( FString strId, FVariant value );

	void Internal_RemoveBlueprintFromShoppingList( const FString& blueprintName, int32 amount );

public:
	/** Broadcast when a buildable or decor has been constructed. */
	UPROPERTY( BlueprintAssignable, Category = "Build", DisplayName = "OnBuildableConstructed" )
	FOnBuildableConstructedNew BuildableConstructedDelegate;

	/** Broadcast when a player sets a default material customization desc */
	UPROPERTY( BlueprintAssignable, Category = "Customization", DisplayName = "OnHotbarUpdatedForMaterialDescriptor" )
	FOnHotbarUpdatedForMaterialDescriptor mOnHotbarUpdatedForMaterialDescriptor;

	/** Broadcast if hotbar has been replicated */
	FOnHotbarReplicated mOnHotbarReplicated;

	UPROPERTY( BlueprintAssignable, Category = "Todo List")
	FOnPublicTodoListUpdated mOnPublicTodoListUpdated;

	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Shopping List")
	FOnShoppingListUpdated mOnShoppingListUpdated;

	UPROPERTY( BlueprintAssignable, Category = "ColorData")
	FOnSlotDataUpdated mOnColorDataUpdated;

protected:
	/** All hotbar actions assigned */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_HotbarShortcuts )
	TArray< FHotbar > mHotbars;

	/** All hotbar actions assigned to presets. A preset is a saved set of shortcuts that can be assigned to the hotbar */
	UPROPERTY( SaveGame, Replicated )
	TArray< FPresetHotbar > mPresetHotbars;

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

	/** Recipes that are new to the player. This is only for UI feedback and doesn't affect the players ability to use the recipe  */
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

	/** Pawn we should take control of when rejoining game/loading game */
	UPROPERTY( SaveGame )
	class APawn* mOwnedPawn;

	/** Set to true after we have received our initial items */
	UPROPERTY( SaveGame )
	uint8 mHasReceivedInitialItems:1;

	/** If true, then we are server admin */
	UPROPERTY( Replicated )
	uint8 mIsServerAdmin : 1;

	UPROPERTY(SaveGame, Replicated)
	TArray< TSubclassOf< class UFGMapArea > > mVisitedAreas;

	UPROPERTY( SaveGame, Replicated )
	FFactoryCustomizationColorSlot mCustomColorData;
	
	/** The settings for the players shopping list. Only replicated on initial send. Then RPCed back to server for saving. */
	UPROPERTY( EditDefaultsOnly, SaveGame, Replicated, Category = "Shopping List")
	FShoppingListSettings mShoppingListSettings;

private:
	/** Each local player has their own tutorial subsystem */
	UPROPERTY( SaveGame )
	class UFGTutorialSubsystem* mTutorialSubsystem;

	/** Class of tutorial subsystem to spawn */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGTutorialSubsystem > mTutorialSubsystemClass;

	/** Data about all messages that can be displayed in the codex */
	UPROPERTY( SaveGame )
	TArray< FMessageData > mMessageData;

	/** List of equipment classes that have been equipped at least once. */
	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf< class AFGEquipment > > mRememberedFirstTimeEquipmentClasses;

	/** Total number of arm equipment slots for this player */
	UPROPERTY( SaveGame, Replicated )
	int32 mNumArmSlots;

	/** True if we only should show affordable recipes in manufacturing widgets  */
	UPROPERTY( SaveGame, Replicated )
	bool mOnlyShowAffordableRecipes;
	
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

	// Shopping list entries for the in game todo list. Separated for blueprints and recipes.
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ShoppingListBlueprints )
	TArray< FShoppingListBlueprintEntry > mShoppingListBlueprints;
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ShoppingListRecipes )
	TArray< FShoppingListRecipeEntry > mShoppingListRecipes;

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
	
};

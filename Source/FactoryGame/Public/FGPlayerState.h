//Copyright 2016 Coffee Stain Studios.All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include <type_traits>
#include "GameFramework/PlayerState.h"
#include "FGCharacterPlayer.h"
#include "UI/Message/FGMessageBase.h"
#include "FGActorRepresentation.h"
#include "UI/Message/FGMessageBase.h"
#include "FGPlayerState.generated.h"

typedef TSharedPtr<class IHttpRequest> FHttpRequestPtr;
typedef TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildableConstructedNew, TSubclassOf< class UFGItemDescriptor >, itemDesc );

DECLARE_DELEGATE( FOnHotbarReplicated );

/**
 * Collected data for a slot that is specified
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FSlotData
{
	GENERATED_BODY();

	/** The color of the players ping */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Color")
	FLinearColor PingColor;

	/** The color of the players nametag above their head, and in the UI */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Color")
	FLinearColor NametagColor;

	FORCEINLINE bool operator==( const FSlotData& other ) const{
		return other.PingColor == PingColor && other.NametagColor == NametagColor;
	}


public:
	FORCEINLINE ~FSlotData() = default;
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

public:
	FORCEINLINE ~FMessageData() = default;
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

public:
	FORCEINLINE ~FHotbar() = default;
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

public:
	FORCEINLINE ~FPresetHotbar() = default;
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
	void SetSlotData( FSlotData slotData );

	/** get the color data for this player */
	FORCEINLINE FSlotData GetSlotData() const { return mSlotData; }

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
		check( T::StaticClass()->IsChildOf( UFGHotbarShortcut::StaticClass() ) );
		return Cast< T >( CreateShortcut( shortcutClass ) );
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

	/** Set the specified hotbar shortcut on the index if it's valid */
	void SetRecipeShortcutOnIndex( TSubclassOf< class UFGRecipe > recipe, int32 onIndex );

	/** Get the current value of first time equipped and then sets the value to false. */
	bool GetAndSetFirstTimeEquipped( class AFGEquipment* equipment );

	/** Get the controller owning this player state */
	class AFGPlayerController* GetOwningController() const;

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

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Color" )
	FORCEINLINE FLinearColor GetPingColor() const { return mSlotData.PingColor; }
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Color" )
	FORCEINLINE FLinearColor GetNametagColor() const { return mSlotData.NametagColor; }

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

protected:
	// Client get notified that the hotbar has changed
	UFUNCTION()
	void OnRep_HotbarShortcuts();

	// Client get notified that the hotbar index has changed
	UFUNCTION()
	void OnRep_CurrentHotbarIndex();

private:
	/** Server function for updating number observed inventory slots */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_UpdateNumObservedInventorySlots();

public:
	/** Broadcast when a buildable or decor has been constructed. */
	UPROPERTY( BlueprintAssignable, Category = "Build", DisplayName = "OnBuildableConstructed" )
	FOnBuildableConstructedNew BuildableConstructedDelegate;

	/** Broadcast if hotbar has been replicated */
	FOnHotbarReplicated mOnHotbarReplicated;

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
	UPROPERTY( Replicated )
	FSlotData mSlotData;

	/** Pawn we should take control of when rejoining game/loading game */
	UPROPERTY( SaveGame )
	class APawn* mOwnedPawn;

	/** Set to true after we have received our initial items */
	UPROPERTY( SaveGame )
	uint8 mHasReceivedInitialItems:1;

	/** If true, then we are server admin */
	UPROPERTY( Replicated )
	uint8 mIsServerAdmin : 1;
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

	/** The last selected category in the resource sink shop so we can open the shop at the same category later */
	UPROPERTY( Transient )
	TSubclassOf< UFGSchematicCategory > mLastSelectedResourceSinkShopCategory;

	/** How many inventory slots the player has observed that they have. Used to show when we have new available slots in the UI  */
	UPROPERTY( SaveGame, Replicated )
	int32 mNumObservedInventorySlots;

public:
	FORCEINLINE ~AFGPlayerState() = default;
};
// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CameraAnimationCameraModifier.h"
#include "Equipment/FGBuildGun.h"
#include "FGCharacterPlayer.h"
#include "FGChatManager.h"
#include "FGMapMarker.h"
#include "FGPlayerControllerBase.h"
#include "FGPlayerState.h"
#include "PlayerPresenceState.h"
#include "Server/FGDedicatedServerTypes.h"
#include "UI/Message/FGAudioMessage.h"

#include "FGPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FPawnChangedDelegate, APawn*, newPawn );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FPlayerEnteredAreaDelegate, AFGPlayerControllerBase*, playerController, TSubclassOf< class UFGMapArea >, mapArea );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDisabledInputGateDelegate, FDisabledInputGate, newDisabledInputGate );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnToggleInventory, bool, isOpen );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnToggleInteractionUI, bool, isOpen, TSubclassOf< class UUserWidget >, interactionClass );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnFinishRespawn );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnRespawnUIVisibilityChanged, bool, respawnUIVisibility );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnChatMessageEnteredDelegate, FChatMessageStruct&, bool& );
DECLARE_MULTICAST_DELEGATE_OneParam( FOnPlayerControllerBegunPlay, class AFGPlayerController* );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnPlayerRespawnWithInventory, const FInventoryToRespawnWith&, respawnInventory );

UENUM()
enum EHitFeedbackType
{
	Normal,
	WeakSpot,
	Armor
};

UCLASS( Config=Game)
class FACTORYGAME_API AFGPlayerController : public AFGPlayerControllerBase
{
	GENERATED_BODY()
public:
	AFGPlayerController(); 

	// Begin UObject interface
	virtual bool ProcessConsoleExec( const TCHAR* cmd, FOutputDevice& ar, UObject* executor ) override;
	// End UObject interface

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Destroyed() override;
	// End AActor interface

	// Begin AController interface
	virtual void OnRep_PlayerState() override;
	virtual void SetPawn( APawn* inPawn ) override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	// End AController interface

	// Begin APlayerController interface
	virtual void PawnLeavingGame() override;
	virtual void PlayerTick( float DeltaTime ) override;
	virtual void PreClientTravel( const FString& pendingURL, ETravelType travelType, bool isSeamlessTravel ) override;
	virtual void NotifyLoadedWorld( FName worldPackageName, bool isFinalDest ) override;
	// End APlayerController interface

	/** Get the RCO of the given class. */
	UFUNCTION( BlueprintPure, Category = "Remote Call Object", meta = ( DeterminesOutputType = "inClass" ) )
	class UFGRemoteCallObject* GetRemoteCallObjectOfClass( TSubclassOf< UFGRemoteCallObject > inClass );

	UFUNCTION( BlueprintPure, Category = "Remote Call Object", meta = ( DeterminesOutputType = "inClass" ) )
	class UFGRemoteCallObject* RegisterRemoteCallObjectClass( TSubclassOf< UFGRemoteCallObject > inClass );

	/**
	* Called on Server and Owning client when the character we controlled died
	*
	* @param character - the character that died
	**/
	virtual void OnControlledCharacterDied( class AFGCharacterBase* character ) override;

	virtual void OnControlledCharacterRevived( AFGCharacterBase* character ) override;

	//@todonow I do not think respawn works entirely correct for vehicles.
	/** Begin respawning this controllers pawn, call Respawn when done playing any respawn effects. */
	UFUNCTION( BlueprintCallable, Category = "Respawn" )
	void StartRespawn();

	/** Respawns the pawn, do not call this directly to respawn in-game, call StartRespawn instead. */
	UFUNCTION( Reliable, Server, WithValidation, BlueprintCallable, Category = "Respawn", DisplayName = "Respawn" )
	void Server_Respawn();

	/** Suicide if we have a valid pawn */
	UFUNCTION( BlueprintCallable, Exec )
	void Suicide();

	/** @return true if this player controller needs to respawn it's pawn, e.g. the pawn is dead. */
	UFUNCTION( BlueprintPure, Category = "Respawn" )
	bool NeedRespawn() const;

	/** @return true if we're currently respawning. */
	UFUNCTION( BlueprintPure, Category = "Respawn" )
	bool IsRespawning() const { return mIsRespawning; }

	/** Set our suicide status */
	void SetRespawningFromDeath( bool respawningFromDeath );

	/** Did we just kill ourselves */
	bool GetRespawningFromDeath();

	/** Called when the option for FOV changed */
	UFUNCTION()
	void OnFOVUpdated( FString cvar );

	/** Execute the hotbar shortcut with the specified index */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void ExecuteShortcut( int32 shortcutIndex );

	/** Get all shortcuts in the current hotbar */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void GetCurrentShortcuts( TArray< class UFGHotbarShortcut* >& out_shortcuts );
	
	/** Is a given material customization present as a shortcut on the active hotbar? */
	UFUNCTION( BlueprintPure, Category = "Shortcut" )
	bool DoesHotbarContainMaterialCustomization();

	/** Removes the shortcut at the specified index */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void RemoveShortcutAtIndex( int32 onIndex, int32 onHotbarIndex = -1 );
	
	/** Set the specified hotbar shortcut on the index if it's valid */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void SetRecipeShortcutOnIndex( TSubclassOf< class UFGRecipe > recipe, int32 onIndex, int32 onHotbarIndex = -1 );

	/** Set the Customization hotbar shortcut on the index if it's valid */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void SetCustomizationShortcutOnIndex( TSubclassOf< class UFGCustomizationRecipe > customizationRecipe, int32 onIndex );

	/** Set the emote hotbar shortcut on the index if it's valid */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void SetEmoteShortcutOnIndex( TSubclassOf< class UFGEmote > emote, int32 onIndex );

	/** Set the blueprint hotbar shortcut on the index if it's valid */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void SetBlueprintShortcutOnIndex( const FString& blueprintName, int32 onIndex );

	/** Remove a saved color preset */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|GlobalColorPresets" )
	void RemovePlayerColorPresetAtIndex( int32 index );

	UFUNCTION( Reliable, Server )
	void Server_RemovePlayerColorPresetAtIndex( int32 index );

	/** Set a saved color preset */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|GlobalColorPresets" )
	void AddPlayerColorPreset( FText presetName, FLinearColor color );

	UFUNCTION( Reliable, Server )
	void Server_AddPlayerColorPreset( const FText& presetName, FLinearColor color );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|SwatchGroup" )
	void SetDefaultSwatchForBuildableGroup( TSubclassOf< class UFGSwatchGroup > swatchGroup, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > newSwatch );
	
	/** Set the default swatch for */
	UFUNCTION( Reliable, Server )
	void Server_SetDefaultSwatchForBuildableGroup( TSubclassOf< class UFGSwatchGroup > swatchGroup, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > newSwatch );
	
	/** Set the current hotbar index */
	void SetHotbarIndex( int32 newIndex );

	UFUNCTION( BlueprintPure, Category = "Shortcut" )
	int32 GetCurrentHotbarIndex() const;

	/** Returns the current hotbar object that player has. Might be null early on on the clients. */
	UFUNCTION( BlueprintPure, Category = "Shortcut" )
	class UFGPlayerHotbar* GetActiveHotbar() const;
	
	/** Returns the number of hotbars the players have. */
	UFUNCTION( BlueprintPure, Category = "Shortcut" )
	int32 GetNumHotbars() const;

	/** Returns the hotbar at the specified index. Might be null early on or when the index is invalid. */
	UFUNCTION( BlueprintPure, Category = "Shortcut" )
	class UFGPlayerHotbar* GetHotbarAtIndex( int32 hotbarIndex ) const;

	/** Returns all hotbars that the player has */
	UFUNCTION( BlueprintPure, Category = "Shortcut" )
	void GetAllHotbars( TArray<UFGPlayerHotbar*>& out_hotbars ) const;

	/** Get the shortcut index of a recipe, -1 if it doesn't have any shortcut index assigned */
	UFUNCTION( BlueprintPure, Category = "Shortcut" )
	int32 GetRecipeShortcutIndex( TSubclassOf< class UFGRecipe > recipe ) const;

	/**
	* Converts a keyEvent to what shortcut it's associated with
	* @return -1 if not associated with any shortcut, else the shortcut index
	*/
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	int32 GetShortcutIndexFromKey( const FKeyEvent& key ) const;

	/** Called on owning client when respawning starts */
	UPROPERTY( BlueprintAssignable )
	FOnFinishRespawn OnFinishRespawn;

	/** Called when the player is respawned, accepts the data used for respawning as a parameter */
	UPROPERTY( BlueprintAssignable, Category = "Inventory" )
	FFGOnPlayerRespawnWithInventory OnRespawnWithInventory;

	/** Called when the player opens or closes the inventory */
	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Inventory" )
	FOnToggleInventory OnToggleInventory;

	/** Called when the player opens or closes the inventory */
	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Inventory" )
	FOnToggleInteractionUI OnToggleInteractionUI;

	/** Called when the pawn this controller is controlling enters a map area */
	UPROPERTY( BlueprintAssignable, Category = "Map Area", DisplayName = "OnMapAreaEntered" )
	FPlayerEnteredAreaDelegate MapAreaEntered;

	/** Called when the pawn this controller is controlling changes to other than nullPeter */
	UPROPERTY( BlueprintAssignable, Category = "Pawn", DisplayName = "OnPawnChanged" )
	FPawnChangedDelegate PawnChanged;

	/** Called when the visbility of respawn UI should change */
	UPROPERTY( BlueprintAssignable, Category = "UI"  )
	FOnRespawnUIVisibilityChanged mOnRespawnUIVisibilityChanged;

	/** Called when chat message has been entered by the player but before it has been processed by anything, gives the opportunity to process or cancel it */
	FOnChatMessageEnteredDelegate ChatMessageEntered;

	/** Called when player controller has received a BeginPlay event and after vanilla logic has been run */
	static FOnPlayerControllerBegunPlay PlayerControllerBegunPlay;

	// Begin AFGMapManager RPCs
	// @todok2 should me move these to a RCO of its own in map manager instead?
	/** Tells the server to start transferring fog of war data to the requesting client  */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_RequestFogOfWarData();

	/** Transfer fog of war data to the client */
	UFUNCTION( Reliable, Client )
	void Client_TransferFogOfWarData( const TArray<uint8>& fogOfWarRawData, int32 finalIndex );

	UFUNCTION( Reliable, Server )
	void Server_RequestMapMarkerData();
	/** Transfer map marker data to the client */
	UFUNCTION( Reliable, Client )
	void Client_TransferMapMarkerData( const TArray<FMapMarker>& mapMarkers );
	
	UFUNCTION( Reliable, Server )
	void Server_AddMapMarker( FMapMarker mapMarker );

	UFUNCTION( Reliable, Client )
	void Client_OnMapMarkerAdded( FMapMarker mapMarker );

	UFUNCTION( Reliable, Server )
	void Server_RemoveMapMarker( int32 index );

	UFUNCTION( Reliable, Client )
	void Client_OnMapMarkerRemoved( int32 index );
	
	UFUNCTION( Reliable, Server )
	void Server_SetHighlightRepresentation( class AFGPlayerState* fgPlayerState, class UFGActorRepresentation* actorRepresentation );
	UFUNCTION( Reliable, Server )
	void Server_SetHighlighMarker( class AFGPlayerState* fgPlayerState, int32 markerID );

	UFUNCTION( Reliable, Client )
	void Client_OnRepresentationHighlighted( class AFGPlayerState* fgPlayerState, class UFGActorRepresentation* actorRepresentation );
	UFUNCTION( Reliable, Client )
	void Client_OnMarkerHighlighted( class AFGPlayerState* fgPlayerState, int32 markerID );
	// End AFGMapManager RPCs

	/** Play the indicated CameraAnim on this camera.
	 * @param AnimToPlay - Camera animation to play
	 * @param AnimParams - Animation Parameters
	 */
	UFUNCTION(unreliable, client, BlueprintCallable, Category="Camera")
	void ClientPlayCameraAnimationSequence(class UCameraAnimationSequence* AnimToPlay, float Scale=1.f, float Rate=1.f, float BlendInTime=0.f, float BlendOutTime=0.f, bool bLoop=false, bool bRandomStartTime=false, ECameraShakePlaySpace Space=ECameraShakePlaySpace::CameraLocal, FRotator CustomPlaySpace=FRotator::ZeroRotator );
	
	/** Gets the size on the viewport of the given actor */
	UFUNCTION( BlueprintPure, Category = "HUD" )
	float GetObjectScreenRadius( AActor* actor, float boundingRadius );

	/** Gets the object radius for a given actor in order to align with a desired screen space radius */
	UFUNCTION( BlueprintPure, Category = "HUD" )
	float GetScreenBasedObjectRadius( AActor* actor, float screenRadius );

	/** Gets called on the client */
	UFUNCTION( Reliable, Client, BlueprintCallable )
	void Client_AddMessage( TSubclassOf<class UFGMessageBase> newMessage );

	/** Gets called on the client */
	UFUNCTION( BlueprintCallable, Category = "Message" )
	bool GetPlayerHasMessage( TSubclassOf< class UFGMessageBase > newMessage );

	FORCEINLINE class UFGMapAreaTexture* GetMapAreaTexture() const { return mCachedMapAreaTexture; }

	/**
	* Disables the ability to use certain aspects connected to input in the game. 
	* When struct is changed, mDisabledInputGateChanged will broadcast to signal value changes. 
	* 
	* When true, the input is DISABLED. 
	**/
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void SetDisabledInputGate( FDisabledInputGate newDisabledInputGate );

	/** Getter for current disabled input states */
	UFUNCTION(BlueprintCallable, Category = "Input")
	FORCEINLINE FDisabledInputGate GetDisabledInputGate() const { return mDisabledInputGate; }

	UPROPERTY( BlueprintAssignable )
	FDisabledInputGateDelegate mDisabledInputGateChanged;

	UFUNCTION( BlueprintCallable, Category = "Input")
	FORCEINLINE bool IsInTutorialMode() { return mInTutorialMode; }
	
	/** Set when a player is added to the TutorialManager */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void SetTutorialMode( bool active ) { mInTutorialMode = active; }

	UFUNCTION( Client, Reliable )
	void Client_NotifyHitFeedback( EHitFeedbackType feedbackType, AActor* damageCauser, AFGCharacterBase* hitCharacter );

	/** Sends chat message visible only to this particular client */
	UFUNCTION( Client, Reliable )
	void Client_SendChatMessage( const FChatMessageStruct& chatMessage );
	
	/** Used to create our list of sequences  */
	UFUNCTION( BlueprintImplementableEvent, Category = "Cheat" )
	void CreateSequenceList();

	UFUNCTION( BlueprintPure, Category = "Screenshot" )
	FString GetScreenshotPath( bool isHighRes );

	virtual bool DestroyNetworkActorHandled() override;

	virtual void AcknowledgePossession( class APawn* P ) override;

	/** Getter for proximity subsystem */
	UFUNCTION( BlueprintPure, Category = "Proximity" )
	FORCEINLINE class AFGProximitySubsystem* GetProximitySubsystem() const { return mProximitySubsystem; }

	/** Changes the current hotbar to the next index, wraps around  */
	UFUNCTION( BlueprintCallable, Category = "Hotbar" )
	void CycleToNextHotbar();

	/** Changes the current hotbar to the previous index, wraps around  */
	UFUNCTION( BlueprintCallable, Category = "Hotbar" )
	void CycleToPreviousHotbar();


	virtual bool GetPresenceState(FPlayerPresenceState& outState) const override;

	/** Templated getter for RCO */
	template<typename T>
	FORCEINLINE T* GetRemoteCallObjectOfClass() 
	{ 
		return Cast<T>(GetRemoteCallObjectOfClass(T::StaticClass()));
	}

	/** Returns the map area that the pawn is currently in */
	UFUNCTION( BlueprintPure, Category = "Map" )
    TSubclassOf< UFGMapArea > GetCurrentMapArea() const;

	UFUNCTION( BlueprintPure, Category = "Map" )
	FORCEINLINE bool HasCurrentAreaBeenPreviouslyVisited() const { return mCurrentAreaWasPreviouslyVisited; }

	/** Lower limit of photo mode FOV. */
	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	FORCEINLINE int32 GetPhotoModeFOVMin() const { return mMinPhotoModeFOV; }

	/** Upper limit of photo mode FOV. */
	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
    FORCEINLINE int32 GetPhotoModeFOVMax() const { return mMaxPhotoModeFOV; }

	UFUNCTION(Server, Reliable)
	void OnAreaEnteredServer(TSubclassOf< UFGMapArea > newArea);

	/** Called whenever an interact widget gets added or removed. */
	void OnInteractWidgetAddedOrRemoved( class UFGInteractWidget* widget, bool added );

	UFUNCTION( BlueprintImplementableEvent, Category = "Photo Mode" )
	class UFGPhotoModeWidget* GetPhotoModeWidget() const;
	
	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	bool GetIsPhotoMode() { return mPhotoModeEnabled; }

	UFUNCTION( BlueprintPure, Category = "Input" )
	int32 GetMappingContextPriority() const;
	
	/** Used to distinguish admin players from simple clients on dedicated servers. Will only hold a useful value on dedicated servers */
	FServerEntryToken mServerEntryTicket;

	class UFGGameUI* GetGameUI() const;

	UInputMappingContext* GetMappingContextChords() const { return mMappingContextChords; }

	/** Get the character we are controlling (if we are in vehicles, this finds our pawn in the vehicle), can return null if we don't control any character */
	UFUNCTION( BlueprintPure, Category = "Character" )
	class AFGCharacterBase* GetControlledCharacter() const;
	
protected:
	/** Pontentially spawns deathcreate when disconnecting if we are dead */
	void PonderRemoveDeadPawn();

	/** Return false if we don't control anything */
	bool ControlledCharacterIsAliveAndWell() const;

	/**
	 * Called on owning client when respawning starts
	 */
	UFUNCTION( BlueprintImplementableEvent, Category="Respawn" )
	void OnStartRespawn( bool isJoining );

	/**
	* Called on start of a local client player. Reutrn the component that should handle the wind for the player
	*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Sounds" )
	UAkComponent* OnSetupMovementWind();

	// Begin APlayerController interface
	virtual void SetupInputComponent() override;
	// End APlayerController interface

	/** Trace and find a location to spawn a ping */
	void TraceLocationForPing( FHitResult& hitResult );
	
	/** Sends a ping to the other players from a given normalized 2D location. Maps the normalized value to the map bounds and linetraces down to the first thing it hits at that location */
	UFUNCTION( BlueprintCallable, Category = "Map" )
	void SpawnAttentionPingFrom2DLoc( FVector2D normalizedLocation );
	
	/** Add a map marker from a given normalzied 2D location. Maps the normalized value to the map bounds and linetraces down to the first thing it hits at that location
	  * Return true if we could add a map marker. False if we have reached marker limit */
	UFUNCTION( BlueprintCallable, Category = "Map" )
	UPARAM( DisplayName = "Success" ) bool AddMapMarkerFrom2DLoc( const FMapMarker& mapMarker, FVector2D normalizedLocation, FMapMarker& out_NewMapMarker );
	
	void EnterMapMarkerMode();
	UFUNCTION( BlueprintCallable, Category = "Map" )
	void ExitMapMarkerMode();
	void OnAddMapMarkerPressed();
	void UpdateHoveredMapMarker();
	
	/** Brings up a widget to add a map marker at the look at location */

	/** Temp Nativized event to reduce refernces in RCO.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Portable Miner")
	void OnDismantlePortableMiner(class AFGPortableMiner* PortableMiner);

	/** Temp Nativized event to reduce refernces in RCO.*/
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "GolfCart" )
	void OnDismantleGolfCart( class AFGWheeledVehicle* inGolfCart );

	/** Function that checks which map area our pawn is in */
	UFUNCTION()
	void CheckPawnMapArea();

	/** Caches a lot off stuff needed for the map area checks */
	bool InitMapAreaCheckFunction();

	UFUNCTION( BlueprintImplementableEvent, Category = "Map" )
	void OnChat();
	
	UFUNCTION( BlueprintCallable, Category = "Chat" )
	void EnterChatMessage( const FString& inMessage );

	UFUNCTION( BlueprintNativeEvent, Category = "Input" )
	void OnDisabledInputGateChanged();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Map" )
	void ToggleMap();

	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void EnablePhotoMode( bool isEnabled );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Photo Mode" )
	void TakePhoto();

	UFUNCTION( BlueprintImplementableEvent, Category = "Photo Mode" )
	void TogglePhotoModeInstructionsWidget();

	UFUNCTION( BlueprintImplementableEvent, Category = "Photo Mode" )
	void TogglePhotoModeInstructionsWidgetVisibility();

	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void TogglePhotoMode();
	
	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void ToggleHiResPhotoMode();

	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	int32 GetPhotoModeFOV() { return mPhotoModeFOV; }

	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	bool GetHiResPhotoModeEnabled() { return mHiResPhotoMode; }
	
	/** Returns true if we could give all items to the player. Partial adds are allowed */
	UFUNCTION( BlueprintCallable, Category = "Items" )
	bool GiveItemStacks( TSubclassOf< class UFGItemDescriptor > itemDescriptor, int32 numberOfStacks = 1 );
	UFUNCTION( Reliable, Server )
	void Server_GiveItemStacks( TSubclassOf< class UFGItemDescriptor > itemDescriptor, int32 numberOfStacks );
	/** Returns true if we could give all items to the player. Partial adds are allowed */
	UFUNCTION( BlueprintCallable, Category = "Items" )
	bool GiveItemSingle( TSubclassOf< class UFGItemDescriptor > itemDescriptor, int32 numberOfItems = 1 );
	UFUNCTION( Reliable, Server )
	void Server_GiveItemSingle( TSubclassOf< class UFGItemDescriptor > itemDescriptor, int32 numberOfItems );

#if WITH_CHEATS
	void ToggleCheatBoard();
#endif
	
private:
	/** Begins the setup of the tutorial subsystem */
	void SetupTutorial();

	/** Called when the server and client is done waiting for level streaming etc. */
	void FinishRespawn();

	UFUNCTION( Reliable, Server )
	void Server_RemoveShortcutOnIndex( int32 onIndex, int32 onHotbarIndex );
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_SetRecipeShortcutOnIndex( TSubclassOf<class UFGRecipe> recipe, int32 onIndex, int32 onHotbarIndex = -1 );
	UFUNCTION( Reliable, Server )
	void Server_SetCustomizationShortcutOnIndex( TSubclassOf< class UFGCustomizationRecipe > customizationRecipe, int32 onIndex );
	UFUNCTION( Reliable, Server )
	void Server_SetEmoteShortcutOnIndex( TSubclassOf< class UFGEmote > emote, int32 onIndex );
	UFUNCTION( Reliable, Server )
	void Server_SetBlueprintShortcutOnIndex( const FString& blueprintName, int32 onIndex );
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_SetHotbarIndex( int32 index );
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_SendChatMessage( const FChatMessageStruct& newMessage );
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_SpawnAttentionPingActor( FVector pingLocation, FVector pingNormal );
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_Suicide();
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_StartRespawn();
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_FinishRespawn();

	/** These are called in the respawn/join logic to let the server and client wait for the level streaming. */
	void Server_WaitForLevelStreaming();
	UFUNCTION( Reliable, Client )
	void Client_WaitForLevelStreaming();

	UFUNCTION()
	void OnRep_IsRespawning();

	void DisablePawnMovement( bool isDisabled );

	void SetRespawnUIVisibility( bool respawnUIVisibility );

	static void testAndProcesAdaMessages( AFGPlayerController* owner, const FString &inMessage, AFGPlayerState* playerState, float serverTimeSeconds, class APlayerState* PlayerState, class AFGGameState* fgGameState );
	
	/** Gets the saved mappings from game user settings and applies them to the enhanced input subsystem */
	void SetupSavedKeyMappings( class UEnhancedInputLocalPlayerSubsystem* inputSubsystem );

	/** Input Actions */
	virtual void Input_Respawn( const FInputActionValue& ActionValue );

	// Tried to merge all these down into the same binding (1D Axis, round the value to int), but couldn't get it to work with the pressed trigger for some reason, so we're doing it this way ¯\_(ツ)_/¯
	virtual void Input_HotbarShortcut1( const FInputActionValue& ActionValue );
	virtual void Input_HotbarShortcut2( const FInputActionValue& ActionValue );
	virtual void Input_HotbarShortcut3( const FInputActionValue& ActionValue );
	virtual void Input_HotbarShortcut4( const FInputActionValue& ActionValue );
	virtual void Input_HotbarShortcut5( const FInputActionValue& ActionValue );
	virtual void Input_HotbarShortcut6( const FInputActionValue& ActionValue );
	virtual void Input_HotbarShortcut7( const FInputActionValue& ActionValue );
	virtual void Input_HotbarShortcut8( const FInputActionValue& ActionValue );
	virtual void Input_HotbarShortcut9( const FInputActionValue& ActionValue );
	virtual void Input_HotbarShortcut10( const FInputActionValue& ActionValue );
	
	virtual void Input_Chat( const FInputActionValue& ActionValue );
	
	virtual void Input_Pause( const FInputActionValue& ActionValue );
	
	virtual void Input_CheatMenu( const FInputActionValue& ActionValue );
	
	virtual void Input_CycleHotbarAxis( const FInputActionValue& ActionValue );
	
	virtual void Input_AttentionPing( const FInputActionValue& ActionValue );
	
	virtual void Input_MapMarkerMode( const FInputActionValue& ActionValue );
	virtual void Input_MapMarkerPlace( const FInputActionValue& ActionValue );

	virtual void Input_ToggleMap( const FInputActionValue& ActionValue );
	virtual void Input_TogglePhotoMode( const FInputActionValue& ActionValue );
	
	virtual void Input_PhotoModeFOVScroll( const FInputActionValue& ActionValue );
    virtual void Input_PhotoModeToggleInstructionWidget( const FInputActionValue& ActionValue );
	virtual void Input_PhotoModeToggleHiRes( const FInputActionValue& ActionValue );
	
	virtual void Input_ClipboardCopy( const FInputActionValue& actionValue );
    virtual void Input_ClipboardPaste( const FInputActionValue& actionValue );
	
public:
	/**
	 * Binds the input context to the input subsystem owned by this local player
	 * Will also apply additional associated mapping contexts on top with lower priority
	 */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void SetMappingContextBound( UInputMappingContext* context, bool bind, int32 priority = 0 );
	
	/** Indicates if this playercontroller should trigger sound volumes */
	UPROPERTY( EditDefaultsOnly, Category = "Sound" )
	bool mCanAffectAudioVolumes;

	float mRespawnInvincibilityTimer = 0.0f;

	UPROPERTY( Replicated )
	TObjectPtr<class AFGFoliageStateRepProxy> mFoliageStateRepProxy;
	
protected:
	/** Object that manages non-cheat commands. Instantiated in shipping builds. */
	UPROPERTY( Transient )
	class UFGConsoleCommandManager* mConsoleCommandManager;

	/** The array of all remote call objects this player controller has */
	UPROPERTY( Replicated )
	TArray< UFGRemoteCallObject* > mRemoteCallObjects;

	/** Mapping context for chorded keys. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TObjectPtr< UInputMappingContext > mMappingContextChords;

	/** Mapping context for the player controller. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TObjectPtr< UInputMappingContext > mMappingContext;

	/** Mapping context which gets applied when the player dies. */
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
    TObjectPtr< UInputMappingContext > mMappingContextDead;
	
	/** Mapping context for the photo mode. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TObjectPtr< UInputMappingContext > mMappingContextPhotoMode;

	/** Mapping context for the map marker mode. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TObjectPtr< UInputMappingContext > mMappingContextMapMarkerMode;

	/** The class of the attention ping actor we want to use */
	UPROPERTY( EditDefaultsOnly, Category = "Attention Ping" )
	TSubclassOf< class AFGAttentionPingActor > mAttentionPingActorClass;

	/** How often should we check which map area the pawn is in? */
	UPROPERTY( EditDefaultsOnly )
	float mMapAreaCheckInterval;

	/** In what map area is our pawn right now ? */
	UPROPERTY()
	TSubclassOf< class UFGMapArea > mCurrentMapArea;

	UPROPERTY()
	bool mCurrentAreaWasPreviouslyVisited;

	UPROPERTY()
	UAkComponent* mMovementWindComp;

	FVector mMovementWindVelocityBuffer;
	float mTurnOffMovementWindTimer;
	float mMovementWindInAirTimer;
	float mMovementSpeedSoft; //Used to detect changes in movement speed


	float mNoMovementTime; //Used to detect if player has been idling for a long time.. idealy we should cehck for input too, but this should be good enough for now

private:
	/** If we're currently in the state of respawning */
	UPROPERTY( ReplicatedUsing = OnRep_IsRespawning )
	bool mIsRespawning;

	/** Handler for the timer that checks which map area the pawn is in */
	FTimerHandle mAreaCheckTimerHandle;

	/** Cached info about the map areas */
	UPROPERTY()
	class UFGMapAreaTexture* mCachedMapAreaTexture;

	/** If the tutorial is currently active and affecting the player controller */
	UPROPERTY( Replicated )
	bool mInTutorialMode;

	/** Did we died */
	UPROPERTY()
	bool mRespawnFromDeath;

	/** Did we died */
	UPROPERTY()
	bool mRespawnFromJoin;

	/** Current field of view */
	int32 mCurrentFOV;

	FDisabledInputGate mDisabledInputGate;

	//Photo mode 
	int32 mPhotoModeFOV; 
	bool mPhotoModeEnabled;
	bool mHiResPhotoMode;

	UPROPERTY( EditDefaultsOnly, Category = "Photo Mode" )
	int32 mMinPhotoModeFOV;

	UPROPERTY( EditDefaultsOnly, Category = "Photo Mode" )
	int32 mMaxPhotoModeFOV;

	/** Subsystem that keeps track of effects in proximity to the player */
	UPROPERTY()
	class AFGProximitySubsystem* mProximitySubsystem;

	/** How often to run UpdateMusicPlayers  */
	UPROPERTY( EditDefaultsOnly, Category = "Photo Mode" )
	float mMusicPlayerTickIntervalStart;

	/** Time left until next tick */
	float mMusicPlayerTickInterval;

	/** If we should show the UI for respawning prompt or not */
	bool mRespawnUIVisibility;

	/** List of music player to keep track of  */
	UPROPERTY()
	TArray< UObject* > mMusicPlayerList;

	bool mMapMarkerModeActive;
	bool mMapMarkerModeButtonPressed;
};

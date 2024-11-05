// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CameraAnimationCameraModifier.h"
#include "Equipment/FGBuildGun.h"
#include "FGCharacterPlayer.h"
#include "FGChatManager.h"
#include "FGMapMarker.h"
#include "FGOnboardingStep.h"
#include "FGPlayerControllerBase.h"
#include "FGPlayerState.h"
#include "PlayerPresenceState.h"
#include "UI/Message/FGAudioMessage.h"
#include "FGPlayerController.generated.h"

enum class EPrivilegeLevel : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FPawnChangedDelegate, APawn*, newPawn );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FPlayerEnteredAreaDelegate, AFGPlayerControllerBase*, playerController, TSubclassOf< class UFGMapArea >, mapArea );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDisabledInputGateDelegate, FDisabledInputGate, newDisabledInputGate );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnToggleInventory, bool, isOpen );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnToggleInteractionUI, bool, isOpen, TSubclassOf< class UUserWidget >, interactionClass );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnFinishRespawn );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnChatMessageEnteredDelegate, FChatMessageStruct&, bool& );
DECLARE_MULTICAST_DELEGATE_OneParam( FOnPlayerControllerBegunPlay, class AFGPlayerController* );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnPlayerRespawnWithInventory, const FInventoryToRespawnWith&, respawnInventory );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnInputActionRemapped, const FName&, inActionName );
DECLARE_MULTICAST_DELEGATE_ThreeParams( FOnPlayerControllerPawnChanged, class APlayerController*, APawn*, APawn* );

DECLARE_DYNAMIC_DELEGATE( FFGRuntimeInputActionDelegate );

UENUM()
enum EHitFeedbackType
{
	Normal,
	WeakSpot,
	Armor
};

class UFGRecipe;
class UFGBlueprintDescriptor;

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
	virtual void PostRenderFor( APlayerController* PC, UCanvas* Canvas, FVector CameraPosition, FVector CameraDir ) override;
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
	virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;
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

	/** Called when the controlled character inputs/exits the portal */
	void OnControlledCharacterPortalStateChanged( AFGCharacterPlayer* character, bool isInPortalNow );

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

	/** @return true if we are currently waiting for the client to acknowledge the respawn sequence */
	bool IsClientRespawnGracePeriodActive() const { return mPlayerRespawnGracePeriodActive; }

	/** Set our suicide status */
	void SetRespawningFromDeath( bool respawningFromDeath );

	/** Did we just kill ourselves */
	bool GetRespawningFromDeath();

	/** Called when the option for FOV changed */
	UFUNCTION()
	void OnFOVUpdated( FString cvar );

	/** Updates default FOV of the camera manager from either photo mode FOV or */
	void UpdateCameraManagerDefaultFOV();

	/** Execute the hotbar shortcut with the specified index */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void ExecuteShortcut( int32 shortcutIndex );

	/** Get all shortcuts in the current hotbar */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void GetCurrentShortcuts( TArray< class UFGHotbarShortcut* >& out_shortcuts );

	// <FL> [KajtaziT] actually returns ALL shortcuts, not just valid shortcuts	
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void GetCurrentShortcutsInSlots( TArray< class UFGHotbarShortcut* >& out_shortcuts );
	// </FL>
	
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

	/** Returns true if the intro sequence is currently playing on the pawn controlled by this player controller*/
	UFUNCTION( BlueprintPure, Category = "Intro Sequence" )
	bool IsPlayingIntroSequence() const;

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
	
	/** Triggered when a input action was remapped */
	UPROPERTY( BlueprintAssignable, Category = "Input" )
	FOnInputActionRemapped mOnInputActionRemapped;

	/** Called when chat message has been entered by the player but before it has been processed by anything, gives the opportunity to process or cancel it */
	FOnChatMessageEnteredDelegate ChatMessageEntered;

	/** Called when player controller has received a BeginPlay event and after vanilla logic has been run */
	static FOnPlayerControllerBegunPlay PlayerControllerBegunPlay;

	/** Called when controlled pawn changes on the player controller */
	static FOnPlayerControllerPawnChanged StaticOnControlledPawnChanged;

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
	bool IsInTutorialMode();

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

	class UFGGameUI* GetGameUI() const;
	bool IsPauseMenuOpen() const;

	UInputMappingContext* GetMappingContextChords() const { return mMappingContextChords; }

	/** Get the character we are controlling (if we are in vehicles, this finds our pawn in the vehicle), can return null if we don't control any character */
	UFUNCTION( BlueprintPure, Category = "Character" )
	class AFGCharacterBase* GetControlledCharacter() const;

	/** Return the location of the controlled pawn. If no pawn is controlled it returns an empty FVector */
	FVector GetPawnLocation() const;

	FORCEINLINE class UFGConsoleCommandManager* GetConsoleCommandManager() const { return mConsoleCommandManager; }

	/** Updates player's privilege level on the dedicated server */
	void SetDSPrivilegeLevel( EPrivilegeLevel newPrivilegeLevel );

	/** Returns the privilege level of the player when playing on a dedicated server. None if not playing on Dedicated Server */
	UFUNCTION( BlueprintPure, Category = "Dedicated Server" )
	FORCEINLINE EPrivilegeLevel GetDSPrivilegeLevel() const { return mDedicatedServerPrivilegeLevel; }

	/** Returns true if the player is playing as a Client connected to a Dedicated Server */
	UFUNCTION( BlueprintPure, Category = "Dedicated Server" )
	bool IsConnectedToDedicatedServer() const;

	// <FL> radial menus
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void SetShortcut( int ShortcutIndex, TSubclassOf< UFGRecipe > Recipe, UFGBlueprintDescriptor* Blueprint );

	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame" )
	TSubclassOf< class UFGInteractWidget > mHotbarRadialMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "FactoryGame")
	TSubclassOf< class UFGInteractWidget > mShortcutRadialMenuWidgetClass;

	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame" )
	TSubclassOf< class UFGInteractWidget > mHandheldRadialMenuWidgetClass;
	// </FL>

	void OnSystemUIOverlayStateChanged(bool bOverlayShown);

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

	void ToggleCheatBoard();

	/** Returns true if level streaming has been completed in the proximity of this player */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Level Streaming" )
	bool IsLevelStreamingComplete() const;
	
private:
	void ListenForOnOnboardingStepUpdated();
	UFUNCTION()
	void Native_OnOnboardingStepUpdated( UFGOnboardingStep* currentOnboardingStep );

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
	UFUNCTION( Reliable, Server )
	void Server_ClientDoneRespawning();
	UFUNCTION()
	void OnRep_IsRespawning();
	/** Called by the server when the client grace period during respawn has elapsed */
	void OnClientGracePeriodElapsed();

	static void testAndProcesAdaMessages( AFGPlayerController* owner, const FString &inMessage, AFGPlayerState* playerState, float serverTimeSeconds, class APlayerState* PlayerState, class AFGGameState* fgGameState );
	
	/** Gets the saved mappings from game user settings and applies them to the enhanced input subsystem */
	void SetupSavedKeyMappings( class UEnhancedInputLocalPlayerSubsystem* inputSubsystem );	

	/** Input Actions */
	virtual void Input_Respawn( const FInputActionValue& ActionValue );

	// Tried to merge all these down into the same binding (1D Axis, round the value to int), but couldn't get it to work with the pressed trigger for some reason, so we're doing it this way ?\_(?)_/?
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

	// <FL> hotbar and handheld radial menus
	virtual void Input_HandheldRadialMenu_Started  ( const FInputActionInstance& ActionInstance );
	virtual void Input_HandheldRadialMenu_Completed( const FInputActionInstance& ActionInstance );
	virtual void Input_HotbarRadialMenu_Started    ( const FInputActionInstance& ActionInstance );
	virtual void Input_HotbarRadialMenu_Completed  ( const FInputActionInstance& ActionInstance );
	virtual void Input_HotbarRadialMenuPageDown	   ( const FInputActionInstance& ActionInstance );
	virtual void Input_HotbarRadialMenuPageUp      ( const FInputActionInstance& ActionInstance );

	void UpdateHotbarRadialMenuPage();

	void OnRadialMenuWidgetCreate(	TSubclassOf< class UFGInteractWidget > WidgetClass, TObjectPtr< UInputMappingContext > MappingContext, bool UnequipBuildGun);
	void OnRadialMenuWidgetDestroy( TSubclassOf< class UFGInteractWidget > WidgetClass, TObjectPtr< UInputMappingContext > MappingContext, const FInputActionInstance& ActionInstance );

	void AddMappingContextImmediately(TObjectPtr< UInputMappingContext > MappingContext);
	void RemoveMappingContextImmediately(TObjectPtr< UInputMappingContext > MappingContext);

	// </FL>
	
	virtual void Input_Chat( const FInputActionValue& ActionValue );
	
	virtual void Input_Pause( const FInputActionValue& ActionValue );
	
	virtual void Input_CheatMenu( const FInputActionValue& ActionValue );
	
	virtual void Input_DebugMenu(const FInputActionValue& ActionValue);

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

	/** Binds a specified delegate to an input action. Exists so actions can be bound in runtime for blueprints. */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void BindToAction( const class UInputAction* action, ETriggerEvent triggerEvent, const FFGRuntimeInputActionDelegate& delegate );

	/** Unbinds delegates for input associated with this object. */
	UFUNCTION( BlueprintCallable, Category = "Input", meta = ( DefaultToSelf = "object") )
	void ClearActionBindingsForObject( UObject* object );
	
	/** Indicates if this playercontroller should trigger sound volumes */
	UPROPERTY( EditDefaultsOnly, Category = "Sound" )
	bool mCanAffectAudioVolumes;

	float mRespawnInvincibilityTimer = 0.0f;

	UPROPERTY( Replicated )
	TObjectPtr<class AFGFoliageStateRepProxy> mFoliageStateRepProxy;
	
	UFUNCTION( BlueprintCallable, Category = "Shortcut Radial" )
	void CreateShortcutRadialMenu(TSubclassOf< UFGRecipe > RecipeClass, UFGBlueprintDescriptor* Blueprint);

	UFUNCTION(BlueprintCallable, Category = "Shortcut Radial")
	void DestroyShortcutRadialMenu();

	UPROPERTY( Replicated )
	TObjectPtr<class AFGLightweightBuildableRepProxy> mLightweightBuildableRepProxy;
	
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

	/** Mapping context for when the character is in the portal */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TObjectPtr< UInputMappingContext > mMappingContextInPortal;

	/** The class of the attention ping actor we want to use */
	UPROPERTY( EditDefaultsOnly, Category = "Attention Ping" )
	TSubclassOf< class AFGAttentionPingActor > mAttentionPingActorClass;

	// <FL> mapping context for the hotbar radial menu
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TObjectPtr< UInputMappingContext > mMappingContextHotbarRadialMenu;

	// <FL> mapping context for the shortcut radial menu
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr< UInputMappingContext > mMappingContextShortcutRadialMenu;

	// <FL> mapping context for the handheld radial menu
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr< UInputMappingContext > mMappingContextHandheldRadialMenu;

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

	float mLastFrameVelocityLength;
	
	float mNoMovementTime; //Used to detect if player has been idling for a long time. ideally we should check for input too, but this should be good enough for now

	// Defaulted to 150 km/h.
	UPROPERTY( EditDefaultsOnly )
	float mSpeedToReachForAchievement = 4166.667f;
	
public:
	float GetLookInputDelayTime(); // Full time in seconds until look input is fully activated again after closing the Handheld or Hotbar radial menu
	float GetLookInputFadeFactor(); // Returns a factor to smoothly scale the looking input after closing the Handheld or Hotbar radial menu

	float mLookInputDelay = 0.0f; // Remaining time in seconds until look input is fully activated again after closing the Handheld or Hotbar radial menu

private:
	/** If we're currently in the state of respawning */
	UPROPERTY( ReplicatedUsing = OnRep_IsRespawning )
	bool mIsRespawning;

	/** True if we just finished respawning and are waiting for the client to confirm that */
	bool mPlayerRespawnGracePeriodActive{false};

	/** Handler for the timer that checks which map area the pawn is in */
	FTimerHandle mAreaCheckTimerHandle;

	/** Cached info about the map areas */
	UPROPERTY()
	class UFGMapAreaTexture* mCachedMapAreaTexture;

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

	/** List of music player to keep track of  */
	UPROPERTY()
	TArray< UObject* > mMusicPlayerList;

	bool mMapMarkerModeActive;
	bool mMapMarkerModeButtonPressed;

	/** Privilege level of this player when playing on the dedicated server. None if not playing on Dedicated Server */
	UPROPERTY( Replicated, Transient )
	EPrivilegeLevel mDedicatedServerPrivilegeLevel;
};

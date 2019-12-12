#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGPlayerControllerBase.h"
#include "FGGameState.h"
#include "FGChatManager.h"
#include "FGPlayerController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FPlayerEnteredAreaDelegate, TSubclassOf< class UFGMapArea >, mapArea );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDisabledInputGateDelegate, FDisabledInputGate, newDisabledInputGate );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnToggleInventory, bool, isOpen );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnToggleInteractionUI, bool, isOpen, TSubclassOf< class UUserWidget >, interactionClass );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnShortcutsLayoutChanged );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnShortcutChanged );

UCLASS( Config=Game)
class AFGPlayerController : public AFGPlayerControllerBase
{
	GENERATED_BODY()
public:
	AFGPlayerController(); 

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual bool ReplicateSubobjects( class UActorChannel* channel, class FOutBunch* bunch, FReplicationFlags* repFlags ) override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AController interface
	virtual void OnRep_PlayerState() override;
	virtual void SetPawn( APawn* inPawn ) override;
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

	/** Execute the hotbar shortcut with the specified index */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void ExecuteShortcut( int32 shortcutIndex );

	/** Get all hotbar shortcuts */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void GetAllShortcuts( TArray< class UFGHotbarShortcut* >& out_shortcuts );

	/** Get all valid shortcuts */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void GetValidShortcuts( TArray<class UFGHotbarShortcut*>& out_shortcuts );

	/** Called when the shortcuts layout have changed, e.g. shortcut added. */
	UPROPERTY( BlueprintAssignable )
	FOnShortcutsLayoutChanged OnShortcutsLayoutChanged;

	/** Called when a shortcut has changed, e.g. activated or inactivated */
	UPROPERTY( BlueprintAssignable )
	FOnShortcutChanged OnShortcutChanged;

	/** Called when the player opens or closes the inventory */
	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Inventory" )
	FOnToggleInventory OnToggleInventory;

	/** Called when the player opens or closes the inventory */
	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Inventory" )
	FOnToggleInteractionUI OnToggleInteractionUI;
	
	/** Set the specified hotbar shortcut on the index if it's valid */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void SetRecipeShortcutOnIndex( TSubclassOf< class UFGRecipe > recipe, int32 onIndex );

	/** Get the shortcut index of a recipe, -1 if it doesn't have any shortcut index assigned */
	UFUNCTION( BlueprintPure, Category = "Shortcut" )
	int32 GetRecipeShortcutIndex( TSubclassOf< class UFGRecipe > recipe ) const;

	/** Set the specified shortcut on the index if it's valid */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	void SetDismantleShortcutOnIndex( int32 onIndex );

	/** Get the shortcut index dismantle have, -1 if it doesn't have any shortcut index assigned */
	UFUNCTION( BlueprintPure, Category = "Shortcut" )
	int32 GetDismantleShortcutIndex() const;

	/**
	 * Converts a keyEvent to what shortcut it's associated with
	 * @return -1 if not associated with any shortcut, else the shortcut index 
	 */
	UFUNCTION( BlueprintCallable, Category = "Shortcut" )
	int32 GetShortcutIndexFromKey( const FKeyEvent& key );

	/** Called when the pawn this controller is controlling enters a map area */
	UPROPERTY( BlueprintAssignable, Category = "Map Area", DisplayName = "OnMapAreaEntered" )
	FPlayerEnteredAreaDelegate MapAreaEntered;

	/** Tells the server to start transferring fog of war data to the requesting client  */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_RequestFogOfWarData();

	/** Transfer fog of war data to the client */
	UFUNCTION( Reliable, Client )
	void Client_TransferFogOfWarData( const TArray<uint8>& fogOfWarRawData, int32 index );

	/** Gets the size on the viewport of the given actor */
	UFUNCTION( BlueprintPure, Category = "HUD" )
	float GetObjectScreenRadius( AActor* actor, float boundingRadius );

	/** Gets the object radius for a given actor in order to align with a desired screen space radius */
	UFUNCTION( BlueprintPure, Category = "HUD" )
	float GetScreenBasedObjectRadius( AActor* actor, float screenRadius );

	/** Gets called on the client */
	UFUNCTION( Reliable, Client, BlueprintCallable )
	void Client_AddMessage( TSubclassOf< class UFGMessageBase > newMessage );

	/** Gets called on the client */
	UFUNCTION( BlueprintCallable, Category = "Message" )
	bool GetPlayerHasMessage( TSubclassOf< class UFGMessageBase > newMessage );

	FORCEINLINE class UFGMapAreaTexture* GetMapAreaTexture() const { return mCachedMapAreaTexture; }

	/** Exec to perform a MFA analysis. */
	UFUNCTION( Exec )
	void MaterialFlowAnalysis( FString recipeName );
	/** Exec to perform a Material Lookup. */
	UFUNCTION( Exec )
	void MaterialLookup( FString itemName );

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
	FORCEINLINE void SetTutorialMode( bool active ) { mInTutorialMode = active; }

	/** Deals the damage on an impact from a projectile fired by a weapon */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_DealImpactDamage( const FHitResult& impact, FVector forwardVector, float damage, TSubclassOf< UDamageType > damageType, AActor* inInstigator );

	/** Deals the radial damage from an exploding projectile fired by a weapon */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_DealRadialDamage( const FHitResult& impact, float damage, float radius, TSubclassOf< UDamageType > damageType, AActor* inInstigator );

	/** Used to create our list of sequences  */
	UFUNCTION( BlueprintImplementableEvent, Category = "Cheat" )
	void CreateSequenceList();

	UFUNCTION( BlueprintPure, Category = "Screenshot" )
	FString GetScreenshotPath( bool isHighRes );

	virtual bool DestroyNetworkActorHandled() override;


	virtual void AcknowledgePossession( class APawn* P ) override;

protected:
	/** Pontentially spawns deathcreate when disconnecting if we are dead */
	void PonderRemoveDeadPawn();

	/** SERVER ONLY: Mostly for the saves that have gotten a nulled out session name */
	UFUNCTION(exec)
	void SetSessionName( FString newSessionName );

	UFUNCTION( exec )
	void TrackAkComponents( bool byClass = true );
	UFUNCTION( exec )
	void TrackAkMemoryPools();
	UFUNCTION( exec )
	void TrackAkComponentsWithNoPositionOrOwner();

	/** Get the character we are controlling (if we are in vehicles, this finds our pawn in the vehicle), can return null if we don't control any character */
	class AFGCharacterBase* GetControlledCharacter() const;

	/** Return false if we don't control anything */
	bool ControlledCharacterIsAliveAndWell() const;

	/**
	 * Called on owning client when respawning starts
	 */
	UFUNCTION( BlueprintImplementableEvent, Category="Respawn" )
	void OnStartRespawn( bool isJoining );

	/**
	* Called on owning client when respawning starts
	*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Respawn" )
	void OnFinishRespawn();


	/**
	* Called on start of a local client player. Reutrn the component that should handle the wind for the player
	*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Sounds" )
	UAkComponent* OnSetupMovementWind();

	/** User pressed primary fire button */
	UFUNCTION()
	virtual void OnPrimaryFire();

	// Begin APlayerController interface
	virtual void SetupInputComponent() override;
	virtual void BuildInputStack( TArray< UInputComponent* >& inputStack ) override;
	// End APlayerController interface

	/** Sends a ping to the other players at the look at location */
	void OnAttentionPingPressed();

	/** Function that checks which map area our pawn is in */
	UFUNCTION()
	void CheckPawnMapArea();

	/** Caches a lot off stuff needed for the map area checks */
	bool InitMapAreaCheckFunction();

	/** Returns the map area that the pawn is currently in */
	UFUNCTION( BlueprintPure, Category = "Map" )
	TSubclassOf< UFGMapArea > GetCurrentMapArea() const;

	UFUNCTION( BlueprintCallable, Category = "Chat" )
	void EnterChatMessage( const FString& inMessage );

	UFUNCTION( BlueprintNativeEvent, Category = "Input" )
	void OnDisabledInputGateChanged();

	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void EnablePhotoMode( bool isEnabled );

	UFUNCTION( BlueprintImplementableEvent, Category = "Photo Mode" )
	void TakePhoto();

	UFUNCTION( BlueprintImplementableEvent, Category = "Photo Mode" )
	void TogglePhotoModeInstructionsWidget();

	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void TogglePhotoMode();
	
	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void ToggleHiResPhotoMode();

	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void IncrementPhotoModeFOV();
	
	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void DecrementPhotoModeFOV();

	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	int32 GetPhotoModeFOV() { return mPhotoModeFOV; }

	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	bool GetIsPhotoMode() { return mPhotoModeEnabled; }

	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	bool GetHiResPhotoModeEnabled() { return mHiResPhotoMode; }


private:
	/** Begins the setup of the tutorial subsystem */
	void SetupTutorial();

	/** Called when the server and client is done waiting for level streaming etc. */
	void FinishRespawn();

	UFUNCTION( Reliable, Server, WithValidation )
	void Server_SetRecipeShortcutOnIndex( TSubclassOf<class UFGRecipe> recipe, int32 onIndex );
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_SetDismantleShortcutOnIndex( int32 onIndex );
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

	void OnShortcutsReplicated();

	static void testAndProcesAdaMessages( AFGPlayerController* owner, const FString &inMessage, AFGPlayerState* playerState, float serverTimeSeconds, APlayerState* PlayerState, AFGGameState* fgGameState );
public:
	

	/** Indicates if this playercontroller should trigger sound volumes */
	UPROPERTY( EditDefaultsOnly, Category = "Sound" )
	bool mCanAffectAudioVolumes;
protected:
	/** The array of all remote call objects this player controller has */
	UPROPERTY( Replicated )
	TArray< UFGRemoteCallObject* > mRemoteCallObjects;

	/** 
	 * This input component should only be used for chords, Alt/Ctrl/Shift/Cmd + Any Key.
	 * This will be on top of stack, since it only consumes input if entire chord is pressed, so a single left click will be let through
	 */
	UPROPERTY()
	class UInputComponent* mInputComponentChords;

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
	UAkComponent* mMovementWindComp;

	FVector mMovementWindVelocityBuffer;
	float mTurnOffMovementWindTimer;
	float mMovementWindInAirTimer;
	float mMovementSpeedSoft; //Used to detect changes in movement speed

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

	UPROPERTY()
	class UInputComponent* mPhotomodeInputComponent;
};
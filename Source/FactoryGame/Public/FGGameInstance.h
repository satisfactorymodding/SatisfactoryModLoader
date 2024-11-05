// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Engine/GameInstance.h"
#include "Online/FGOnlineHelpers.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Framework/Application/IInputProcessor.h" // <FL> [WuttkeP] Added input pre-processor for automatically updating the last used input device type.
#include "FGGameInstance.generated.h"

// <FL> ZimmermannA For usage outside of game instance
extern TAutoConsoleVariable< bool > CVarForceMouseAndKeyboardDeviceType;
extern TAutoConsoleVariable< bool > CVarForceGamepadDeviceType;

UENUM(BlueprintType)
enum class EInputDeviceMode : uint8
{
	InputDeviceMode_MouseAndKeyboardAndGamepad,
	InputDeviceMode_MouseAndKeyboard,
	InputDeviceMode_Gamepad
};
// </FL>

class IFGDedicatedServerInterface;

UENUM(BlueprintType)
enum class EJoinSessionState : uint8
{
	JSS_NotJoiningSession,
	JSS_WaitingForLoginToComplete,
	JSS_QueryingHostsId,
	JSS_DestroyingOldSession,
	JSS_ConnectingToHost
};

// <FL> [WuttkeP] Added types for input device type detection and switching.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnActiveInputDeviceTypeChanged, EInputDeviceType, newDeviceType );
DECLARE_DYNAMIC_DELEGATE_OneParam( FFGInputDeviceTypeChangedDelegate, EInputDeviceType, newDeviceType);
// </FL>

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnJoinSessionStateChanged, EJoinSessionState, newState );

// <FL> [WuttkeP] Added callback for updating key hints.
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FFGKeyHintsChanged );
// </FL>

// Used for reaching through the SlateApplication focus changed event to blueprints.
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FFGOnFocusChanged );

USTRUCT()
struct FOnJoinSessionData
{
	GENERATED_BODY()

	void Init( class UFGLocalPlayer* player, const FOnlineSessionSearchResult& session )
	{
		LocalPlayer = player;
		Session = session;

		JoinInProgress = true;
	}

	void Done()
	{
		JoinInProgress = false;
		LocalPlayer = nullptr;
	}

	void SetState( EJoinSessionState newState, FOnJoinSessionStateChanged& onStateChangedDelegate );

	FORCEINLINE EJoinSessionState GetState() const { return State; }

	/** Player that want to join the session */
	UPROPERTY()
	class UFGLocalPlayer* LocalPlayer;

	/** Session to join */
	FOnlineSessionSearchResult Session;

	/** True if we are currently joining a session */
	uint8 JoinInProgress:1;
private:
	EJoinSessionState State;
};

/**
*
*/
USTRUCT( BlueprintType )
struct FFGModPackage
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite, Category = "Modding" )
	FName ModPath;

	UPROPERTY( BlueprintReadWrite, Category = "Modding" )
	bool HasFGMods;

	UPROPERTY( BlueprintReadWrite, Category = "Modding" )
	FString Author;

	UPROPERTY( BlueprintReadWrite, Category = "Modding" )
	FString Version;

	UPROPERTY( BlueprintReadWrite, Category = "Modding" )
	FString Description;

	FFGModPackage()
	{
		ModPath = FName( TEXT( "" ) );
		HasFGMods = false;
		Author = TEXT( "" );
		Version = TEXT( "" );
		Description = TEXT( "" );
	}
};

USTRUCT( BlueprintType )
struct FFGGameNetworkErrorMsg
{
	GENERATED_BODY()
	FFGGameNetworkErrorMsg( ENetworkFailure::Type _errorType, const FString& _errorMsg ) : errorType( _errorType ), errorMsg( _errorMsg )
	{}
	FFGGameNetworkErrorMsg( ) : errorType( -1 ), errorMsg( "No errors" )
	{}
	UPROPERTY( BlueprintReadWrite)
	TEnumAsByte<ENetworkFailure::Type> errorType;

	UPROPERTY( BlueprintReadWrite )
	FString errorMsg;
};

/** Used to store the encryption data for the outgoing connection from the client to the dedicated server */
struct FFGPendingConnectionEncryptionData
{
	/** Encryption token that is associated to this encryption data. Used to make sure we do not use a wrong token. */
	FString EncryptionToken;
	/** Encryption data to use for encrypting the connection */
	FEncryptionData EncryptionData;
};

// Don't pass the error here, as we want the user to specify how it want to handle the error itself (peek or get)
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnNewError );

/** Delegate when a network error has occured, like mismatching version, timeouts and so on */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnNetworkErrorRecieved, ENetworkFailure::Type, errorType, FString, errorMsg );

class UFGLocalPersistenceStore;
	/**
 * @OSS: Responsibilities:
 * - QueryNATType:
 * This queries the backend systems what kind of NAT they think we have. Doesn't always succeed
 * - Joining Sessions
 * We have two ways of joining sessions, invites or through joining someones presence. This is done through the UGameInstance::JoinSession
 * call. This will automatically tear down our current session. Leave the current game and join the new session
 */
UCLASS()
class FACTORYGAME_API UFGGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	// Begin UGameInstance interface
	virtual void Init() override;
	virtual void StartGameInstance() override;
	virtual bool JoinSession( ULocalPlayer* localPlayer, const FOnlineSessionSearchResult& searchResult ) override;
	virtual void ReceivedNetworkEncryptionAck(const FOnEncryptionKeyResponse& Delegate) override;
	virtual void ReceivedNetworkEncryptionToken(const FString& EncryptionToken, const FOnEncryptionKeyResponse& Delegate) override;
	virtual EEncryptionFailureAction ReceivedNetworkEncryptionFailure(UNetConnection* Connection) override;
#if WITH_EDITOR
	virtual FGameInstancePIEResult InitializeForPlayInEditor(int32 PIEInstanceIndex, const FGameInstancePIEParameters& Params) override;
#endif
	// End UGameInstance interface

	/** Get the music manager */
	FORCEINLINE class UFGMusicManager* GetMusicManager() const{ return mMusicManager; }

	/** Access the save system */
	FORCEINLINE class UFGSaveSystem* GetSaveSystem() const{ return mSaveSystem; }

	/** @return OnlineSession class to use for this game instance  */
	virtual TSubclassOf<UOnlineSession> GetOnlineSessionClass() override;
	
	/** Returns the telemetry instance, if analytics are disabled it returns nullptr. */
	static class UDSTelemetry* GetTelemetryInstanceFromWorld( UWorld* world );
	
	// @todo: Move error functions to a "message bus" class	
	/** Pushes a error to the game, that handles it appropriately */
	void PushError( TSubclassOf<class UFGErrorMessage> errorMessage );

	/** Pushes a error to the game, that handles it appropriately */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|ErrorHandling", meta=(DefaultToSelf = "worldContext"))
	static void PushError( UObject* worldContext, TSubclassOf<class UFGErrorMessage> errorMessage );
	
	/** Get the next error and removes it from the error queue, returns null when there is no more errors */
	class UFGErrorMessage* GetNextError();

	/** Get the next error and removes it from the error queue, returns null when there is no more errors */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|ErrorHandling", meta=(DefaultToSelf = "worldContext"))
	static class UFGErrorMessage* GetNextError( UObject* worldContext );

	/** Peek at the next error and keep it in the error queue, returns null when there is no more errors */
	class UFGErrorMessage* PeekNextError() const;

	/** Peek at the next error and keep it in the error queue, returns null when there is no more errors */
	UFUNCTION( BlueprintPure, Category="FactoryGame|ErrorHandling", meta=(DefaultToSelf = "worldContext"))
	static class UFGErrorMessage* PeekNextError( UObject* worldContext );

	/** Marks that the player has seen alpha info screen */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetHasSeenAlphaInfoScreen();

	/** Has the player seen the alpha info screen? */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool ShouldShowAlphaInfoScreen() const;

	// Finds non-original content and populates ModPackages
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Modding" )
	bool FindModPackages();

	// Populates UGC arrays with data from ModPackages, Updates ModPackages Information with contents
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Modding" )
	void GetFGUGC( UClass* WeaponClass, UClass* EnemyClass, UClass* BossClass, UClass *PlayerPawnClass );

	// Called when exiting to desktop/shutting down
	virtual void Shutdown() override;

	/* returns true if there were an error, and fills in the enum and string. If there were no error the type and msg will be undefined, and the function returns false. To get the next message or reset the error state, call PopLatestNetworkError function*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ErrorHandling" )
	bool GetLatestNetworkError( FFGGameNetworkErrorMsg& msg );

	/* Pops the latest network message, removing it from the queue and resetting the error state. If there is more messages left after the pop it will return true, otherwise false. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|ErrorHandling" )
	bool PopLatestNetworkError();

	UFUNCTION(BlueprintPure, Category="FactoryGame|Online")
	EJoinSessionState GetCurrentJoinSessionState() const;

	/** Get the instance of the debug overlay widget. Will create one if it doesn't exists. Might return null if we don't have a specificed debug overlay widget class */
	class UFGDebugOverlayWidget* GetDebugOverlayWidget();

	/** Returns the interface to the dedicated server specific functionality on the game instance level */
	IFGDedicatedServerInterface* GetDedicatedServerInterface() const;

	/** Updates the encryption data set for the pending client connection */
	void SetPendingConnectionEncryptionData( const FFGPendingConnectionEncryptionData& NewEncryptionData );

	// <FL> [WuttkeP] Added functions for input device type detection and switching.
	UFUNCTION( BlueprintPure )
	EInputDeviceType GetActiveInputDeviceType();
	// </FL>

	
	/** Listener delegate is called by the SlateApplication. The OnFocusChanged delegate can be bound to in blueprint. */
	UPROPERTY( BlueprintAssignable, Category = "UI" )
	FFGOnFocusChanged mOnFocusChangedDelegate;
	FDelegateHandle mOnFocusChangedListenerDelegate;

protected:
	// Called when a map has loaded properly in Standalone
	virtual void LoadComplete( const float loadTime, const FString& mapName ) override;

	/** Called after we have destroyed a old session for joining a new session */
	virtual void OnDestroyOldSessionComplete_JoinSession( FName gameSessionName, bool wasSuccessful );

	/** Called after we have queried a friends product id */
	virtual void OnQueryFriendProductIdCompleted_JoinSession( bool wasSuccessful, FString EpicId, struct EOS_ProductUserIdDetails* ProductId );

	/** Called after we have queried a friends product id */
	UFUNCTION()
	virtual void PollHostProductUserId_JoinSession();

	/** Called after we have joined a session, makes sure we copy the session settings from the host */
	void OnJoinSessionComplete( FName sessionName, EOnJoinSessionCompleteResult::Type joinResult );

	void SendRecievedNetworkErrorOnDelegate( UWorld* world, UNetDriver* driver, ENetworkFailure::Type errorType, const FString& errorMsg );

	void OnLastInputDeviceTypeChanged(EInputDeviceType deviceType);

	/** Add a callback to the input device type changed event and immediately call it, for convenience. */
	UFUNCTION( BlueprintCallable )
	void AddAndCallDeviceTypeChangedCallback( UPARAM(DisplayName="Event") FFGInputDeviceTypeChangedDelegate Delegate);

private:
	void OnPreLoadMap( const FString& levelName );

	/** Initializes the Game Analytics Service. Requires that the Epic Online Services handle has been created beforehand. */
	void InitGameAnalytics();
	void ShutdownGameAnalytics();

	/** Telemetry */
	bool InitTelemetry( const FString& gameID, const FString& buildID, const FString& onlinePlatformIdentifier, const FString& onlinePlatformUserID );
	void ShutdownTelemetry();
	void SubmitGameStartTelemetry() const;
	UFUNCTION()
	void SubmitNetModeTelemetry( UWorld* world ) const;
	void SubmitModTelemetry() const;

	void JoinSession_Internal();

protected:
	/** The global save system */
	UPROPERTY()
	class UFGSaveSystem* mSaveSystem;

	// @todo: Make accessors for this when moving this to FGErrorBus or similar
	/** Called whenever a new error is added that doesn't send you to main menu */
	UPROPERTY(BlueprintAssignable)
	FOnNewError mOnNewError;

	TArray< FFGGameNetworkErrorMsg > mNetworkErrorQueue;

	UPROPERTY( BlueprintAssignable )
	FOnNetworkErrorRecieved mOnNetworkErrorRecieved;
	
	///** Main telemetry instance, nullptr if telemetry is turned off by the player, class not defined if telemetry is disabled for a build. */
	class UDSTelemetry* mTelemetryInstance;

	UPROPERTY( Transient )
	UObject* mTelemetryInstanceObject;
	
	/** List of errors that we should pop */
	UPROPERTY()
	TArray<class UFGErrorMessage*> mErrorList;

	/** Storing data for joining a session */
	UPROPERTY()
	FOnJoinSessionData mJoinSessionData;

	/** Called when the state of joining session has been updated */
	UPROPERTY(BlueprintAssignable)
	FOnJoinSessionStateChanged mOnJoinSessionStateUpdated;

	/** Join session complete handle */
	FDelegateHandle mOnJoinSessionCompleteHandle;
	
	/** Used to query NAT type, nothing more */
	EOS_HP2P mP2PHandle = nullptr;

	/** Encryption data for our pending connection to the DS */
	FFGPendingConnectionEncryptionData mPendingConnectionEncryptionData;

	EInputDeviceMode mInputDeviceMode = EInputDeviceMode::InputDeviceMode_MouseAndKeyboard;

public:

	void SetInputDeviceMode(EInputDeviceMode InputDeviceMode);
	bool GetConsoleVariableBool(const char* Variable);
	void SetConsoleVariable(const char* Variable, bool Active);

	EInputDeviceMode GetInputDeviceMode() { return mInputDeviceMode; }

	// Mod packages found - valid or invalid
	UPROPERTY( BlueprintReadOnly, Category = "Modding" )
	TArray< FFGModPackage > ModPackages;

	/** Controlling our music since... 2018 */
	UPROPERTY()
	class UFGMusicManager* mMusicManager;

	/** Has the player seen the alpha info screen, used to only show it once per session */
	bool mHasSeenAlphaInfo;

	// <FL> [WuttkeP] Added callback for updating key hints.
	/** Fired when a key hint changes without the focused widget changing. */
	UPROPERTY( BlueprintAssignable, Category = "Input" )
	FFGKeyHintsChanged mOnKeyHintsChanged;
	// </FL>

	// <FL> [WuttkeP] Added callback for input device type switching.
	UPROPERTY( BlueprintAssignable, Category = "Input" )
	FFGOnActiveInputDeviceTypeChanged mOnActiveInputDeviceTypeChanged;
	// </FL>

	// <FL> [KonradA] Getter For Local Persistence store
	UFUNCTION(BlueprintCallable)
	UFGLocalPersistenceStore* GetLocalPersistenceStore();
	// </FL>
	
#if WITH_EDITOR
	/** If this game instance was started as a part of Play In Editor, this will cache the Server Port it is using */
	int32 mCachedPIEServerPort;
#endif
private:
	UPROPERTY()
	class UFGDebugOverlayWidget* mDebugOverlayWidget;

	//<FL>[KonradA] Helper store for key value pairs so that users can locally store data that does not need to be replicated
	UPROPERTY()
	UFGLocalPersistenceStore* mLocalPersistenceStore;
	//</FL>

	/** Is called by the SlateApplication */
	void OnFocusChanged( const FFocusEvent& FocusEvent, const FWeakWidgetPath& OldFocusedWidgetPath,
						 const TSharedPtr< SWidget >& OldFocusedWidget, const FWidgetPath& NewFocusedWidgetPath,
						 const TSharedPtr< SWidget >& NewFocusedWidget );
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Engine/GameInstance.h"
#include "NAT.h"
// MODDING EDIT: Online stuff doesn't work
//#include "AnalyticsService.h"
#include "FGAnalyticsMacros.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
// MODDING EDIT: Online stuff...
//#include "EOSSDKForwards.h"
//#include "AnalyticsService.h"
#include "FGGameInstance.generated.h"

// MODDING EDIT
UCLASS()
class UAnalyticsService : public UObject
{
	GENERATED_BODY()
};
typedef struct EOS_P2PHandle* EOS_HP2P;
typedef struct EOS_ProductUserIdDetails* EOS_ProductUserId;

UENUM(BlueprintType)
enum class EJoinSessionState : uint8
{
	JSS_NotJoiningSession,
	JSS_WaitingForLoginToComplete,
	JSS_QueryingHostsId,
	JSS_DestroyingOldSession,
	JSS_ConnectingToHost
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnJoinSessionStateChanged, EJoinSessionState, newState );

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


// Don't pass the error here, as we want the user to specify how it want to handle the error itself (peek or get)
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnNewError );

/** Delegate when a network error has occured, like mismatching version, timeouts and so on */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnNetworkErrorRecieved, ENetworkFailure::Type, errorType, FString, errorMsg );

// Called if/when the NAT-type is updated
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnNatTypeUpdated, ECachedNATType, natType );
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
	UFGGameInstance();
	~UFGGameInstance();

	// Begin UGameInstance interface
	virtual void Init() override;
	virtual bool JoinSession( ULocalPlayer* localPlayer, const FOnlineSessionSearchResult& searchResult ) override;
	// End UGameInstance interface

	/** Get the music manager */
	FORCEINLINE class UFGMusicManager* GetMusicManager() const{ return mMusicManager; }

	/** Access the save system */
	FORCEINLINE class UFGSaveSystem* GetSaveSystem() const{ return mSaveSystem; }

	/** @return OnlineSession class to use for this game instance  */
	virtual TSubclassOf<UOnlineSession> GetOnlineSessionClass() override;

	/** Service provider for analytics */
	FORCEINLINE UAnalyticsService* GetAnalyticsService() const { return mAnalyticsService; }

	/** Returns the relative analytics services from the world context holder */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|GameAnalytics", DisplayName = "GetGameAnalyticsService", Meta = ( DefaultToSelf = "WorldContext" ) )
	static UAnalyticsService* GetGameAnalyticsService( UObject* worldContext );

	/** Returns the relative analytics services from the world context holder */
	static UAnalyticsService* GetAnalyticsServiceFromWorld( UWorld* worldContext );

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

	/** Set if the player has seen alpha info screen */
	UFUNCTION( BlueprintCallable )
	void SetHasSeenAlphaInfoScreen( bool hasSeen );

	/** Has the player seen the alpha info screen? */
	UFUNCTION( BlueprintCallable )
	FORCEINLINE bool HasPlayerSeenAlphaInfoScreen() const { return mHasSeenAlphaInfo; }

	// Finds non-original content and populates ModPackages
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Modding" )
	bool FindModPackages();

	// Populates UGC arrays with data from ModPackages, Updates ModPackages Information with contents
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Modding" )
	void GetFGUGC( UClass* WeaponClass, UClass* EnemyClass, UClass* BossClass, UClass *PlayerPawnClass );

	// Called when exiting to desktop/shutting down
	virtual void Shutdown() override;

	/** Setter for  mSkipOnboarding*/
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Onboarding" ) 
	void SetSkipOnboarding( bool doSkip );

	/** Getter for  mSkipOnboarding*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Onboarding" )
	FORCEINLINE bool GetSkipOnboarding() { return mSkipOnboarding; }

	//[Gafgar:Tue/07-04-2020] moved to be done automatically now
	///** Query our current NAT-type */
	void QueryNATType();

	/** Get cached NAT-type */
	FORCEINLINE ECachedNATType GetCachedNATType() const{ return mCachedNATType; }


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

public: //MODDING EDIT protected -> public
	// Called when a map has loaded properly in Standalone
	virtual void LoadComplete( const float loadTime, const FString& mapName ) override;
protected: // MODDING EDIT

	/** Called after we have destroyed a old session for joining a new session */
	virtual void OnDestroyOldSessionComplete_JoinSession( FName gameSessionName, bool wasSuccessful );

	/** Called after we have queried a friends product id */
	virtual void OnQueryFriendProductIdCompleted_JoinSession( bool wasSuccessful, FString EpicId, EOS_ProductUserId ProductId );

	/** Called after we have queried a friends product id */
	UFUNCTION()
	virtual void PollHostProductUserId_JoinSession();

	/** Forward function when nat query is completed */
	static void _OnNATUpdatedCallback( void* userData, ECachedNATType Data);

	/** Called when we receive a callback about our current NAT-type  */
	void OnNATUpdated( ECachedNATType Data);

	/** Called after we have joined a session, makes sure we copy the session settings from the host */
	void OnJoinSessionComplete( FName sessionName, EOnJoinSessionCompleteResult::Type joinResult );

	void SendRecievedNetworkErrorOnDelegate( UWorld* world, UNetDriver* driver, ENetworkFailure::Type errorType, const FString& errorMsg );

private:
	void OnPreLoadMap( const FString& levelName );
	void OnPostLoadMap( UWorld* loadedWorld );

	// Usually called when loading save/exiting to menu
	void OnWorldDestroy( UWorld* world );

	/** Initializes the Game Analytics Service. Requires that the Epic Online Services handle has been created beforehand. */
	void InitGameAnalytics();

	void JoinSession_Internal();
	
	/** Called when the option for sending gameplay data is changed*/
	UFUNCTION()
	void OnSendGameplayDataUpdated( FString cvar );

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

	/** The global Analytics Service */
	UPROPERTY()
	UAnalyticsService* mAnalyticsService;

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

	/** Has the player chosen to skip the onboarding? */
	bool mSkipOnboarding;

	/** Called when nat-type is updated */
	UPROPERTY(BlueprintAssignable)
	FOnNatTypeUpdated mOnNatTypeUpdated;

	/** Used to query NAT type, nothing more */
	EOS_HP2P mP2PHandle;

	/** Our last seen NAT-type */
	ECachedNATType mCachedNATType;

	///** The handle for the Epic Online Services manager. Is initialized in Init(). */
	//UPROPERTY()
	//class UEOSManager* mCachedEOSManager;
	
public:
	// Mod packages found - valid or invalid
	UPROPERTY( BlueprintReadOnly, Category = "Modding" )
	TArray< FFGModPackage > ModPackages;

	/** Controlling our music since... 2018 */
	UPROPERTY()
	class UFGMusicManager* mMusicManager;

	/** Has the player seen the alpha info screen, used to only show it once per session */
	bool mHasSeenAlphaInfo;
	
private:
	UPROPERTY()
	class UFGDebugOverlayWidget* mDebugOverlayWidget;
	
};

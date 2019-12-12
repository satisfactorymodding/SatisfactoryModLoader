#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Engine/GameInstance.h"
#include "NAT.h"
//#include "EpicPeerManager.h"
//#include "AnalyticsService.h"
#include "FGAnalyticsMacros.h"
#include "OnlineSessionSettings.h"
#include "Online.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Engine/EngineTypes.h"
#include "FGGameInstance.generated.h"



USTRUCT()
struct FOnJoinSessionData
{
	GENERATED_BODY()

	void Init( ULocalPlayer* player, const FOnlineSessionSearchResult& session )
	{
		LocalPlayer = player;
		//Session = session;

		JoinInProgress = true;
		HasDestoryedExistingSession = false;
	}

	// We have destroyed a existing progress
	void DestroyedExistingSession()
	{
		HasDestoryedExistingSession = true;
	}

	void Done()
	{
		JoinInProgress = false;
		HasDestoryedExistingSession = false;
	}

	/** Player that want to join the session */
	UPROPERTY()
	ULocalPlayer* LocalPlayer;

	// MODDING EDIT: Online not working
	///** Session to join */
	//FOnlineSessionSearchResult Session;

	/** True if we are currently joining a session */
	bool JoinInProgress;

	/** If true, then we have just destroyed a exsting session */
	bool HasDestoryedExistingSession;
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

UCLASS()
class UFGGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFGGameInstance();

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

	// MODDING EDIT
	///** Service provider for analytics */
	//FORCEINLINE class UAnalyticsService* GetAnalyticsService() const { return mAnalyticsService; }

	// MODDING EDIT
	///** Returns the relative analytics services from the world context holder */
	//UFUNCTION( BlueprintPure, Category = "GameAnalytics", DisplayName = "GetGameAnalyticsService", Meta = ( DefaultToSelf = "WorldContext" ) )
	//static UAnalyticsService* GetGameAnalyticsService( UObject* worldContext );
	//
	///** Returns the relative analytics services from the world context holder */
	//static UAnalyticsService* GetAnalyticsServiceFromWorld( UWorld* worldContext );

	// @todo: Move error functions to a "message bus" class	
	/** Pushes a error to the game, that handles it appropriately */
	void PushError( TSubclassOf<class UFGErrorMessage> errorMessage );

	/** Pushes a error to the game, that handles it appropriately */
	UFUNCTION( BlueprintCallable, Category="Error", meta=(DefaultToSelf = "worldContext"))
	static void PushError( UObject* worldContext, TSubclassOf<class UFGErrorMessage> errorMessage );
	
	/** Get the next error and removes it from the error queue, returns null when there is no more errors */
	class UFGErrorMessage* GetNextError();

	/** Get the next error and removes it from the error queue, returns null when there is no more errors */
	UFUNCTION( BlueprintCallable, Category="Error", meta=(DefaultToSelf = "worldContext"))
	static class UFGErrorMessage* GetNextError( UObject* worldContext );

	/** Peek at the next error and keep it in the error queue, returns null when there is no more errors */
	class UFGErrorMessage* PeekNextError() const;

	/** Peek at the next error and keep it in the error queue, returns null when there is no more errors */
	UFUNCTION( BlueprintPure, Category="Error", meta=(DefaultToSelf = "worldContext"))
	static class UFGErrorMessage* PeekNextError( UObject* worldContext );

	/** Set if the player has seen alpha info screen */
	UFUNCTION( BlueprintCallable )
	void SetHasSeenAlphaInfoScreen( bool hasSeen );

	/** Has the player seen the alpha info screen? */
	UFUNCTION( BlueprintCallable )
	FORCEINLINE bool HasPlayerSeenAlphaInfoScreen() const { return mHasSeenAlphaInfo; }

	// Finds non-original content and populates ModPackages
	UFUNCTION( BlueprintCallable, Category = "Modding" )
	bool FindModPackages();

	// Populates UGC arrays with data from ModPackages, Updates ModPackages Information with contents
	UFUNCTION( BlueprintCallable, Category = "Modding" )
	void GetFGUGC( UClass* WeaponClass, UClass* EnemyClass, UClass* BossClass, UClass *PlayerPawnClass );

	// Called when exiting to desktop/shutting down
	virtual void Shutdown() override;

	/** Setter for  mSkipOnboarding*/
	UFUNCTION( BlueprintCallable, Category = "Onboarding" ) 
	void SetSkipOnboarding( bool doSkip );

	/** Getter for  mSkipOnboarding*/
	UFUNCTION( BlueprintPure, Category = "Onboarding" )
	FORCEINLINE bool GetSkipOnboarding() { return mSkipOnboarding; }

	/** Query our current NAT-type */
	void QueryNATType();

	/** Get cached NAT-type */
	FORCEINLINE ECachedNATType GetCachedNATType() const{ return mCachedNATType; }


	/* returns true if there were an error, and fills in the enum and string. If there were no error the type and msg will be undefined, and the function returns false. To get the next message or reset the error state, call PopLatestNetworkError function*/
	UFUNCTION( BlueprintPure, Category = "ErrorHandling" )
	bool GetLatestNetworkError( FFGGameNetworkErrorMsg& msg );

	/* Pops the latest network message, removing it from the queue and resetting the error state. If there is more messages left after the pop it will return true, otherwise false. */
	UFUNCTION( BlueprintCallable, Category = "ErrorHandling" )
	bool PopLatestNetworkError();
protected:
	// Called when a map has loaded properly in Standalone
	virtual void LoadComplete( const float loadTime, const FString& mapName ) override;

	/** Called after we have destroyed a session for joining a invite */
	virtual void OnDestroySessionComplete_JoinInvite( FName gameSessionName, bool wasSuccessful );

	// MODDING EDIT: Online not working
	///** Called when we receive a callback about our current NAT-type */
	//void OnNATQueryCompleted( const struct FOnlineError& requestStatus, TOptional<ENATType> foundNATType );
	//
	///** Called after we have joined a session, makes sure we copy the session settings from the host */
	//void OnJoinSessionComplete( FName sessionName, EOnJoinSessionCompleteResult::Type joinResult );
private:
	void OnPreLoadMap( const FString& levelName );
	void OnPostLoadMap( UWorld* loadedWorld );

	// Usually called when loading save/exiting to menu
	void OnWorldDestroy( UWorld* world );

	/** Initializes the Game Analytics Service. Requires that the Epic Online Services handle has been created beforehand. */
	void InitGameAnalytics();

	/** 
	* Update 'tick' for EOS services. Consider routing the regular tick functionality to this GameInstance UObject 
	* if Epic Online Services seems to require quicker tick rates. 
	**/
	void UpdateEOSHandle();
	FTimerHandle mAnalyticsUpdateTimerHandle;

protected:
	/** The global save system */
	UPROPERTY()
	class UFGSaveSystem* mSaveSystem;

	// @todo: Make accessors for this when moving this to FGErrorBus or similar
	/** Called whenever a new error is added that doesn't send you to main menu */
	UPROPERTY(BlueprintAssignable)
	FOnNewError mOnNewError;

	// MODDING EDIT
	///** The global Analytics Service */
	//UPROPERTY()
	//class UAnalyticsService* mAnalyticsService;

	/** List of errors that we should pop */
	UPROPERTY()
	TArray<class UFGErrorMessage*> mErrorList;

	/** Storing data for joining a session */
	UPROPERTY()
	FOnJoinSessionData mJoinSessionData;

	/** Join session complete handle */
	FDelegateHandle mOnJoinSessionCompleteHandle;

	/** Has the player chosen to skip the onboarding? */
	bool mSkipOnboarding;

	/** Called when nat-type is updated */
	UPROPERTY(BlueprintAssignable)
	FOnNatTypeUpdated mOnNatTypeUpdated;

	// MODDING EDIT: Online not working
	///** Used to query NAT type, nothing more */
	//TUniquePtr<class FEpicPeerManager> mEpicPeerManager;

	/** Our last seen NAT-type */
	ECachedNATType mCachedNATType;

	// MODDING EDIT
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
};

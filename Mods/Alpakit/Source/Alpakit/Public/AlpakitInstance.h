#pragma once

#include "CoreMinimal.h"
#include "AlpakitProfile.h"
#include "Misc/MonitoredProcess.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Misc/DateTime.h"

enum class EAlpakitInstanceState
{
	None,
	Running,
	Completed
};

enum class EAlpakitInstanceResult
{
	Undetermined,
	Success,
	Fail,
	Cancelled
};

struct FAlpakitInstanceMessageEntry
{
	ELogVerbosity::Type Verbosity{ELogVerbosity::Display};
	FString Message;
};

DECLARE_MULTICAST_DELEGATE_OneParam( FOnAlpakitProcessCompleted, EAlpakitInstanceResult /*Result*/ );
DECLARE_MULTICAST_DELEGATE_OneParam( FOnAlpakitMessageReceived, const FAlpakitInstanceMessageEntry& /*Message*/ );
DECLARE_MULTICAST_DELEGATE_OneParam( FOnAlpakitInstanceSpawned, TSharedPtr<class FAlpakitInstance> /*NewInstance*/ )

/** An instance of running Alpakit process */
class ALPAKIT_API FAlpakitInstance : public TSharedFromThis<FAlpakitInstance>
{
	EAlpakitInstanceState InstanceState{EAlpakitInstanceState::None};
	EAlpakitInstanceResult Result{EAlpakitInstanceResult::Undetermined};
	FDateTime EndTime;
	FString PluginName;
	TSharedRef<FAlpakitProfile> Profile;
	TSharedPtr<SNotificationItem> NotificationItem;
	TSharedPtr<class FSerializedUATProcess> UATProcess;
	FOnAlpakitProcessCompleted OnProcessCompletedDelegate;

	TArray<FAlpakitInstanceMessageEntry> MessageList;
	FOnAlpakitMessageReceived OnMessageReceivedDelegate;
public:
	FAlpakitInstance( const FString& InPluginName, TSharedRef<FAlpakitProfile> InProfile );

	FORCEINLINE EAlpakitInstanceState GetInstanceState() const { return InstanceState; }
	FORCEINLINE EAlpakitInstanceResult GetResult() const { return Result; }
	FORCEINLINE FDateTime GetEndTime() const { return EndTime; }
	FORCEINLINE FString GetPluginName() const { return PluginName; }

	FORCEINLINE const TArray<FAlpakitInstanceMessageEntry>& GetMessageList() const { return MessageList; }
	FORCEINLINE FOnAlpakitProcessCompleted& OnProcessCompleted() { return OnProcessCompletedDelegate; }
	FORCEINLINE FOnAlpakitMessageReceived& OnMessageReceived() { return OnMessageReceivedDelegate; }
	
	bool Start();
	void Cancel() const;

	static void GetRunningInstances( TArray<TSharedPtr<FAlpakitInstance>>& OutRunningInstances );

	// Called when the new AlpakitInstance is spawned.
	static FOnAlpakitInstanceSpawned OnNewInstanceSpawned;
private:
	static FCriticalSection GlobalListCriticalSection;
	static TArray<TSharedPtr<FAlpakitInstance>> GlobalList;
	
	void OnWorkerMessageReceived(FString Message);
	void OnWorkerCancelled();
	void OnWorkerCompleted(int32 ExitCode);
	
	void OnWorkerMessageReceived_GameThread( const FString& Message );
	void OnWorkerCancelled_GameThread();
	void OnWorkerCompleted_GameThread( bool bSuccess, double Duration, int32 ExitCode );

	void HandleCancelButtonClicked();
	void HandleDismissButtonClicked();
	void HandleOutputLogNavigate();

	void AddMessageToOutputLog( ELogVerbosity::Type Verbosity, const FString& Message );

	void SpawnNotification();
	void DismissNotification();
	void MarkNotificationAsSuccess( double Duration );
	void MarkNotificationAsFail( int32 ExitCode );
	void MarkNotificationCancelled();

	void RegisterInGlobalList();
	void RemoveFromGlobalList();
};


#include "AlpakitInstance.h"
#include "Alpakit.h"
#include "AlpakitStyle.h"
#include "Editor.h"
#include "SAlpakitLogTabContent.h"
#include "Async/Async.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Notifications/NotificationManager.h"
#include "LauncherServices/Public/ILauncher.h"
#include "LauncherServices/Public/ILauncherServicesModule.h"
#include "Modules/ModuleManager.h"
#include "TargetDeviceServices/Public/ITargetDeviceServicesModule.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "Alpakit"

FOnAlpakitInstanceSpawned FAlpakitInstance::OnNewInstanceSpawned;
FCriticalSection FAlpakitInstance::GlobalListCriticalSection;
TArray<TSharedPtr<FAlpakitInstance>> FAlpakitInstance::GlobalList;

FAlpakitInstance::FAlpakitInstance( const FString& InPluginName, TSharedRef<FAlpakitProfile> InProfile ) : PluginName( InPluginName ), Profile( InProfile )
{
}

bool FAlpakitInstance::Start()
{
	check( IsInGameThread() );
	check( InstanceState == EAlpakitInstanceState::None || InstanceState == EAlpakitInstanceState::Completed );

	UATProcess = MakeShareable(new FSerializedUATProcess(Profile->MakeUATCommandLine()));
	
	UATProcess->OnOutput().BindSP( this, &FAlpakitInstance::OnWorkerMessageReceived );
	UATProcess->OnCanceled().BindSP( this, &FAlpakitInstance::OnWorkerCancelled );
	UATProcess->OnCompleted().BindSP( this, &FAlpakitInstance::OnWorkerCompleted );

	UATProcess->Launch();
	
	InstanceState = EAlpakitInstanceState::Running;
	Result = EAlpakitInstanceResult::Undetermined;
	MessageList.Empty();
	
	SpawnNotification();

	// Register this instance in the global list
	RegisterInGlobalList();
	return true;
}

void FAlpakitInstance::Cancel() const
{
	check( IsInGameThread() || IsInSlateThread() );
	check( InstanceState == EAlpakitInstanceState::Running );

	if ( UATProcess.IsValid() )
	{
		UATProcess->Cancel(true);
	}
}

void FAlpakitInstance::OnWorkerMessageReceived( FString Message )
{
	const TSharedPtr<FAlpakitInstance> SharedSelf = AsShared();
	AsyncTask( ENamedThreads::GameThread, [SharedSelf, Message]()
	{
		SharedSelf->OnWorkerMessageReceived_GameThread( Message );
	} );
}

void FAlpakitInstance::OnWorkerCancelled()
{
	const TSharedPtr<FAlpakitInstance> SharedSelf = AsShared();
	AsyncTask( ENamedThreads::GameThread, [SharedSelf]()
	{
		SharedSelf->OnWorkerCancelled_GameThread();
	} );
}

void FAlpakitInstance::OnWorkerCompleted( int32 ExitCode )
{
	const TSharedPtr<FAlpakitInstance> SharedSelf = AsShared();
	bool bSuccess = ExitCode == 0;
	double Duration = UATProcess->GetDuration().GetTotalSeconds();
	AsyncTask( ENamedThreads::GameThread, [SharedSelf, bSuccess, Duration, ExitCode]()
	{
		SharedSelf->OnWorkerCompleted_GameThread(bSuccess, Duration, ExitCode);
	} );
}

void FAlpakitInstance::OnWorkerMessageReceived_GameThread( const FString& Message )
{
	check( IsInGameThread() );
	ELogVerbosity::Type Verbosity = ELogVerbosity::Display;
	if ( Message.Contains( TEXT("Fatal: ") ) )
	{
		Verbosity = ELogVerbosity::Fatal;
	}
	else if ( Message.Contains( TEXT("Error: ") ) )
	{
		Verbosity = ELogVerbosity::Error;
	}
	else if ( Message.Contains( TEXT("Warning: ") ) )
	{
		Verbosity = ELogVerbosity::Warning;
	}
	AddMessageToOutputLog( Verbosity, Message );
}

void FAlpakitInstance::OnWorkerCancelled_GameThread()
{
	check( IsInGameThread() );
	check( InstanceState == EAlpakitInstanceState::Running );

	InstanceState = EAlpakitInstanceState::Completed;

	EndTime = FDateTime::UtcNow();

	Result = EAlpakitInstanceResult::Cancelled;
	AddMessageToOutputLog( ELogVerbosity::Display, TEXT("Packaging cancelled by the user.") );
	MarkNotificationCancelled();

	OnProcessCompletedDelegate.Broadcast( Result );
	RemoveFromGlobalList();
}

void FAlpakitInstance::OnWorkerCompleted_GameThread( bool bSuccess, double Duration, int32 ExitCode )
{
	check( IsInGameThread() );
	check( InstanceState == EAlpakitInstanceState::Running );

	InstanceState = EAlpakitInstanceState::Completed;
	if ( bSuccess )
	{
		Result = EAlpakitInstanceResult::Success;
		AddMessageToOutputLog( ELogVerbosity::Display, FString::Printf( TEXT("Packaging finished in %.2fs"), Duration ) );
		MarkNotificationAsSuccess( Duration );
	}
	else
	{
		Result = EAlpakitInstanceResult::Fail;
		AddMessageToOutputLog( ELogVerbosity::Error, FString::Printf( TEXT("Packaging failed with ExitCode=%d"), ExitCode ) );
		MarkNotificationAsFail( Duration );
	}

	EndTime = FDateTime::UtcNow();
	
	OnProcessCompletedDelegate.Broadcast( Result );
	RemoveFromGlobalList();
}

void FAlpakitInstance::AddMessageToOutputLog( ELogVerbosity::Type Verbosity, const FString& Message )
{
	check( IsInGameThread() );

	const FAlpakitInstanceMessageEntry MessageEntry{ Verbosity, Message };
	MessageList.Add( MessageEntry );
	OnMessageReceivedDelegate.Broadcast( MessageEntry );

	// Duplicate the message to the log file so it can be easily copied from there
	FMsg::Logf( __FILE__, __LINE__, LogAlpakit.GetCategoryName(), Verbosity, TEXT("[Package %s] %s"), *PluginName, *Message );
}

void FAlpakitInstance::HandleCancelButtonClicked()
{
	const TSharedPtr<FAlpakitInstance> SharedSelf = AsShared();
	AsyncTask( ENamedThreads::GameThread, [SharedSelf]()
	{
		if ( SharedSelf->InstanceState == EAlpakitInstanceState::Running )
		{
			SharedSelf->UATProcess->Cancel();
		}
	} );
}

void FAlpakitInstance::HandleDismissButtonClicked()
{
	const TSharedPtr<FAlpakitInstance> SharedSelf = AsShared();
	AsyncTask( ENamedThreads::GameThread, [SharedSelf]()
	{
		SharedSelf->DismissNotification();
	} );
}

void FAlpakitInstance::HandleOutputLogNavigate()
{
	const TSharedPtr<FAlpakitInstance> SharedSelf = AsShared();
	AsyncTask( ENamedThreads::GameThread, [SharedSelf]()
	{
		const TSharedPtr<SDockTab> AlpakitLogTab = FGlobalTabmanager::Get()->TryInvokeTab( FTabId( FAlpakitModule::AlpakitLogTabName ) );
		if ( AlpakitLogTab.IsValid() )
		{
			const TSharedRef<SAlpakitLogTabContent> TabContent = StaticCastSharedRef<SAlpakitLogTabContent>( AlpakitLogTab->GetContent() );
			TabContent->SetAlpakitInstance( SharedSelf );
		}
	} );
}

void FAlpakitInstance::SpawnNotification()
{
	check( IsInGameThread() );
	
	FNotificationInfo NotificationInfo{ FText::Format( LOCTEXT("PackageModTaskName", "Packaging Mod {0}..."), FText::FromString( PluginName ) ) };
	NotificationInfo.Image = FAlpakitStyle::Get().GetBrush("Alpakit.Icon");
	NotificationInfo.bFireAndForget = false;
	NotificationInfo.ExpireDuration = 10.0f;

	NotificationInfo.Hyperlink = FSimpleDelegate::CreateSP( AsShared(), &FAlpakitInstance::HandleOutputLogNavigate );
	NotificationInfo.HyperlinkText = LOCTEXT("ShowAlpakitLogHyperlink", "Show Alpakit Log");

	NotificationInfo.ButtonDetails.Add(
		FNotificationButtonInfo(
			LOCTEXT("NotificationTaskCancel", "Cancel"),
			LOCTEXT("UatTaskCancelToolTip", "Cancels execution of this task."),
			FSimpleDelegate::CreateSP( AsShared(), &FAlpakitInstance::HandleCancelButtonClicked ),
			SNotificationItem::CS_Pending
		)
	);
	NotificationInfo.ButtonDetails.Add(
		FNotificationButtonInfo(
			LOCTEXT("NotificationTaskDismiss", "Dismiss"),
			FText(),
			FSimpleDelegate::CreateSP( AsShared(), &FAlpakitInstance::HandleDismissButtonClicked ),
			SNotificationItem::CS_Fail
		)
	);
		
	NotificationItem = FSlateNotificationManager::Get().AddNotification( NotificationInfo );
	NotificationItem->SetCompletionState( SNotificationItem::CS_Pending );
	GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileStart_Cue.CompileStart_Cue"));
}

void FAlpakitInstance::DismissNotification()
{
	if ( NotificationItem.IsValid() )
	{
		NotificationItem->SetExpireDuration( 0.0f );
		NotificationItem->SetFadeOutDuration( 0.5f );
		NotificationItem->Fadeout();
		NotificationItem.Reset();
	}
}

void FAlpakitInstance::MarkNotificationAsSuccess( double Duration )
{
	if ( NotificationItem.IsValid() )
	{
		NotificationItem->SetText( FText::Format( LOCTEXT("PackageModTaskNameSuccess", "Packaged Mod {0}"), FText::FromString( PluginName ) ) );
		NotificationItem->SetSubText( FText::Format( LOCTEXT("PackageModResultSuccess", "Packaging finished in {0}s."), Duration ) );
		NotificationItem->SetCompletionState( SNotificationItem::CS_Success );
		NotificationItem->ExpireAndFadeout();
		NotificationItem.Reset();
	}

	GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileSuccess_Cue.CompileSuccess_Cue"));
}

void FAlpakitInstance::MarkNotificationAsFail( int32 ExitCode )
{
	if ( NotificationItem.IsValid() )
	{
		NotificationItem->SetText( FText::Format( LOCTEXT("PackageModTaskNameFail", "Failed To Package Mod {0}"), FText::FromString( PluginName ) ) );
		NotificationItem->SetSubText( FText::Format( LOCTEXT("PackageModResultFail", "Process Exited with ExitCode {0}, See Log for more details."), ExitCode ) );
		NotificationItem->SetCompletionState( SNotificationItem::CS_Fail );
		NotificationItem->ExpireAndFadeout();
		NotificationItem.Reset();
	}

	GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileFailed_Cue.CompileFailed_Cue"));
}

void FAlpakitInstance::MarkNotificationCancelled()
{
	if ( NotificationItem.IsValid() )
	{
		NotificationItem->SetText( FText::Format( LOCTEXT("PackageModTaskNameCancelled", "Packaging {0} Cancelled"), FText::FromString( PluginName ) ) );
		NotificationItem->SetSubText( LOCTEXT("PackageModResultCancel", "The packaging process was cancelled by the user.") );
		NotificationItem->SetCompletionState( SNotificationItem::CS_None );
		NotificationItem->ExpireAndFadeout();
		NotificationItem.Reset();
	}
}

void FAlpakitInstance::GetRunningInstances( TArray<TSharedPtr<FAlpakitInstance>>& OutRunningInstances )
{
	FScopeLock GlobalAlpakitInstanceListLock( &GlobalListCriticalSection );
	OutRunningInstances.Append( GlobalList );
}

void FAlpakitInstance::RegisterInGlobalList()
{
	FScopeLock GlobalAlpakitInstanceListLock( &GlobalListCriticalSection );

	if ( const TSharedPtr<FAlpakitInstance> SharedSelf = AsShared() )
	{
		GlobalList.AddUnique( SharedSelf );
		OnNewInstanceSpawned.Broadcast( SharedSelf );
	}
}

void FAlpakitInstance::RemoveFromGlobalList()
{
	FScopeLock GlobalAlpakitInstanceListLock( &GlobalListCriticalSection );
	GlobalList.Remove( AsShared() );
}

#undef LOCTEXT_NAMESPACE

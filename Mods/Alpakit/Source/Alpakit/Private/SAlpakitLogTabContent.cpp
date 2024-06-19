#include "SAlpakitLogTabContent.h"
#include "AlpakitInstance.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "Alpakit"

SAlpakitLogTabContent::~SAlpakitLogTabContent()
{
	if ( OnNewInstanceSpawnedHandle.IsValid() )
	{
		FAlpakitInstance::OnNewInstanceSpawned.Remove( OnNewInstanceSpawnedHandle );
		OnNewInstanceSpawnedHandle.Reset();
	}

	if ( OnInstanceMessageHandle.IsValid() && AlpakitInstance.IsValid() )
	{
		AlpakitInstance->OnMessageReceived().Remove( OnInstanceMessageHandle );
		OnInstanceMessageHandle.Reset();
	}
}

void SAlpakitLogTabContent::Construct( const FArguments& InArgs )
{
	ChildSlot[
	SNew( SVerticalBox )
		+SVerticalBox::Slot().HAlign( HAlign_Left ).Padding( 5.0f, 10.0f, 5.0f, 2.0f ).AutoHeight()
		[
			SNew( SHorizontalBox )
			+SHorizontalBox::Slot().AutoWidth()
			[
				SNew( STextBlock )
				.Font( FCoreStyle::GetDefaultFontStyle("Regular", 10 ) )
				.Text( LOCTEXT("LogPluginName", "Mod: ") )
			]
			+SHorizontalBox::Slot().AutoWidth()
			[
				SNew( STextBlock )
				.Font( FCoreStyle::GetDefaultFontStyle("Bold", 10 ) )
				.Text( this, &SAlpakitLogTabContent::GetPluginNameText )
			]
		]
		+SVerticalBox::Slot().HAlign( HAlign_Left ).Padding( 5.0f, 0.0f, 5.0f, 2.0f ).AutoHeight()
		[
			SNew( SHorizontalBox )
			+SHorizontalBox::Slot().AutoWidth()
			[
				SNew( STextBlock )
				.Font( FCoreStyle::GetDefaultFontStyle("Regular", 10 ) )
				.Text( LOCTEXT("LogStatusColumn", "Status: ") )
			]
			+SHorizontalBox::Slot().AutoWidth()
			[
				SNew( STextBlock )
				.Font( FCoreStyle::GetDefaultFontStyle("Bold", 10 ) )
				.ColorAndOpacity( this, &SAlpakitLogTabContent::GetStatusColor )
				.Text( this, &SAlpakitLogTabContent::GetStatusText )
			]
		]
		+SVerticalBox::Slot().HAlign( HAlign_Left ).Padding( 5.0f, 0.0f, 5.0f, 0.0f ).AutoHeight()
		[
			SNew( STextBlock )
			.TextStyle(FAppStyle::Get(), "SmallText")
			.Text( this, &SAlpakitLogTabContent::GetStatusDescription )
		]
		+SVerticalBox::Slot().HAlign( HAlign_Fill ).Padding( 5.0f, 5.0f, 5.0f, 0.0f ).FillHeight( 1.0f )
		[
			SNew( SBorder )
			.BorderImage( FAppStyle::GetBrush("ToolPanel.GroupBorder") )
			.Padding( 2.0f )
			[
				SAssignNew(MessageListView, SListView<TSharedPtr<FAlpakitInstanceMessageEntry>>)
					.HeaderRow
					(
						SNew(SHeaderRow)
						.Visibility(EVisibility::Collapsed)
						+ SHeaderRow::Column("Status")
						.DefaultLabel(LOCTEXT("TaskListOutputLogColumnHeader", "Output Log"))
					)
					.ListItemsSource(&MessageList)
					.OnGenerateRow(this, &SAlpakitLogTabContent::HandleMessageListViewGenerateRow)
					.ItemHeight(24.0)
					.SelectionMode(ESelectionMode::Multi)
					.AllowOverscroll(EAllowOverscroll::No)
					.ConsumeMouseWheel(EConsumeMouseWheel::Always)
			]
		]
		+SVerticalBox::Slot().AutoHeight().Padding( FMargin( 20.0f, 10.0f ) )
		[
			SNew( SHorizontalBox )
			+ SHorizontalBox::Slot().HAlign( HAlign_Center ).AutoWidth()
			[
				SNew(SButton)
				.ContentPadding(FMargin(6.0f, 2.0f))
				.IsEnabled_Lambda([this]{ return MessageListView->GetNumItemsSelected() > 0; })
				.Text(LOCTEXT("CopyButtonText", "Copy"))
				.ToolTipText(LOCTEXT("CopyButtonTooltip", "Copy the selected log messages to the clipboard"))
				.OnClicked(this, &SAlpakitLogTabContent::OnCopyLogButtonClicked)
			]

			+ SHorizontalBox::Slot().HAlign( HAlign_Center ).Padding(4.0f, 0.0f, 0.0f, 0.0f).AutoWidth()
			[
				SNew(SButton)
				.ContentPadding(FMargin(6.0f, 2.0f))
				.IsEnabled_Lambda([this]{ return !MessageList.IsEmpty(); })
				.Text(LOCTEXT("ClearButtonText", "Clear Log"))
				.ToolTipText(LOCTEXT("ClearButtonTooltip", "Clear the log window"))
				.OnClicked(this, &SAlpakitLogTabContent::OnClearLogButtonClicked)
			]

			+ SHorizontalBox::Slot().HAlign( HAlign_Center ).Padding(4.0f, 0.0f, 0.0f, 0.0f).AutoWidth()
			[
				SNew(SButton)
				.ContentPadding(FMargin(6.0f, 2.0f))
				.IsEnabled_Lambda([this]{ return !MessageList.IsEmpty(); })
				.Text(LOCTEXT("ExportButtonText", "Save Log..."))
				.ToolTipText(LOCTEXT("SaveButtonTooltip", "Save the entire log to a file"))
				.OnClicked(this, &SAlpakitLogTabContent::OnSaveLogButtonClicked)
			]

			+SHorizontalBox::Slot().FillWidth(1)
			
			+SHorizontalBox::Slot().HAlign( HAlign_Center ).Padding( 0.0f, 0.0f, 10.0f, 0.0f ).AutoWidth()
			[
				SNew( SButton )
				.Text( LOCTEXT("ButtonRetry", "Run Again") )
				.ToolTipText( LOCTEXT("ButtonRetryTooltip", "Retry the Packaging Task with the same Parameters.") )
				.IsEnabled( this, &SAlpakitLogTabContent::IsRetryButtonEnabled )
				.OnClicked( this, &SAlpakitLogTabContent::OnRetryButtonClicked )
			]
			+SHorizontalBox::Slot().HAlign( HAlign_Center ).AutoWidth()
			[
				SNew( SButton )
				.Text( LOCTEXT("ButtonCancel", "Cancel") )
				.ToolTipText( LOCTEXT("ButtonCancelTooltip", "Cancels the currently running Packaging Task.") )
				.IsEnabled( this, &SAlpakitLogTabContent::IsCancelButtonEnabled )
				.OnClicked( this, &SAlpakitLogTabContent::OnCancelButtonClicked )
			]
		]
	];

	const TWeakPtr<SAlpakitLogTabContent> WeakSelf = StaticCastWeakPtr<SAlpakitLogTabContent>( AsWeak() );
	FAlpakitInstance::OnNewInstanceSpawned.AddLambda( [WeakSelf]( TSharedPtr<FAlpakitInstance> NewInstance )
	{
		if ( const TSharedPtr<SAlpakitLogTabContent> SharedSelf = WeakSelf.Pin() )
		{
			SharedSelf->OnNewAlpakitInstanceSpawned( NewInstance );
		}
	} );
}

FReply SAlpakitLogTabContent::OnClearLogButtonClicked()
{
	MessageList.Reset();
	MessageListView->RequestListRefresh();
	return FReply::Handled();
}

FReply SAlpakitLogTabContent::OnCopyLogButtonClicked()
{
	TArray<TSharedPtr<FAlpakitInstanceMessageEntry>> SelectedItems = MessageListView->GetSelectedItems();

	if (SelectedItems.Num() > 0)
	{
		FString SelectedText;

		for( int32 Index = 0; Index < SelectedItems.Num(); ++Index )
		{
			SelectedText += SelectedItems[Index]->Message;
			SelectedText += LINE_TERMINATOR;
		}

		FPlatformApplicationMisc::ClipboardCopy( *SelectedText );
	}
	return FReply::Handled();
}

FReply SAlpakitLogTabContent::OnSaveLogButtonClicked()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();

	TArray<FString> Filenames;

	TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
	void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid()) ? ParentWindow->GetNativeWindow()->GetOSWindowHandle() : nullptr;

	FDateTime Timestamp = FDateTime::Now();
	if (AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::Completed)
		Timestamp = AlpakitInstance->GetEndTime();
	
	if (DesktopPlatform->SaveFileDialog(
		ParentWindowHandle,
		LOCTEXT("SaveLogDialogTitle", "Save Log As...").ToString(),
		LastLogFileSaveDirectory,
		FString::Printf(TEXT("Alpakit-%s-%s.log"), *AlpakitInstance->GetPluginName(), *Timestamp.ToString(TEXT("%Y-%m-%d-%H-%M-%S"))),
		TEXT("Log Files (*.log)|*.log"),
		EFileDialogFlags::None,
		Filenames))
	{
		if (Filenames.Num() > 0)
		{
			FString Filename = Filenames[0];

			// keep path as default for next time
			LastLogFileSaveDirectory = FPaths::GetPath(Filename);

			// add a file extension if none was provided
			if (FPaths::GetExtension(Filename).IsEmpty())
			{
				Filename += Filename + TEXT(".log");
			}

			// save file
			FArchive* LogFile = IFileManager::Get().CreateFileWriter(*Filename);

			if (LogFile != NULL)
			{
				for( int32 Index = 0; Index < MessageList.Num(); ++Index )
				{
					FString LogEntry = MessageList[Index]->Message + LINE_TERMINATOR;
					LogFile->Serialize(TCHAR_TO_ANSI(*LogEntry), LogEntry.Len());
				}

				LogFile->Close();

				delete LogFile;
			}
			else
			{
				FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("SaveLogDialogFileError", "Failed to open the specified file for saving!"));
			}
		}
	}
	
	return FReply::Handled();
}

FReply SAlpakitLogTabContent::OnCancelButtonClicked()
{
	if ( AlpakitInstance.IsValid() && AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::Running )
	{
		AlpakitInstance->Cancel();
	}
	return FReply::Handled();
}

FReply SAlpakitLogTabContent::OnRetryButtonClicked()
{
	if ( AlpakitInstance.IsValid() && AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::Completed )
	{
		ClearMessageList();
		AlpakitInstance->Start();
	}
	return FReply::Handled();
}

bool SAlpakitLogTabContent::IsCancelButtonEnabled() const
{
	return AlpakitInstance.IsValid() && AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::Running;
}

bool SAlpakitLogTabContent::IsRetryButtonEnabled() const
{
	return AlpakitInstance.IsValid() && AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::Completed;
}

FText SAlpakitLogTabContent::GetPluginNameText() const {
	if ( !AlpakitInstance.IsValid() || AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::None )
	{
		return LOCTEXT("PluginNameNA", "N/A");
	}
	return FText::FromString(AlpakitInstance->GetPluginName());
}

FText SAlpakitLogTabContent::GetStatusText() const
{
	if ( !AlpakitInstance.IsValid() || AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::None )
	{
		return LOCTEXT("StatusIdle", "Idle");
	}
	if ( AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::Completed )
	{
		const EAlpakitInstanceResult Result = AlpakitInstance->GetResult();

		FText ResultText;
		
		if ( Result == EAlpakitInstanceResult::Success )
		{
			ResultText = LOCTEXT("StatusCompleted", "Completed");
		}
		if ( Result == EAlpakitInstanceResult::Fail )
		{
			ResultText = LOCTEXT("StatusFailed", "Failed");
		}
		if ( Result == EAlpakitInstanceResult::Cancelled )
		{
			ResultText = LOCTEXT("StatusCancelled", "Cancelled By User");
		}

		FTimespan Delta = FDateTime::UtcNow() - AlpakitInstance->GetEndTime();
		
		return FText::Format(LOCTEXT("StatusAt", "{0} at {1} ({2} ago)"), ResultText, FText::AsDateTime(AlpakitInstance->GetEndTime()), FText::AsTimespan(Delta));
	}
	return LOCTEXT("StatusRunning", "Running...");
}

FSlateColor SAlpakitLogTabContent::GetStatusColor() const
{
	if ( !AlpakitInstance.IsValid() || AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::None )
	{
		return FSlateColor( FColor::White );
	}
	if ( AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::Completed )
	{
		const EAlpakitInstanceResult Result = AlpakitInstance->GetResult();
		return FSlateColor( Result == EAlpakitInstanceResult::Success ? FColor::Green : FColor::Red );
	}
	return FSlateColor( FColor::Yellow );
}

FText SAlpakitLogTabContent::GetStatusDescription() const
{
	if ( !AlpakitInstance.IsValid() || AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::None )
	{
		return LOCTEXT("StatusDescNone", "Start a new Package Action from Alpakit Menu to Continue.");
	}
	if ( AlpakitInstance->GetInstanceState() == EAlpakitInstanceState::Completed )
	{
		const EAlpakitInstanceResult Result = AlpakitInstance->GetResult();
		if ( Result == EAlpakitInstanceResult::Success )
		{
			return LOCTEXT("StatusDescCompleted", "The Packaging Action has been Completed successfully.");
		}
		if ( Result == EAlpakitInstanceResult::Fail )
		{
			return LOCTEXT("StatusDescFailed", "The Packaging Action has finished with an Error. See Output Log for details.");
		}
		if ( Result == EAlpakitInstanceResult::Cancelled )
		{
			return LOCTEXT("StatusDescCancelled", "The Packaging Action has been Cancelled.");
		}
	}
	return LOCTEXT("StatusDescRunning", "The Packaging Action is currently running.");
}

TSharedRef<ITableRow> SAlpakitLogTabContent::HandleMessageListViewGenerateRow( TSharedPtr<FAlpakitInstanceMessageEntry> Message, const TSharedRef<STableViewBase>& TableView ) const
{
	return SNew( STableRow<TSharedPtr<FAlpakitInstanceMessageEntry>>, TableView )
		.Content()[
			SNew( STextBlock )
			.TextStyle(FAppStyle::Get(), "SmallText")
			.ColorAndOpacity( VerbosityToColor( Message->Verbosity ) )
			.Text( FText::FromString( Message->Message ) )
		];
}

FColor SAlpakitLogTabContent::VerbosityToColor( ELogVerbosity::Type Verbosity )
{
	switch ( Verbosity )
	{
		case ELogVerbosity::Fatal:
		case ELogVerbosity::Error:
			return FColor::Red;
		case ELogVerbosity::Warning:
			return FColor::Yellow;
		default:
			return FColor::White;
	}
}

void SAlpakitLogTabContent::SetAlpakitInstance( const TSharedPtr<FAlpakitInstance>& NewInstance )
{
	if ( AlpakitInstance != NewInstance )
	{
		if ( AlpakitInstance.IsValid() )
		{
			AlpakitInstance->OnMessageReceived().Remove( OnInstanceMessageHandle );
			OnInstanceMessageHandle.Reset();
		}
		AlpakitInstance = NewInstance;
		UpdateMessageListFromInstance();
	}
}

void SAlpakitLogTabContent::OnNewAlpakitInstanceSpawned( const TSharedPtr<FAlpakitInstance>& NewInstance )
{
	if ( !AlpakitInstance.IsValid() || AlpakitInstance->GetInstanceState() != EAlpakitInstanceState::Running )
	{
		SetAlpakitInstance( NewInstance );
	}
}

void SAlpakitLogTabContent::OnAlpakitMessage( const FAlpakitInstanceMessageEntry& Message )
{
	MessageList.Add( MakeShared<FAlpakitInstanceMessageEntry>( Message ) );

	// only scroll when at the end of the listview
	bool bShouldScroll = !MessageListView->IsScrollbarNeeded() || FMath::IsNearlyEqual(MessageListView->GetScrollDistanceRemaining().Y, 0.0f, 1.e-7f);

	MessageListView->RequestListRefresh();

	if (bShouldScroll)
	{
		MessageListView->RequestScrollIntoView(MessageList.Last());
	}
}

void SAlpakitLogTabContent::ClearMessageList()
{
	MessageList.Empty();
	MessageListView->RequestListRefresh();
}

void SAlpakitLogTabContent::UpdateMessageListFromInstance()
{
	MessageList.Empty();
	if ( AlpakitInstance.IsValid() )
	{
		const TWeakPtr<SAlpakitLogTabContent> WeakSelf = StaticCastWeakPtr<SAlpakitLogTabContent>( AsWeak() );
		OnInstanceMessageHandle = AlpakitInstance->OnMessageReceived().AddLambda( [WeakSelf]( const FAlpakitInstanceMessageEntry& Message )
		{
			if ( const TSharedPtr<SAlpakitLogTabContent> SharedSelf = WeakSelf.Pin() )
			{
				SharedSelf->OnAlpakitMessage( Message );
			}
		} );

		for ( const FAlpakitInstanceMessageEntry& ExistingMessage : AlpakitInstance->GetMessageList() )
		{
			MessageList.Add( MakeShared<FAlpakitInstanceMessageEntry>( ExistingMessage ) );
		}
	}
	MessageListView->RequestListRefresh();
	if(MessageList.Num() > 0) {
		MessageListView->RequestScrollIntoView(MessageList.Last());
	}
}

#undef LOCTEXT_NAMESPACE

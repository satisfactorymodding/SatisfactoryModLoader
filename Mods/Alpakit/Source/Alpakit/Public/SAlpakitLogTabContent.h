#pragma once

#include "CoreMinimal.h"
#include "AlpakitInstance.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class FAlpakitInstance;

class ALPAKIT_API SAlpakitLogTabContent : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SAlpakitLogTabContent) {}
	SLATE_END_ARGS()

	virtual ~SAlpakitLogTabContent() override;
public:
	void Construct( const FArguments& InArgs );

	void SetAlpakitInstance( const TSharedPtr<FAlpakitInstance>& NewInstance );
protected:
	bool IsCancelButtonEnabled() const;
	bool IsRetryButtonEnabled() const;
	
	FReply OnCancelButtonClicked();
	FReply OnRetryButtonClicked();
	FReply OnClearLogButtonClicked();
	FReply OnCopyLogButtonClicked();
	FReply OnSaveLogButtonClicked();
	
	FText GetPluginNameText() const;
	FText GetStatusText() const;
	FSlateColor GetStatusColor() const;
	FText GetStatusDescription() const;

	void OnNewAlpakitInstanceSpawned( const TSharedPtr<FAlpakitInstance>& NewInstance );

	void OnAlpakitMessage( const FAlpakitInstanceMessageEntry& Message );
	TSharedRef<ITableRow> HandleMessageListViewGenerateRow( TSharedPtr<FAlpakitInstanceMessageEntry> Message, const TSharedRef< class STableViewBase >& TableView ) const;

	void ClearMessageList();
	void UpdateMessageListFromInstance();

	static FColor VerbosityToColor( ELogVerbosity::Type Verbosity );
	
	TArray<TSharedPtr<FAlpakitInstanceMessageEntry>> MessageList;
	TSharedPtr<FAlpakitInstance> AlpakitInstance;
	TSharedPtr<SListView<TSharedPtr<FAlpakitInstanceMessageEntry>>> MessageListView;

	FDelegateHandle OnInstanceMessageHandle;
	FDelegateHandle OnNewInstanceSpawnedHandle;
	
	FString LastLogFileSaveDirectory;
};

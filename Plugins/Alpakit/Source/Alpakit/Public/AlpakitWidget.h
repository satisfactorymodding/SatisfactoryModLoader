#pragma once

//Slate
#include "Slate.h"
#include "AlpakitSettings.h"
#include "IDetailsView.h"

class SAlpakaWidget : public SCompoundWidget
{
	//Slate Init
public:
	SLATE_BEGIN_ARGS(SAlpakaWidget) //, _bKeepVisible(false)
	{}


	SLATE_END_ARGS()
public:
	//Constructor
	void Construct(const FArguments& InArgs);

	//As Widget
	TSharedRef<class SWidget> AsWidget();

	//~~~ Tick ~~~ 
	//void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

public:
	// UI
	TSharedPtr<SButton> AlpakitButton;
	TSharedPtr<SButton> SaveSettingsButton;

	// Bindings
	UAlpakitSettings* Settings;

	/** The details view we do most of our work within */
	TSharedPtr<IDetailsView> DetailsView;

	// Functions
	FReply ChooseSatisfactoryFolder();
	bool OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames);
	bool OpenDirectoryDialog(const FString& DialogTitle, const FString& DefaultPath, FString& OutFileNames);
	FReply Pakit();

	void CookContent();
	void CookDone(FString result, double runtime);
};
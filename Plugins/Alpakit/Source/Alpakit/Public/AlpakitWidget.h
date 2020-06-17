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
	FReply Pakit();

	static void Alpakit(TFunction<void()> Done);
	static void CookContent(UAlpakitSettings* Settings, TFunction<void()> Done);
	static void CookDone(FString result, double runtime, UAlpakitSettings* Settings, TFunction<void()> Done);
};
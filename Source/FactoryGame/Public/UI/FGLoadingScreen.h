// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UnrealString.h"

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Animation/CurveSequence.h"
#include "UMG.h"
#include "Styling/ISlateStyle.h"

/**
 * Loading screen with support for a custom text.
 */
class FACTORYGAME_API SFGLoadingScreen : public SCompoundWidget
{
public:
	static void Initialize();
	static void Shutdown();

	static TSharedPtr< class ISlateStyle > Get();
	static FName GetStyleSetName();

	SLATE_BEGIN_ARGS( SFGLoadingScreen ) :
	_LoadingText( NSLOCTEXT( "LoadingScreen", "LoadingsScreenDefaultText", "Loading" ) )
	{}

	/** The loading text to display */
	SLATE_ARGUMENT( FText, LoadingText )

	SLATE_END_ARGS()

	void Construct( const FArguments& inArgs );
private:
	static FString InContent( const FString& relativePath, const ANSICHAR* extension );
private:
	/** Text to display when loading. */
	FText mLoadingText;

	static TSharedPtr< class FSlateStyleSet > StyleSet;

public:
	FORCEINLINE ~SFGLoadingScreen() = default;
};

/**
 * Loading Spinner
 */
class FACTORYGAME_API SFGSpinnerLoader : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SFGSpinnerLoader ) :
		_Background( SFGLoadingScreen::Get()->GetBrush( "LoadingScreen.SpinnerBackground" ) ),
		_Foreground( SFGLoadingScreen::Get()->GetBrush( "LoadingScreen.SpinnerForeground" ) ),
		_Period( 0.75f )
		{}

		/** What the static background looks like */
		SLATE_ARGUMENT( const FSlateBrush*, Background )
		/** What the spinning foreground looks like. */
		SLATE_ARGUMENT( const FSlateBrush*, Foreground )
		/** The amount of time in seconds for a full circle */
		SLATE_ARGUMENT( float, Period )

	SLATE_END_ARGS()

	/** Constructs the widget */
	void Construct( const FArguments& inArgs );

	/** Sets the amount of time in seconds for a full circle */
	void SetPeriod( float inPeriod );

	virtual int32 OnPaint( const FPaintArgs& args, const FGeometry& allottedGeometry, const FSlateRect& myCullingRect, FSlateWindowElementList& outDrawElements, int32 layerId, const FWidgetStyle& inWidgetStyle, bool isParentEnabled ) const override;
	virtual FVector2D ComputeDesiredSize(float) const override;
private:
	void ConstructSequence();
private:
	/** The sequence to drive the spinning animation */
	FCurveSequence mSequence;
	FCurveHandle mCurve;

	const FSlateBrush* mBackground;
	const FSlateBrush* mForeground;

	/** The amount of time in seconds for a full circle */
	float mPeriod;

public:
	FORCEINLINE ~SFGSpinnerLoader() = default;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Animation/CurveSequence.h"
#include "Styling/ISlateStyle.h"

/**
 * Loading screen with support for a custom text.
 */
class FACTORYPREEARLYLOADINGSCREEN_API SFGMinimalLoadingScreen : public SCompoundWidget
{
public:
	static void Initialize();
	static void Shutdown();

	static TSharedPtr< class ISlateStyle > Get();
	static FName GetStyleSetName();

	SLATE_BEGIN_ARGS( SFGMinimalLoadingScreen ) :
	_LoadingText( NSLOCTEXT( "LoadingScreen", "LoadingsScreenDefaultText", "" ) )
	{}

	/** The loading text to display */
	SLATE_ARGUMENT( FText, LoadingText )

	SLATE_END_ARGS()

	void Construct( const FArguments& inArgs );
	void SetLoadingText( FText inText );
	
private:
	TSharedPtr<class STextBlock> mLoadingTextBlock;
	static TSharedPtr< class FSlateStyleSet > StyleSet;
};

/**
 * Loading Spinner
 */
class SFGSpinnerLoader : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SFGSpinnerLoader ) :
		_Background( SFGMinimalLoadingScreen::Get()->GetBrush( "LoadingScreen.SpinnerBackground" ) ),
		_Foreground( SFGMinimalLoadingScreen::Get()->GetBrush( "LoadingScreen.SpinnerForeground" ) ),
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
	
	/** The sequence to drive the spinning animation */
	FCurveSequence mSequence;
	FCurveHandle mCurve;

	const FSlateBrush* mBackground = nullptr;
	const FSlateBrush* mForeground = nullptr;

	/** The amount of time in seconds for a full circle */
	float mPeriod = 0.f;
};

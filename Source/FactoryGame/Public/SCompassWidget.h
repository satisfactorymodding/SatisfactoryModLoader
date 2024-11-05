// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Animation/CurveSequence.h"
#include "Components/Widget.h"
#include "SCompassWidget.generated.h"

class AFGHUD;
struct FCompassEntry;

/**
 * Slate implementation for the compass widget. Shows compass entries retrieved from the HUD of the owning player
 */
UCLASS()
class FACTORYGAME_API UFGCompassWidget : public UWidget
{
	GENERATED_BODY()
public:
	UFGCompassWidget();

	// Begin UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End UWidget interface

	TArray<FCompassEntry>& GetCompassEntries();
	bool ShouldHideCompass() const;
private:
	AFGHUD* GetOwningHUD() const;
public:
	/** Anchor point for the compass markers, in widget's relative space. Normally (0.5, 0.5) for center */
	UPROPERTY( EditAnywhere, Category = "Compass Widget" )
	FVector2f CompassAnchorPoint;

	/** Width of the compass \"visibility" zone in which compass entries will be shown */
	UPROPERTY( EditAnywhere, Category = "Compass Widget" )
	float CompassWidth;

	UPROPERTY( EditAnywhere, Category="Compass Widget" )
	FSlateFontInfo FontInfo;
	
#if WITH_EDITORONLY_DATA
	/** Compass entries to use for previewing the widget */
	UPROPERTY( EditAnywhere, Category = "Compass Widget" )
	TArray<FCompassEntry> PreviewCompassEntries;
#endif
private:
	/** Fallback empty array to use when no HUD is available */
	TArray<FCompassEntry> EmptyCompassEntries;
};

class FACTORYGAME_API SCompassWidget : public SWidget
{
public:
	SLATE_BEGIN_ARGS( SCompassWidget ) : _AnchorPoint( FVector2f( 0.5f, 0.5f ) ), _CompassWidth( 800.0f ) {}
	SLATE_ARGUMENT(FVector2f, AnchorPoint);
	SLATE_ARGUMENT(float, CompassWidth);
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TWeakObjectPtr<UFGCompassWidget>& OwnerCompassWidget );

	// Begin SWidget interface
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;
	virtual FChildren* GetChildren() override;
	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;
	virtual bool SupportsKeyboardFocus() const override { return false; }
	virtual bool ComputeVolatility() const override { return false; }
	// End SWidget interface

	static void DrawEntry(const FVector2f& RootLocation, const FCompassEntry& Entry, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& LayerId);
	static void DrawEntrySpecialEffect(const FVector2f& RootLocation, const FCompassEntry& Entry, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& LayerId);
	static void UpdateEntryTextMetrics( FCompassEntry& Entry, const FSlateFontInfo& FontInfo );
	
protected:
	TWeakObjectPtr<UFGCompassWidget> mOwnerCompassWidget;
	FVector2f mCompassAnchorPoint{};
	float mCompassWidth{};
	FCurveSequence Anim;
	FSlateFontInfo mFont;
};

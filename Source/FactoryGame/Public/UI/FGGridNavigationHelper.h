// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGGridNavigationHelper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FFGNavigateBorderEvent, EUINavigation, Navigation, const FGeometry&, CurrentFocusGeometry );

UENUM()
enum class EFGGridNavigationStyle
{
	PreferLeastNavigationDistance, // prefer the least distance in navigation direction (go to the next row instead of skipping to a row that is long enough)
	PreferLeastPerpendicularDistance // prefer the least distance perpendicular to the navigation direction (skip rows if another widget is in the same row/column or closer)	
};

/**
 * Helper type for setting up a grid-like navigation between widgets.
 */
UCLASS()
class FACTORYGAME_API UFGGridNavigationHelper : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	/** Setup the navigation for the given widgets. Can be called multiple times to update the widgets. */
	UFUNCTION( BlueprintCallable )
	void SetupNavigation( const TArray<UWidget*>& widgets );

private:
	UFUNCTION( BlueprintCallable )
	UWidget* DoNavigation( EUINavigation NavigationDirection );

	UFUNCTION( BlueprintCallable )
	UWidget* FindNextGridWidget( UWidget* Pivot, EUINavigation NavigationDirection );

	UWidget* FindNextGridWidgetSlate( TSharedPtr<SWidget> slateWidget, EUINavigation NavigationDirection );

	void HandleSlateFocusChanging(const FFocusEvent& FocusEvent, const FWeakWidgetPath& OldFocusedWidgetPath, const TSharedPtr<SWidget>& OldFocusedWidget, const FWidgetPath& NewFocusedWidgetPath, const TSharedPtr<SWidget>& NewFocusedWidget);

public:
	/** Store the column when navigating up/down when passing shorter rows. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	bool mKeepColumn = false;

	/** Triggered when the user navigates past all of the widgets. */
	UPROPERTY( BlueprintAssignable )
	FFGNavigateBorderEvent mOnNavigateBorder;

	UPROPERTY( EditAnywhere )
	EFGGridNavigationStyle mVerticalNavigationStyle = EFGGridNavigationStyle::PreferLeastNavigationDistance;

	UPROPERTY( EditAnywhere )
	EFGGridNavigationStyle mHorizontalNavigationStyle = EFGGridNavigationStyle::PreferLeastPerpendicularDistance;

private:
	TStaticArray<float, 3> GetDistances( TSharedPtr<SWidget> FromWidget, TSharedPtr<SWidget> ToWidget, EUINavigation NavigationDirection );

	TArray< UWidget* > mAllWidgets;

	double mActiveColumn = -1.0;
};

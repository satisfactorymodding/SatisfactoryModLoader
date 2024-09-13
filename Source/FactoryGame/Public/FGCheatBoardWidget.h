//Copyright 2016 Coffee Stain Studios.All Rights Reserved.

#pragma once

#include "FGCheatManager.h"
#include "Widgets/SCompoundWidget.h"
#include "FactoryGame.h"
#include "FGCheatBoardMenuElements.h"

DECLARE_MULTICAST_DELEGATE_TwoParams( FFGCheatBoardGetCheatObjects, UFGCheatManager* /** CheatManager */, TArray<UObject*>& /** OutCheatObjects */ );

class FACTORYGAME_API SFGCheatBoardWidget : public SCompoundWidget, public FGCObject
{
	/** Cache the cheat manager */
	SLATE_BEGIN_ARGS( SFGCheatBoardWidget ) {}
	SLATE_ARGUMENT( TObjectPtr<UFGCheatManager>, mOwnerCheatManager )
	SLATE_END_ARGS()
public:
	/** Called when initializing cheat menu to collect additional objects willing to be represented in the cheat board */
	static FFGCheatBoardGetCheatObjects GetCheatObjects;
	
	/** Constructs the base Slate UI */
	void Construct( const FArguments& InArgs );

	/** Shut it down */
	void CloseCheatBoard();

	// Begin SCompoundWidget interface
	virtual FReply OnKeyDown( const FGeometry& myGeometry, const FKeyEvent& inKeyEvent );
	virtual bool SupportsKeyboardFocus() const;
	virtual FReply OnFocusReceived( const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent ) override;
	// End SCompoundWidget interface

	// Begin FGCObject interface
	virtual FString GetReferencerName() const override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End FGCObject interface
public:
	static FCheatBoardParamSelectionData GetRootCheatMenuSelectionData();
	static void SetRootCheatMenuSelectionData( const FCheatBoardParamSelectionData& NewSelectionData );
	
	/** Combines GotoNextParameterProperty and ShowInputWindowForProperty */
	void ShowInputWindowForNextCheatParameter();
	
	/** Shows the input window for a specific property type */
	void ShowInputWindowForProperty( FProperty* Property, const FCheatBoardParamSelectionData& CurrentSelectionData );

	/** Prompts the user with true and false inputs */
	void ShowInputWindowForBoolProperty( const FCheatBoardParamSelectionData& CurrentSelectionData );

	/** Prompts the user with the number input field */
	void ShowInputWindowForNumber( const FCheatBoardParamSelectionData& CurrentSelectionData );

	TSharedPtr<IFGCheatBoardParameterFilter> ResolveGlobalParameterFilterForClass( const UClass* ClassType ) const;
	TSharedPtr<IFGCheatBoardParameterFilter> ResolveGlobalParameterFilterForAsset( const UClass* AssetType ) const;
	
	/** Prompts the user to input a class */
	void ShowInputForClass( const UClass* SuperClass, TSharedPtr<IFGCheatBoardParameterFilter> ParameterFilter, const FCheatBoardParamSelectionData& CurrentSelectionData );

	/** Prompts the user to pick an asset of the given class from the asset registry */
	void ShowInputForAsset( const UClass* AssetClass, TSharedPtr<IFGCheatBoardParameterFilter> ParameterFilter, const FCheatBoardParamSelectionData& CurrentSelectionData );

	/** Prompts the user to input a text (FString, FText or FName) */
	void ShowInputWindowForText( const FProperty* Property, const FCheatBoardParamSelectionData& CurrentSelectionData );

	/** Prompts the user to select an enum value */
	void ShowInputWindowForEnum( const UEnum* Enum, const FCheatBoardParamSelectionData& CurrentSelectionData );

	void ResetMenu();
	void ShowMenu( const TSharedPtr<FCheatMenuCategory>& InMenu, const FString& InMenuTitle, const FCheatBoardParamSelectionData& CurrentSelectionData );

	/** When we click on a cheat in the list this get triggered */
	FReply OnCheatClicked( TSharedRef<FCheatMenuElement> Cheat );
	/** Called when the players commits text in the input window */
	void OnInputTextCommitted( const FText& InText, ETextCommit::Type InCommitType );
	FReply OnInputFilterKeyDown( const FGeometry& Geometry, const FKeyEvent& KeyEvent );

	void OnInputFilterChanged( const FText& InText );
	/** Called when the players commits text in the input window */
	void OnInputFilterCommitted( const FText& InText, ETextCommit::Type InCommitType );

	FReply OnClearFilter();

	/** Applies filter string to the current tree widget to filter out the unwanted results */
	void ApplyFilterWithFilterString( bool bAutoSelectFirstElement );

	/** Creates the value picker widget for the bool parameter */
	TSharedRef<SWidget> CreateWidgetForBoolParamProperty( const FCheatMenuParam& CheatMenuParam );
	/** If the user presses on true or false, this triggers and gives us the value */
	FReply OnBoolParamPicked( bool bValue );
	/** Creates the value picker for the object property param */
	TSharedRef<SWidget> CreateWidgetForObjectParamProperty( const FCheatMenuParam& CheatMenuParam );
	/** If the user presses on a resource, this triggers and gives us the value */
	FReply OnObjectParamPicked( TObjectPtr<UObject> InObject );
	/** Creates the value picker for the number (or enum) based property param */
	TSharedRef<SWidget> CreateWidgetForNumberParamProperty( const FCheatMenuParam& CheatMenuParam );
	/** If the user presses on true or false, this triggers and gives us the value */
	FReply OnNumberParamPicked( int64 NumberValue );
	/** Creates widget for a simple text param property */
	TSharedPtr<SWidget> CreateWidgetForTextParamProperty( const FCheatMenuParam& CheatMenuParam ) const;

	/** Creates a widget for the toggle cheat object */
	TSharedPtr<SWidget> CreateWidgetForToggleCheat( TSharedRef<FCheatMenuCheatToggle> CheatToggle );
	/** Creates a widget for the exec cheat object */
	TSharedPtr<SWidget> CreateWidgetForExecCheat( TSharedRef<FCheatMenuObject> CheatObject );
	/** Creates a widget for the cheat parameter */
	TSharedPtr<SWidget> CreateWidgetForParameterSelection( TSharedRef<FCheatMenuParam> CheatParam );

	/** Get the next parameter for the currently active cheat */
	FProperty* GotoNextParameterProperty( FCheatBoardParamSelectionData& OutLastSelectionData );

	/** Changes the user focus to be on the Button Slot content */
	void SetFocusOnButtonSlot() const;
	/** Changes the user focus to be on the Filter Text Box */
	void SetFocusOnFilterTextBox() const;
private:
	/** Our owner cheat manager */
	TObjectPtr<UFGCheatManager> mOwnerCheatManager;

	/** Cached slot for the list of cheat buttons */
	SVerticalBox::FSlot* mCheatButtonSlot{nullptr};

	/** Cached slot for the possible input buttons */
	SOverlay::FOverlaySlot* mInputSlot{nullptr};
	SVerticalBox::FSlot* mTileTextSlot{nullptr};
	TSharedPtr<STextBlock> mTitleTextBox;

	SVerticalBox::FSlot* mFilterTextSlot{nullptr};
	TSharedPtr<SEditableTextBox> mFilterTextBox;
	TSharedPtr<SButton> mFilterClearButton;

	/** Top level cheat menu */
	TSharedPtr<FCheatMenuCategory> mRootCheatMenu;
	/** Cheat menu that is currently active */
	TSharedPtr<FCheatMenuCategory> mActiveCheatMenu;
	/** Item source array for the currently active menu */
	TArray<TSharedPtr<FCheatMenuElement>> mActiveCheatMenuItemSource;
	/** Fallback parameter filters */
	TMap<UClass*, FFGCheatBoardParameterFilter> mGlobalClassParameterFilters;
	/** Fallback parameter filters for assets */
	TMap<UClass*, FFGCheatBoardParameterFilter> mGlobalAssetParameterFilters;

	/** The parameters that should be processed by the function */
	TSharedPtr<FCheatMenuObject> mCurrentCheat;
	/** Current parameter we are inputting for the current cheat */
	FProperty* mCurrentCheatParameter{nullptr};

	/** This is the property we asked for input about */
	FProperty* mPropertyWaitingForInput{nullptr};

	/** The text style used in this widget */
	TUniquePtr<FTextBlockStyle> mButtonTextStyle;
	TUniquePtr<FTextBlockStyle> mButtonToggleTextStyle;
	TUniquePtr<FTextBlockStyle> mCategoryTextStyle;
	TUniquePtr<FButtonStyle> mCheatButtonStyle;
	TUniquePtr<FTableRowStyle> mCheatRowStyle;

	/** The text style in the box where the user inputs shit */
	TUniquePtr<FEditableTextBoxStyle> mEditableTextStyle{nullptr};

	TSharedPtr<SCheatTreeView> mTreeMenu;
	
	/** Called to generate a widget for the specified tree item */
	TSharedRef<ITableRow> CheatMenu_OnGenerateRow( TSharedPtr<FCheatMenuElement> Item, const TSharedRef<STableViewBase>& OwnerTable );

	/** Given a tree item, fills an array of child items */
	void CheatMenu_OnGetChildren( TSharedPtr<FCheatMenuElement> Item, TArray<TSharedPtr<FCheatMenuElement>>& OutChildren );
	void CheatMenu_OnMouseClick( TSharedPtr<FCheatMenuElement> Item );

	/** Populates the cheat menu from the cached cheat manager */
	void PopulateCheatMenu();
	void PopulateCheatMenuFromObject( UObject* Object, TArray<TSharedPtr<FCheatMenuElement>>& AllCheatMenuElements, TMap<TSharedPtr<FCheatMenuElement>, FString>& CheatMenuCategories );
};

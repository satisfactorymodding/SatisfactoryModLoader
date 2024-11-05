// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Templates/SharedPointer.h"
#include "UObject/StructOnScope.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Views/STreeView.h"

struct FCheatMenuCategory;
class SCheatTreeView;
class IFGCheatBoardParameterFilter;
struct FFGCheatBoardParameterFilter;
struct FCheatBoardParamSelectionData;
class UFGCheatManager;

/** Base class for cheat menu elements */
struct FACTORYGAME_API FCheatMenuElement : TSharedFromThis<FCheatMenuElement>
{
	enum class EItemType : uint8
	{
		ET_None,
		ET_Category,
		ET_CheatToggle,
		ET_CheatObject,
		ET_ParameterSelection,
	};

	explicit FCheatMenuElement( const TSharedPtr<FCheatMenuCategory> InParentCategory, const FString& InDisplayName );
	virtual ~FCheatMenuElement() = default;

	// Begin FCheatMenuElement interface
	virtual EItemType GetType() const = 0;
	virtual void AddReferencedObjects( FReferenceCollector& ReferenceCollector ) {};
	virtual void ForEachElement( TFunctionRef<void(const TSharedPtr<FCheatMenuElement>& Element)> Functor, bool bRecursive = true );
	virtual int16 GetSortValue() const;
	virtual bool IsMatchingSearchString( const FString& InSearchString ) const;
	virtual void FilterElementRecursive( const FString& InSearchString );
	virtual void SortRecursive();
	virtual TSharedPtr<FCheatMenuElement> GetFirstNonFilteredSubItem();
	virtual void ExpandElementRecursive( TSharedPtr<SCheatTreeView> TreeView );
	// End FCheatMenuElement interface

	/** Requests this item to be expanded and visible inside of the tree view. Will automatically expand it's parents until it reaches the tree's root. */
	void RequestItemExpansion( TSharedPtr<SCheatTreeView> TreeView ) const;

	/** Finds the given element in this element sub-tree, possibly, recursively */
	TSharedPtr<FCheatMenuElement> FindElement( const FString& InDisplayName, bool bRecursive = true );

	static bool LenientStringMatch(const FString& MyStr, const FString& InSearchString );

	bool operator>( const FCheatMenuElement& b ) const;
	bool operator<( const FCheatMenuElement& b ) const;
	bool operator==( const FString& InDisplayName ) const;

	FString DisplayName;
	TWeakPtr<FCheatMenuCategory> Parent;
	int16 SortBaseValue = 0;
	/** True if this element is currently filtered out and should not be visible */
	bool IsFiltered = false;
};

struct FACTORYGAME_API FCheatMenuParam : FCheatMenuElement
{
	explicit FCheatMenuParam( const TSharedPtr<FCheatMenuCategory> InParentCategory, const FString& InDisplayName );
	FCheatMenuParam( const TSharedPtr<FCheatMenuCategory> InParentCategory, const FString& InDisplayName, UObject* InObjectValue );
	FCheatMenuParam( const TSharedPtr<FCheatMenuCategory> InParentCategory, const FString& InDisplayName, bool bInBoolValue );
	FCheatMenuParam( const TSharedPtr<FCheatMenuCategory> InParentCategory, const FString& InDisplayName, int64 InIntegerValue );

	// Begin FCheatMenuElement interface
	virtual EItemType GetType() const override;
	virtual void AddReferencedObjects(FReferenceCollector& ReferenceCollector) override;
	// End FCheatMenuElement interface

	//we don't need support for all types, just the ones we want to have in a menu with our full menu logics, like when picking in big lists
	enum class EParamType : uint8
	{
		PT_None,
		PT_Bool,
		PT_Number,
		PT_Obj,
		PT_Str,
	};
	EParamType ParamType;

	bool bBoolVal{false};
	int64 NumberValue{0};
	TObjectPtr<UObject> ObjectPtr{nullptr};
};

struct FACTORYGAME_API FCheatMenuCategory : FCheatMenuElement
{
	FCheatMenuCategory( const TSharedPtr<FCheatMenuCategory>& InParentCategory, const FString& InCategoryName );

	// Begin FCheatMenuElement interface
	virtual EItemType GetType() const override;
	virtual void AddReferencedObjects(FReferenceCollector& ReferenceCollector) override;
	virtual int16 GetSortValue() const override;
	virtual void ForEachElement(TFunctionRef<void(const TSharedPtr<FCheatMenuElement>& Element)> Functor, bool bRecursive) override;
	virtual void FilterElementRecursive(const FString& InSearchString) override;
	virtual void SortRecursive() override;
	virtual TSharedPtr<FCheatMenuElement> GetFirstNonFilteredSubItem() override;
	virtual void ExpandElementRecursive(TSharedPtr<SCheatTreeView> TreeView) override;
	// End FCheatMenuElement interface

	TArray<TSharedPtr<FCheatMenuElement>> SubElements;

	/** Finds a category that is a direct children of this element */
	TSharedPtr<FCheatMenuCategory> FindCategory( const FString& CategoryName ) const;
};

/** Cheat menu element for toggle-able cheats */
struct FACTORYGAME_API FCheatMenuCheatToggle : FCheatMenuElement
{
	FCheatMenuCheatToggle( const TSharedPtr<FCheatMenuCategory> InParentCategory, UFunction* InSetterFunction, UFunction* InGetterFunction, UObject* InCheatManagerObject );

	// Begin FCheatMenuFunction interface
	virtual EItemType GetType() const override;
	virtual void AddReferencedObjects(FReferenceCollector& ReferenceCollector) override;
	// End FCheatMenuFunction interface

	bool GetCheatToggleState() const;
	void SetCheatToggleState( bool bNewState ) const;

	FText GetStateText() const;
	FSlateColor GetStateTextColor() const;

	/** Function to read value of the toggle cheat */
	TObjectPtr<UFunction> SetterFunction;
	TObjectPtr<UFunction> GetterFunction;
	/** Cheat manager object that should be used to run this function */
	TObjectPtr<UObject> CheatManager;
};

/** Cheat menu element for function-like cheats */
struct FACTORYGAME_API FCheatMenuObject : FCheatMenuElement
{
	FCheatMenuObject( const TSharedPtr<FCheatMenuCategory> InParentCategory, UFunction* InCheatFunction, UObject* InCheatManagerObject );

	// Begin FCheatMenuFunction interface
	virtual EItemType GetType() const override;
	virtual void AddReferencedObjects(FReferenceCollector& ReferenceCollector) override;
	// End FCheatMenuFunction interface

	void ExecuteCheat();	

	/** The function that should be executed for this cheat */
	TObjectPtr<UFunction> CheatFunction;
	/** Stored so we can remember our values till next time */
	FStructOnScope ParamBuffer;
	/** Cheat manager object that should be used to run this function */
	TObjectPtr<UObject> CheatManager;
	/** Maps parameter names to filters for them */
	TObjectPtr<UFunction> ParamFilterFunction;

	FCheatBoardParamSelectionData GetParamSelectionData( FName InParamName ) const;
	void SetParamSelectionData( FName InParamName, const FCheatBoardParamSelectionData& InSelectionData ) const;
	TSharedPtr<IFGCheatBoardParameterFilter> GetParameterFilter( FName InParamName, TSharedPtr<IFGCheatBoardParameterFilter> InFallbackFilter ) const;
};

/** Tree view for the cheat elements */
class FACTORYGAME_API SCheatTreeView : public STreeView<TSharedPtr<FCheatMenuElement>>
{
public:
	// Begin STreeView interface
	virtual FReply OnPreviewKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;
	// End STreeView interface

	TSharedPtr<SEditableTextBox> mFilterTextBox;
	SVerticalBox::FSlot* mFilterTextSlot;
	class SFGCheatBoardWidget* mOwningBoard;
};

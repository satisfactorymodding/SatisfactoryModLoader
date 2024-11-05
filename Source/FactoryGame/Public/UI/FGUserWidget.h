// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Templates/SharedPointer.h"
#include "Components/Widget.h"
#include "Engine/Blueprint.h"
#include "FGWidgetChild.h"
#include "GameplayTagContainer.h"
#include "FGUserWidget.generated.h"

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogUI, Log, All);

UENUM(BlueprintType)
enum class EFGKeyHintDelegateType : uint8
{
	Preview,
	KeyDown,
	KeyUp,
	Details
};

UENUM( BlueprintType )
enum class EFGKeyHintVariant : uint8
{
	Default,
	Hold,
	LongPress
};

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EKeybindingEvaluationMethod : uint8
{
	/** Use the preview OnKeyDown event instead of the regular one. Required for using navigation buttons, but may also break things. */
	UsePreviewEvent = 1 << 0,
	/** Check for visibility of FocusWidget instead of inclusion in Focus Path. */
	UseFocusWidgetVisibility = 1 << 1,
	AllowKeyRepeat = 1 << 2,
};
ENUM_CLASS_FLAGS(EKeybindingEvaluationMethod)

USTRUCT( BlueprintType ) 
struct FFGKeybinding // this has a details customization in FGKeybindingDetails.cpp
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere )
	FKey Key;

	// if set, this key must be pressed simulataneously with the key above for the action to trigger.
	UPROPERTY( EditAnywhere )
	FKey ComboKey;

	UPROPERTY( EditAnywhere )
	EFGKeyHintVariant Variant = EFGKeyHintVariant::Default;

	UPROPERTY( EditAnywhere )
	FText HintText;

	UPROPERTY( EditAnywhere )
	FName HintTag;

	// <FL>[KonradA] Make an override tag accessible for the keybindings menu as well
	UPROPERTY( EditAnywhere )
	FGameplayTag OverrideHintImageTag;
	// </FL>

	// if set, this widget must be in the focus path (or visible if EvaluationMethod is UseFocusWidgetVisibility) for the keybinding to be active.
	UPROPERTY(EditAnywhere)
	FFGWidgetChild FocusWidget;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = EKeybindingEvaluationMethod))
	int32 EvaluationMethod;

	// KeyDownCallback
	UPROPERTY( EditAnywhere )
	FName Callback;

	UPROPERTY( EditAnywhere )
	FName OnKeyUpCallback;

	UPROPERTY( EditAnywhere )
	FName DetailsCallback;

	bool operator==(const FFGKeybinding& Rhs) const
	{
		if (Key                 != Rhs.Key)                 return false;
		if (ComboKey            != Rhs.ComboKey)            return false;
		if (Variant             != Rhs.Variant)             return false;
		if (HintTag             != Rhs.HintTag)             return false;
		if (EvaluationMethod    != Rhs.EvaluationMethod)    return false;
		if (Callback            != Rhs.Callback)            return false;
		if (OnKeyUpCallback     != Rhs.OnKeyUpCallback)     return false;
		if (DetailsCallback     != Rhs.DetailsCallback)     return false;
		if (HintText.ToString() != Rhs.HintText.ToString()) return false;
		return true;
	}
};

USTRUCT( BlueprintType )
struct FFGKeyHint
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite )
	FKey Key;

	UPROPERTY( BlueprintReadWrite )
	FKey ComboKey;

	UPROPERTY( BlueprintReadWrite )
	FText HintText;

	UPROPERTY( BlueprintReadWrite )
	EFGKeyHintVariant Variant = EFGKeyHintVariant::Default;

	UPROPERTY( BlueprintReadWrite )
	FGameplayTag OverrideHintTag;
};

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EFocusHighlightMethod : uint8
{
	// Collapse HighlightWidget if FocusWidget not in focus path.
	SetVisibility       = 1 << 0, 
	// Set color and opacity of HighlightWidget if FocusWidget not in focus path. HighlightWidget must be a UUserWidget.
	SetColorAndOpacity  = 1 << 1,
	// Set border color of HighlightWidget if FocusWidget not in focus path. HighlightWidget must be of type UBorder.
	SetBorderColor      = 1 << 2,
	// Set text color of Highlight Widget if FocusWidget not in focus path. HighlightWidget must be of type UTextBlock.
	SetTextColor        = 1 << 3,

};
ENUM_CLASS_FLAGS(EFocusHighlightMethod)

USTRUCT(BlueprintType)
struct FFGFocusHighlight
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FFGWidgetChild FocusWidget;

	UPROPERTY(EditAnywhere)
	FFGWidgetChild HighlightWidget;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "/Script/FactoryGame.EFocusHighlightMethod"))
	int32 HighlightMethod;
};

DECLARE_DYNAMIC_DELEGATE_RetVal(FEventReply, FFGKeyHintDelegate);
DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam( bool, FFGOnKeyBindingDetails, UPARAM( ref ) FFGKeyHint&, KeyBinding );

UCLASS()
class FACTORYGAME_API UFGUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	//~ Begin UUSerWidget Interface
	virtual void NativeConstruct() override;
	virtual FReply NativeOnPreviewKeyDown( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent ) override;
	virtual FReply NativeOnKeyDown( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent ) override;
	virtual FReply NativeOnKeyUp( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent ) override;

	virtual void NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override;
	void HandleFocusChange(const FWeakWidgetPath& OldFocusPath, const FWidgetPath& NewFocusPath, const FFocusEvent& InFocusEvent);

#if WITH_EDITOR
	virtual void ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree, class IWidgetCompilerLog& CompileLog) const override;
#endif
	//~ End UUSerWidget Interface

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Input" )
	void GetKeyHints( FName hintTag, TArray<FFGKeyHint>& out_keyHints );

	virtual void GetKeyHints_Implementation( FName hintTag, TArray<FFGKeyHint>& out_keyHints );

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TArray< FFGKeybinding > Keybindings;

	UPROPERTY( EditDefaultsOnly, Category = "Input")
	bool bUseParentKeybindings = false;

	UPROPERTY( EditInstanceOnly, Category = "Input" )
	bool bIgnoreDefaultKeybindings = false;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TArray< FFGFocusHighlight > FocusHighlights;

	/** WIP: Widget is a popup window. Stop outgoing navigation and stop any input from propagating up. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	bool bIsPopup = false;

	UWidgetTree* GetWidgetTree(UWidget* Widget);

	UFUNCTION( BlueprintPure, Category = "Input" )
	static float GetLongPressSeconds();

	static UFGUserWidget* FromSlateWidget(SWidget& SlateWidget);

	static bool PreprocessKeyDownEvent(const FKeyEvent& InKeyEvent);
	static bool PreprocessKeyUpEvent(UWorld* World, const FKeyEvent& InKeyEvent);

private:

	FReply CallDelegateForKeyEventOfType(const FKeyEvent& InKeyEvent, EFGKeyHintDelegateType DelegateType);
	FReply CallKeybindingDelegate(const FFGKeybinding& Keybinding, EFGKeyHintDelegateType DelegateType);
	void BeginLongPress(const FFGKeybinding& Keybinding);

	TArray< FFGKeybinding > AllKeybindings;
};

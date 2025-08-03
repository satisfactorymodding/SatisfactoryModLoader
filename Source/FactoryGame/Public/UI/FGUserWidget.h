// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "Engine/Blueprint.h"
#include "FGWidgetChild.h"
#include "GameplayTagContainer.h"
#include "FGUserWidget.generated.h"

class UInputAction;

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogUI, Log, All);

UENUM(BlueprintType)
enum class EFGKeyHintDelegateType : uint8
{
	Preview,
	KeyDown,
	KeyUp,
	BeginLongPressDown,
	Details
};

UENUM( BlueprintType )
enum class EFGKeyHintVariant : uint8
{
	Default,
	Hold,
	LongPress,
	VeryLongPress
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
	int32 EvaluationMethod = 0;

	// KeyDownCallback
	UPROPERTY( EditAnywhere )
	FName Callback;

	UPROPERTY( EditAnywhere )
	FName OnKeyUpCallback;

	UPROPERTY( EditAnywhere )
	FName DetailsCallback;

	UPROPERTY( EditAnywhere )
	FName OnLongPressKeyDownCallback;

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
		if (OnLongPressKeyDownCallback     != Rhs.OnLongPressKeyDownCallback)     return false;
		if (HintText.ToString() != Rhs.HintText.ToString()) return false;
		return true;
	}

	UFGUserWidget* DelegateWidget = nullptr; // the widget that added it's keybindings via AddChildKeybindings, needed for callback resolution.
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
	FName HintTag;

	UPROPERTY( BlueprintReadWrite )
	EFGKeyHintVariant Variant = EFGKeyHintVariant::Default;

	UPROPERTY( BlueprintReadWrite )
	FGameplayTag OverrideHintTag;

	UPROPERTY( BlueprintReadWrite )
	float LongPressSeconds = -1.f;

	UPROPERTY( BlueprintReadWrite )
	bool Disabled = false;

	UPROPERTY( BlueprintReadOnly )
	TObjectPtr<UInputAction> ButtonHintAction;
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
	// Set brush color of Highlight Widget if FocusWidget not in focus path. HighlightWidget must be of type UImage.
	SetImageBrushColor        = 1 << 4,

};
ENUM_CLASS_FLAGS(EFocusHighlightMethod)

USTRUCT(BlueprintType)
struct FFGFocusHighlight
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFGWidgetChild FocusWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFGWidgetChild HighlightWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "/Script/FactoryGame.EFocusHighlightMethod"))
	int32 HighlightMethod = INDEX_NONE;

	FLinearColor DefaultColor =  FLinearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	//<FL>[KonradA] List of Additional Widgets that can affect this highlight's state.
	// implemented as additional list to not break existing implementation/blueprint references
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray< FFGWidgetChild > AdditionalWidgetsToConsiderForFocus;
};

DECLARE_DYNAMIC_DELEGATE_RetVal(FEventReply, FFGKeyHintDelegate);
DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam( bool, FFGOnKeyBindingDetails, UPARAM( ref ) FFGKeyHint&, KeyBinding );

UCLASS()
class FACTORYGAME_API UFGBaseWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Input")
	void OnInputDeviceTypeChanged(EInputDeviceType deviceType);
	virtual void OnInputDeviceTypeChanged_Implementation(EInputDeviceType deviceType) {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Input")
	void OnGlobalFocusChanged();
	virtual void OnGlobalFocusChanged_Implementation() {}

	// if set to true, the widget will receive OnGlobalFocusChanged events
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
	bool bGlobalFocusChangedEvents = false;
};

UCLASS()
class FACTORYGAME_API UFGUserWidget : public UFGBaseWidget
{
	GENERATED_BODY()
public:

	//~ Begin UUSerWidget Interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

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
	void GetKeyHints( TArray<FFGKeyHint>& out_keyHints );

	virtual void GetKeyHints_Implementation( TArray<FFGKeyHint>& out_keyHints );

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TArray< FFGKeybinding > Keybindings;

	UPROPERTY( EditDefaultsOnly, Category = "Input")
	bool bUseParentKeybindings = false;

	UPROPERTY( EditInstanceOnly, Category = "Input" )
	bool bIgnoreDefaultKeybindings = false;

	UPROPERTY(EditAnywhere, Category = "Input",meta= ( ToolTip= "When having a combokey, repeat events of the main key that are not explicitly consumed will be consumed automatically." ) )
	bool bAutoConsumeRepeatEventsWithComboKey = false;

	// <FL> [KonradA]
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Input", meta= ( ToolTip= "Some widgets might want to not process highlights under certain circumstances, e.g. when keyboard controls are enabled" ) )
	bool bSuspendFocusHighlights = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input",meta= ( ToolTip= "Some widgets might want to use directional dpad input while having LT/RT pressed for unrelated reasons but not break out as a combo key." ) )
	bool bEvaluateDPadEventsWithInvalidComboKey = false;
	//</FL>

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TArray< FFGFocusHighlight > FocusHighlights;

	/** WIP: Widget is a popup window. Stop outgoing navigation and stop any input from propagating up. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	bool bIsPopup = false;

	UWidgetTree* GetWidgetTree(UWidget* Widget);

	UFUNCTION( BlueprintPure, Category = "Input" )
	static float GetLongPressSeconds( const EFGKeyHintVariant& KeyVariant );

	static UFGUserWidget* FromSlateWidget(SWidget& SlateWidget);

	static bool PreprocessKeyDownEvent(const FKeyEvent& InKeyEvent);
	static bool PreprocessKeyUpEvent(UWorld* World, const FKeyEvent& InKeyEvent);
	static void DisplayDebugKeyHints( UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos );
	static void DisplayDebugKeybindings( UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos );

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Highlights" )
	void OnFocusHighlightActivated( const FFGFocusHighlight& highlight );
	virtual void OnFocusHighlightActivated_Implementation( const FFGFocusHighlight& highlight );

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Highlights" )
	void OnFocusHighlightDeactivated( const FFGFocusHighlight& highlight );
	virtual void OnFocusHighlightDeactivated_Implementation( const FFGFocusHighlight& highlight );

	bool IsFocusWidgetForKeybindFound( const FFGKeybinding& Keybinding );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void OverwriteKeybindings( TArray<FFGKeybinding> newkeyHints );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	FKey FindKeyByBindingTag( FName HintTag );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	bool UpdateKeybindingByTag( FName HintTag, FKey NewKey );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void AddChildKeybindings(UFGUserWidget* ChildWidget);

private:

	FReply CallDelegateForKeyEventOfType(const FKeyEvent& InKeyEvent, EFGKeyHintDelegateType DelegateType);
	FReply CallKeybindingDelegate(const FFGKeybinding& Keybinding, EFGKeyHintDelegateType DelegateType);
	void BeginLongPress(const FFGKeybinding& Keybinding);
	static void FakeKeyDownAndUpEvents(const FKeyEvent& InKeyEvent);
	static void FakeKeyUpEvent(const FKeyEvent& InKeyEvent);
	void AddParentKeybindings();
	TArray< FFGKeybinding > AllKeybindings;
};

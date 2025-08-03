// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/FGUserWidget.h"
#include "InputAction.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Components/Widget.h"
#include "Subsystems/EngineSubsystem.h"
#include "FGButtonHintBar.generated.h"

UENUM( BlueprintType )
enum class EFGButtonHintBarMode : uint8
{
	FocusPath,		// button hints are updated on focus changes.  
	EnhancedInput,  //
	WidgetPath		// 
};

USTRUCT( BlueprintType )
struct FFGButtonHintDescription
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FKey ComboKey;

	//overrides InputAction and Key, looks for matching Tag in Satisfactory Input Settings
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FGameplayTag OverrideHintTag;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FText HintText;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	EFGKeyHintVariant Variant = EFGKeyHintVariant::Default;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float LongPressSeconds = -1.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	bool Disabled = false;
};

USTRUCT( BlueprintType )
struct FFGButtonBindingDescription
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TObjectPtr<UInputAction> InputAction;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TObjectPtr<UInputAction> ChordInputAction;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Force this Key instead of looking up the InputAction" )  )
	FKey OverrideKey;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "If left empty will use DisplayName from PlayerMappableKeySettings" ) )
	FText DescriptionText;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName MappableSettingName;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	EFGKeyHintVariant Variant = EFGKeyHintVariant::Default;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGKeyHintListUpdated, const TArray<FFGKeyHint>&, KeyHints );

UCLASS()
class UFGButtonHintSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Conditional; }
	virtual bool IsTickable() const override { return IsInitialized(); }
	virtual bool IsTickableWhenPaused() const override { return IsInitialized(); }
	virtual bool IsTickableInEditor() const override { return IsInitialized(); }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UFGButtonHintSubsystem, STATGROUP_Tickables); }
	void NotifyKeyHintsChanged() { mUpdateKeyhintsNextFrame = true; }

private:
	void HandleSlateFocusChanging(const FFocusEvent& FocusEvent, const FWeakWidgetPath& OldFocusedWidgetPath, const TSharedPtr<SWidget>& OldFocusedWidget, const FWidgetPath& NewFocusedWidgetPath, const TSharedPtr<SWidget>& NewFocusedWidget);
	void UpdateKeyHints();
	void UpdateKeyHintsFromFocusPath(const FWidgetPath& FocusPath);

	FDelegateHandle mFocusChangingHandle;
	bool mUpdateKeyhintsNextFrame = false;
public:
	FFGKeyHintListUpdated mKeyHintListUpdated;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGButtonHintBar : public UFGBaseWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void UpdateButtonHints( const TArray<FFGButtonHintDescription>& buttonHints );

	UFUNCTION( BlueprintCallable )
	void InsertButtonHint( const FFGButtonHintDescription& ButtonHint, int32 Index );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	bool RemoveButtonHintAtIndex( int32 Index, FFGButtonHintDescription& out_ButtonHint );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	bool RemoveButtonHintByInputAction( UInputAction* InputAction, FFGButtonHintDescription& out_ButtonHint );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void UpdateKeyHintsFromWidgetPath();

	UFUNCTION( BlueprintImplementableEvent, Category="Input" )
	void OnKeyHintsUpdated();

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void SetHintTag(FName hintTag);

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray<FFGButtonHintDescription> mButtonHints;

	UPROPERTY( BlueprintReadOnly )
	TArray<FFGKeyHint> mCurrentKeyHints;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	EFGButtonHintBarMode mMode = EFGButtonHintBarMode::FocusPath;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true) )
	FName mHintTag;

	/** If set to true, the bar will never show. Used to hide bars of stacked Widget_Window_DarkMode. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	bool mHintBarIsAlwaysHidden = false;

private:

	UFUNCTION()
	void HandleKeyHintListUpdated(const TArray<FFGKeyHint>& KeyHints);

	UFUNCTION()
	void HandleKeyHintsChanged();

	UFUNCTION()
	void HandleEnhancedInputMappingsRebuilt();

	void UpdateKeyHintsFromFocusPath(const FWidgetPath& FocusPath);
	void UpdateKeyHintsFromEnhancedInput();

	bool ParentWindowIsTopmostOnWidgetStack();
	void SortKeyHints();

	class UFGGameUI* GetGameUI();
	class UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;
};

USTRUCT(Blueprintable)
struct FFGKeyHintGroup
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FKey GroupKey;

	UPROPERTY(BlueprintReadWrite)
	TArray<FFGKeyHint> KeyHints;
};

UCLASS()
class FACTORYGAME_API UFGButtonHintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION( BlueprintCallable, Category = "Input|KeyHints" )
	static void GroupAndSortKeyHints( const TArray<FFGKeyHint>& KeyHints, TArray<FFGKeyHintGroup>& out_Groups );
};
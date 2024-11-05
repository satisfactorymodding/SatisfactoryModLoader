// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/FGUserWidget.h"
#include "InputAction.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
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
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGButtonHintBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void UpdateButtonHints( const TArray<FFGButtonHintDescription>& buttonHints );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void UpdateKeyHintsFromWidgetPath();

	UFUNCTION( BlueprintImplementableEvent, Category="Input" )
	void OnKeyHintsUpdated();

	UPROPERTY( EditAnywhere )
	TArray<FFGButtonHintDescription> mButtonHints;

	UPROPERTY( BlueprintReadOnly )
	TArray<FFGKeyHint> mCurrentKeyHints;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	EFGButtonHintBarMode mMode = EFGButtonHintBarMode::FocusPath;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true) )
	FName mHintTag;

private:
	void HandleSlateFocusChanging(const FFocusEvent& FocusEvent, const FWeakWidgetPath& OldFocusedWidgetPath, const TSharedPtr<SWidget>& OldFocusedWidget, const FWidgetPath& NewFocusedWidgetPath, const TSharedPtr<SWidget>& NewFocusedWidget);
	UFUNCTION()
	void HandleKeyHintsChanged();
	void UpdateKeyHintsFromFocusPath( const FWidgetPath& FocusPath );

	UFUNCTION()
	void HandleEnhancedInputMappingsRebuilt();
	void UpdateKeyHintsFromEnhancedInput();

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
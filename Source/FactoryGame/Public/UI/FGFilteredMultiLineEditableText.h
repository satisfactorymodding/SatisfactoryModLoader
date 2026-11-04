// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/MultiLineEditableText.h"
#include "UI/FGTextFilterValidator.h"
#include "FGFilteredMultiLineEditableText.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnMultiLineEditableTextFilteringStarted );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnMultiLineEditableTextFilteredTextChanged, const FText&, FilteredText );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnMultiLineEditableTextFilteredTextCommitted, const FText&, FilteredText, ETextCommit::Type, CommitMethod );

/**
 * MultiLineEditableText counterpart to UFGFilteredEditableText - see that
 * class for the full rationale and FGTextFilterValidator.h for the shared
 * logic.
 *
 * Note: by default, Enter inserts a newline here instead of committing
 * (OnTextCommitted only fires on focus-loss/programmatic commit), so this
 * leans more on OnTextChanged than the single-line variants - the shared
 * validator doesn't care how often or why OnTextCommitted fires, so this
 * needs no special-casing.
 */
UCLASS( meta = ( HideFunctions = "GetText", DisplayName="Filtered Editable Text (Multi-Line)" ) )
class FACTORYGAME_API UFGFilteredMultiLineEditableText : public UMultiLineEditableText
{
	GENERATED_BODY()

public:
	UFGFilteredMultiLineEditableText( const FObjectInitializer& ObjectInitializer );

	UFUNCTION( BlueprintPure, Category = "Filtered Editable Text" )
	FText GetFilteredText() const { return mValidator.GetFilteredText(); }

	UFUNCTION( BlueprintPure, Category = "Filtered Editable Text" )
	FText GetUnvalidatedText() const { return Super::GetText(); }

	UFUNCTION( BlueprintPure, Category = "Filtered Editable Text" )
	bool IsValidationInProgress() const { return mValidator.IsValidationInProgress(); }

	UFUNCTION( BlueprintCallable, Category = "Filtered Editable Text" )
	void InitializeFilteredText( const FText& initialText );

	UPROPERTY( BlueprintAssignable, Category = "Filtered Editable Text" )
	FOnMultiLineEditableTextFilteringStarted OnFilteringStarted;

	UPROPERTY( BlueprintAssignable, Category = "Filtered Editable Text" )
	FOnMultiLineEditableTextFilteredTextChanged OnFilteredTextChanged;

	UPROPERTY( BlueprintAssignable, Category = "Filtered Editable Text" )
	FOnMultiLineEditableTextFilteredTextCommitted OnFilteredTextCommitted;

protected:
	virtual void SynchronizeProperties() override;

private:
	UFUNCTION()
	void HandleTextChanged( const FText& newText );

	UFUNCTION()
	void HandleTextCommitted( const FText& newText, ETextCommit::Type commitMethod );

	FFGTextFilterValidator mValidator;
};
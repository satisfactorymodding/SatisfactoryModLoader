// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableTextBox.h"
#include "UI/FGTextFilterValidator.h"
#include "FGFilteredEditableTextBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnEditableTextBoxFilteringStarted );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnEditableTextBoxFilteredTextChanged, const FText&, FilteredText );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnEditableTextBoxFilteredTextCommitted, const FText&, FilteredText, ETextCommit::Type, CommitMethod );

/**
 * EditableTextBox counterpart to UFGFilteredEditableText - see that class for
 * the full rationale and FGTextFilterValidator.h for the shared logic.
 */
UCLASS( meta = ( HideFunctions = "GetText", DisplayName="Filtered Text Box") )
class FACTORYGAME_API UFGFilteredEditableTextBox : public UEditableTextBox
{
	GENERATED_BODY()

public:
	UFGFilteredEditableTextBox( const FObjectInitializer& ObjectInitializer );

	UFUNCTION( BlueprintPure, Category = "Filtered Editable Text" )
	FText GetFilteredText() const { return mValidator.GetFilteredText(); }

	UFUNCTION( BlueprintPure, Category = "Filtered Editable Text" )
	FText GetUnvalidatedText() const { return Super::GetText(); }

	UFUNCTION( BlueprintPure, Category = "Filtered Editable Text" )
	bool IsValidationInProgress() const { return mValidator.IsValidationInProgress(); }

	UFUNCTION( BlueprintCallable, Category = "Filtered Editable Text" )
	void InitializeFilteredText( const FText& initialText );

	UPROPERTY( BlueprintAssignable, Category = "Filtered Editable Text" )
	FOnEditableTextBoxFilteringStarted OnFilteringStarted;

	UPROPERTY( BlueprintAssignable, Category = "Filtered Editable Text" )
	FOnEditableTextBoxFilteredTextChanged OnFilteredTextChanged;

	UPROPERTY( BlueprintAssignable, Category = "Filtered Editable Text" )
	FOnEditableTextBoxFilteredTextCommitted OnFilteredTextCommitted;

protected:
	virtual void SynchronizeProperties() override;

private:
	UFUNCTION()
	void HandleTextChanged( const FText& newText );

	UFUNCTION()
	void HandleTextCommitted( const FText& newText, ETextCommit::Type commitMethod );

	FFGTextFilterValidator mValidator;
};
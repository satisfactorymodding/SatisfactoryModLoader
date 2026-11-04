// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGEditableText.h"
#include "Components/EditableText.h"
#include "UI/FGTextFilterValidator.h"
#include "FGFilteredEditableText.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnFilteringStarted );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnFilteredTextChanged, const FText&, FilteredText );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnFilteredTextCommitted, const FText&, FilteredText, ETextCommit::Type, CommitMethod );

/**
 * EditableText that filters its own content for profanity (see
 * FGTextFilterValidator.h for the actual logic, shared with the other
 * UFGFiltered* widgets). GetFilteredText() never returns unvalidated text.
 *
 * The base GetText() is hidden from this widget's Blueprint context menu since
 * it's non-virtual and gives no such guarantee. 
 */
UCLASS( meta = ( HideFunctions = "GetText" ) )
class FACTORYGAME_API UFGFilteredEditableText : public UFGEditableText
{
	GENERATED_BODY()

public:
	UFGFilteredEditableText( const FObjectInitializer& ObjectInitializer );

	UFUNCTION( BlueprintPure, Category = "Filtered Editable Text" )
	FText GetFilteredText() const { return mValidator.GetFilteredText(); }

	UFUNCTION( BlueprintPure, Category = "Filtered Editable Text" )
	FText GetUnvalidatedText() const { return Super::GetText(); }

	UFUNCTION( BlueprintPure, Category = "Filtered Editable Text" )
	bool IsValidationInProgress() const { return mValidator.IsValidationInProgress(); }

	UFUNCTION( BlueprintCallable, Category = "Filtered Editable Text" )
	void InitializeFilteredText( const FText& initialText );

	UPROPERTY( BlueprintAssignable, Category = "Filtered Editable Text" )
	FOnFilteringStarted OnFilteringStarted;

	UPROPERTY( BlueprintAssignable, Category = "Filtered Editable Text" )
	FOnFilteredTextChanged OnFilteredTextChanged;

	UPROPERTY( BlueprintAssignable, Category = "Filtered Editable Text" )
	FOnFilteredTextCommitted OnFilteredTextCommitted;

protected:
	// Not the constructor - template-instanced widgets lose constructor-time bindings.
	virtual void SynchronizeProperties() override;

private:
	UFUNCTION()
	void HandleTextChanged( const FText& newText );

	UFUNCTION()
	void HandleTextCommitted( const FText& newText, ETextCommit::Type commitMethod );

	FFGTextFilterValidator mValidator;
};
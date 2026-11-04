// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * Single-flight, staleness-guarded profanity-filter validation loop, shared by
 * the UFGFiltered* EditableText widgets.
 */
class FACTORYGAME_API FFGTextFilterValidator
{
public:
	FFGTextFilterValidator() = default;

	FFGTextFilterValidator( UObject* owner, TFunction< FText() > getLiveText, TFunction< void( const FText& ) > applyConfirmedText );

	void NotifyTextChanged( const FText& newText );

	void NotifyTextCommitted( const FText& newText, TFunction< void( const FText& ) > onFiltered );

	FText GetFilteredText() const;
	bool IsValidationInProgress() const { return mIsValidationInProgress; }

	TFunction< void() > OnStarted;
	TFunction< void( const FText& ) > OnSettled;

private:
	void StartValidation( const FString& textToValidate );
	void HandleFilterCompleted( bool success, const FString& sanitizedMessage );
	void SettleCommit( const FText& filteredText, const TFunction< void( const FText& ) >& onFiltered );

	// Some backend filter APIs currently false-positive on single characters (a
	// bug there, not a real profanity match) - skip the call and treat as clean.
	static bool ShouldSkipApiCall( const FString& text );

	TWeakObjectPtr< UObject > mOwner;
	TFunction< FText() > mGetLiveText;
	TFunction< void( const FText& ) > mApplyConfirmedText;

	FText mConfirmedFilteredText;
	bool mIsValidationInProgress = false;
	FString mLastSubmittedForValidation;
};
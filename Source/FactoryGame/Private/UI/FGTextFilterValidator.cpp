#include "UI/FGTextFilterValidator.h"

FFGTextFilterValidator::FFGTextFilterValidator(UObject* owner, TFunction<FText()> getLiveText, TFunction<void(const FText&)> applyConfirmedText){ }
void FFGTextFilterValidator::NotifyTextChanged(const FText& newText){ }
void FFGTextFilterValidator::NotifyTextCommitted(const FText& newText, TFunction<void(const FText&)> onFiltered){ }
FText FFGTextFilterValidator::GetFilteredText() const{ return FText(); }
void FFGTextFilterValidator::StartValidation(const FString& textToValidate){ }
void FFGTextFilterValidator::HandleFilterCompleted(bool success, const FString& sanitizedMessage){ }
void FFGTextFilterValidator::SettleCommit(const FText& filteredText, const TFunction<void(const FText&)>& onFiltered){ }
bool FFGTextFilterValidator::ShouldSkipApiCall(const FString& text){ return false; }

#include "Configuration/ModConfiguration.h"

#include "Misc/DataValidation.h"
#define LOCTEXT_NAMESPACE "SML"

#if WITH_EDITOR
EDataValidationResult UModConfiguration::IsDataValid(FDataValidationContext& Context) const {
	EDataValidationResult ValidationResult = EDataValidationResult::Valid;
	if (DisplayName.IsEmpty()) {
		Context.AddError(LOCTEXT("ConfigDisplayNameEmpty", "Configuration Display Name is not set"));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (!IsValid(RootSection)) {
		Context.AddError(LOCTEXT("ConfigRootSectionNull", "Root Section value is not set"));
		ValidationResult = EDataValidationResult::Invalid;
	} else {
		const EDataValidationResult ChildResult = RootSection->IsDataValid(Context);
		if (ChildResult == EDataValidationResult::Invalid) {
			ValidationResult = EDataValidationResult::Invalid;
		}
	}
	return ValidationResult;
}
#endif

#undef LOCTEXT_NAMESPACE
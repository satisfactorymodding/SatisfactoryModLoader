#include "Configuration/ModConfiguration.h"
#define LOCTEXT_NAMESPACE "SML"

void UModConfiguration::ResetUserConfigToDefaults() {
	const UModConfiguration* DefaultCDO = GetClass()->GetDefaultObject<UModConfiguration>();
	if (DefaultCDO && DefaultCDO->RootSection && this->RootSection) {
		this->RootSection->ResetToDefault(DefaultCDO->RootSection);
	}
}

#if WITH_EDITOR
EDataValidationResult UModConfiguration::IsDataValid(TArray<FText>& ValidationErrors) {
	EDataValidationResult ValidationResult = EDataValidationResult::Valid;
	if (DisplayName.IsEmpty()) {
		ValidationErrors.Add(LOCTEXT("ConfigDisplayNameEmpty", "Configuration Display Name is not set"));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (!IsValid(RootSection)) {
		ValidationErrors.Add(LOCTEXT("ConfigRootSectionNull", "Root Section value is not set"));
		ValidationResult = EDataValidationResult::Invalid;
	} else {
		const EDataValidationResult ChildResult = RootSection->IsDataValid(ValidationErrors);
		if (ChildResult == EDataValidationResult::Invalid) {
			ValidationResult = EDataValidationResult::Invalid;
		}
	}
	return ValidationResult;
}
#endif

#undef LOCTEXT_NAMESPACE
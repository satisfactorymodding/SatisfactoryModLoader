#include "SessionSettings/SessionSetting.h"
#include "Settings/FGUserSettingCategory.h"
#define LOCTEXT_NAMESPACE "SML"

USMLSessionSetting::USMLSessionSetting() {
	ShowInBuilds = EIncludeInBuilds::IIB_PublicBuilds;
	ManagerAvailability = static_cast<EUserSettingManagers>(StaticEnum<EUserSettingManagers>()->GetMaxEnumValue());
	IsSettingSessionWide = true;
}

void USMLSessionSetting::PostLoad() {
	Super::PostLoad();
	// Ensure at runtime that the setting is visible in the settings menu
	ShowInBuilds = EIncludeInBuilds::IIB_PublicBuilds;
	// Ensure at runtime that the setting is using an invalid manager so it is not loaded by the game
	ManagerAvailability = static_cast<EUserSettingManagers>(StaticEnum<EUserSettingManagers>()->GetMaxEnumValue());
	// Ensure at runtime that the setting is marked as session-wide
	IsSettingSessionWide = true;
}

#if WITH_EDITOR
EDataValidationResult USMLSessionSetting::IsDataValid(TArray<FText>& ValidationErrors) {
	EDataValidationResult ValidationResult = EDataValidationResult::Valid;
	if (StrId.IsEmpty()) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoStrId", "StrId is not set"));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (DisplayName.IsEmpty()) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoDisplayName", "DisplayName is not set"));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (ToolTip.IsEmpty()) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoToolTip", "ToolTip is not set"));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (!IsValid(CategoryClass)) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoCategoryClass", "CategoryClass is not set"));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (!IsValid(SubCategoryClass)) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoSubCategoryClass", "SubCategoryClass is not set"));
		ValidationResult = EDataValidationResult::Invalid;
	}
	return ValidationResult;
}
#endif
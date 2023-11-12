#include "SessionSettings/SessionSetting.h"

#include "SessionSettings/SessionSettingsManager.h"
#include "Settings/FGUserSettingCategory.h"
#include "Settings/FGUserSettingApplyType.h"
#define LOCTEXT_NAMESPACE "SML"

USMLSessionSetting::USMLSessionSetting() {
	ShowInBuilds = EIncludeInBuilds::IIB_PublicBuilds;
	ManagerTypeAvailability = USessionSettingsManager::StaticClass();
	IsSettingSessionWide = true;
}

void USMLSessionSetting::PostLoad() {
	Super::PostLoad();
	// Ensure at runtime that the setting is visible in the settings menu
	ShowInBuilds = EIncludeInBuilds::IIB_PublicBuilds;
	// Ensure at runtime that the setting is not managed by another options manager
	ManagerTypeAvailability = USessionSettingsManager::StaticClass();
	// Ensure at runtime that the setting is marked as session-wide
	IsSettingSessionWide = true;
}

#if WITH_EDITOR
EDataValidationResult USMLSessionSetting::IsDataValid(TArray<FText>& ValidationErrors) {
	EDataValidationResult ValidationResult = EDataValidationResult::Valid;
	if (StrId.IsEmpty()) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoStrId", "StrId is not set. Without one, it's impossible to use the value of this session setting."));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (DisplayName.IsEmpty()) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoDisplayName", "DisplayName is not set. Would appear blank at runtime."));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (ToolTip.IsEmpty()) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoToolTip", "ToolTip is not set. Please describe the setting for the end user."));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (!IsValid(CategoryClass)) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoCategoryClass", "CategoryClass is not set. Please use a category with your mod's name as the name."));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (!IsValid(SubCategoryClass)) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoSubCategoryClass", "SubCategoryClass is not set. Unassigned subcategories not allowed."));
		ValidationResult = EDataValidationResult::Invalid;
	}
	if (!ApplyType) {
		ValidationErrors.Add(LOCTEXT("SessionSettingNoApplyType", "ApplyType is not set. This would crash the game at runtime; use FGUserSettingApplyType instead."));
		ValidationResult = EDataValidationResult::Invalid;
	}
	return ValidationResult;
}
#endif

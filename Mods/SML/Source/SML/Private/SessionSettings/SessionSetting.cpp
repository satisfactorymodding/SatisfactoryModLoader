#include "SessionSettings/SessionSetting.h"

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

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Settings/FGUserSetting.h"
#include "Settings/FGUserSettingCategory.h"
#include "FGOptionsLibrary.generated.h"

/**
 * @todok2 do we even need this library anymore?
 */
UCLASS()
class FACTORYGAME_API UFGOptionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/** Gathers and organizes all user settings belonging to the given manager. 
	 * Parent settings are sorted by menu priority, display name, then by category and subcategory.
	 * Sub settings are sorted by menu priority under their respective parent setting.
	 * The function also ensures all setting assets are loaded.
	 * @param manager The manager that will manage the found user settings.
	 * @param out_userSettings Will be populated with the found settings
	 * @param managerAvailabilityOverride When set, this will be used to check whenever the setting belongs to the given manager instead of the class of the manager
	 * @param bDedicatedServerRelevantOnly true if we should only gather settings that are relevant for the dedicated server
	 */
	static void GatherUserSettings( IFGOptionInterface* manager, TMap< FString, class UFGUserSettingApplyType* >& out_userSettings, UClass* managerAvailabilityOverride = nullptr, bool bDedicatedServerRelevantOnly = false );

	/** Returns categorized option row widgets as well as setting up suboption for these widgets
	 * @param visibilityDisqualifiers Options that should be set on the setting for it to receive a widget
	 * @param owningWidget The widget that will be the owner of the new option row widgets
	 * @param optionInterface The interface that manages the user settings
	 * @param userSettings The setting to create the option row from
	 */
	static TArray<FUserSettingCategoryMapping> GetCategorizedUserSettingsWidgets( ESettingVisiblityDisqualifier visibilityDisqualifiers, UUserWidget* owningWidget, TScriptInterface<class IFGOptionInterface> optionInterface, TMap< FString, class UFGUserSettingApplyType* > userSettings );

	/** Returns categorized option row widgets as well as setting up suboption for these widgets
	 * @param worldContext Needed so we can check if each setting should be shown in the current config 
	 * @param owningWidget The widget that will be the owner of the new option row widgets
	 * @param optionInterface The interface that manages the user settings
	 * @param userSettings The setting to create the option row from
	 */
	static TArray<FUserSettingCategoryMapping> GetCategorizedUserSettingsWidgets( UObject* worldContext, UUserWidget* owningWidget, TScriptInterface<class IFGOptionInterface> optionInterface, TMap< FString, class UFGUserSettingApplyType* > userSettings );

	
	/** Creates a option row widget for the given user setting
	 * @param owningWidget The widget that will be the owner of the new option row widget 
	 * @param userSetting The setting to create the option row from
	 * @param optionInterface The interface that manages the user setting
	 */
	static UFGDynamicOptionsRow* SetupUserSetting( UUserWidget* owningWidget, class UFGUserSetting* userSetting, TScriptInterface< class IFGOptionInterface > optionInterface );

};

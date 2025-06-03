// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FGOptionInterface.h"
#include "FGOptionsSettings.h"
#include "Misc/Variant.h"
#include "FGUserSetting.generated.h"

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogUserSetting, Log, All );

USTRUCT( BlueprintType )
struct FSettingsWidgetLocationDescriptor
{
	GENERATED_BODY()
public:
	FSettingsWidgetLocationDescriptor() {
		CategoryClass = nullptr;
		SubCategoryClass = nullptr;
		SubOptionTo = nullptr;
		MenuPriority = 0;
	}

	FSettingsWidgetLocationDescriptor( TSubclassOf< class UFGUserSettingCategory > in_CategoryClass,
									   TSubclassOf< class UFGUserSettingCategory > in_SubCategoryClass,
										UFGUserSetting* in_SubOptionTo,
									   float in_MenuPriority )
	{
		CategoryClass = in_CategoryClass;
		SubCategoryClass = in_SubCategoryClass;
		SubOptionTo = in_SubOptionTo;
		MenuPriority = in_MenuPriority;
	};

	inline bool operator==( const FSettingsWidgetLocationDescriptor& rhs ) const;

	/** This is the main category class for this setting. It represents the broader category under which a specific setting falls */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Setting" )
	TSubclassOf< class UFGUserSettingCategory > CategoryClass;

	/** This is the sub category class for this setting. It represents a more specific category for a setting, which is shown when expanding
	 * the main category class */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Setting" )
	TSubclassOf< class UFGUserSettingCategory > SubCategoryClass;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Availability" )
	UFGUserSetting* SubOptionTo;
	/** The order in menus is decided by this value. Lower values means earlier in menu. Negative values are allowed. [-N..0..N]*/
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "User Interface" )
	float MenuPriority;
};

/** Old enum indicating what menu the option belongs to. Was used before switching to the manager subclass */
UENUM()
enum class EUserSettingManagers : uint8
{
	USM_OptionsMenu UMETA( DisplayName = "Options Menu" ),
	USM_Advanced UMETA( DisplayName = "Advanced Game Settings" ),
	USM_PhotoMode UMETA( DisplayName = "Photo Mode" ),
	USM_None UMETA( DisplayName = "None" )
};

// Disqualifiers if we should not show the setting at all
UENUM( Meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class ESettingVisiblityDisqualifier : uint64
{
	USAD_None = 0 UMETA( Hidden ),
	USAD_NotOnServer = 1 << 0 UMETA( DisplayName = "Don't show on server" ),
	USAD_NotOnClient = 1 << 1 UMETA( DisplayName = "Don't show on client" ),
	USAD_NotInMainMenu = 1 << 2 UMETA( DisplayName = "Don't show in main menu" ),
	USAD_NotInGame = 1 << 3 UMETA( DisplayName = "Don't show in game" ),
	USAD_NotForVulkan = 1 << 4 UMETA( DisplayName = "Don't show when RHI is Vulkan" ),
	USAD_DedicatedServerOnly = 1 << 5 UMETA( DisplayName = "Only show on Dedicated Server" ),
	USAD_DedicatedServerUIOnly = 1 << 6 UMETA( DisplayName = "Only show in the Dedicated Server Options UI" ),
	// <FL> [PfaffN] Added visibility flags for each platform
	// TODO @Nick: Rename this from NotOnWindows to NotOnDesktop in C++
	USAD_NotOnWindows = 1 << 7 UMETA( DisplayName = "Don't show on Desktop" ),
	USAD_NotOnPS5 = 1 << 8 UMETA( DisplayName = "Don't show on Playstation 5" ),
	USAD_NotOnXSX = 1 << 9 UMETA( DisplayName = "Don't show on Xbox Series X|S" )
	// </FL>
};
ENUM_CLASS_FLAGS( ESettingVisiblityDisqualifier );

// Disqualifiers if we should allow editing of the setting
UENUM( BlueprintType, Meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class ESettingEditabilityDisqualifier : uint8
{
	USED_None = 0 UMETA( Hidden ),
	USED_NonReversibleInGame
	= 1 << 0 UMETA( DisplayName = "This setting can't be reversed once changed in game, but can be reversed in the Main Menu" ),
	USED_NonReversible = 1 << 1 UMETA( DisplayName = "This setting can't be reversed once changed" )
};

// <FL> [PfaffN] Platform type to identify the target platform setting
// Windows, Mac, Linux, IOS, Android
UENUM( BlueprintType )
enum class ETargetPlatformSettings
{
	TPS_Windows UMETA( DisplayName = "Windows" ),
	TPS_Linux UMETA( DisplayName = "Linux" ),
	TPS_PS5 UMETA( DisplayName = "Playstation 5" ),
	TPS_PS5_Pro UMETA( DisplayName = "Playstation 5 Pro" ),
	TPS_XSX_Lockhart UMETA( DisplayName = "Xbox Series S (Lockhart)" ),
	TPS_XSX_Anaconda UMETA( DisplayName = "Xbox Series X (Anaconda)" )
};
// </FL>

/**
 *
 */
UCLASS( NotBlueprintable )
class FACTORYGAME_API UFGUserSetting : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFGUserSetting();

	// Used for legacy support until all settings are migrated
	FOptionRowData ToOptionRowData() const;

	/** Returns a set of visibility disqualifiers for the given world. That means, the setting will not be shown if any of them are set on
	 * the option */
	static ESettingVisiblityDisqualifier GetVisibilityDisqualifiers( UWorld* world );

	// Should this option be showed in the current config. Takes into account various things like build config, graphics api, net mode and
	// game mode
	bool ShouldShowInCurrentConfig( ESettingVisiblityDisqualifier visibilityDisqualifiers ) const;

	// Should this option be showed in the current config. Takes into account various things like build config, graphics api, net mode and
	// game mode
	FORCEINLINE bool ShouldShowInCurrentConfig( UWorld* world ) const
	{
		return ShouldShowInCurrentConfig( GetVisibilityDisqualifiers( world ) );
	}

	FVariant GetDefaultValue() const;

	/** Returns the option interface actively handling this setting, or nullptr if not found */
	IFGOptionInterface* GetPrimaryOptionInterface( UWorld* world ) const;

	TSubclassOf< class UFGOptionsValueController > GetValueSelectorWidgetClass() const;

	// Used to migrate legacy properties on the settings
	virtual void PostLoad() override;
	// @Nick: This function override will just migrate ManagerAvailability for old assets, it does not actually serialize anything by itself
	virtual void Serialize( FStructuredArchive::FRecord Record ) override;

#if WITH_EDITOR
	virtual bool SetupValueFunction( class UK2Node_CallFunction* callFunction, bool isGetterFunction ) const;
	virtual EDataValidationResult IsDataValid( FDataValidationContext& validationContext ) const override;
#endif

	bool HasVisibilityDisqualifier( ESettingVisiblityDisqualifier disqualifier ) const;
	bool HasEditabilityDisqualifier( ESettingEditabilityDisqualifier disqualifier ) const;

	/** Returns true if this variable should create and use a Console Variable */
	bool ShouldUseCVar() const;

	/** Returns true if this setting is relevant for the dedicated server */
	bool IsDedicatedServerRelevant() const;

private:
	// Should we show this setting in the current build. Even if returns false, the setting value can still be read and evaluated!
	bool ShouldShowInBuild() const;

public:
	// The identifier in the system. Not shown to player. Used to link this setting with a underlying value in the game
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Setting" )
	FString StrId;

	// Should we manage and if needed create a cvar for this setting based on StrId. Not needed for any functionality so leave it empty if
	// you don't know you want it.
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Setting" )
	bool UseCVar;

	// True if this setting is relevant for the dedicated server and changing it's value has an effect on the server or the players
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Setting" )
	bool bRelevantForDedicatedServer;

	/** If this option is handled by a cvar this text will set as the help text, if this text is empty we will use ToolTip instead.
	 * If the cvar already exists, then we don't override it's help text.
	 * If changed in editor you need to restart the editor to see this take affect . This is because the name already been registered
	 * and I don't feel it's worth trying to unregister/reregister settings in editor. Values will be updated each new PIE session but this
	 * text won't
	 */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Setting" )
	FString DocString;

	/** The name that is showed for this setting in the UI  */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Setting" )
	FText DisplayName;

	/** The tooltip that is showed for this setting in the UI. Used for cvar help text as well, see DocString for more information about
	 * that  */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Setting" )
	FText ToolTip;

	/** This is the main category class for this setting. It represents the broader category under which a specific setting falls */
	UPROPERTY()
	TSubclassOf< class UFGUserSettingCategory > CategoryClass_DEPRECATED;

	/** This is the sub category class for this setting. It represents a more specific category for a setting, which is shown when expanding
	 * the main category class */
	UPROPERTY()
	TSubclassOf< class UFGUserSettingCategory > SubCategoryClass_DEPRECATED;

	/** The order in menus is decided by this value. Lower values means earlier in menu. Negative values are allowed. [-N..0..N]*/
	UPROPERTY()
	float MenuPriority_DEPRECATED;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "UserInterface" )
	TArray< FSettingsWidgetLocationDescriptor > WidgetsToCreate;

	/** If true this setting affect the whole session and not only the local player */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Setting" )
	bool IsSettingSessionWide;

	/** The class that we want to use to apply values of this setting. Leave at default if you want a "normal" setting */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Apply Type" )
	TSoftClassPtr< class UFGUserSettingApplyType > ApplyType;

	/** What kind of value does this setting contain. The widget shown in the UI for this setting is decided by this unless a
	 * CustomValueSelectorWidget is defined */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Instanced, Category = "Value Selector" )
	class UFGUserSetting_ValueSelector* ValueSelector;

	/** Select a custom widget to override the value selctors default widget */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value Selector" )
	TSoftClassPtr< class UFGOptionsValueController > CustomValueSelectorWidget;

	/** Specifies what manager this option should be displayed in, e.g. Options, AGS or Photo Mode. Must point to a native class to avoid
	 * loading assets unnecessarily. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Availability",
			   meta = ( MustImplement = "/Script/FactoryGame.FGOptionInterface" ) )
	UClass* ManagerTypeAvailability;

	// When any of these are true in the current menu we don't show the setting
	UPROPERTY( EditDefaultsOnly, Category = "Availability",
			   meta = ( Bitmask, BitmaskEnum = "/Script/FactoryGame.ESettingVisiblityDisqualifier" ) )
	int64 VisibilityDisqualifiers;

	// When any of these are true in the current menu we don't allow the user to edit the setting
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Availability",
			   meta = ( Bitmask, BitmaskEnum = "/Script/FactoryGame.ESettingEditabilityDisqualifier" ) )
	uint8 EditabilityDisqualifiers;

	// Not used for now but we want support for it later
	UPROPERTY()
	UFGUserSetting* SubOptionTo_DEPRECATED;

private:
	/** Slightly misleading name, as this doesn't only apply to builds. If set to Never, it won't show up in editor
	 * 	We could strip the settings from builds but I assumed added settings that is not meant to be in build might rely on the default
	 * values so felt safer to keep the setting in the build but hide it.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Availability" )
	EIncludeInBuilds ShowInBuilds = EIncludeInBuilds::IIB_Development;

	/** Deprecated property holding the availability for the manager type */
	UPROPERTY()
	EUserSettingManagers ManagerAvailability_DEPRECATED;
};

UCLASS( Blueprintable, abstract, editinlinenew )
class FACTORYGAME_API UFGUserSetting_ValueSelector : public UObject
{
	GENERATED_BODY()

public:
	virtual TSubclassOf< class UFGOptionsValueController > GetValueSelectorWidgetClass() const;

	// Legacy helper
	virtual EOptionType GetOptionType() const
	{
		checkNoEntry();
		return EOptionType::OT_Checkbox;
	}

	virtual bool ShouldFocusOptionSlotToEdit() const
	{
		checkNoEntry();
		return false;
	}

	virtual FVariant GetDefaultValue() const { return FVariant(); }

#if WITH_EDITOR
	virtual FName GetGraphSchemaName() const;
	virtual bool SetupValueFunction( class UK2Node_CallFunction* callFunction, bool isGetterFunction ) const { return false; }
#endif
};

UCLASS( Blueprintable, DefaultToInstanced, editinlinenew, meta = ( DisplayName = "CheckBox" ) )
class FACTORYGAME_API UFGUserSetting_CheckBox : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()
public:
	virtual TSubclassOf< class UFGOptionsValueController > GetValueSelectorWidgetClass() const override;

	virtual EOptionType GetOptionType() const override { return EOptionType::OT_Checkbox; }
	
	virtual bool ShouldFocusOptionSlotToEdit() const override { return false; }
	virtual FVariant GetDefaultValue() const override;

#if WITH_EDITOR
	virtual FName GetGraphSchemaName() const override;

	virtual bool SetupValueFunction( class UK2Node_CallFunction* callFunction, bool isGetterFunction ) const override;
#endif

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	bool DefaultCheckBoxValue;

	// <FL> [PfaffN] Default values for different platforms
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	TMap< ETargetPlatformSettings, bool > PlatformDefaultCheckBoxValues;
	// </FL>
};

UCLASS( Blueprintable, DefaultToInstanced, editinlinenew, meta = ( DisplayName = "Integer Selector" ) )
class FACTORYGAME_API UFGUserSetting_IntSelector : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()

	UFGUserSetting_IntSelector();

public:
	virtual TSubclassOf< class UFGOptionsValueController > GetValueSelectorWidgetClass() const override;

	virtual EOptionType GetOptionType() const override { return EOptionType::OT_IntegerSelection; }

	virtual bool ShouldFocusOptionSlotToEdit() const override { return ShowAsDropdown == false; }

	virtual FVariant GetDefaultValue() const override;

#if WITH_EDITOR
	virtual FName GetGraphSchemaName() const override;

	virtual bool SetupValueFunction( class UK2Node_CallFunction* callFunction, bool isGetterFunction ) const override;
#endif

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	int32 Defaultvalue;

	// <FL> [PfaffN] Default values for different platforms
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	TMap< ETargetPlatformSettings, int32 > PlatformDefaultIntValues;
	// </FL>

	/** The values that this setting can be set to. Notice that the index is only for the order. The FIntegerSelection::Value can be set to
	 * any int32 value */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	TArray< FIntegerSelection > IntegerSelectionValues;

	/** When his is true the user can't select the last index manually. It has to be set programmatically */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	bool BlockLastIndexFromManualSelection;

	/** When last index is selected from automatic selection the user can't change the setting. Only valid if
	 * BlockLastIndexFromManualSelection is enabled */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value",
			   meta = ( EditCondition = "BlockLastIndexFromManualSelection", EditConditionHides ) )
	bool LockLastIndexWhenSelected;

	/** Should this integer selection be shown as a dropdown instead of a  */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	bool ShowAsDropdown;
};

UCLASS( Blueprintable, DefaultToInstanced, editinlinenew, meta = ( DisplayName = "Slider" ) )
class FACTORYGAME_API UFGUserSetting_Slider : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()

public:
	virtual TSubclassOf< class UFGOptionsValueController > GetValueSelectorWidgetClass() const override;

	virtual EOptionType GetOptionType() const override { return EOptionType::OT_Slider; }

	virtual bool ShouldFocusOptionSlotToEdit() const override { return true; }

	virtual FVariant GetDefaultValue() const override;

#if WITH_EDITOR
	virtual bool SetupValueFunction( class UK2Node_CallFunction* callFunction, bool isGetterFunction ) const override;
#endif

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	float MinValue = 0.f;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	float MaxValue = 1.f;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	float MinDisplayValue = 0.f;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	float MaxDisplayValue = 1.f;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	int32 MaxFractionalDigits = 1;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	bool ShowZeroAsOff;

	// The default value the slider will show. This should be in the MinDisplayValue - MaxDisplayValue range
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	float DefaultSliderValue = 0.5f;

	// <FL> [PfaffN] Default values for different platforms
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Value" )
	TMap< ETargetPlatformSettings, float > PlatformDefaultSliderValues;
	// </FL>
};

UCLASS( Blueprintable, DefaultToInstanced, editinlinenew, meta = ( DisplayName = "Custom" ) )
class FACTORYGAME_API UFGUserSetting_Custom : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()
public:
	virtual EOptionType GetOptionType() const override { return EOptionType::OT_Custom; }

	virtual bool ShouldFocusOptionSlotToEdit() const override { return false; }

	// @todok2 Add support for GetDefaultValue
};

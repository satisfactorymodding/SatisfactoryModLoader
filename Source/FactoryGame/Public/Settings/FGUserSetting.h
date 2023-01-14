// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGOptionInterface.h"
#include "FGOptionsSettings.h"
#include "OptionValueContainer.h"
#include "Misc/Variant.h"
#include "Engine/DataAsset.h"
#include "FGUserSetting.generated.h"

UENUM( BlueprintType )
enum class EUserSettingManagers : uint8
{
	USM_OptionsMenu					UMETA( DisplayName = "Options Menu" ),
	USM_Advanced					UMETA( DisplayName = "Advanced Gameplay Settings" ),
	USM_PhotoMode					UMETA( DisplayName = "Photo Mode" )
};

UENUM( BlueprintType, Meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class EUserSettingAvailabilityDisqualifier : uint8
{
	USAD_None			= 0			UMETA(Hidden),
	USAD_NotOnServer	= 1 << 0	UMETA( DisplayName = "Don't show on server" ),
	USAD_NotOnClient	= 1 << 1	UMETA( DisplayName = "Don't show on client" ),
	USAD_NotInMainMenu	= 1 << 2	UMETA( DisplayName = "Don't show in main menu" ),
	USAD_NotInGame		= 1 << 3	UMETA( DisplayName = "Don't show in game" ),
	USAD_NotForVulkan	= 1 << 4	UMETA( DisplayName = "Don't show when RHI is Vulkan" ),
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FUserSettingCatergoryMapping
{
	GENERATED_BODY()
	
	UPROPERTY( BlueprintReadOnly )
	FText CategoryName;
	
	UPROPERTY( BlueprintReadOnly )
	TArray< class UUserWidget* > SettingWidgets;
};

/**
 * 
 */
UCLASS( NotBlueprintable )
class FACTORYGAME_API UFGUserSetting : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	// Used for legacy support until all settings are migrated
	FOptionRowData ToOptionRowData() const;
	
	// Should we show this setting in the current build
	bool ShouldShowInBuild() const;
	
	void RestoreToDefaultValue();
	FVariant GetDefaultValue() const;
	
public:
	// The identifier in the system. Not shown to player. Used to link this setting with a underlying value in the game
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="Setting" )
	FString StrId;

	// Should we create a cvar for this setting base don StrId. Not needed for any functionality so leave it empty if you don't know you want it.
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="Setting" )
	bool CreateCVarFromStrid;
	
	UPROPERTY( EditDefaultsOnly, Category="Setting" )
	FText DisplayName;

	UPROPERTY( EditDefaultsOnly, Category="Setting" )
	FText ToolTip;

	UPROPERTY( EditDefaultsOnly, Category="Setting" )
	FText Category;

	// Not used for now but we want support for it later 
	UPROPERTY( BlueprintReadWrite, VisibleDefaultsOnly, Category="Setting" )
	EOptionApplyType ApplyType;

	UPROPERTY( EditAnywhere, Instanced, BlueprintReadWrite, Category = "Value Selector"  )
	class UFGUserSetting_ValueSelector* ValueSelector;
	
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="Availability"  )
	EUserSettingManagers ManagerAvailability;
	
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="Availability", meta=(Bitmask,BitmaskEnum="EUserSettingAvailabilityDisqualifier") )
	uint8 AvailabilityDisqualifiers;

	// Not used for now but we want support for it later 
	UPROPERTY( BlueprintReadWrite, VisibleDefaultsOnly, Category="Availability" )
	UFGUserSetting* SubOption;

	// Transient values modfied at runtime to keep track of state;
	FVariant CurrentValue = FVariant();
	TArray<FOnOptionUpdated> Subscribers;

private:
	/** Slightly misleading name, as this doesn't only apply to builds. If set to Never, it won't show up in editor
	 * 	We could strip the settings from builds but I assumed added settings that is not meant to be in build might rely on the default values
	 * 	so felt safer to keep the setting in the build but hide it.
	 */
	UPROPERTY( EditDefaultsOnly, Category="Availability" )
	EIncludeInBuilds mShowInBuilds = EIncludeInBuilds::IIB_Development;
	
};

UCLASS( Blueprintable, abstract, editinlinenew )
class FACTORYGAME_API UFGUserSetting_ValueSelector : public UObject
{
	GENERATED_BODY()

public:
	virtual TSubclassOf< class UFGOptionsValueController > GetSettingValueSelectorWidgetClass() const;

	// Legacy helper
	virtual EOptionType GetOptionType() const { checkNoEntry(); return EOptionType::OT_Checkbox; }

	virtual FVariant GetDefaultValue() const { return FVariant(); }
};

UCLASS( Blueprintable, DefaultToInstanced, editinlinenew, meta = ( DisplayName = "CheckBox" ) )
class FACTORYGAME_API UFGUserSetting_CheckBox : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()
public:
	virtual TSubclassOf< class UFGOptionsValueController > GetSettingValueSelectorWidgetClass() const override;

	virtual EOptionType GetOptionType() const override { return EOptionType::OT_Checkbox; }
	
	virtual FVariant GetDefaultValue() const override { return FVariant(DefaultCheckBoxValue); }
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	bool DefaultCheckBoxValue;

};

// @todok2 this needs more work and testing to make sure it works properly when changing enum and similar
// We need to add support for enum display names as FText so they can be translated.
// Maybe this should just be a dervied UFGUserSetting_IntSelector with some magic to populate values from a selected enum
UCLASS( editinlinenew, meta = ( DisplayName = "Enum Selector" )  )
class FACTORYGAME_API UFGUserSetting_EnumSelector : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()

public:
	virtual TSubclassOf< class UFGOptionsValueController > GetSettingValueSelectorWidgetClass() const override;

	virtual EOptionType GetOptionType() const override { return EOptionType::OT_IntegerSelection; }

	// @todok2 cache this?
	TArray<FIntegerSelection> GetIntegerSelectionValues( int32& out_DefaultSelectionIndex );

	UFUNCTION()
	TArray<FString> GetEnumOptions() const;

	// @todok2 Add support for GetDefaultValue

	// Can we replace or at least cache this with a enum*
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	FString EnumAsString;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value", meta=(GetOptions="GetEnumOptions") )
	FString DefaultEnumValue;
};

UCLASS( Blueprintable, DefaultToInstanced, editinlinenew, meta = ( DisplayName = "Integer Selector" ) )
class FACTORYGAME_API UFGUserSetting_IntSelector : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()

	UFGUserSetting_IntSelector();

public:
	virtual TSubclassOf< class UFGOptionsValueController > GetSettingValueSelectorWidgetClass() const override;

	virtual EOptionType GetOptionType() const override { return EOptionType::OT_IntegerSelection; }

	virtual FVariant GetDefaultValue() const override { return FVariant(Defaultvalue); }
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	int32 Defaultvalue;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	TArray<FIntegerSelection> IntegerSelectionValues;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	bool BlockLastIndexFromManualSelection;
};



UCLASS( Blueprintable, DefaultToInstanced, editinlinenew, meta = ( DisplayName = "Slider" ) )
class FACTORYGAME_API UFGUserSetting_Slider : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()
	
public:
	virtual TSubclassOf< class UFGOptionsValueController > GetSettingValueSelectorWidgetClass() const override;

	virtual EOptionType GetOptionType() const override { return EOptionType::OT_Slider; }

	virtual FVariant GetDefaultValue() const override { return FVariant(DefaultSliderValue); }
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	float MinValue = 0.f;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	float MaxValue = 1.f;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	float MinDisplayValue = 0.f;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	float MaxDisplayValue = 1.f;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	int32 MaxFractionalDigits = 1;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	bool ShowZeroAsOff;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	float DefaultSliderValue = 0.5f;
};

UCLASS( Blueprintable, DefaultToInstanced, editinlinenew, meta = ( DisplayName = "Custom" ) )
class FACTORYGAME_API UFGUserSetting_Custom : public UFGUserSetting_ValueSelector
{
	GENERATED_BODY()
public:
	virtual TSubclassOf< class UFGOptionsValueController > GetSettingValueSelectorWidgetClass() const override;

	virtual EOptionType GetOptionType() const override { return EOptionType::OT_Custom; }

	// @todok2 Add support for GetDefaultValue
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Value" )
	TSubclassOf< class UFGOptionsValueController > CustomValueSelectorWidget;
};

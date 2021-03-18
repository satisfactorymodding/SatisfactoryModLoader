// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "OptionValueContainer.h"
#include "FGOptionsSettings.generated.h"

UENUM( BlueprintType )
enum class EOptionCategory : uint8
{
	OC_Gameplay					UMETA( DisplayName = "Gameplay" ),
	OC_Audio					UMETA( DisplayName = "Audio" ),
	OC_Video					UMETA( DisplayName = "Video" ),
	OC_Controls					UMETA( DisplayName = "Controls" ),
	OC_Keybindings				UMETA( DisplayName = "Keybindings" ),
	OC_UserInterface			UMETA( DisplayName = "User Interface" ),
	OC_Online					UMETA( DisplayName = "Online" ),
	OC_Debug					UMETA( DisplayName = "Debug" )
};

UENUM( BlueprintType )
enum class EOptionType : uint8
{
	OT_Checkbox					UMETA( DisplayName = "Checkbox" ),
	OT_Slider					UMETA( DisplayName = "Slider" ),
	OT_IntegerSelection			UMETA( DisplayName = "IntegerSelection" ),
	OT_FloatSelection			UMETA( DisplayName = "FloatSelection" ),
	OT_Custom					UMETA( DisplayName = "Custom" )
};

UENUM( BlueprintType )
enum class EOptionNetmodeType : uint8
{
	ONT_ServerAndClient			UMETA( DisplayName = "Server and Client" ),
	ONT_OnlyServer				UMETA( DisplayName = "Only Server" ),
	ONT_OnlyClient				UMETA( DisplayName = "Only Client" )
};

UENUM( BlueprintType )
enum class EOptionGamemodeType : uint8
{
	OGT_Always					UMETA( DisplayName = "Always" ),
	OGT_OnlyInMainMenu			UMETA( DisplayName = "Only In Main Menu" ),
	OGT_OnlyInGame				UMETA( DisplayName = "Only In Game" )
};

USTRUCT( BlueprintType )
struct FIntegerSelection
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	FText Name;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	int32 Value;
};

USTRUCT( BlueprintType )
struct FFloatSelection
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	FText Name;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float Value;
};

USTRUCT( BlueprintType )
struct FOptionRowData
{
	GENERATED_BODY()

public:
	FOptionRowData() :
		OptionType( EOptionType::OT_Checkbox ),
		DefaultCheckBoxValue( false ),
		MinValue( 0 ),
		MaxValue( 0 ),
		MinDisplayValue( 0 ),
		MaxDisplayValue( 0 ),
		MaxFractionalDigits( 0 ),
		ShowZeroAsOff( false ),
		DefaultSliderValue( 0 ),
		OptionApplyType( EOptionApplyType::OAT_Normal ),
		NetmodeAvailability( EOptionNetmodeType::ONT_ServerAndClient ),
		GamemodeAvailability( EOptionGamemodeType::OGT_Always ),
		CustomWidgetClass( nullptr )
	{
	}

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	FText OptionName;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	EOptionType OptionType;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	FString ConsoleVariable;
	
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	bool DefaultCheckBoxValue;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float MinValue;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float MaxValue;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float MinDisplayValue;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float MaxDisplayValue;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	int32 MaxFractionalDigits;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	bool ShowZeroAsOff;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float DefaultSliderValue;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	TArray<FIntegerSelection> IntegerSelectionValues;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	TArray<FFloatSelection> FloatSelectionValues;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	int32 DefaultSelectionIndex;
	
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	FText Tooltip;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	EOptionApplyType OptionApplyType;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	EOptionNetmodeType NetmodeAvailability;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	EOptionGamemodeType GamemodeAvailability;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	TSubclassOf< class UFGOptionsValueController > CustomWidgetClass;
};

USTRUCT( BlueprintType, meta = ( ShowOnlyInnerProperties ) )
struct FActionMappingDisplayName
{
	GENERATED_BODY()
	
	FActionMappingDisplayName(){}

	FActionMappingDisplayName( FName keyBidningName ) :
		ActionMappingName( keyBidningName )
	{}

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	FName ActionMappingName;

	UPROPERTY( BlueprintReadOnly, EditAnywhere )
	FText DisplayName;
};

USTRUCT( BlueprintType, meta = ( ShowOnlyInnerProperties ) )
struct FAxisMappingDisplayName
{
	GENERATED_BODY()

	FAxisMappingDisplayName(){}

	FAxisMappingDisplayName( FName axisMappingName ) :
		AxisMappingName( axisMappingName )
	{}

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	FName AxisMappingName;

	UPROPERTY( BlueprintReadOnly, EditAnywhere )
	FText DisplayNamePositiveScale;

	UPROPERTY( BlueprintReadOnly, EditAnywhere )
	FText DisplayNameNegativeScale;
};

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Satisfactory User Options" ) )
class FACTORYGAME_API UFGOptionsSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	
	/** Return the display name struct for an action mapping */
	UFUNCTION( BlueprintCallable )
	static bool GetActionMappingDisplayName( FName actionMappingName, FActionMappingDisplayName& out_ActionMappingDisplayName )
	{
		TArray<FActionMappingDisplayName> actionBindingsDisplayNames = GetDefault<UFGOptionsSettings>()->mActionBindingsDisplayNames;
		bool result = false;
		if( FActionMappingDisplayName* actionMappingDisplayName = actionBindingsDisplayNames.FindByPredicate( [ actionMappingName ]( const FActionMappingDisplayName& actionBindingsDisplayNames ){ return actionBindingsDisplayNames.ActionMappingName.IsEqual( actionMappingName ); } ) )
		{
			out_ActionMappingDisplayName = *actionMappingDisplayName;
			result = true;
		}
		return result;
	}

	/** Return the display name struct for an axis mapping */
	UFUNCTION( BlueprintCallable )
	static bool GetAxisMappingDisplayName( FName axisMappingName, FAxisMappingDisplayName& out_AxisMappingDisplayName )
	{
		TArray<FAxisMappingDisplayName> axisBindingsDisplayNames = GetDefault<UFGOptionsSettings>()->mAxisBindingsDisplayNames;
		bool result = false;
		if( FAxisMappingDisplayName* axisMappingDisplayName = axisBindingsDisplayNames.FindByPredicate( [ axisMappingName ]( const FAxisMappingDisplayName& axisBindingsDisplayNames ){ return axisBindingsDisplayNames.AxisMappingName.IsEqual( axisMappingName ); } ) )
		{
			out_AxisMappingDisplayName = *axisMappingDisplayName;
			result = true;
		}
		return result;
	}

	/** Return all display name structs for an action mappings */
	UFUNCTION( BlueprintCallable )
	static void GetActionMappings( TArray<FActionMappingDisplayName>& out_ActionMappingDisplayName )
	{
		out_ActionMappingDisplayName.Append( GetDefault<UFGOptionsSettings>()->mActionBindingsDisplayNames );
	}

	/** Return all display name structs for an axis mappings */
	UFUNCTION( BlueprintCallable )
	static void GetAxisMappings( TArray<FAxisMappingDisplayName>& out_AxisMappingDisplayName )
	{
		out_AxisMappingDisplayName.Append( GetDefault<UFGOptionsSettings>()->mAxisBindingsDisplayNames );
	}

#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
public:
	UPROPERTY( EditAnywhere, config, Category = "Key Bindings", meta = ( ShowOnlyInnerProperties, ToolTip = "This maps a axis name to a postive and negative display name. If no display name is provided we show the axis name" ) )
	TArray<FAxisMappingDisplayName> mAxisBindingsDisplayNames;

	UPROPERTY( EditAnywhere, config, Category = "Key Bindings", meta = ( ShowOnlyInnerProperties, ToolTip = "This maps a action name to a display name. If no display name is provided we show the action name" ) )
	TArray<FActionMappingDisplayName> mActionBindingsDisplayNames;

	UPROPERTY( EditAnywhere, config, Category = "Options", meta = ( ToolTip = "" ) )
	TArray<FOptionRowData> mGameplayOptions;

	UPROPERTY( EditAnywhere, config, Category = "Options", meta = ( ToolTip = "" ) )
	TArray<FOptionRowData> mAudioOptions;

	UPROPERTY( EditAnywhere, config, Category = "Options", meta = ( ToolTip = "" ) )
	TArray<FOptionRowData> mVideoOptions;

	UPROPERTY( EditAnywhere, config, Category = "Options", meta = ( ToolTip = "" ) )
	TArray<FOptionRowData> mControlsOptions;

	UPROPERTY( EditAnywhere, config, Category = "Options", meta = ( ToolTip = "" ) )
	TArray<FOptionRowData> mUserInterfaceOptions;
		
	UPROPERTY( EditAnywhere, config, Category = "Options", meta = ( ToolTip = "" ) )
	TArray<FOptionRowData> mOnlineOptions;

	UPROPERTY( EditAnywhere, config, Category = "Options", meta = ( ToolTip = "" ) )
	TArray<FOptionRowData> mDebugOptions;

	UPROPERTY( EditAnywhere, config, Category = "Widget Classes", meta = ( ToolTip = "" ) )
	TMap<EOptionType, TSubclassOf< class UFGOptionsValueController >> mOptionTypeWidgetsClasses;

	UPROPERTY( EditAnywhere, config, Category = "Widget Classes", meta = ( ToolTip = "" ) )
	TSubclassOf< class UFGDynamicOptionsRow > mOptionRowWidgetClass;

};

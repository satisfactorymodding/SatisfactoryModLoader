// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Engine/DeveloperSettings.h"
#include "IncludeInBuild.h"
#include "Templates/SubclassOf.h"
#include "FGOptionsSettings.generated.h"

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Satisfactory User Options" ) )
class FACTORYGAME_API UFGOptionsSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGOptionsSettings* Get() { return GetDefault<UFGOptionsSettings>(); };

public:
	UPROPERTY( EditAnywhere, config, Category = "Widget Classes" )
	TSoftClassPtr< class UFGOptionsValueController > mSliderWidgetClass;

	UPROPERTY( EditAnywhere, config, Category = "Widget Classes" )
	TSoftClassPtr< class UFGOptionsValueController > mIntegerSelectionWidgetClass;
	
	UPROPERTY( EditAnywhere, config, Category = "Widget Classes" )
	TSoftClassPtr< class UFGOptionsValueController > mCheckboxWidgetClass; 
	
	UPROPERTY( EditAnywhere, config, Category = "Widget Classes", meta = ( ToolTip = "The widget class used when option type is integer selection and we want to show it as a dropdown menu" ) )
	TSoftClassPtr< class UFGOptionsValueController > mDropDownWidgetClass;

	UPROPERTY( EditAnywhere, config, Category = "Widget Classes" )
	TSoftClassPtr< class UFGOptionsValueController > mLinearColorPickerWidgetClass;

	UPROPERTY( EditAnywhere, config, Category = "Widget Classes", meta = ( ToolTip = "" ) )
	TSoftClassPtr< class UFGDynamicOptionsRow > mOptionRowWidgetClass;

	UPROPERTY( EditAnywhere, config, Category = "Hologram", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<class UMaterialParameterCollection> mHologramColourParameterCollection;

	UPROPERTY( EditAnywhere, Config, Category = "Vehicle Paths" )
	TSoftObjectPtr<class UMaterialParameterCollection> mVehiclePathParameterCollection;

	UPROPERTY( EditAnywhere, config, Category = "Video", meta = ( ToolTip = "This maps video quality scalability levels to benchmark results to. float value represents max benchamrk result for that level. e.g 0 - 50, 1 - 150 and so on" ) )
	TMap< int32, float > mVideoQualityBenchmarkMapping;

	UPROPERTY( EditAnywhere, config, Category = "Video" )
	TSoftClassPtr<class UFGUserSettingCategory> mVideoQualityCategory;

	// @todok2 Move below to input settings when that is added
	UPROPERTY( EditAnywhere, config, Category = "Input", meta = ( ToolTip = "These are the mapping contexts we want to show in the options menu to allow rebinding of their actions" ) )
	TArray<TSoftObjectPtr<class UInputMappingContext>> mPlayerRebindableMappingContexts;

	UPROPERTY( EditAnywhere, config, Category = "Input", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<class UInputAction> mCtrlInputAction;

	UPROPERTY( EditAnywhere, config, Category = "Input", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<class UInputAction> mShiftInputAction;

	UPROPERTY( EditAnywhere, config, Category = "Input", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<class UInputAction> mAltInputAction;
};

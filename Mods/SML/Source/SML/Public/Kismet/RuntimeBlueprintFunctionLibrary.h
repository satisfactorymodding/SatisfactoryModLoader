#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h" 
#include "Configuration/ConfigProperty.h"
#include "Configuration/ConfigManager.h"
#include "Configuration/Properties/ConfigPropertyFloat.h"
#include "Configuration/Properties/ConfigPropertyInteger.h"
#include "Configuration/Properties/ConfigPropertySection.h"
#include "Configuration/Properties/ConfigPropertyString.h"
#include "Configuration/Properties/ConfigPropertyArray.h"
#include "Configuration/Properties/ConfigPropertyBool.h"
#include "Components/SpinBox.h" 
#include "Components/ComboBoxString.h" 
#include "RuntimeBlueprintFunctionLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FObjFunctionBind, UObject*, Object);

UCLASS()
class SML_API URuntimeBlueprintFunctionLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "SML | Utilities", meta = (DeprecatedFunction, DeprecationMessage = "Use 'Load Class Asset Blocking' or 'Async Load Class Asset' from Unreal as needed instead", DisplayName = "Find Class By Name (Deprecated)"))
	static UClass* FindClassByName(FString ClassNameInput);

	/** Returns true in Editor*/
	UFUNCTION(BlueprintPure, Category = "SML | Utilities", meta = (DeprecatedFunction, DeprecationMessage = "Use 'IsGEditor' from SML Blueprint System Library instead", DisplayName = "Is Editor (Deprecated)"))
	static bool IsEditor();

	/** Retrieves FName from UConfigProperty */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CP to Name", CompactNodeTitle = "To Name", BlueprintAutocast), Category = "SML | Configuration")
	static FName Conv_ConfigPropertyToName(UConfigProperty* Property);
	/** Retrieves FText from UConfigProperty */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CP to Text", CompactNodeTitle = "To Text", BlueprintAutocast), Category = "SML | Configuration")
	static FText Conv_ConfigPropertyToText(UConfigProperty* Property);
	/** Retrieves FString from UConfigProperty */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CP to String", CompactNodeTitle = "To String", BlueprintAutocast), Category = "SML | Configuration")
	static FString Conv_ConfigPropertyToString(UConfigProperty* Property);
	/** Retrieves Float from UConfigProperty */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CP to Float", CompactNodeTitle = "To Float", BlueprintAutocast), Category = "SML | Configuration")
	static float Conv_ConfigPropertyToFloat(UConfigProperty* Property);
	/** Retrieves int32 from UConfigProperty */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CP to Int", CompactNodeTitle = "To Int", BlueprintAutocast), Category = "SML | Configuration")
	static int32 Conv_ConfigPropertyToInteger(UConfigProperty* Property);
	/** Retrieves Bool from UConfigProperty */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CP to Bool", CompactNodeTitle = "To Bool", BlueprintAutocast), Category = "SML | Configuration")
	static bool Conv_ConfigPropertyToBool(UConfigProperty* Property);
	
	/** Retrieves int32 from UConfigPropertyInteger */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CPF To Float", CompactNodeTitle = "To Float", BlueprintAutocast), Category = "SML | Configuration")
	static float Conv_ConfigPropertyFloatToFloat(UConfigPropertyFloat* Property);
	/** Retrieves int32 from UConfigPropertyInteger */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CPI To Integer", CompactNodeTitle = "To Int", BlueprintAutocast), Category = "SML | Configuration")
	static int32 Conv_ConfigPropertyIntegerToInteger(UConfigPropertyInteger* Property);
	/** Retrieves Bool from UConfigPropertyBool */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CPB To Bool", CompactNodeTitle = "To Bool", BlueprintAutocast), Category = "SML | Configuration")
	static bool Conv_ConfigPropertyBoolToBool(UConfigPropertyBool* Property);
	/** Retrieves String from UConfigPropertyString */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CBS To String", CompactNodeTitle = "To String", BlueprintAutocast), Category = "SML | Configuration")
	static FString Conv_ConfigPropertyStringToString(UConfigPropertyString* Property);
	/** Retrieves ConfigProperty from ConfigPropertySection by Key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Section", CompactNodeTitle = ".", BlueprintAutocast), Category = "SML | Configuration")
	static UConfigProperty*  Conv_ConfigPropertySectionToConfigProperty(UConfigPropertySection* Property, FString Key);
	/** Retrieves ConfigProperty Array from PropertyArray */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Array", CompactNodeTitle = "[]", BlueprintAutocast), Category = "SML | Configuration")
	static TArray<UConfigProperty* > Conv_ConfigPropertyArrayToConfigPropertyArray(UConfigPropertyArray* Property);
	
	/** Retrieves FString Array from PropertyArray */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CPArray To String Array", CompactNodeTitle = "[String]", BlueprintAutocast), Category = "SML | Configuration")
	static TArray<FString> Conv_ConfigPropertyArrayToStringArray(UConfigPropertyArray* Property);
	/** Retrieves Float Array from PropertyArray */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CPArray To Float Array", CompactNodeTitle = "[Float]", BlueprintAutocast), Category = "SML | Configuration")
	static TArray<float> Conv_ConfigPropertyArrayToFloatArray(UConfigPropertyArray* Property);
	/** Retrieves int32 Array from PropertyArray */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CPArray To Int Array", CompactNodeTitle = "[Int]", BlueprintAutocast), Category = "SML | Configuration")
	static TArray<int32> Conv_ConfigPropertyArrayToIntegerArray(UConfigPropertyArray* Property);
	/** Retrieves Bool Array from PropertyArray */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CPArray To Bool Array", CompactNodeTitle = "[Bool]", BlueprintAutocast), Category = "SML | Configuration")
	static TArray<bool> Conv_ConfigPropertyArrayToBoolArray(UConfigPropertyArray* Property);

	/** Retrieves UWidget from Property directly*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CP to Widget", CompactNodeTitle = "To Widget", BlueprintAutocast, DefaultToSelf = "ParentWidget", HidePin = "ParentWidget"), Category = "SML | Configuration")
	static UWidget* Conv_ConfigPropertyToWidget(UConfigProperty* Property, UObject* ParentWidget);
	/** Retrieves UserWidget from Property directly*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "CP to UserWidget", CompactNodeTitle = "To UWidget", BlueprintAutocast, DefaultToSelf = "ParentWidget", HidePin = "ParentWidget"), Category = "SML | Configuration")
	static UUserWidget* Conv_ConfigPropertyToUserWidget(UConfigProperty* Property, UObject* ParentWidget);
	
	/** Retrieves root configuration section value Property for provided configuration ID */
	UFUNCTION(BlueprintPure, Category = "SML | Configuration", meta = ( WorldContext = "WorldContext" ))
	static UConfigProperty* GetModConfigurationProperty( const FConfigId& ConfigId, UObject* WorldContext );

	/** Retrieves root configuration Property for provided configuration Class */
	UFUNCTION(BlueprintPure, Category = "SML | Configuration", meta = ( WorldContext = "WorldContext" ))
	static UConfigProperty* GetModConfigurationPropertyByClass(TSubclassOf<UModConfiguration> ConfigClass, UObject* WorldContext);

	/** Converts ModConfigClass to Configuration Root Property */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "MC to ConfigProperty", CompactNodeTitle = "To Instance", BlueprintAutocast, WorldContext = "WorldContext"), Category = "SML | Configuration")
	static UConfigProperty* Conv_ModConfigurationToConfigProperty(TSubclassOf<UModConfiguration> ConfigClass, UObject* WorldContext);
	
	/** Converts Config Id to Configuration Root Property */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ConfigId to ConfigProperty", CompactNodeTitle = "To Instance", BlueprintAutocast, WorldContext = "WorldContext"), Category = "SML | Configuration")
	static UConfigProperty* Conv_ConfigIdToConfigProperty(const FConfigId& ConfigId, UObject* WorldContext);

	/** Converts Config Id to Configuration Class */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ConfigId to Configuration Class", CompactNodeTitle = "To Config Class", BlueprintAutocast, WorldContext = "WorldContext"), Category = "SML | Configuration")
	static TSubclassOf<UModConfiguration> Conv_ConfigIdToModConfigurationClass(const FConfigId& ConfigId, UObject* WorldContext);

	/** Allows Widget creation from UObjects without (self)WorldContext. Widget as OwningObject required. */
	UFUNCTION(BlueprintCallable, Category = "Widget | Advanced")
	static UUserWidget* CreateSMLWidget(UUserWidget* OwningObject, TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName);

	/** Allows Font Editing. This needs to be called before PreConstruct. */
	UFUNCTION(BlueprintCallable, Category = "Widget | Advanced")
	static void SetSpinBoxFont(USpinBox* Box, FSlateFontInfo Font);

	/** Allows Font Editing. This needs to be called before PreConstruct. */
	UFUNCTION(BlueprintCallable, Category = "Widget | Advanced")
	static void SetComboBoxFont(UComboBoxString* Box, FSlateFontInfo Font);

	/**
	  * Allows Binding on BP (blueprint) Functions. Function must be implemented in Blueprint
	  * @param    Binding            Delegate to call when the function is called. In blueprint you usually want to hook this to an "Add Custom Event..."
	  * @param    HookOffsetStart    true to execute Binding before normal function body, false to execute after
	  */
	UFUNCTION(BlueprintCallable, Category= "Widget | Advanced")
	static void BindOnBPFunction(const TSubclassOf<UObject> Class, FObjFunctionBind Binding, const FString FunctionName, bool HookOffsetStart);
};

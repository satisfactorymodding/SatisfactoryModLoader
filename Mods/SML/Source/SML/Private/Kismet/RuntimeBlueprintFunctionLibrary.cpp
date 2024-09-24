#include "Kismet/RuntimeBlueprintFunctionLibrary.h"
#include "FGBlueprintFunctionLibrary.h"
#include "Configuration/RootConfigValueHolder.h"
#include "SatisfactoryModLoader.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Patching/BlueprintHookHelper.h"
#include "Patching/BlueprintHookManager.h"
#include "Settings/FGAdvancedGameSettings.h"

UClass* URuntimeBlueprintFunctionLibrary::FindClassByName(FString ClassNameInput) {
	// prevent crash from wrong user Input
	if (ClassNameInput.Len() == 0) {
		return nullptr;
	}
	const TCHAR* ClassName = *ClassNameInput;

	if (UClass* Result = FindObject<UClass>(ANY_PACKAGE, ClassName, false)) {
		return Result;
	}
	if (UObjectRedirector* RenamedClassRedirector = FindObject<UObjectRedirector>(ANY_PACKAGE, ClassName, true)) {
		return Cast<UClass>(RenamedClassRedirector->DestinationObject);
	}
	return nullptr;
}

bool URuntimeBlueprintFunctionLibrary::IsEditor() {
	return FPlatformProperties::HasEditorOnlyData();
}

FName URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyToName(UConfigProperty* Property) {
	return *Conv_ConfigPropertyToString(Property);
}

FText URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyToText(UConfigProperty* Property) {
	return FText::FromString(Conv_ConfigPropertyToString(Property));
}

FString URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyToString(UConfigProperty* Property) {
	if (Cast<UConfigPropertyString>(Property)) {
		UConfigPropertyString* Obj = Cast<UConfigPropertyString>(Property);
		return Obj->Value;
	}
	if (Cast<UConfigPropertyBool>(Property)) {
		UConfigPropertyBool* Obj = Cast<UConfigPropertyBool>(Property);
		return FString::FromInt(int32(Obj->Value));
	}
	if (Cast<UConfigPropertyFloat>(Property)) {
		UConfigPropertyFloat* Obj = Cast<UConfigPropertyFloat>(Property);
		return FString::SanitizeFloat(Obj->Value);
	}
	if (Cast<UConfigPropertyInteger>(Property)) {
		UConfigPropertyInteger* Obj = Cast<UConfigPropertyInteger>(Property);
		return FString::FromInt(int32(Obj->Value));
	}
	if (Cast<UConfigPropertyArray>(Property)) {
		return TEXT("Array");
	}
	if (Cast<UConfigPropertySection>(Property)) {
		return TEXT("Object");
	}
	return TEXT("Null");
};

float URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyToFloat(UConfigProperty* Property) {
	if (Cast<UConfigPropertyFloat>(Property)) {
		UConfigPropertyFloat* Obj = Cast<UConfigPropertyFloat>(Property);
		return Obj->Value;
	}
	if (Cast<UConfigPropertyBool>(Property)) {
		UConfigPropertyBool* Obj = Cast<UConfigPropertyBool>(Property);
		return float(int32(Obj->Value));
	}
	if (Cast<UConfigPropertyString>(Property)) {
		UConfigPropertyString* Obj = Cast<UConfigPropertyString>(Property);
		if (Obj->Value.IsNumeric()) {
			return FCString::Atof(*Obj->Value);
		}
	}
	if (Cast<UConfigPropertyInteger>(Property)) {
		UConfigPropertyInteger* Obj = Cast<UConfigPropertyInteger>(Property);
		return float(Obj->Value);
	}
	return 0.f;
}

int32 URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyToInteger(UConfigProperty* Property) {
	if (Cast<UConfigPropertyInteger>(Property)) {
		UConfigPropertyInteger* Obj = Cast<UConfigPropertyInteger>(Property);
		return Obj->Value;
	}
	if (Cast<UConfigPropertyFloat>(Property)) {
		UConfigPropertyFloat* Obj = Cast<UConfigPropertyFloat>(Property);
		return int32(Obj->Value);
	}
	if (Cast<UConfigPropertyBool>(Property)) {
		UConfigPropertyBool* Obj = Cast<UConfigPropertyBool>(Property);
		return int32(Obj->Value);
	}
	if (Cast<UConfigPropertyString>(Property)) {
		UConfigPropertyString* Obj = Cast<UConfigPropertyString>(Property);
		if (Obj->Value.IsNumeric()) {
			return int32(FCString::Atof(*Obj->Value));
		}
	}
	return 0;
}

bool URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyToBool(UConfigProperty* Property) {
	if (Cast<UConfigPropertyBool>(Property)) {
		UConfigPropertyBool* Obj = Cast<UConfigPropertyBool>(Property);
		return int32(Obj->Value);
	}
	if (Cast<UConfigPropertyInteger>(Property)) {
		UConfigPropertyInteger* Obj = Cast<UConfigPropertyInteger>(Property);
		return (bool)Obj->Value;
	}
	if (Cast<UConfigPropertyFloat>(Property)) {
		UConfigPropertyFloat* Obj = Cast<UConfigPropertyFloat>(Property);
		return Obj->Value != 0.0f;
	}
	if (Cast<UConfigPropertyString>(Property)) {
		UConfigPropertyString* Obj = Cast<UConfigPropertyString>(Property);
		if (Obj->Value.IsNumeric()) {
			return (bool)FCString::Atoi(*Obj->Value);
		}
		return Obj->Value == TEXT("true") || Obj->Value == TEXT("1");
	}
	return false;
};

float URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyFloatToFloat(UConfigPropertyFloat* Property) {
	return Property->Value;
};

int32 URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyIntegerToInteger(UConfigPropertyInteger* Property) {
	return Property->Value;
};

bool URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyBoolToBool(UConfigPropertyBool* Property) {
	return Property->Value;
};

FString URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyStringToString(UConfigPropertyString* Property) {
	return Property->Value;
};

UConfigProperty* URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertySectionToConfigProperty(UConfigPropertySection* Property, FString Key) {
	if (Property == NULL) {
		return nullptr;
	}
	UConfigProperty* const* Result = Property->SectionProperties.Find(Key);
	return Result ? *Result : NULL;
};

TArray<UConfigProperty*> URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyArrayToConfigPropertyArray(UConfigPropertyArray* Property) {
	if (Property == NULL) {
		return TArray<UConfigProperty*>();
	}
	return Property->Values;
};

TArray<FString> URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyArrayToStringArray(UConfigPropertyArray* Property) {
	TArray<FString> Out;
	if (Property)
		for (auto* i : Property->Values)
			Out.Add(Conv_ConfigPropertyToString(i));
	return Out;
};

TArray<float> URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyArrayToFloatArray(UConfigPropertyArray* Property) {
	TArray<float> Out;
	if (Property)
		for (auto* i : Property->Values)
			Out.Add(Conv_ConfigPropertyToFloat(i));
	return Out;
};

TArray<int32> URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyArrayToIntegerArray(UConfigPropertyArray* Property) {
	TArray<int32> Out;
	if (Property)
		for (auto* i : Property->Values)
			Out.Add(Conv_ConfigPropertyToInteger(i));
	return Out;
}

TArray<bool> URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyArrayToBoolArray(UConfigPropertyArray* Property) {
	TArray<bool> Out;
	if (Property)
		for (auto* i : Property->Values)
			Out.Add(Conv_ConfigPropertyToBool(i));
	return Out;
};

UWidget* URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyToWidget(UConfigProperty* Property, UObject* ParentWidget) {
	if (Property == NULL) {
		return NULL;
	}
	return Property->CreateEditorWidget(Cast<UUserWidget>(ParentWidget));
};

UUserWidget* URuntimeBlueprintFunctionLibrary::Conv_ConfigPropertyToUserWidget(UConfigProperty* Property, UObject* ParentWidget) {
	return Cast<UUserWidget>(Conv_ConfigPropertyToWidget(Property, ParentWidget));
};

UConfigProperty* URuntimeBlueprintFunctionLibrary::GetModConfigurationProperty( const FConfigId& ConfigId, UObject* WorldContext ) {

	if ( const UWorld* World = GEngine->GetWorldFromContextObject( WorldContext, EGetWorldErrorMode::ReturnNull ) )
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance()) {
			const UConfigManager* ConfigManager = GameInstance->GetSubsystem<UConfigManager>();
			const FRegisteredConfigurationData* ConfigurationData = ConfigManager->Configurations.Find(ConfigId);
			if (!ConfigurationData) {
				return nullptr;
			}
			return ConfigurationData->RootValue->GetWrappedValue();
		}
	}
	return nullptr;
};

UConfigProperty* URuntimeBlueprintFunctionLibrary::GetModConfigurationPropertyByClass(TSubclassOf<UModConfiguration> ConfigClass, UObject* WorldContext) {
	if (ConfigClass == NULL) {
		return nullptr;
	}
	if ( UWorld* World = GEngine->GetWorldFromContextObject( WorldContext, EGetWorldErrorMode::ReturnNull ) )
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance()) {
			UConfigManager* ConfigManager = GameInstance->GetSubsystem<UConfigManager>();
#if WITH_EDITOR
			// Assuming we have not registered in Editor World or similiar
			// But also considering this might work in the Editor once someone emulates the Startup Registration on PIE Play
			// we check only in Editor if Configurations are Empty. 
			// Editor Widgets that are used while not in PIE dont have proper World Context.
			// For this Function to work regardless on Play State in Editor
			// This Function "Simulates" it being where it would be inGame
			// This return is for Comsetic and visual pre-display only 
			// while also allowing modification of Default Values.
			if (ConfigManager->Configurations.Num() == 0) {
				return ConfigClass.GetDefaultObject()->RootSection;
			}
#endif
			for (auto i : ConfigManager->Configurations) {
				if (i.Value.ConfigurationClass == ConfigClass) {
					return i.Value.RootValue->GetWrappedValue();
				}
			}
		} else {
#if WITH_EDITOR
			// Editor Widgets that are used while not in PIE don't have proper World Context.
			return ConfigClass.GetDefaultObject()->RootSection;
#endif
		}
	}
	return NULL;
};

UConfigProperty* URuntimeBlueprintFunctionLibrary::Conv_ModConfigurationToConfigProperty( TSubclassOf<UModConfiguration> ConfigClass, UObject* WorldContext) {
	return GetModConfigurationPropertyByClass(ConfigClass, WorldContext);
}

UConfigProperty* URuntimeBlueprintFunctionLibrary::Conv_ConfigIdToConfigProperty(const FConfigId& ConfigId, UObject* WorldContext) {
	return GetModConfigurationProperty(ConfigId, WorldContext);
}

TSubclassOf<UModConfiguration> URuntimeBlueprintFunctionLibrary::Conv_ConfigIdToModConfigurationClass(const FConfigId& ConfigId, UObject* WorldContext) {
	if ( UWorld* World = GEngine->GetWorldFromContextObject( WorldContext, EGetWorldErrorMode::ReturnNull ) )
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance()) {
			UConfigManager* ConfigManager = GameInstance->GetSubsystem<UConfigManager>();
			const FRegisteredConfigurationData* ConfigurationData = ConfigManager->Configurations.Find(ConfigId);
			if (ConfigurationData == nullptr)
			{
				return nullptr;
			}
			return ConfigurationData->ConfigurationClass;
		}
	}
	return nullptr;
}

UUserWidget* URuntimeBlueprintFunctionLibrary::CreateSMLWidget(UUserWidget* OwningObject, TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName) {
	SCOPE_CYCLE_COUNTER(STAT_CreateWidget);
	if (OwningObject) {
		return Cast<UUserWidget>(UUserWidget::CreateWidgetInstance(*OwningObject, UserWidgetClass, WidgetName));
	}
	return nullptr;
}

void URuntimeBlueprintFunctionLibrary::SetSpinBoxFont(USpinBox* Box, FSlateFontInfo Font) {
	if (Box) {
		Box->Font = Font;
	}
}

void URuntimeBlueprintFunctionLibrary::SetComboBoxFont(UComboBoxString* Box, FSlateFontInfo Font) {
	if (Box) {
		Box->Font = Font;
	}
}

void URuntimeBlueprintFunctionLibrary::BindOnBPFunction(const TSubclassOf<UObject> Class, FObjFunctionBind Binding, const FString FunctionName, bool bHookOffsetStart) {
	if (Class == NULL) {
		UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Failed to bind on Blueprint Function '%s': Class is null"), *FunctionName);
		return;
	}
	UFunction* Function = Class->FindFunctionByName(*FunctionName);
	if (Function == NULL) {
		UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Failed to bind on Blueprint Function '%s' of class '%s': Function does not exist"), *FunctionName, *Class->GetPathName());
		return;
	}
	if (Function->IsNative()) {
		UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Failed to bind on Blueprint Function '%s' of class '%s': Function is native"), *FunctionName, *Class->GetPathName());
		return;
	}
	const EPredefinedHookOffset Offset = bHookOffsetStart ? EPredefinedHookOffset::Start : EPredefinedHookOffset::Return;
	UBlueprintHookManager* HookManager = GEngine->GetEngineSubsystem<UBlueprintHookManager>();

	HookManager->HookBlueprintFunction(Function, [Binding](const FBlueprintHookHelper& HookHelper) {
		Binding.ExecuteIfBound(HookHelper.GetContext());
	}, Offset);
}

#pragma once
#include "ModLoading/ModInfo.h"
#include "CoreMinimal.h"
#include "ReflectionHelper.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBlueprintLegacy, Verbose, Verbose);

UCLASS()
class SML_API USMLBlueprintLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Mod Loading -> Is Mod Loaded"))
	static bool IsModLoaded(const FString& ModReference);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Mod Loading -> Get Loaded Mods"))
	static TArray<FString> GetLoadedMods();

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Mod Loading -> Get Loaded Mod Info"))
	static FModInfo GetLoadedModInfo(const FString& ModReference);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Logging functions instead"))
	static void LogDebug(const FString& Str, bool bIgnoreDebugMode = false);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Logging functions instead"))
    static void LogInfo(const FString& Str);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Logging functions instead"))
	static void LogWarning(const FString& Str);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Logging functions instead"))
	static void LogError(const FString& Str);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Logging functions instead"))
	static void LogFatal(const FString& Str);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Mod Loading -> Get SML Version"))
	static FVersion GetSMLVersion();

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Mod Loading -> Get Extra Mod Loader Attributes"))
	static FVersion GetBootstrapperVersion();

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta = (DeprecatedFunction, DeprecationMessage = "Use SML|Mod Loading -> Is Development Mode Enabled"))
	static bool GetDevelopmentModeEnabled();
	
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Config", DeprecatedFunction, DeprecatedMessage = "Use new SML configuration system"))
	static void SaveConfig(const FString& ModReference, const FDynamicStructInfo& Config);

	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Config", DeprecatedFunction, DeprecatedMessage = "Use new SML configuration system"))
	static void LoadConfig(const FString& ModReference, UPARAM(ref) const FDynamicStructInfo& Config);

	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Struct", DeprecatedFunction, DeprecatedMessage = "Use new SML configuration system"))
    static void StructToJson(UPARAM(ref) FString& String, bool bUsePrettyPropertyNames, const FDynamicStructInfo& Struct);

	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Struct", DeprecatedFunction, DeprecatedMessage = "Use new SML configuration system"))
	static void StructFromJson(const FString& String, bool bUsePrettyPropertyNames, UPARAM(ref) const FDynamicStructInfo& Struct);

public:
	DECLARE_FUNCTION(execSaveConfig) {
		P_GET_PROPERTY(UStrProperty, ModReference);
		const FDynamicStructInfo StructInfo = FReflectionHelper::CheckStructParameter(Context, Stack);
		P_FINISH;
		if (StructInfo.Struct) {
			SaveConfig(ModReference, StructInfo);
		}
	}

	DECLARE_FUNCTION(execLoadConfig) {
		P_GET_PROPERTY(UStrProperty, ModReference);
		const FDynamicStructInfo StructInfo = FReflectionHelper::CheckStructParameter(Context, Stack);
		P_FINISH;
		if (StructInfo.Struct) {
			LoadConfig(ModReference, StructInfo);
		}
	}

	DECLARE_FUNCTION(execStructToJson) {
		P_GET_PROPERTY_REF(UStrProperty, OutJsonString);
		P_GET_PROPERTY(UBoolProperty, bUsePrettyPropertyNames);
		const FDynamicStructInfo StructInfo = FReflectionHelper::CheckStructParameter(Context, Stack);
		P_FINISH;
		if (StructInfo.Struct) {
			StructToJson(OutJsonString, bUsePrettyPropertyNames, StructInfo);
		}
	}
	
	DECLARE_FUNCTION(execStructFromJson) {
		P_GET_PROPERTY(UStrProperty, InJsonString);
		P_GET_PROPERTY(UBoolProperty, bUsePrettyPropertyNames);
		const FDynamicStructInfo StructInfo = FReflectionHelper::CheckStructParameter(Context, Stack);
		P_FINISH;
		if (StructInfo.Struct) {
			StructFromJson(InJsonString, bUsePrettyPropertyNames, StructInfo);
		}
	}
};

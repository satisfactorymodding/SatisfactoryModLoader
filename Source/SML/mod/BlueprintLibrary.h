#pragma once

#include "mod/ModInfo.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SML/util/Utility.h"
#include "BlueprintLibrary.generated.h"

UCLASS()
class SML_API USMLBlueprintLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	static TSharedPtr<FJsonValue> ConvertUPropToJsonValue(UProperty* Prop, void* PtrToProp);
	static TSharedPtr<FJsonObject> ConvertUStructToJsonObject(UStruct* Struct, void* PtrToStruct, bool UsePrettyName = true);
	static void ConvertJsonObjectToUStruct(TSharedPtr<FJsonObject> Json, UStruct* Struct, void* PtrToStruct, bool UsePrettyName = true);
	static void ConvertJsonValueToUProperty(TSharedPtr<FJsonValue> Json, UProperty* Prop, void* PtrToProp);

	/** Constructs sem version from version string */
	UFUNCTION(BlueprintPure, Category = "SML|Version")
    static FVersion ParseVersionString(const FString& String);

	/** Converts version data to the string */
	UFUNCTION(BlueprintPure, Category = "SML|Version", meta = (DisplayName = "ToString (Version)", CompactNodeTitle = "->", ScriptMethod="ToString"))
	static FString Conv_VersionToString(const FVersion& Version);
	
	/** Returns true when mod with provided ModId is loaded */
	UFUNCTION(BlueprintPure, Category = "SML|ModLoading")
	static bool IsModLoaded(const FString& ModId);

	/** Returns list of loaded mods (their ModIds actually) */
	UFUNCTION(BlueprintPure, Category = "SML|ModLoading")
	static const TArray<FString>& GetLoadedMods();

	/** Retrieves information about loaded mod by it's ModId. Returns empty struct if mod is not loaded */
	UFUNCTION(BlueprintPure, Category = "SML|ModLoading")
	static FModInfo GetLoadedModInfo(const FString& ModId);

	/** Tries to load mod icon and returns pointer to the loaded texture, or FallbackIcon if icon cannot be loaded */
	UFUNCTION(BlueprintCallable, Category = "SML|ModLoading")
	static UTexture2D* LoadModIconTexture(const FString& ModId, UTexture2D* FallbackIcon);
	
	/**
	 * Logs the given string in debug level to the SML Log file and the game log as well as into the console
	 * @param str - the string you want to log
	 * @param ignoreDebugMode - if set to true, forces the string to get logged, else it wont get logged if debug mode is not enabled
	 */
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 1), Category = "SML|Logging")
	static void LogDebug(const FString& str, bool ignoreDebugMode = false);

	/**
	* Logs the given string in info level to the SML Log file and the game log as well as into the console
	* @param str - the string you want to log
	*/
	UFUNCTION(BlueprintCallable, Category = "SML|Logging")
    static void LogInfo(const FString& str);
	
	/**
	 * Logs the given string in warning level to the SML Log file and the game log as well as into the console
	 * @param str - the string you want to log
	 */
	UFUNCTION(BlueprintCallable, Category = "SML|Logging")
	static void LogWarning(const FString& str);

	/**
	 * Logs the given string in error level to the SML Log file and the game log as well as into the console
	 * @param str - the string you want to log
	 */
	UFUNCTION(BlueprintCallable, Category = "SML|Logging")
	static void LogError(const FString& str);

	/**
	 * Logs the given string in fatal level to the SML Log file and the game log as well as into the console
	 * @param str - the string you want to log
	 */
	UFUNCTION(BlueprintCallable, Category = "SML|Logging")
	static void LogFatal(const FString& str);

	/**
	 * Returns the currently used SML version
	 */
	UFUNCTION(BlueprintPure, Category = "SML|Version")
	static FVersion GetSMLVersion();

	/**
	 * Returns the currently used bootstrapper version
	 */
	UFUNCTION(BlueprintPure, Category = "SML|Version")
	static FVersion GetBootstrapperVersion();

	/**
	 * Returns the currently used DevelopmentMode Setting
	 */
	UFUNCTION(BlueprintPure, Category = "SML|Development")
	static bool GetDevelopmentModeEnabled();

	/**
	 * Saves the given struct as config file for the given modid
	 * @param modid - the modid you want to save to config for
	 * @param Config - the struct you want to save as config
	 */
	UFUNCTION(BlueprintCallable, Category = "SML|Config", CustomThunk, meta = (CustomStructureParam = "Config"))
	static void SaveConfig(const FString& modid, UProperty* Config);

	/**
	 * Loads the config for the given modid to the given struct.
	 * Additional config entries not mapped to the struct are just ignored.
	 * Additional struct attributes not contained in the config files just wont change the attribute in the struct.
	 * This allows for using default values, by simply setting the attributes of the struct to the default values, before you pass it to the function.
	 * @param modid - the modid of the config you want to load
	 * @param Config - the struct you want to use as default values and were to copy the loaded config values to
	 */
	UFUNCTION(BlueprintCallable, Category = "SML|Config", CustomThunk, meta = (CustomStructureParam = "Config"))
	static void LoadConfig(const FString& modid, UPARAM(ref) UProperty*& Config);

	UFUNCTION(BlueprintCallable, Category = "SML|Config", CustomThunk, meta = (CustomStructureParam = "Structure"))
    static void StructToJson(UPARAM(ref) FString& String, bool UsePrettyPropertyNames, UProperty* Structure);

	UFUNCTION(BlueprintCallable, Category = "SML|Config", CustomThunk, meta = (CustomStructureParam = "Structure"))
	static void StructFromJson(const FString& String, bool UsePrettyPropertyNames, UPARAM(ref) UProperty*& Structure);

private:
	static FORCEINLINE bool CheckStructParameter(UObject* Context, FFrame& Stack) {
		Stack.MostRecentProperty = NULL;
		Stack.MostRecentPropertyAddress = NULL;
		Stack.StepCompiledIn<UStructProperty>(NULL);

		UStructProperty* StructProperty = Cast<UStructProperty>(Stack.MostRecentProperty);
		if (StructProperty == NULL) {
			const FBlueprintExceptionInfo ExceptionInfo(EBlueprintExceptionType::AccessViolation,
				INVTEXT("SML: BlueprintLibrary: Tried to serialize non-struct object. Only structs are supported"));
			FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
			return false;
		}
		
		if (Stack.MostRecentPropertyAddress == NULL) {
			const FBlueprintExceptionInfo ExceptionInfo(EBlueprintExceptionType::AccessViolation,
				INVTEXT("SML: BlueprintLibrary: Tried to serialize NULL struct"));
			FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
			return false;
		}
		return true;
	}
public:
	
	DECLARE_FUNCTION(execSaveConfig) {
		FString ModId;
		Stack.StepCompiledIn<UStrProperty>(&ModId);
		const bool StructCorrect = CheckStructParameter(Context, Stack);
		UStructProperty* StructProperty = Cast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;
		if (StructCorrect && StructProperty && StructPtr) {
			const TSharedPtr<FJsonObject> Config = ConvertUStructToJsonObject(StructProperty->Struct, StructPtr);
			SML::WriteModConfig(ModId, Config.ToSharedRef());
		}
	}

	DECLARE_FUNCTION(execLoadConfig) {
		FString ModId;
		Stack.StepCompiledIn<UStrProperty>(&ModId);
		const bool StructCorrect = CheckStructParameter(Context, Stack);
		UStructProperty* StructProperty = Cast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;
		if (StructCorrect && StructProperty && StructPtr) {
			TSharedPtr<FJsonObject> Config = ConvertUStructToJsonObject(StructProperty->Struct, StructPtr);
			Config = SML::ReadModConfig(ModId, Config.ToSharedRef());
			ConvertJsonObjectToUStruct(Config, StructProperty->Struct, StructPtr);
		}
	}

	DECLARE_FUNCTION(execStructToJson) {
		Stack.MostRecentPropertyAddress = NULL;
		Stack.StepCompiledIn<UStrProperty>(NULL);
		FString* OutStructString = reinterpret_cast<FString*>(Stack.MostRecentPropertyAddress);
		bool bUsePrettyPropertyNames;
		Stack.StepCompiledIn<UBoolProperty>(&bUsePrettyPropertyNames);
		
		const bool StructCorrect = CheckStructParameter(Context, Stack);
		UStructProperty* StructProperty = Cast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;
		
		if (OutStructString == NULL) {
			const FBlueprintExceptionInfo ExceptionInfo(EBlueprintExceptionType::AccessViolation,
				INVTEXT("SML: BlueprintLibrary: Tried to serialize struct to NULL string"));
			FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
			return;
		}
		if (StructCorrect && StructProperty && StructPtr) {
			InternalGetStructAsJson(StructProperty, StructPtr, *OutStructString, bUsePrettyPropertyNames);
		}
	}
	
	static void InternalGetStructAsJson(UStructProperty *Structure, void * StructurePtr, FString &String, bool UsePretty = false);

	DECLARE_FUNCTION(execStructFromJson) {
		FString SourceJsonString;
		Stack.StepCompiledIn<UStrProperty>(&SourceJsonString);
		bool bUsePrettyPropertyNames;
		Stack.StepCompiledIn<UBoolProperty>(&bUsePrettyPropertyNames);
		
		const bool StructCorrect = CheckStructParameter(Context, Stack);
		UStructProperty* StructProperty = Cast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		P_FINISH;

		if (StructCorrect && StructProperty && StructPtr) {
			const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(SourceJsonString);
			FJsonSerializer Serializer;
			TSharedPtr<FJsonObject> Result;
			Serializer.Deserialize(Reader, Result);
			ConvertJsonObjectToUStruct(Result, StructProperty->Struct, StructPtr, bUsePrettyPropertyNames);
		}
	}
};

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SML/util/Utility.h"
#include "BlueprintLibrary.generated.h"

UCLASS()
class USMLBlueprintLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	static TSharedPtr<FJsonValue> convertUPropToJsonValue(UProperty* prop, void* ptrToProp);
	static TSharedPtr<FJsonObject> convertUStructToJsonObject(UStruct* Struct, void* ptrToStruct, bool UsePrettyName = true);
	static void convertJsonObjectToUStruct(TSharedPtr<FJsonObject> json, UStruct* Struct, void* ptrToStruct, bool UsePrettyName = true);
	static void convertJsonValueToUProperty(TSharedPtr<FJsonValue> json, UProperty* prop, void* ptrToProp);

	/**
	 * Logs the given string in debug level to the SML Log file and the game log as well as into the console
	 * @param str - the string you want to log
	 * @param ignoreDebugMode - if set to true, forces the string to get logged, else it wont get logged if debug mode is not enabled
	 */
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 1), Category = "SML|Logging")
	static void LogDebug(const FString& str, bool ignoreDebugMode = false);

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
	UFUNCTION(BlueprintCallable, Category = "SML")
	static FString GetSMLVersion();

	/**
	 * Returns the currently used bootstrapper version
	 */
	UFUNCTION(BlueprintCallable, Category = "SML")
	static FString GetBootstrapperVersion();

	/**
	 * Saves the given struct as config file for the given modid
	 * @param modid - the modid you want to save to config for
	 * @param Config - the struct you want to save as config
	 */
	UFUNCTION(BlueprintCallable, Category = "SML", CustomThunk, meta = (CustomStructureParam = "Config"))
	static void SaveConfig(const FString& modid, UProperty* Config);


	/**
	 * Loads the config for the given modid to the given struct.
	 * Additional config entries not mapped to the struct are just ignored.
	 * Additional struct attributes not contained in the config files just wont change the attribute in the struct.
	 * This allows for using default values, by simply setting the attributes of the struct to the default values, before you pass it to the function.
	 * @param modid - the modid of the config you want to load
	 * @param Config - the struct you want to use as default values and were to copy the loaded config values to
	 */
	UFUNCTION(BlueprintCallable, Category = "SML", CustomThunk, meta = (CustomStructureParam = "Config"))
	static void LoadConfig(const FString& modid, UPARAM(ref) UProperty*& Config);

	DECLARE_FUNCTION(execSaveConfig) {
		FString modid;
		Stack.StepCompiledIn<UStrProperty>(&modid);
		Stack.Step(Stack.Object, NULL);
	
		UStructProperty* Struct = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		TSharedPtr<FJsonObject> config = convertUStructToJsonObject(Struct->Struct, StructPtr);
		
		SML::writeModConfig(modid, config.ToSharedRef());
	}

	DECLARE_FUNCTION(execLoadConfig) {
		FString modid;
		Stack.StepCompiledIn<UStrProperty>(&modid);
		Stack.Step(Stack.Object, NULL);

		UStructProperty* Struct = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		TSharedPtr<FJsonObject> config = convertUStructToJsonObject(Struct->Struct, StructPtr);
		
		config = SML::readModConfig(modid, config.ToSharedRef());

		convertJsonObjectToUStruct(config, Struct->Struct, StructPtr);
	}

	UFUNCTION(BlueprintCallable, Category = "SML", CustomThunk, meta = (CustomStructureParam = "Structure"))
		static void GetStructAsJson(UPARAM(ref)FString &String, bool  UsePretty, UProperty *Structure);

	DECLARE_FUNCTION(execGetStructAsJson)
	{
		bool UsePretty;

		PARAM_PASSED_BY_REF(String, UStrProperty, FString);
		Stack.StepCompiledIn<UBoolProperty>(&UsePretty);
		Stack.Step(Stack.Object, NULL);

		UStructProperty* StructureProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);

		void* StructurePtr = Stack.MostRecentPropertyAddress;

		P_FINISH;
		InternalGetStructAsJson(StructureProperty, StructurePtr, String, UsePretty);
	}
	static void InternalGetStructAsJson(UStructProperty *Structure, void * StructurePtr, FString &String, bool UsePretty = false);


	UFUNCTION(BlueprintCallable, Category = "SML", CustomThunk, meta = (CustomStructureParam = "Structure"))
		static void StructfromJson(const FString& String,  bool UsePrety, UPARAM(ref) UProperty*& Structure);

	DECLARE_FUNCTION(execStructfromJson) {
		FString String;
		bool UsePretty;
		Stack.StepCompiledIn<UStrProperty>(&String);
		Stack.StepCompiledIn<UBoolProperty>(&UsePretty);
		Stack.Step(Stack.Object, NULL);

		UStructProperty* Struct = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(*String);
		FJsonSerializer Serializer;
		TSharedPtr<FJsonObject> result;
		Serializer.Deserialize(reader, result);
		convertJsonObjectToUStruct(result, Struct->Struct, StructPtr, UsePretty);
	}
};

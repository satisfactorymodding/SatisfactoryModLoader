#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintReflectedObject.h"
#include "ReflectionHelper.h"
#include "BlueprintReflectionLibrary.generated.h"

UCLASS()
class SML_API UBlueprintReflectionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /** Allocates reflected object wrapper for given object */
    UFUNCTION(BlueprintPure, Category = "Reflection")
    static FReflectedObject ReflectObject(UObject* Object);

    /** Allocates reflected object wrapper for given struct value */
    UFUNCTION(BlueprintPure, Category = "Reflection", CustomThunk)
    static FReflectedObject ReflectStruct(const FDynamicStructInfo& StructInfo);

    /** Deflects reflected object into the raw UObject* pointer */
    UFUNCTION(BlueprintPure, Category = "Reflection")
    static UObject* DeflectObject(const FReflectedObject& ReflectedObject);

    /** Deflects reflected object into the passed struct out variable */
    UFUNCTION(BlueprintCallable, Category = "Reflection", CustomThunk)
    static void DeflectStruct(const FReflectedObject& ReflectedObject, UPARAM(Ref) const FDynamicStructInfo& StructInfo);

    /** Returns a list of reflected properties for provided object */
    UFUNCTION(BlueprintPure, Category = "Reflection")
    static TArray<FReflectedPropertyInfo> GetReflectedProperties(const FReflectedObject& ReflectedObject);

    /** Retrieves a value of byte property */
    UFUNCTION(BlueprintPure, Category = "Reflection")
    static uint8 GetByteProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex = 0);

    /** Updates a value of byte property */
    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetByteProperty(const FReflectedObject& ReflectedObject, FName PropertyName, uint8 Value, int32 ArrayIndex = 0);

    /** Retrieves a value of 64-bit signed integer */
    UFUNCTION(BlueprintPure, Category = "Reflection")
    static int64 GetInt64Property(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex = 0);

    /** Updates a value of 64-bit signed integer variable */
    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetInt64Property(const FReflectedObject& ReflectedObject, FName PropertyName, int64 Value, int32 ArrayIndex = 0);
    
    /** Retrieves a value of 32-bit signed integer */
    UFUNCTION(BlueprintPure, Category = "Reflection")
    static int32 GetInt32Property(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex = 0);

    /** Updates a value of 32-bit signed integer variable */
    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetInt32Property(const FReflectedObject& ReflectedObject, FName PropertyName, int32 Value, int32 ArrayIndex = 0);

    /** Retrieves a value of floating point variable from object */
    UFUNCTION(BlueprintPure, Category = "Reflection")
    static float GetFloatProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex = 0);

    /** Updates a value of floating point property on reflected object */
    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetFloatProperty(const FReflectedObject& ReflectedObject, FName PropertyName, float Value, int32 ArrayIndex = 0);

    /** Retrieves a value of string variable on reflected object */
    UFUNCTION(BlueprintPure, Category = "Reflection")
    static FString GetStringProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex = 0);

    /** Updates a value of string variable on passed object */
    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetStringProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FString& Value, int32 ArrayIndex = 0);

    /** Retrieves boolean property value from reflected object */
    UFUNCTION(BlueprintPure, Category = "Reflection")
    static bool GetBoolProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex = 0);

    /** Updates a value of boolean property on reflected object */
    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetBoolProperty(const FReflectedObject& ReflectedObject, FName PropertyName, bool Value, int32 ArrayIndex = 0);

    /** Retrieves a value of name property from reflected object */
    UFUNCTION(BlueprintPure, Category = "Reflection")
    static FName GetNameProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex = 0);

    /** Updates a value of name property on reflected object */
    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetNameProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FName& Name, int32 ArrayIndex = 0);

    UFUNCTION(BlueprintPure, Category = "Reflection")
    static FText GetTextProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex = 0);

    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetTextProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FText& Text, int32 ArrayIndex = 0);

    UFUNCTION(BlueprintPure, Category = "Reflection")
    static UObject* GetObjectProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex = 0);

    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetObjectProperty(const FReflectedObject& ReflectedObject, FName PropertyName, UObject* Object, int32 ArrayIndex = 0);

    UFUNCTION(BlueprintPure, Category = "Reflection")
    static FReflectedObject GetStructProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex = 0);

    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetStructProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FReflectedObject& Struct, int32 ArrayIndex = 0);

    UFUNCTION(BlueprintPure, Category = "Reflection")
    static FReflectedEnumValue GetEnumProperty(const FReflectedObject& ReflectedObject, FName PropertyName);

    UFUNCTION(BlueprintCallable, Category = "Reflection")
    static void SetEnumProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FReflectedEnumValue& Enum);

    DECLARE_FUNCTION(execDeflectStruct) {
        P_GET_STRUCT(FReflectedObject, ReflectedObject);
        const FDynamicStructInfo StructInfo = FReflectionHelper::CheckStructParameter(Context, Stack);
        P_FINISH;
        if (StructInfo.Struct != NULL) {
            const FBlueprintExceptionInfo ExceptionInfo(EBlueprintExceptionType::AccessViolation,
              INVTEXT("Tried to pass NULL struct to DeflectStruct"));
            FBlueprintCoreDelegates::ThrowScriptException(Context, Stack, ExceptionInfo);
            return;
        }
        DeflectStruct(ReflectedObject, StructInfo);
    }

    DECLARE_FUNCTION(execReflectStruct) {
        const FDynamicStructInfo StructInfo = FReflectionHelper::CheckStructParameter(Context, Stack);
        P_FINISH;
        if (StructInfo.Struct != NULL) {
            const FBlueprintExceptionInfo ExceptionInfo(EBlueprintExceptionType::AccessViolation,
              INVTEXT("Tried to pass NULL struct to ReflectStruct"));
            FBlueprintCoreDelegates::ThrowScriptException(Context, Stack, ExceptionInfo);
            return;
        }
        FReflectedObject ReflectedObject = ReflectStruct(StructInfo);
        *(FReflectedObject*)RESULT_PARAM = ReflectedObject;
    }
};

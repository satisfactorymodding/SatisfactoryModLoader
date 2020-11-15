#pragma once
#include "CoreMinimal.h"
#include "BlueprintReflectedObject.generated.h"

class SML_API FReflectedObjectState {
public:
    virtual ~FReflectedObjectState() = default;

    virtual void CopyStructValue(UScriptStruct* StructType, void* StructValue) const = 0;
    virtual UObject* GetObjectPointer() const = 0;
    virtual bool ShouldStripPropertyNames() const = 0;
    virtual UStruct* GetStructObject() const = 0;
    virtual void* GetObjectData() = 0;
    virtual void AddReferencedObjects(FReferenceCollector& ReferenceCollector) = 0;
};

/** Describes type of the reflected property */
UENUM(BlueprintType)
enum class EReflectedPropertyType : uint8 {
    ERPT_Invalid UMETA(DisplayName = "Invalid"),
    ERPT_Byte UMETA(DisplayName = "Byte"),
    ERPT_Int32 UMETA(DisplayName = "Int"),
    ERPT_Int64 UMETA(DisplayName = "Int64"),
    ERPT_Float UMETA(DisplayName = "Float"),
    ERPT_String UMETA(DisplayName = "String"),
    ERPT_Bool UMETA(DisplayName = "Boolean"),
    ERPT_Name UMETA(DisplayName = "Name"),
    ERPT_Text UMETA(DisplayName = "Text"),
    ERPT_Struct UMETA(DisplayName = "Struct"),
    ERPT_Object UMETA(DisplayName = "Object"),
    ERPT_Enum UMETA(DisplayName = "Enum")
    //TODO interface support?
};

/** Describes a single reflected property accessible to blueprints */
USTRUCT(BlueprintType)
struct SML_API FReflectedPropertyInfo {
    GENERATED_BODY()
public:
    /** Name of the reflected property */
    UPROPERTY(BlueprintReadOnly)
    FName PropertyName;

    /** Type of the reflected property */
    UPROPERTY(BlueprintReadOnly)
    EReflectedPropertyType PropertyType;

    /** Dimensions of the fixed-size property array */
    UPROPERTY(BlueprintReadOnly)
    int32 ArrayDim;
};

/** Describes reflected enumeration value */
USTRUCT(BlueprintType)
struct SML_API FReflectedEnumValue {
    GENERATED_BODY()
public:
    FReflectedEnumValue();
    FReflectedEnumValue(UEnum* EnumType, int64 EnumValue);
    
    int64 GetCurrentValue() const;
    void SetCurrentValue(int64 NewValue);
    UEnum* GetEnumerationType() const;
private:
    UPROPERTY()
    UEnum* EnumerationType;
    /** Raw enumeration value represented as integer */
    UPROPERTY()
    int64 RawEnumValue;
};

/** Describes a reflected object such as script struct or UObject with a set of associated properties */
USTRUCT(BlueprintType)
struct SML_API FReflectedObject {
    GENERATED_BODY()
public:
    /** Setups state of this object from passed UObject pointer */
    void SetupFromUObject(UObject* Object);
    
    /** Setups state of this object from passed struct type and data */
    void SetupFromStruct(UScriptStruct* StructType, const void* StructData = NULL);

    /** Returns pointer to the wrapped object, if it's an object wrapper */
    UObject* GetWrappedObject() const;

    /** Copies wrapped struct value into the output struct */
    void CopyWrappedStruct(UScriptStruct* StructType, void* StructValue) const;

    template<typename T>
    FORCEINLINE void CopyWrappedStruct(T& OutStruct) const {
        CopyWrappedStruct(T::StaticStruct(), &OutStruct);
    }
    
    /** Returns a list of all reflected properties exposed by this object */
    TArray<FReflectedPropertyInfo> GetReflectedProperties() const;
    
    //Begin UProperty accessors
    uint8 GetByteProperty(FName PropertyName, int32 ArrayIndex = 0) const;
    void SetByteProperty(FName PropertyName, uint8 Value, int32 ArrayIndex = 0) const;
    
    int32 GetInt32Property(FName PropertyName, int32 ArrayIndex = 0) const;
    void SetInt32Property(FName PropertyName, int32 Value, int32 ArrayIndex = 0) const;

    int64 GetInt64Property(FName PropertyName, int32 ArrayIndex = 0) const;
    void SetInt64Property(FName PropertyName, int64 Value, int32 ArrayIndex = 0) const;
    
    float GetFloatProperty(FName PropertyName, int32 ArrayIndex = 0) const;
    void SetFloatProperty(FName PropertyName, float Value, int32 ArrayIndex = 0) const;
    
    FString GetStringProperty(FName PropertyName, int32 ArrayIndex = 0) const;
    void SetStringProperty(FName PropertyName, const FString& Value, int32 ArrayIndex = 0) const;

    bool GetBoolProperty(FName PropertyName, int32 ArrayIndex = 0) const;
    void SetBoolProperty(FName PropertyName, bool Value, int32 ArrayIndex = 0) const;

    FName GetNameProperty(FName PropertyName, int32 ArrayIndex = 0) const;
    void SetNameProperty(FName PropertyName, const FName& Name, int32 ArrayIndex = 0) const;

    FText GetTextProperty(FName PropertyName, int32 ArrayIndex = 0) const;
    void SetTextProperty(FName PropertyName, const FText& Text, int32 ArrayIndex = 0) const;

    UObject* GetObjectProperty(FName PropertyName, int32 ArrayIndex = 0) const;
    void SetObjectProperty(FName PropertyName, UObject* Object, int32 ArrayIndex = 0) const;

    FReflectedObject GetStructProperty(FName PropertyName, int32 ArrayIndex = 0) const;
    void SetStructProperty(FName PropertyName, const FReflectedObject& Struct, int32 ArrayIndex = 0) const;

    template<typename T>
    FORCEINLINE void SetStructProperty(FName PropertyName, const T& StructPtr) {
        FReflectedObject ReflectedObject{};
        ReflectedObject.SetupFromStruct(T::StaticStruct(), &StructPtr);
        SetStructProperty(PropertyName, ReflectedObject);
    }

    FReflectedEnumValue GetEnumProperty(FName PropertyName) const;
    void SetEnumProperty(FName PropertyName, const FReflectedEnumValue& Enum) const;
    //End UProperty accessors

    /** Exposes references to GC system */
    void AddStructReferencedObjects(class FReferenceCollector& Collector) const;

    FORCEINLINE UStruct* GetStruct() const { return State.IsValid() ? State->GetStructObject() : NULL; }
private:
    /** Finds a property with a given short name and verifies that it is blueprint readable/writeable */
    UProperty* FindProperty(FName PropertyName, bool bCheckForWriteable) const;

    FORCEINLINE bool ShouldStripNames() const { return State.IsValid() ? State->ShouldStripPropertyNames() : false; }
    FORCEINLINE void* GetObjectData() const { return State.IsValid() ? State->GetObjectData() : NULL; }
    FORCEINLINE static bool IsValidIndex(int32 Index, int32 ArrayDim) { return Index >= 0 && Index < ArrayDim; }
    
    TSharedPtr<FReflectedObjectState> State;
};

template<>
struct SML_API TStructOpsTypeTraits<FReflectedObject> : public TStructOpsTypeTraitsBase2<FReflectedObject> {
    enum {
        WithCopy = true,
        WithAddStructReferencedObjects = true,
    };
};

class SML_API FReflectedObjectState_UObject : public FReflectedObjectState {
    public:
        FReflectedObjectState_UObject(UObject* Object);

    virtual void CopyStructValue(UScriptStruct* StructType, void* StructValue) const override;
    virtual UObject* GetObjectPointer() const override;
    virtual bool ShouldStripPropertyNames() const override;
    virtual UStruct* GetStructObject() const override;
    virtual void* GetObjectData() override;
    virtual void AddReferencedObjects(FReferenceCollector& ReferenceCollector) override;
    private:
        UObject* ReferencedObject;
};

class SML_API FReflectedObjectState_ScriptStruct : public FReflectedObjectState {
    public:
        FReflectedObjectState_ScriptStruct(UScriptStruct* Struct);
    virtual ~FReflectedObjectState_ScriptStruct() override;

    virtual void CopyStructValue(UScriptStruct* StructType, void* StructValue) const override;
    virtual UObject* GetObjectPointer() const override;
    virtual bool ShouldStripPropertyNames() const override;
    void CopyDataFromStruct(const void* SourceStruct) const;
    virtual UStruct* GetStructObject() const override;
    virtual void* GetObjectData() override;
    virtual void AddReferencedObjects(FReferenceCollector& ReferenceCollector) override;
    private:
        UScriptStruct* ScriptStruct;
    void* StructDataPointer;
};
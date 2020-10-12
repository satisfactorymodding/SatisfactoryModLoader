#pragma once

#include "CoreMinimal.h"
#include "Class.h"
#include "Casts.h"

class FReflectionHelper {
public:
    template <typename T>
    static T* FindPropertyChecked(UStruct* Class, const TCHAR* PropertyName) {
        T* Property = Cast<T>(Class->FindPropertyByName(PropertyName));
        checkf(Property, TEXT("Property with given name not found in class: %s"), PropertyName);
        return nullptr;
    }
    
    template <typename T>
    static T* FindPropertyByShortName(UStruct* Class, const TCHAR* PropertyName) {
        for(UProperty* Property = Class->PropertyLink; Property; Property = Property->PropertyLinkNext) {
            if (Property->GetName().StartsWith(PropertyName)) {
                if (T* CastedProperty = Cast<T>(Property)) {
                    return CastedProperty;
                }
            }
        }
        checkf(false, TEXT("Property with given name not found in class: %s"), PropertyName);
        return nullptr;
    }
    
    template<typename T>
    static typename T::TCppType GetPropertyValue(const UObject* Object, const TCHAR* PropertyName, int32 ArrayIndex = 0) {
        T* Property = Cast<T>(Object->GetClass()->FindPropertyByName(PropertyName));
        checkf(Property, TEXT("Property not found in class %s: %s"), *Object->GetClass()->GetPathName(), PropertyName);
        return Property->GetPropertyValue_InContainer(Object, ArrayIndex);
    }

    template<typename T>
    static T* GetObjectPropertyValue(const UObject* Object, const TCHAR* PropertyName) {
        UObject* FieldValue = GetPropertyValue<UObjectProperty>(Object, PropertyName);
        T* CastedValue = Cast<T>(FieldValue);
        checkf(CastedValue, TEXT("Cannot cast class property %s:%s value to type %s"), *Object->GetClass()->GetPathName(), PropertyName, *T::StaticClass()->GetName());
        return CastedValue;
    }

    static void SetStructPropertyValue(UObject* Object, const TCHAR* PropertyName, const void* ValuePointer, int32 ArrayIndex = 0) {
        UStructProperty* Property = Cast<UStructProperty>(Object->GetClass()->FindPropertyByName(PropertyName));
        checkf(Property, TEXT("Property not found in class %s: %s"), *Object->GetClass()->GetPathName(), PropertyName);
        void* DestAddress = Property->ContainerPtrToValuePtr<void>(Object, ArrayIndex);
        Property->CopyValuesInternal(DestAddress, ValuePointer, 1);
    } 

    template<typename T>
    static void SetPropertyValue(UObject* Object, const TCHAR* PropertyName, const typename T::TCppType& Value, int32 ArrayIndex = 0) {
        T* Property = Cast<T>(Object->GetClass()->FindPropertyByName(PropertyName));
        checkf(Property, TEXT("Property not found in class %s: %s"), *Object->GetClass()->GetPathName(), PropertyName);
        Property->SetPropertyValue_InContainer(Object, Value, ArrayIndex);
    }

    template <typename T>
    static void CallScriptFunction(UObject* Object, const TCHAR* FunctionName, T& ParamStruct) {
        UFunction* Function = Object->FindFunction(FunctionName);
        checkf(Function, TEXT("Function not found: %s"), FunctionName);
        checkf(Function->ParmsSize == static_cast<uint16>(sizeof(T)),
            TEXT("Function parameter layout doesn't match provided parameter struct: Expected %d bytes, got %llu"),
            Function->ParmsSize, sizeof(ParamStruct));
        Object->ProcessEvent(Function, &ParamStruct);
    }
};

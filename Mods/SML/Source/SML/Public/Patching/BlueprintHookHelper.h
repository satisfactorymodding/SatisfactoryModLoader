#pragma once
#include "UObject/Object.h"
#include "UObject/Stack.h"
#include "Concepts/BaseStructureProvider.h"
#include "Concepts/StaticStructProvider.h"

struct FBlueprintHookVariableHelper
{
public:
	FBlueprintHookVariableHelper(FFrame& Frame) : Frame(Frame) {}
	virtual ~FBlueprintHookVariableHelper() = default;

	/**
	 * Gets a property and a pointer to its value by name. Used as a helper function in other methods of this struct.
	 *
	 * For users of this function, the ValuePtr is *not* to be used with _InContainer or ContainerPtr methods of FProperty,
	 * it is already the pointer to the value of the property.
	 *
	 * Example:
	 * \code
	 * void* ValuePtr;
	 * FProperty* Property = helper.GetPropertyByName(TEXT("ReturnValue"), ValuePtr);
	 * \endcode
	 * 
	 * @tparam T a FProperty type
	 * @param VariableName the variable name, as shown in the blueprint (may or may not contain spaces)
	 * @param ValuePtr [out] a pointer to the value of the variable, for advanced users
	 * @param ArrayIndex [optional] the index in native static-sized property array (not TArray) types, unlikely to be found in blueprints
	 * @return a property pointer for the requested property
	 */
	template <typename T>
	T* GetVariableProperty(const TCHAR* VariableName, void*& ValuePtr, int32 ArrayIndex = 0) const
	{
		FProperty* Property = GetVariablePropertyInternal(VariableName, ValuePtr, ArrayIndex);
		T* CastedProperty = CastField<T>(Property);
		fgcheckf(CastedProperty, TEXT("Property %s is not of type %s"), VariableName, *T::StaticClass()->GetName());
		return CastedProperty;
	}

	/**
	 * Gets a pointer to the value of the named basic variable.
	 * <b>This method won't work on bool, struct or enum variables; use the corresponding methods instead.</b>
	 *
	 * Example:
	 * \code
	 * int* ReturnValuePtr = helper.GetVariablePtr<FIntProperty>( TEXT("ReturnValue") );
	 * \endcode
	 *
	 * @param VariableName the name of the variable to access. Will assert if the variable is not found or is not the expected type
	 * @param ArrayIndex [optional] the index in native static-sized property array (not TArray) types, unlikely to be found in blueprints
	 * @returns a pointer to the value, which can be used to get and/or set the underlying value.
	 */
	template<typename T>
	typename T::TCppType* GetVariablePtr(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		void* ValuePtr;
		T* Property = GetVariableProperty<T>(VariableName, ValuePtr, ArrayIndex);
		return Property->GetPropertyValuePtr(ValuePtr);
	}

	/**
	 * Gets a pointer to the value of the named struct variable. <b>This method will only work on struct variables; for other types use the corresponding methods instead.</b>
	 *
	 * Example usage:
	 * \code
	 * FLinearColor* MyColorValue = helper.GetStructVariablePtr<FLinearColor>( TEXT("MyColor") );
	 * \endcode
	 *
	 * @param VariableName the name of the member variable to access. Will assert if the variable is not found or is not the expected type
	 * @param ArrayIndex [optional] the index in native static-sized property array (not TArray) types, unlikely to be found in blueprints
	 * @returns a pointer to the value, which can be used to get and/or set the underlying value
	 */
	template<typename T>
	T* GetStructVariablePtr(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		UStruct* StructType = nullptr;
		if constexpr (TModels_V<CStaticStructProvider, T>) {
			StructType = T::StaticStruct();
		}
		else if constexpr (TModels_V<CBaseStructureProvider, T>) {
			StructType = TBaseStructure<T>::Get();
		}
		fgcheckf(StructType, TEXT("Type does not provide a static structure type"));
		void* ValuePtr;
		FStructProperty* Property = GetVariableProperty<FStructProperty>(VariableName, ValuePtr, ArrayIndex);
		fgcheckf(StructType->IsChildOf(Property->Struct), TEXT("Property %s is not of type %s"), VariableName, *StructType->GetName());
		return (T*)ValuePtr;
	}

	/**
	 * Gets a pointer to the value of the named enum variable. <b>This method will only work on enum variables; for other types use the corresponding methods instead.</b>
	 *
	 * Example:
	 * \code
	 * EMyEnum* EnumValuePtr = helper.GetEnumVariablePtr<EMyEnum>( TEXT("EnumValue") );
	 * \endcode
	 *
	 * @param VariableName the name of the Output variable to access. Will assert if the variable is not found or is not the expected type
	 * @param ArrayIndex [optional] the index in native static-sized property array (not TArray) types, unlikely to be found in blueprints
	 * @returns A pointer to the value, which can be used to get and/or set the underlying value.
	 */
	template<typename TEnum>
	TEnum* GetEnumVariablePtr(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		void* ValuePtr;
		FEnumProperty* EnumProperty = GetVariableProperty<FEnumProperty>(VariableName, ValuePtr, ArrayIndex);
		UEnum* Enum = StaticEnum<TEnum>();
		fgcheckf(Enum == EnumProperty->GetEnum(), TEXT("Property %s is not of type %s"), VariableName, *Enum->GetName());
		return (TEnum*)ValuePtr;
	}

	/**
	 * Gets an FScriptArrayHelper for reading/writing values of the named array variable. Array properties store a FScriptArray value, which cannot be directly accessed or modified.
	 * The inner property type is also provided to enable reading/writing the contents of the array.
	 * 
	 * @param VariableName the name of the member variable to access. Will assert if the variable is not found or is not the expected type
	 * @param InnerType [out] the inner property type of the array, used to read/write the contents of the array
	 * @param ArrayIndex [optional] the index in native static-sized property array (not TArray) types, unlikely to be found in blueprints
	 * @returns an FScriptArrayHelper that can be used to read/write contents of the underlying map.
	 */
	template <typename T>
	FScriptArrayHelper GetArrayVariable(const TCHAR* VariableName, T*& InnerType, int32 ArrayIndex = 0) const {
		void* ValuePtr;
		FArrayProperty* Property = GetVariableProperty<FArrayProperty>(VariableName, ValuePtr, ArrayIndex);
		InnerType = CastField<T>(Property->Inner);
		fgcheckf(InnerType, TEXT("Array property %s does not have %s as inner type. Actual inner type: %s"), VariableName, *T::StaticClass()->GetName(), *Property->Inner->GetClass()->GetName());
		return FScriptArrayHelper(Property, ValuePtr);
	}

	/**
	 * Gets an FScriptMapHelper for reading/writing values of the named map variable. Map properties store a FScriptMap value, which cannot be directly accessed or modified.
	 * The key and value property types are also provided to enable reading/writing the contents of the map.
	 *
	 * @param VariableName the name of the member variable to access. Will assert if the variable is not found or is not the expected type
	 * @param KeyType [out] the key property type of the map, used to read/write the contents of the map
	 * @param ValueType [out] the value property type of the map, used to read/write the contents of the map
	 * @param ArrayIndex [optional] the index in native static-sized property array (not TArray) types, unlikely to be found in blueprints
	 * @returns an FScriptMapHelper that can be used to read/write contents of the underlying map.
	 */
	template <typename K, typename V>
	FScriptMapHelper GetMapVariable(const TCHAR* VariableName, K*& KeyType, V*& ValueType, int32 ArrayIndex = 0) const {
		void* ValuePtr;
		FMapProperty* Property = GetVariableProperty<FMapProperty>(VariableName, ValuePtr, ArrayIndex);
		KeyType = CastField<K>(Property->KeyProp);
		ValueType = CastField<V>(Property->ValueProp);
		fgcheckf(KeyType, TEXT("Property %s does not have %s as key type. Actual key type: %s"), VariableName, *K::StaticClass()->GetName(), *Property->KeyProp->GetClass()->GetName());
		fgcheckf(ValueType, TEXT("Property %s does not have %s as value type. Actual value type: %s"), VariableName, *V::StaticClass()->GetName(), *Property->ValueProp->GetClass()->GetName());
		return FScriptMapHelper(Property, ValuePtr);
	}

	/**
	 * Gets an FScriptSetHelper for reading/writing values of the named set variable. Set properties store a FScriptSet value, which cannot be directly accessed or modified.
	 * The element property type is also provided to enable reading/writing the contents of the set.
	 *
	 * @param VariableName the name of the member variable to access. Will assert if the variable is not found or is not the expected type
	 * @param ArrayIndex [optional] the index in native static-sized property array (not TArray) types, unlikely to be found in blueprints
	 * @returns an FScriptSetHelper that can be used to read/write contents of the underlying set.
	*/
	template <typename T>
	FScriptSetHelper GetSetVariable(const TCHAR* VariableName, T*& InnerType, int32 ArrayIndex = 0) const {
		void* ValuePtr;
		FSetProperty* Property = GetVariableProperty<FSetProperty>(VariableName, ValuePtr, ArrayIndex);
		InnerType = CastField<T>(Property->ElementProp);
		fgcheckf(InnerType, TEXT("Set property %s does not have %s as element type. Actual element type: %s"), VariableName, *T::StaticClass()->GetName(), *Property->ElementProp->GetClass()->GetName());
		return FScriptSetHelper(Property, ValuePtr);
	}

	/**
	 * Gets the value of the named bool variable. Due to bitfield packing, the generic GetVariablePtr method cannot be used for bools.
	 * 
	 * @param VariableName the name of the local variable to access. Will assert if the variable is not found or is not the expected type
	 * @param ArrayIndex [optional] the index in native static-sized property array (not TArray) types, unlikely to be found in blueprints
	 * @returns the value of the variable
	 */
	bool GetBoolVariable(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		void* ValuePtr;
		FBoolProperty* Property = GetVariableProperty<FBoolProperty>(VariableName, ValuePtr, ArrayIndex);
		return Property->GetPropertyValue(ValuePtr);
	}

	/**
	 * Sets the value of the named bool variable. Due to bitfield packing, the generic GetVariablePtr method cannot be used for bools.
	 *
	 * @param VariableName the name of the local variable to access. Will assert if the variable is not found or is not the expected type
	 * @param ArrayIndex [optional] the index in native static-sized property array (not TArray) types, unlikely to be found in blueprints
	 * @param Value the value to set the variable to
	 */
	void SetBoolVariable(const TCHAR* VariableName, bool Value, int32 ArrayIndex = 0) const {
		void* ValuePtr;
		FBoolProperty* Property = GetVariableProperty<FBoolProperty>(VariableName, ValuePtr, ArrayIndex);
		Property->SetPropertyValue(ValuePtr, Value);
	}
protected:
	virtual FProperty* GetVariablePropertyInternal(const TCHAR* VariableName, void*& ValuePtr, int32 ArrayIndex) const = 0;

	FFrame& Frame;
};

struct FBlueprintHookVariableHelper_Context : public FBlueprintHookVariableHelper
{
public:
	FBlueprintHookVariableHelper_Context(FFrame& Frame) : FBlueprintHookVariableHelper(Frame) {}
protected:
	virtual FProperty* GetVariablePropertyInternal(const TCHAR* VariableName, void*& ValuePtr, int32 ArrayIndex) const override {
		UClass* ContextClass = Frame.Object->GetClass();
		FProperty* Property = ContextClass->FindPropertyByName(VariableName);
		fgcheckf(Property, TEXT("Did not find Variable %s on Context type %s"), VariableName, *ContextClass->GetName());
		ValuePtr = Property->ContainerPtrToValuePtr<void>(Frame.Object, ArrayIndex);
		return Property;
	}
};

struct FBlueprintHookVariableHelper_Local : public FBlueprintHookVariableHelper
{
public:
	FBlueprintHookVariableHelper_Local(FFrame& Frame) : FBlueprintHookVariableHelper(Frame) {}
protected:
	virtual FProperty* GetVariablePropertyInternal(const TCHAR* VariableName, void*& ValuePtr, int32 ArrayIndex) const override {
		FProperty* Property = Frame.Node->FindPropertyByName(VariableName);
		fgcheckf(Property, TEXT("Could not find a local variable named %s"), VariableName);
		fgcheckf(!Property->HasAnyPropertyFlags(CPF_OutParm), TEXT("%s is an [out] variable and must be accessed via the Out variable helper"), VariableName);
		ValuePtr = Property->ContainerPtrToValuePtr<void>(Frame.Locals, ArrayIndex);
		return Property;
	}
};

struct FBlueprintHookVariableHelper_Out : public FBlueprintHookVariableHelper
{
public:
	FBlueprintHookVariableHelper_Out(FFrame& Frame) : FBlueprintHookVariableHelper(Frame) {}
protected:
	virtual FProperty* GetVariablePropertyInternal(const TCHAR* VariableName, void*& ValuePtr, int32 ArrayIndex) const override {
		fgcheckf(ArrayIndex == 0, TEXT("Output variables do not support array indexing"));
		FOutParmRec* Out = Frame.OutParms;
		while (Out && Out->Property->GetName() != VariableName) {
			Out = Out->NextOutParm;
		}
		fgcheckf(Out, TEXT("Current Frame has no output variable named %s. Maybe you're looking for a Local variable?"), VariableName);
		FProperty* Property = Out->Property;
		ValuePtr = Out->PropAddr;
		return Property;
	}
};

/** 
 * Helps in reading/writing information about the currently-executing hooked blueprint function
 */
class SML_API FBlueprintHookHelper {
public:
	FFrame& FramePointer;
private:
	int32 ReturnInstructionOffset;

public:
	FORCEINLINE FBlueprintHookHelper(FFrame& Frame, const int32 MyReturnInstructionOffset) : FramePointer(Frame), ReturnInstructionOffset(MyReturnInstructionOffset) {}

	/**
	 * Jumps to function's EX_Return instruction to terminate function execution
	 * Function execution will be finished after all hooks are processed, so other
	 * hooks registered for same offset will be called anyway
	 * @note Other hooks at the same offset will be still called in the normal order, even if one of them jumps to function return
	 */
	void JumpToFunctionReturn() const {
		FramePointer.Code = &FramePointer.Node->Script[ReturnInstructionOffset];
	}

	/**
	 * Returns object pointer to the object which current function is executed on
	 */
	FORCEINLINE UObject* GetContext() const { return FramePointer.Object; }

	/**
	 * Member variables are viewable in Unreal Editor under the Variables accordion in the My Blueprint tab of the Graph view of the blueprint.
	 */
	TSharedRef<FBlueprintHookVariableHelper_Context> GetContextVariableHelper() const {
		return MakeShared<FBlueprintHookVariableHelper_Context>(FramePointer);
	}

	/**
	 * Local variables include function Input variables and temporary local variables inside the function.
	 */
	TSharedRef<FBlueprintHookVariableHelper_Local> GetLocalVariableHelper() const {
		return MakeShared<FBlueprintHookVariableHelper_Local>(FramePointer);
	}

	/**
	 * Function Output variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	 */
	TSharedRef<FBlueprintHookVariableHelper_Out> GetOutVariableHelper() const {
		return MakeShared<FBlueprintHookVariableHelper_Out>(FramePointer);
	}
};

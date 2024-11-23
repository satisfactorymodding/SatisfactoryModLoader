#pragma once
#include "UObject/Object.h"
#include "UObject/Stack.h"

/** 
 * Holds contextual information about function execution by the time hook is called
 * Can be used to retrieve self object reference, local variable values and
 * manipulate execution of the byte-code beyond hook
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

private:
	template<typename T>
	FORCEINLINE T* GetContextProperty(const TCHAR* PropertyName) const {
		UObject* Context = GetContext();
		UClass* ContextClass = Context->GetClass();
		FProperty* BaseProperty = ContextClass->FindPropertyByName(PropertyName);
		fgcheckf(BaseProperty, TEXT("Did not find property %s on Context type %s"), PropertyName, *ContextClass->GetName());
		T* Property = CastField<T>(BaseProperty);
		fgcheckf(Property, TEXT("Property %s on Context type %s does not have an FProperty of the requested type. Actual FProperty type: %s"), PropertyName, *ContextClass->GetName(), *BaseProperty->GetClass()->GetName());
		return Property;
	}

public:
	template<typename T>
	typename T::TCppType* GetContextVarPtr(const TCHAR* PropertyName, int32 ArrayIndex = 0) const {
		T* Property = GetContextProperty<T>(PropertyName);
		return Property->GetPropertyValuePtr_InContainer(GetContext(), ArrayIndex);
	}
	
	template<typename TEnum>
	TEnum* GetContextVarEnumPtr(const TCHAR* PropertyName, int32 ArrayIndex = 0) const {
		FEnumProperty* Property = GetContextProperty<FEnumProperty>(PropertyName);
		// K2 only supports byte enums right now, according to a comment in EdGraphSchema_K2.cpp
		return (TEnum*)Property->ContainerPtrToValuePtr<uint8>(GetContext(), ArrayIndex);
	}
	
	// Bool properties have unique handling - they don't have a CppType because they can packed into a single
	// bit and there's no CppType for that, so all reads/modifications have to go through the property API
	bool GetContextVarBool(const TCHAR* PropertyName, int32 ArrayIndex = 0) const {
		FBoolProperty* Property = GetContextProperty<FBoolProperty>(PropertyName);
		return Property->GetPropertyValue_InContainer(GetContext(), ArrayIndex);
	}
	
	void SetContextVarBool(const TCHAR* PropertyName, bool Value, int32 ArrayIndex = 0) const {
		FBoolProperty* Property = GetContextProperty<FBoolProperty>(PropertyName);
		Property->SetPropertyValue_InContainer(GetContext(), Value, ArrayIndex);
	}

private:
	template<typename T>
	FORCEINLINE T* GetLocalVarProperty(const TCHAR* VariableName) const {
		FProperty* BaseProperty = FramePointer.Node->FindPropertyByName(VariableName);
		fgcheckf(BaseProperty, TEXT("Could not find a local variable named %s"), VariableName);
		fgcheckf(!BaseProperty->HasAnyPropertyFlags(CPF_OutParm), TEXT("%s is an [out] variable and must be accessed via the GetOutVar functions"), VariableName);
		T* Property = CastField<T>(BaseProperty);
		fgcheckf(Property, TEXT("Local variable %s does not have an FProperty of the requested type. Actual FProperty type: %s"), VariableName, *BaseProperty->GetClass()->GetName());
		return Property;
	}

public:

	/**
	 * Retrieves local variable pointer from stack frame by the provided name
	 * This method won't work on bool variables; use GetLocalBoolVar instead
	 * This method won't work on [out] variables, as these are stored separately from local stack frame
	 * Passed pointer is guaranteed to be valid for the duration of hook execution
	 *
	 * @param VariableName name of the local variable to retrieve
	 * @param ArrayIndex if variable represents a statically sized array, retrieve value at specified index
	 * @return pointer to the local variable value
	 * @note Will check false if provided variable name represents an [out] variable
	 */
	template<typename T>
	typename T::TCppType* GetLocalVarPtr(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		T* Property = GetLocalVarProperty<T>(VariableName);
		return Property->GetPropertyValuePtr_InContainer(FramePointer.Locals, ArrayIndex);
	}

	template<typename TEnum>
	TEnum* GetLocalVarEnumPtr(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		FEnumProperty* Property = GetLocalVarProperty<FEnumProperty>(VariableName);
		// K2 only supports byte enums right now, according to a comment in EdGraphSchema_K2.cpp
		return (TEnum*)Property->ContainerPtrToValuePtr<uint8>(FramePointer.Locals, ArrayIndex);
	}

	bool GetLocalVarBool(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		FBoolProperty* Property = GetLocalVarProperty<FBoolProperty>(VariableName);
		return Property->GetPropertyValue_InContainer(FramePointer.Locals, ArrayIndex);
	}

	void SetLocalVarBool(const TCHAR* VariableName, bool Value, int32 ArrayIndex = 0) const {
		FBoolProperty* Property = GetLocalVarProperty<FBoolProperty>(VariableName);
		return Property->SetPropertyValue_InContainer(FramePointer.Locals, Value, ArrayIndex);
	}

private:
	template<typename T>
	FORCEINLINE T* GetOutProperty(const TCHAR* VariableName, FOutParmRec** OutOutParm) const {
		FOutParmRec* Out = FramePointer.OutParms;
		while (Out && Out->Property->GetName() != VariableName) {
			Out = Out->NextOutParm;
		}
		fgcheckf(Out, TEXT("Current Frame has no output variable named %s"), VariableName);
		FProperty* BaseProperty = Out->Property;
		T* Property = CastField<T>(BaseProperty);
		fgcheckf(Property, TEXT("Out variable %s does not have an FProperty of the requested type. Actual FProperty type: %s"), VariableName, *BaseProperty->GetClass()->GetName());
		*OutOutParm = Out;
		return Property;
	}

public:
	/**
	 * Retrieves variable passed to method as [out] parameter (pass by reference basically), e.g which
	 * Can be set by blueprint method and changes will be visible to caller
	 * These variables are stored separately from other local variables, so
	 * GetLocalVarPtr won't work on them, you should use this method instead
	 * Passed pointer is guaranteed to be valid for the duration of hook execution
	 * 
	 * @param VariableName name of the [out] variable
	 * @return pointer to the current value stored in the [out] variable
	 * @note Only works on variables which are passed to the function by reference, including ReturnValue
	 */
	template<typename T>
	typename T::TCppType* GetOutVariablePtr(const TCHAR* VariableName = TEXT("ReturnValue")) const {
		FOutParmRec* Out;
		T* Property = GetOutProperty<T>(VariableName, &Out);
		return Property->GetPropertyValuePtr(Out->PropAddr);
	}

	template<typename TEnum>
	TEnum* GetOutVarEnumPtr(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		FOutParmRec* Out;
		FEnumProperty* EnumProperty = GetOutProperty<FEnumProperty>(VariableName, &Out);
		// We get the underlying property for out vars but we didn't for context or local vars.
		// For unknown reasons, the enum property for out variables contains an internal offset
		// that yields the wrong result with ContainerPtrToValuePtr but the underlying numeric
		// property works. Tests of the same approach for local and context vars yield crashes
		// or incorrect enum values.
		FNumericProperty* Property = EnumProperty->GetUnderlyingProperty();
		fgcheckf(Property, TEXT("Enum property has no underlying property? This shouldn't happen."));
		// K2 only supports byte enums right now, according to a comment in EdGraphSchema_K2.cpp
		return (TEnum*)Property->ContainerPtrToValuePtr<uint8>(Out->PropAddr, ArrayIndex);
	}

	bool GetOutVarBool(const TCHAR* VariableName) const {
		FOutParmRec* Out;
		FBoolProperty* Property = GetOutProperty<FBoolProperty>(VariableName, &Out);
		return Property->GetPropertyValue(Out->PropAddr);
	}

	void SetOutVarBool(const TCHAR* VariableName, bool Value ) const {
		FOutParmRec* Out;
		FBoolProperty* Property = GetOutProperty<FBoolProperty>(VariableName, &Out);
		Property->SetPropertyValue(Out->PropAddr, Value);
	}
};

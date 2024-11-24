#pragma once
#include "UObject/Object.h"
#include "UObject/Stack.h"

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


	/************************************************************************************************************************************
	 * Functions to interact with member variables of the Context (i.e. the blueprint object on which the current function is executing).
	 ************************************************************************************************************************************/

	/**
	 * Gets a pointer to the FProperty representing a named blueprint member variable, which are viewable in Unreal Editor under the Variables accordion in the My Blueprint tab of the Graph view of the blueprint.
	 * 
	 * Example usage: FIntProperty* IntProperty = helper.GetContextVarProperty<FIntProperty>( TEXT("MyInt") );
	 * 
	 * This is mostly for internal use but can be also helpful for reading types that require special handling (see GetContextVarMapHelper for an example) and are not supported here yet.
	 */
	template<typename T>
	FORCEINLINE T* GetContextVarProperty(const TCHAR* VariableName) const {
		UObject* Context = GetContext();
		UClass* ContextClass = Context->GetClass();
		FProperty* BaseProperty = ContextClass->FindPropertyByName(VariableName);
		fgcheckf(BaseProperty, TEXT("Did not find Variable %s on Context type %s"), VariableName, *ContextClass->GetName());
		T* Property = CastField<T>(BaseProperty);
		fgcheckf(Property, TEXT("Variable %s on Context type %s does not have an FProperty of the expected type. Actual FProperty type: %s"), VariableName, *ContextClass->GetName(), *BaseProperty->GetClass()->GetName());
		return Property;
	}

	/**
	 * Gets a pointer to the value of a named blueprint member variable on the Context.
	 * Member variables are viewable in Unreal Editor under the Variables accordion in the My Blueprint tab of the Graph view of the blueprint.
	 * This method won't work on bool or enum variables; use the corresponding helper methods instead.
	 *
	 * Example usage: int* MyIntPtr = helper.GetContextVarPtr<FIntProperty>( TEXT("MyInt") );
	 *
	 * @param VariableName - The name of the member variable to access. Will assert if the variable is not found or is not the expected type.
	 * @param ArrayIndex - If the variable represents a statically sized array, returns the value at the specified index.
	 * @returns A pointer to the value, which can be used to get and/or set the underlying value.
	 */
	template<typename T>
	typename T::TCppType* GetContextVarPtr(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		T* Property = GetContextVarProperty<T>(VariableName);
		return Property->GetPropertyValuePtr_InContainer(GetContext(), ArrayIndex);
	}
	
	/**
	 * Gets a pointer to the value of a named enum blueprint member variable on the Context.
	 * Member variables are viewable in Unreal Editor under the Variables accordion in the My Blueprint tab of the Graph view of the blueprint.
	 *
	 * Example usage: EMyEnum* MyEnumValuePtr = helper.GetContextVarEnumPtr<EMyEnum>( TEXT("MyEnumValue") );
	 * 
	 * @param VariableName - The name of the member variable to access. Will assert if the variable is not found or is not the expected type.
	 * @param ArrayIndex - If the variable represents a statically sized array, returns the value at the specified index.
	 * @returns A pointer to the value, which can be used to get and/or set the underlying value.
	 */
	template<typename TEnum>
	TEnum* GetContextVarEnumPtr(const TCHAR* PropertyName, int32 ArrayIndex = 0) const {
		FEnumProperty* Property = GetContextVarProperty<FEnumProperty>(PropertyName);
		// K2 only supports byte enums right now, according to a comment in EdGraphSchema_K2.cpp
		return (TEnum*)Property->ContainerPtrToValuePtr<uint8>(GetContext(), ArrayIndex);
	}
	
	/**
	 * Gets the value of a named bool blueprint member variable on the Context.
	 * Member variables are viewable in Unreal Editor under the Variables accordion in the My Blueprint tab of the Graph view of the blueprint.
	 *
	 * @param VariableName - The name of the member variable to access. Will assert if the variable is not found or is not the expected type.
	 * @param ArrayIndex - If the variable represents a statically sized array, returns the value at the specified index.
	 */
	bool GetContextVarBool(const TCHAR* PropertyName, int32 ArrayIndex = 0) const {
		FBoolProperty* Property = GetContextVarProperty<FBoolProperty>(PropertyName);
		return Property->GetPropertyValue_InContainer(GetContext(), ArrayIndex);
	}
	
	/**
	 * Sets the value of a named bool blueprint member variable on the Context.
	 * Member variables are viewable in Unreal Editor under the Variables accordion in the My Blueprint tab of the Graph view of the blueprint.
	 *
	 * @param VariableName - The name of the member variable to access. Will assert if the variable is not found or is not the expected type.
	 * @param ArrayIndex - If the variable represents a statically sized array, sets the value at the specified index.
	 */
	void SetContextVarBool(const TCHAR* PropertyName, bool Value, int32 ArrayIndex = 0) const {
		FBoolProperty* Property = GetContextVarProperty<FBoolProperty>(PropertyName);
		Property->SetPropertyValue_InContainer(GetContext(), Value, ArrayIndex);
	}

	/**
	 * Gets an FScriptMapHelper for reading/writing values of a named Map blueprint member variable on the Context.
	 * Member variables are viewable in Unreal Editor under the Variables accordion in the My Blueprint tab of the Graph view of the blueprint.
	 * 
	 * This exists because the reading the FMapProperty will return an FScriptMap, which is basically-unusable without being wrapped in an FScriptMapHelper.
	 * 
	 * @param VariableName - The name of the member variable to access. Will assert if the variable is not found or is not the expected type.
	 */
	FScriptMapHelper GetContextVarMapHelper(const TCHAR* PropertyName) const {
		FMapProperty* Property = GetContextVarProperty<FMapProperty>(PropertyName);
		FScriptMap* ScriptMap = Property->GetPropertyValuePtr_InContainer(GetContext());
		return FScriptMapHelper(Property, ScriptMap);
	}

	 /*******************************************************************************************
	  * Functions to interact with local variables of the currently-executing blueprint function.
	  *******************************************************************************************/

	 /**
	  * Gets a pointer to the FProperty representing a named local variable in the executing function. Local variables include function Input variables and temporary local variables inside the function.
	  * Function Input variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	  * Temporary local variable names can be viewed by disassembling the underlying code - see BlueprintHookManager.cpp for one existing way to dump debugging disassambly.
	  * 
	  * Example usage: FIntProperty* LocalIntProperty = helper.GetLocalVarProperty<FIntProperty>( TEXT("localInt") );
	  *
	  * This is mostly for internal use but can be also helpful for reading types that require special handling (see GetContextVarMapHelper for an example) and are not supported here yet.
	  */
	template<typename T>
	FORCEINLINE T* GetLocalVarProperty(const TCHAR* VariableName) const {
		FProperty* BaseProperty = FramePointer.Node->FindPropertyByName(VariableName);
		fgcheckf(BaseProperty, TEXT("Could not find a local variable named %s"), VariableName);
		fgcheckf(!BaseProperty->HasAnyPropertyFlags(CPF_OutParm), TEXT("%s is an [out] variable and must be accessed via the GetOutVar functions"), VariableName);
		T* Property = CastField<T>(BaseProperty);
		fgcheckf(Property, TEXT("Local variable %s does not have an FProperty of the expected type. Actual FProperty type: %s"), VariableName, *BaseProperty->GetClass()->GetName());
		return Property;
	}

	/**
	 * Gets a pointer to the value of a named local variable in the executing function. Local variables include function Input variables and temporary local variables inside the function.
	 * Function Input variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	 * Temporary local variable names can be viewed by disassembling the underlying code - see BlueprintHookManager.cpp for one existing way to dump debugging disassambly.
	 *
	 * This method will assert if used with blueprint function Output variables; use GetOutVar* helper methods for those.
	 * This method won't work on bool or enum variables; use the corresponding helper methods instead.
	 * 
	 * Example usage: int* InputIntPtr = helper.GetLocalVarProperty<FIntProperty>( TEXT("InputInt") );
	 *
	 * @param VariableName - The name of the local variable to access. Will assert if the variable is an Output variable, is not found, or is not the expected type.
	 * @param ArrayIndex - If the variable represents a statically sized array, returns the value at the specified index.
	 * @returns A pointer to the value, which can be used to get and/or set the underlying value.
	 */
	template<typename T>
	typename T::TCppType* GetLocalVarPtr(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		T* Property = GetLocalVarProperty<T>(VariableName);
		return Property->GetPropertyValuePtr_InContainer(FramePointer.Locals, ArrayIndex);
	}

	/**
	 * Gets a pointer to the value of a named enum local variable in the executing function. Local variables include function Input variables and temporary local variables inside the function.
	 * Function Input variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	 * Temporary local variable names can be viewed by disassembling the underlying code - see BlueprintHookManager.cpp for one existing way to dump debugging disassambly.
	 *
	 * This method will assert if used with blueprint function Output variables; use GetOutVar* helper methods for those.
	 *
	 * Example usage: EMyEnum* InputEnumValuePtr = helper.GetContextVarEnumPtr<EMyEnum>( TEXT("InputEnumValue") );
	 *
	 * @param VariableName - The name of the local variable to access. Will assert if the variable is an Output variable, is not found, or is not the expected type.
	 * @param ArrayIndex - If the variable represents a statically sized array, returns the value at the specified index.
	 * @returns A pointer to the value, which can be used to get and/or set the underlying value.
	 */
	template<typename TEnum>
	TEnum* GetLocalVarEnumPtr(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		FEnumProperty* Property = GetLocalVarProperty<FEnumProperty>(VariableName);
		// K2 only supports byte enums right now, according to a comment in EdGraphSchema_K2.cpp
		return (TEnum*)Property->ContainerPtrToValuePtr<uint8>(FramePointer.Locals, ArrayIndex);
	}

	/**
	 * Gets the value of a named bool local variable in the executing function. Local variables include function Input variables and temporary local variables inside the function.
	 * Function Input variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	 * Temporary local variable names can be viewed by disassembling the underlying code - see BlueprintHookManager.cpp for one existing way to dump debugging disassambly.
	 *
	 * @param VariableName - The name of the local variable to access. Will assert if the variable is not found or is not the expected type.
	 * @param ArrayIndex - If the variable represents a statically sized array, returns the value at the specified index.
	 */
	bool GetLocalVarBool(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		FBoolProperty* Property = GetLocalVarProperty<FBoolProperty>(VariableName);
		return Property->GetPropertyValue_InContainer(FramePointer.Locals, ArrayIndex);
	}

	/**
	 * Gets the value of a named bool local variable in the executing function. Local variables include function Input variables and temporary local variables inside the function.
	 * Function Input variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	 * Temporary local variable names can be viewed by disassembling the underlying code - see BlueprintHookManager.cpp for one existing way to dump debugging disassambly.
	 *
	 * @param VariableName - The name of the local variable to access. Will assert if the variable is not found or is not the expected type.
	 * @param ArrayIndex - If the variable represents a statically sized array, sets the value at the specified index.
	 */
	void SetLocalVarBool(const TCHAR* VariableName, bool Value, int32 ArrayIndex = 0) const {
		FBoolProperty* Property = GetLocalVarProperty<FBoolProperty>(VariableName);
		return Property->SetPropertyValue_InContainer(FramePointer.Locals, Value, ArrayIndex);
	}

	/*******************************************************************************************
	 * Functions to interact with Output variables of the currently-executing blueprint function.
	 *******************************************************************************************/

	 /**
	  * Gets a pointer to the FProperty representing a named Output variable of the executing function.
	  * Function Output variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	  *
	  * Example usage:
	  * FOutParmRec* FoundOutParmRecPtr;
	  * FIntProperty* ReturnValueProperty = helper.GetOutVarProperty<FIntProperty>( TEXT("ReturnValue"), &FoundOutParmRecPtr );
	  *
	  * This is mostly for internal use but can be also helpful for reading types that require special handling (see GetContextVarMapHelper for an example) and are not supported here yet.
	  * 
	  * @param VariableName - The name of the Output variable to access. Will assert if the variable is not found or is not the expected type.
	  * @param OutOutParmPtr - Output parameter. A pointer to the pointer the caller wishes to point to the FOutParmRec where the property was found.
	  */
	template<typename T>
	FORCEINLINE T* GetOutVarProperty(const TCHAR* VariableName, FOutParmRec** OutOutParmPtr) const {
		FOutParmRec* Out = FramePointer.OutParms;
		while (Out && Out->Property->GetName() != VariableName) {
			Out = Out->NextOutParm;
		}
		fgcheckf(Out, TEXT("Current Frame has no output variable named %s"), VariableName);
		FProperty* BaseProperty = Out->Property;
		T* Property = CastField<T>(BaseProperty);
		fgcheckf(Property, TEXT("Out variable %s does not have an FProperty of the expected type. Actual FProperty type: %s"), VariableName, *BaseProperty->GetClass()->GetName());
		*OutOutParmPtr = Out;
		return Property;
	}

	/**
	 * Gets a pointer to the value of a named Output variable of the executing function.
	 * Function Output variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	 *
	 * This method won't work on bool or enum variables; use the corresponding helper methods instead.
	 *
	 * Example usage: int* ReturnValuePtr = helper.GetOutVariablePtr<FIntProperty>( TEXT("ReturnValue") );
	 *
	 * @param VariableName - The name of the Output variable to access. Will assert if the variable is not found or is not the expected type.
	 * @returns A pointer to the value, which can be used to get and/or set the underlying value.
	 */
	template<typename T>
	typename T::TCppType* GetOutVariablePtr(const TCHAR* VariableName = TEXT("ReturnValue")) const {
		FOutParmRec* Out;
		T* Property = GetOutVarProperty<T>(VariableName, &Out);
		return Property->GetPropertyValuePtr(Out->PropAddr);
	}

	/**
	 * Gets a pointer to the value of a named enum Output variable of the executing function.
	 * Function Output variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	 *
	 * Example usage: EMyEnum* OutputEnumValuePtr = helper.GetOutVarEnumPtr<EMyEnum>( TEXT("OutputEnumValue") );
	 *
	 * @param VariableName - The name of the Output variable to access. Will assert if the variable is not found or is not the expected type.
	 * @param ArrayIndex - If the variable represents a statically sized array, returns the value at the specified index.
	 * @returns A pointer to the value, which can be used to get and/or set the underlying value.
	 */
	template<typename TEnum>
	TEnum* GetOutVarEnumPtr(const TCHAR* VariableName, int32 ArrayIndex = 0) const {
		FOutParmRec* Out;
		FEnumProperty* EnumProperty = GetOutVarProperty<FEnumProperty>(VariableName, &Out);
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

	/**
	 * Gets the value of a named bool Output variable of the executing function.
	 * Function Output variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	 *
	 * @param VariableName - The name of the local variable to access. Will assert if the variable is not found or is not the expected type.
	 */
	bool GetOutVarBool(const TCHAR* VariableName) const {
		FOutParmRec* Out;
		FBoolProperty* Property = GetOutVarProperty<FBoolProperty>(VariableName, &Out);
		return Property->GetPropertyValue(Out->PropAddr);
	}

	/**
	 * Sets the value of a named bool Output variable of the executing function.
	 * Function Output variables are viewable in Unreal Editor by viewing the Details of a function found under the Functions accordion in the My Blueprint tab of the Graph view of the blueprint.
	 *
	 * @param VariableName - The name of the local variable to access. Will assert if the variable is not found or is not the expected type.
	 */
	void SetOutVarBool(const TCHAR* VariableName, bool Value ) const {
		FOutParmRec* Out;
		FBoolProperty* Property = GetOutVarProperty<FBoolProperty>(VariableName, &Out);
		Property->SetPropertyValue(Out->PropAddr, Value);
	}
};

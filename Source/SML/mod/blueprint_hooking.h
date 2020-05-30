#pragma once
#include "Class.h"
#include "Stack.h"
#include <functional>

class SML_API FBlueprintHookHelper {
public:
	FFrame& FramePointer;
public:
	FORCEINLINE FBlueprintHookHelper(FFrame& Frame) : FramePointer(Frame) {}

	FORCEINLINE UObject* GetContext() const { return FramePointer.Object; }
	
	template<typename T>
	typename T::TCppType* GetLocalVarPtr(const TCHAR* ParameterName, int32 ArrayIndex = 0) {
		T* Property = Cast<T>(FramePointer.Node->FindPropertyByName(ParameterName));
		check(Property);
		return Property->GetPropertyValuePtr_InContainer(FramePointer.Locals, ArrayIndex);
	}

	//Retrieves variable passed to method as [out] parameter (pass by reference basically), e.g which
	//Can be set by blueprint method and changes will be visible to caller
	//These variables are stored separately from other local variables, so
	//GetLocalVarPtr won't work on them, you should use this method instead
	template<typename T>
	typename T::TCppType* GetOutVariablePtr(const TCHAR* VariableName = TEXT("ReturnValue")) {
		FOutParmRec* Out = FramePointer.OutParms;
		check(Out);
		while (Out->Property->GetName() != VariableName) {
			Out = Out->NextOutParm;
			check(Out);
		}
		check(Out->Property->GetName() == VariableName);
		T* Property = Cast<T>(Out->Property);
		check(Property);
		return Property->GetPropertyValuePtr(Out->PropAddr);
	}
};

typedef void(HookSignature)(FBlueprintHookHelper& HookHelper);

SML_API void HandleHookedFunctionCall(FFrame& Stack, int64 HookFunctionAddress, int32 HookOffset);

enum EPredefinedHookOffset: int32 {
	Start = 0,
	Return = INT32_MAX - 1
};

/**
 * Hooks blueprint-implemented function referenced by Function parameter
 * at the given offset from the first blueprint instruction
 * You can use it to hook before exact instruction, or use EPredefinedHookOffset to hook into specific places
 * Note that hooking by exact offset is quite unsafe because instruction positions can change between game updates,
 * but if you absolutely need it, go ahead.
 *
 * Multiple hooks bound to one hook offset will be processed in the order they were registered
 * UClass holding Function will be added to root set to avoid getting Garbage Collected
 */
SML_API void HookBlueprintFunction(UFunction* Function, std::function<HookSignature> Hook, int32 HookOffset = EPredefinedHookOffset::Start);


#pragma once
#include "CoreMinimal.h"
#include "blueprint_hooking.h"
#include "BPHookHelper.generated.h"

UCLASS()
class SML_API UBPHookHelper : public UObject {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintInternalUseOnly, CustomThunk)
	static void ExecuteBPHook(int32 HookOffset);

	DECLARE_FUNCTION(execExecuteBPHook) {
		//StepCompiledIn is not used here since this function cannot be called from BP directly, it can only
		//be inserted into bytecode, so codegen support is not needed
		int32 HookOffset = 0;
		Stack.Step(Context, &HookOffset);
		P_FINISH; //skip EX_EndFunctionParams
		//Call hook function handler that will do some wrapping
		HandleHookedFunctionCall(Stack, HookOffset);
	}
};
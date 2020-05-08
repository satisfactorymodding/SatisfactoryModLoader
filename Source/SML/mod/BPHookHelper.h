#pragma once
#include "CoreMinimal.h"
#include "blueprint_hooking.h"
#include "BPHookHelper.generated.h"

UCLASS()
class UBPHookHelper : public UObject {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintInternalUseOnly, CustomThunk)
	static void ExecuteBPHook(int64 HookedFunctionAddress, int32 HookOffset);

	DECLARE_FUNCTION(execExecuteBPHook) {
		int64 HookedFunctionAddress = 0;
		int32 HookOffset = 0;
		Stack.Step(Context, &HookedFunctionAddress);
		Stack.Step(Context, &HookOffset);
		P_FINISH; //skip EX_EndFunctionParams
		//Call hook function handler that will do some wrapping
		HandleHookedFunctionCall(Stack, HookedFunctionAddress, HookOffset);
	}
};
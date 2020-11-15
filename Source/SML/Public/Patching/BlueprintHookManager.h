#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintHookManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBlueprintHookManager, Warning, Log);

using HookFunctionSignature = void(class FBlueprintHookHelper& HookHelper);

USTRUCT()
struct FFunctionHookInfo {
    GENERATED_BODY()
public:
    TMap<int32, TArray<TFunction<HookFunctionSignature>>> CodeOffsetByHookList;
};

enum EPredefinedHookOffset: int32 {
    Start = 0,
    Return = INT32_MAX - 1
};

UCLASS()
class SML_API UBlueprintHookManager : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
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
    static void HookBlueprintFunction(UFunction* Function, const TFunction<HookFunctionSignature>& Hook, int32 HookOffset = EPredefinedHookOffset::Start);
private:
    /** Called when hook is executed */
    static void HandleHookedFunctionCall(FFrame& Frame, int32 HookOffset);

    UFUNCTION(BlueprintInternalUseOnly, CustomThunk)
    static void ExecuteBPHook(int32 HookOffset);

    DECLARE_FUNCTION(execExecuteBPHook) {
        //StepCompiledIn is not used here since this function cannot be called from BP directly, it can only
        //be inserted into byte-code, so codegen support is not needed
        int32 HookOffset = 0;
        Stack.Step(Context, &HookOffset);
        P_FINISH; //skip EX_EndFunctionParams
        //Call hook function handler that will do some wrapping
        HandleHookedFunctionCall(Stack, HookOffset);
    }

    UPROPERTY()
    TMap<UFunction*, FFunctionHookInfo> HookedFunctions;
    UPROPERTY()
    TMap<UFunction*, int32> ReturnInstructionOffsets;
};

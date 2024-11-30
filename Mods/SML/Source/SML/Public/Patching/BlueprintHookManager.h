#pragma once
#include "Engine/Engine.h"
#include "Subsystems/EngineSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Patching/BlueprintHookHelper.h"
#include "BlueprintHookManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBlueprintHookManager, Log, All);

using HookFunctionSignature = void(FBlueprintHookHelper& HookHelper);

/** Holds information about hooked blueprint function */
USTRUCT()
struct FFunctionHookInfo {
    GENERATED_BODY()
private:
    TMap<int32, TArray<TFunction<HookFunctionSignature>>> CodeOffsetByHookList;
    int32 OriginalReturnStatementOffset;
    int32 ReturnStatementOffset;
    friend class UBlueprintHookManager;
public:
    /** Invokes all hooks associated with provided hook offset */
    void InvokeBlueprintHook(FFrame& Frame, int32 HookOffset);

    /** Re-calculates return statement offset inside of the function */
    void RecalculateReturnStatementOffset(UFunction* Function);
};

/** Describes predefined hook offsets with special handling */
enum EPredefinedHookOffset: int32 {
    Start = 0,
    Return = INT32_MAX - 1
};

UCLASS()
class SML_API UBlueprintHookManager : public UEngineSubsystem {
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
    void HookBlueprintFunction(UFunction* Function, const TFunction<HookFunctionSignature>& Hook, const int32 HookOffset);
private:
    //Minimum amount of bytes required to insert unconditional jump with code offset
    static const int32 JumpBytesRequired = 1 + sizeof(CodeSkipSizeType);

    /** Actually performs bytecode modification to install hook */
    static void InstallBlueprintHook(UFunction* Function, const int32 OriginalHookOffset, const int32 ResolvedHookOffset);

    /** Called by InstallBlueprintHook to modify the bytecode based on the desired hookoffset **/
    static void ModifyOffsetsForNewHookOffset(TArray<uint8>& Script, TSharedPtr<FJsonObject> Expression, int32 HookOffset);

    /** Called when hook is executed */
    void HandleHookedFunctionCall(FFrame& Frame, int32 HookOffset);

    /** This function is just a stub for UHT to generate reflection data, it is not actually implemented. */
    UFUNCTION(BlueprintInternalUseOnly, CustomThunk)
    static void ExecuteBPHook(int32 HookOffset) { fgcheck(0); };

    DECLARE_FUNCTION(execExecuteBPHook) {
        //StepCompiledIn is not used here since this function cannot be called from BP directly, it can only
        //be inserted into byte-code, so codegen support is not needed
        int32 HookOffset = 0;
        Stack.Step(Context, &HookOffset);
        P_FINISH; //skip EX_EndFunctionParams
        //Call hook function handler that will do some wrapping
        UBlueprintHookManager* HookManager = GEngine->GetEngineSubsystem<UBlueprintHookManager>();
        HookManager->HandleHookedFunctionCall(Stack, HookOffset);
    }

    /** Classes that we installed hooks in */
    UPROPERTY()
    TArray<UClass*> HookedClasses;

    /** Mapping of functions to their hook entries */
    UPROPERTY()
    TMap<UFunction*, FFunctionHookInfo> HookedFunctions;
};

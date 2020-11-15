#include "Patching/BlueprintHookManager.h"
#include "BlueprintHookHelper.h"
#include "Toolkit/KismetByteCodeSerializer.h"
#include "util/Logging.h"

DEFINE_LOG_CATEGORY(LogBlueprintHookManager);

#define WRITE_UNALIGNED(Arr, Type, Value) \
Arr.AddUninitialized(sizeof(Type)); \
FPlatformMemory::WriteUnaligned<Type>(&AppendedCode[Arr.Num() - sizeof(Type)], (Type) Value);

void UBlueprintHookManager::HandleHookedFunctionCall(FFrame& Stack, int32 HookOffset) {
	const UBlueprintHookManager* HookManager = GetDefault<UBlueprintHookManager>();
	const FFunctionHookInfo& FunctionHookInfo = HookManager->HookedFunctions.FindChecked(Stack.Node);
	const int32 ReturnInstructionOffset = HookManager->ReturnInstructionOffsets.FindChecked(Stack.Node);
	const TArray<TFunction<HookFunctionSignature>>& Hooks = FunctionHookInfo.CodeOffsetByHookList.FindChecked(HookOffset);
	FBlueprintHookHelper HookHelper{Stack, ReturnInstructionOffset};
	
	for (const TFunction<HookFunctionSignature>& Hook : Hooks) {
		Hook(HookHelper);
	}
}

void InstallBlueprintHook(UFunction* Function, int32 HookOffset) {
	TArray<uint8>& OriginalCode = Function->Script;
	checkf(OriginalCode.Num() > HookOffset, TEXT("Invalid hook: HookOffset > Script.Num()"));
	//basically EX_Jump + CodeSkipSizeType;
	const int32 MinBytesRequired = 1 + sizeof(CodeSkipSizeType);
	int32 BytesToMove = FKismetByteCodeSerializer::GetMinInstructionReplaceLength(Function, MinBytesRequired, HookOffset);
	SML_LOG(LogBlueprintHookManager, Log, TEXT("Installing blueprint hook at function %s, offset %d. Code Size: %d"), *Function->GetPathName(), HookOffset, Function->Script.Num());
	
	if (BytesToMove < 0) {
		//Not enough bytes in method body to fit jump into, append required amount of bytes and fill them with EX_EndOfScript
		const int32 BytesToAppend = -BytesToMove;
		OriginalCode.AddUninitialized(BytesToAppend);
		FPlatformMemory::Memset(&OriginalCode[OriginalCode.Num() - BytesToAppend], EX_EndOfScript, BytesToAppend);
		//If we are here, that means Script.Num() - HookOffset is less than MinBytesRequired
		//So to move instructions properly, we just move MinBytesRequired
		BytesToMove = MinBytesRequired;
	}
	const int32 JumpDestination = HookOffset + BytesToMove;
	SML_LOG(LogBlueprintHookManager, Log, TEXT("InstallBlueprintHook: Verified Code Size: %d"), OriginalCode.Num());
	SML_LOG(LogBlueprintHookManager, Log, TEXT("InstallBlueprintHook: Min Bytes: %d, Hook Offset: %d, Jump Dest: %d"), MinBytesRequired, HookOffset, JumpDestination);

	//Generate code to call function & code we stripped by jump
	TArray<uint8> AppendedCode;
	UFunction* HookCallFunction = UBlueprintHookManager::StaticClass()->FindFunctionByName(TEXT("ExecuteBPHook"));
	check(HookCallFunction);
	//EX_CallMath opcode to call static function & write it's address
	AppendedCode.Add(EX_CallMath);
	WRITE_UNALIGNED(AppendedCode, ScriptPointerType, HookCallFunction);
	//Pass hook hook offset - we don't need to pass function address since we can get it from FFrame object
	AppendedCode.Add(EX_IntConst);
	WRITE_UNALIGNED(AppendedCode, int32, HookOffset);
	//Indicate end of function parameters
	AppendedCode.Add(EX_EndFunctionParms);
	//Append original code we stripped
	AppendedCode.AddUninitialized(BytesToMove);
	FPlatformMemory::Memcpy(&AppendedCode[AppendedCode.Num() - BytesToMove], &OriginalCode[HookOffset], BytesToMove);
	//And then jump to the original location
	AppendedCode.Add(EX_Jump);
	WRITE_UNALIGNED(AppendedCode, CodeSkipSizeType, JumpDestination);
	//Also EX_EndOfScript in the end for safety
	AppendedCode.Add(EX_EndOfScript);

	//Now, append our code to the end of the function
	const int32 StartOfAppendedCode = OriginalCode.Num();
	OriginalCode.Append(AppendedCode);
	//And actually replace start code with jump
	//But first, fill it all with EX_EndOfScript (for safety, again)
	FPlatformMemory::Memset(&OriginalCode[HookOffset], EX_EndOfScript, BytesToMove);
	OriginalCode[HookOffset] = EX_Jump;
	FPlatformMemory::WriteUnaligned<CodeSkipSizeType>(&OriginalCode[HookOffset + 1], StartOfAppendedCode);
	SML_LOG(LogBlueprintHookManager, Log, TEXT("Inserted EX_Jump at %d to %d (Appended Code Size: %d)"), HookOffset, StartOfAppendedCode, AppendedCode.Num());
}

int32 PreProcessHookOffset(UFunction* Function, int32 HookOffset) {
	if (HookOffset == EPredefinedHookOffset::Return) {
		//For now Kismet Compiler will always generate only one Return node, so all
		//execution paths will end up either with executing it directly or jumping to it
		//So we need to hook only in one place to handle all possible execution paths
		const int32 ReturnOffset = FKismetByteCodeSerializer::FindReturnStatementOffset(Function);
		checkf(ReturnOffset != -1, TEXT("EX_Return not found for function"));
		SML_LOG(LogBlueprintHookManager, Log, TEXT("Return Offset for function %s: %d"), *Function->GetPathName(), ReturnOffset);
		SML_LOG(LogBlueprintHookManager, Log, TEXT("Instruction at Offset: %X, Excpected: %X"), Function->Script[ReturnOffset], EX_Return);
		return ReturnOffset;
	}
	return HookOffset;
}

void UBlueprintHookManager::HookBlueprintFunction(UFunction* Function, const TFunction<HookFunctionSignature>& Hook, int32 HookOffset) {
#if !WITH_EDITOR
	checkf(Function->Script.Num(), TEXT("HookBPFunction: Function provided is not implemented in BP"));
	//Make sure to add outer UClass to root set to avoid it being Garbage Collected
	//Because otherwise after GC script byte code will be reloaded, without our hooks applied
	Function->GetTypedOuter<UClass>()->AddToRoot();
	
	SML_LOG(LogBlueprintHookManager, Log, TEXT("Hooking blueprint implemented function %s"), *Function->GetPathName());
	HookOffset = PreProcessHookOffset(Function, HookOffset);
#if UE_BLUEPRINT_EVENTGRAPH_FASTCALLS
	if (Function->EventGraphFunction != nullptr) {
		SML_LOG(LogBlueprintHookManager, Warning, TEXT("Attempt to hook event graph call stub function with fast-call enabled, disabling fast call for that function"));
		SML_LOG(LogBlueprintHookManager, Warning, TEXT("It may result in performance regression for called function, if you need highest performance possible, consider hooking event graph function"));
		SML_LOG(LogBlueprintHookManager, Warning, TEXT("Event graph function: "), *Function->EventGraphFunction->GetPathName(), TEXT(", From Offset: "), Function->EventGraphCallOffset);
		Function->EventGraphFunction = nullptr;
	}
#endif

	UBlueprintHookManager* HookManager = GetMutableDefault<UBlueprintHookManager>();
	FFunctionHookInfo& FunctionHookInfo = HookManager->HookedFunctions.FindOrAdd(Function);
	TArray<TFunction<HookFunctionSignature>>& InstalledHooks = FunctionHookInfo.CodeOffsetByHookList.FindOrAdd(HookOffset);
	if (InstalledHooks.Num() == 0) {
		//First time function is hooked at this offset, call InstallBlueprintHook
		InstallBlueprintHook(Function, HookOffset);
		//Update cached return instruction offset
		const int32 ReturnInstructionOffset = FKismetByteCodeSerializer::FindReturnStatementOffset(Function);
		HookManager->ReturnInstructionOffsets.Add(Function, ReturnInstructionOffset);
	}
	
	//Add provided hook into the array
	InstalledHooks.Add(Hook);
#endif
}

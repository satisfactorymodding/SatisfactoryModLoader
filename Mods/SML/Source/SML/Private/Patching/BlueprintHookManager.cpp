#include "Patching/BlueprintHookManager.h"
#include "Patching/BlueprintHookHelper.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Toolkit/KismetBytecodeDisassembler.h"

//Whenever to debug blueprint hooking. When enabled, JSON files with script bytecode before and after installing hook will be generated
#define DEBUG_BLUEPRINT_HOOKING 0

DEFINE_LOG_CATEGORY(LogBlueprintHookManager);

#define WRITE_UNALIGNED(Arr, Type, Value) \
	Arr.AddUninitialized(sizeof(Type)); \
	FPlatformMemory::WriteUnaligned<Type>(&Arr[Arr.Num() - sizeof(Type)], (Type) Value);

void UBlueprintHookManager::HandleHookedFunctionCall(FFrame& Stack, int32 HookOffset) {
	FFunctionHookInfo& FunctionHookInfo = HookedFunctions.FindChecked(Stack.Node);
	FunctionHookInfo.InvokeBlueprintHook(Stack, HookOffset);
}

#if DEBUG_BLUEPRINT_HOOKING
void DebugDumpFunctionScriptCode(UFunction* Function, int32 HookOffset, int32 ResolvedHookOffset, const FString& Postfix) {
	const FString FileLocation = FPaths::RootDir() + FString::Printf(TEXT("BlueprintHookingDebug_%s_%s_at_%d_resolved_%d_%s.json"), *Function->GetOuter()->GetName(), *Function->GetName(), HookOffset, ResolvedHookOffset, *Postfix);

	FSMLKismetBytecodeDisassembler Disassembler;
	const TArray<TSharedPtr<FJsonValue>> Statements = Disassembler.SerializeFunction(Function);

	FString OutJsonString;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonString);
	FJsonSerializer::Serialize(Statements, Writer);

	FFileHelper::SaveStringToFile(OutJsonString, *FileLocation);
	UE_LOG(LogBlueprintHookManager, Display, TEXT("Dumped hooked function bytecode to %s (%s)"), *FileLocation, *Postfix);
}
#endif

void UBlueprintHookManager::InstallBlueprintHook(UFunction* Function, const int32 OriginalHookOffset, const int32 ResolvedHookOffset) {
	TArray<uint8>& OriginalCode = Function->Script;
	fgcheckf(OriginalCode.Num() > ResolvedHookOffset, TEXT("Invalid hook: Resolved HookOffset > Script.Num()"));

#if DEBUG_BLUEPRINT_HOOKING
	DebugDumpFunctionScriptCode(Function, OriginalHookOffset, ResolvedHookOffset, TEXT("BeforeHook"));
#endif

	// Will assert if the resolved hook offset is not at properly-aligned, parseable statement
	FSMLKismetBytecodeDisassembler Disassembler;
	int32 OutStatementLength;
	fgcheckf(
		Disassembler.GetStatementLength(Function, ResolvedHookOffset, OutStatementLength),
		TEXT("Cannot install a blueprint hook at the requested hook offset, as it is not aligned with the beginning of a statement within the target function.") );

	// First we go over the existing code and add UBlueprintHookManager::JumpBytesRequired to all
	// the offsets. Afterwards we will move the relevant code and add the jump.  Doing it in this
	// order just means we don't have to worry about errantly changing the jump offset we will add.
	TArray<TSharedPtr<FJsonValue>> DisassembledFunction = Disassembler.SerializeFunction(Function);
	for (TSharedPtr<FJsonValue> JsonValue : DisassembledFunction) {
		ModifyOffsetsForNewHookOffset(OriginalCode, JsonValue->AsObject(), ResolvedHookOffset);
	}

	//Add enough room to add the jump. This will shift all the post-hookoffset bytes down so adding
	//the jump at the resolved offset doesn't overwrite valid instructions and data
	OriginalCode.InsertUninitialized(ResolvedHookOffset, UBlueprintHookManager::JumpBytesRequired);

	//Generate code required for calling our hook
	TArray<uint8> AppendedCode;

	//Make sure hook function is not NULL, otherwise we may experience weird crashes later
	UFunction* HookCallFunction = UBlueprintHookManager::StaticClass()->FindFunctionByName(TEXT("ExecuteBPHook"));
	fgcheck(HookCallFunction);

	//We use EX_CallMath for speed since our inserted function doesn't need context, and is fine with being called on CDO
	//EX_CallMath requires just UFunction object pointer and argument list
	AppendedCode.Add(EX_CallMath);
	WRITE_UNALIGNED(AppendedCode, ScriptPointerType, HookCallFunction);
	
	//Begin writing function parameters - we have just the original hook offset constant.
	//The hook function needs this because it stores the user hooks according to their original offset, not the resolved offset.
	AppendedCode.Add(EX_IntConst);
	WRITE_UNALIGNED(AppendedCode, int32, OriginalHookOffset);
	AppendedCode.Add(EX_EndFunctionParms);

	//Insert jump to after the resolved hook offset location for running code after hook
	AppendedCode.Add(EX_Jump);
	const int32 JumpDestination = ResolvedHookOffset + UBlueprintHookManager::JumpBytesRequired;
	WRITE_UNALIGNED(AppendedCode, CodeSkipSizeType, JumpDestination);

	//Append generated code to the end of the function's original code now
	const int32 StartOfAppendedCode = OriginalCode.Num();
	OriginalCode.Append(AppendedCode);

	//Actually insert jump to the start of appended code to original hook location
	OriginalCode[ResolvedHookOffset] = EX_Jump;
	FPlatformMemory::WriteUnaligned<CodeSkipSizeType>(&OriginalCode[ResolvedHookOffset + 1], StartOfAppendedCode);

#if DEBUG_BLUEPRINT_HOOKING
	DebugDumpFunctionScriptCode(Function, OriginalHookOffset, ResolvedHookOffset, TEXT("AfterHook"));
#endif
}

void UBlueprintHookManager::ModifyOffsetsForNewHookOffset(TArray<uint8>& Script, TSharedPtr<FJsonObject> Expression, int32 HookOffset)
{
	int32 Opcode;
	if (!Expression->TryGetNumberField(TEXT("Opcode"), Opcode)) {
		// No opcode means it's not an instruction, so we can just return;
		return;
	}

	//A computed jump could do anything at runtime - it could jump to before or after the hook, so we have no way of knowing how
	//it needs to be modified to work correctly. For now, the only predictable solution is to forbid hooking functions with them.
	fgcheckf(Opcode != EX_ComputedJump, TEXT("Cannot hook a blueprint function that contains an EX_ComputedJump instruction. There's no way to guarantee it would not crash at some point."));

	int32 OpcodeIndex = Expression->GetIntegerField(TEXT("OpcodeIndex"));
	int32 IndexAfterOpcode = OpcodeIndex + 1;

	// This switch was created by comparing to the serialization done in FSMLKismetBytecodeDisassembler::SerializeExpression to
	// identify which opcodes can jump to offsets and where exactly those jump targets reside in the script.
	switch (Opcode)
	{
	case EX_Jump:
	case EX_JumpIfNot:
	case EX_Skip:
	case EX_PushExecutionFlow:
		{
			int32 IndexOfCurrentJumpOffset = IndexAfterOpcode;
			int32 CurrentJumpOffset = Expression->GetIntegerField(TEXT("Offset"));
			if (CurrentJumpOffset > HookOffset) {
				FPlatformMemory::WriteUnaligned(&Script[IndexOfCurrentJumpOffset], (CodeSkipSizeType)(CurrentJumpOffset + UBlueprintHookManager::JumpBytesRequired));
			}
			break;
		}
	case EX_ClassContext:
	case EX_Context:
	case EX_Context_FailSilent:
		{
			// Context instructions' SkipOffsetForNull are not absolute - they are relative to the opcode index of the enclosed Expression. For all
			// known examples, they also just point to right after the Context because the intent is the value tells the code where to continue
			// executing when the Context is null/invalid, and that is quite naturally going to be the next statement. But there's nothing preventing
			// the offset from jumping to anywhere, so we'll handle the general case to be future-proof.
			// 
			// SkipOffsetForNull only needs to be adjusted if the inserting hook offset is between the Context instruction and the absolute address
			// of the jump offset, because inserting the hook pushes them away from each other.

			int32 CurrentSkipOffset = Expression->GetIntegerField(TEXT("SkipOffsetForNull"));
			int32 AbsoluteJumpOffset = Expression->GetObjectField(TEXT("Expression"))->GetIntegerField(TEXT("OpcodeIndex")) + CurrentSkipOffset;

			int32 JumpAdjustment = 0;
			// Jumping backwards to before the Context instruction and we're hooking at/after the absolute jump offset and at/before the context instruction
			if (AbsoluteJumpOffset < OpcodeIndex && HookOffset >= AbsoluteJumpOffset && HookOffset <= OpcodeIndex)
			{
				// Jump an extra jump instruction backwards
				JumpAdjustment = -UBlueprintHookManager::JumpBytesRequired;
			}
			// Jumping forwards to after the Context instruction and we're hooking at/after the next statement and BEFORE the absolute jump offset
			else if (AbsoluteJumpOffset > OpcodeIndex && HookOffset > OpcodeIndex && HookOffset < AbsoluteJumpOffset)
			{
				// Jump an extra jump instruction forwards
				JumpAdjustment = UBlueprintHookManager::JumpBytesRequired;
			}

			if (JumpAdjustment != 0) {
				// The offset is just past the Context object, so we have to get its size so we can write to the correct place
				TSharedPtr<FJsonObject> Context = Expression->GetObjectField(TEXT("Context"));
				int32 SizeOfContext = Context->GetIntegerField(TEXT("OpSizeInBytes"));
				int32 IndexOfCurrentSkipOffset = IndexAfterOpcode + SizeOfContext;
				FPlatformMemory::WriteUnaligned(&Script[IndexOfCurrentSkipOffset], (CodeSkipSizeType)(CurrentSkipOffset + JumpAdjustment));
			}
			break;
		}
	case EX_SwitchValue:
		{
			int32 CurrentJumpOffset = Expression->GetIntegerField(TEXT("OffsetToSwitchEnd"));
			if (CurrentJumpOffset > HookOffset) {
				// The switch end offset is just past the a single Word field holding the number of cases in the switch
				int32 IndexOfCurrentJumpOffset = IndexAfterOpcode + sizeof(uint16);
				FPlatformMemory::WriteUnaligned(&Script[IndexOfCurrentJumpOffset], (CodeSkipSizeType)(CurrentJumpOffset + UBlueprintHookManager::JumpBytesRequired));
				IndexOfCurrentJumpOffset += sizeof(CodeSkipSizeType); // Move past the offset we just wrote
				int32 SwitchOpSizeInBytes = Expression->GetObjectField(TEXT("Expression"))->GetIntegerField(TEXT("OpSizeInBytes"));
				IndexOfCurrentJumpOffset += SwitchOpSizeInBytes; // Move past the switch expression
				// Each case in the switch has an absolute offset reference to the next case, so we have to adjust each of them, as well
				TArray<TSharedPtr<FJsonValue>> Cases = Expression->GetArrayField(TEXT("Cases"));
				for (TSharedPtr<FJsonValue>& Case : Cases) {
					TSharedPtr<FJsonObject> NextCase = Case->AsObject();
					int32 CaseValueSizeInBytes = NextCase->GetObjectField(TEXT("CaseValue"))->GetIntegerField(TEXT("OpSizeInBytes"));
					IndexOfCurrentJumpOffset += CaseValueSizeInBytes;
					int32 OffsetToNextCase = NextCase->GetIntegerField(TEXT("OffsetToNextCase"));
					FPlatformMemory::WriteUnaligned(&Script[IndexOfCurrentJumpOffset], (CodeSkipSizeType)(OffsetToNextCase + UBlueprintHookManager::JumpBytesRequired));
					IndexOfCurrentJumpOffset += sizeof(CodeSkipSizeType);
					int32 CaseResultSizeInBytes = NextCase->GetObjectField(TEXT("CaseResult"))->GetIntegerField(TEXT("OpSizeInBytes"));
					IndexOfCurrentJumpOffset += CaseResultSizeInBytes;
				}
			}
			break;
		}
	case EX_AutoRtfmTransact:
		{
			int32 CurrentJumpOffset = Expression->GetIntegerField(TEXT("Offset"));
			if (CurrentJumpOffset > HookOffset) {
				// The offset is beyond a single TransactionId int
				int32 IndexOfCurrentJumpOffset = IndexAfterOpcode + sizeof(int32);
				FPlatformMemory::WriteUnaligned(&Script[IndexOfCurrentJumpOffset], (CodeSkipSizeType)(CurrentJumpOffset + UBlueprintHookManager::JumpBytesRequired));
			}
			break;
		}
	case EX_SkipOffsetConst:
		{
			int32 CurrentJumpOffset = Expression->GetIntegerField(TEXT("Value"));
			if (CurrentJumpOffset > HookOffset) {
				int32 IndexOfCurrentJumpOffset = IndexAfterOpcode;
				FPlatformMemory::WriteUnaligned(&Script[IndexOfCurrentJumpOffset], (CodeSkipSizeType)(CurrentJumpOffset + UBlueprintHookManager::JumpBytesRequired));
			}
			break;
		}
	}

	// Now we search all the children of this node for jump instructions that need to be updated
	for (auto& Pair : Expression->Values) {
		TSharedPtr<FJsonObject>* ExpressionValue;
		if (Pair.Value->TryGetObject(ExpressionValue)) {
			ModifyOffsetsForNewHookOffset(Script, *ExpressionValue, HookOffset);
			continue;
		}
		TArray<TSharedPtr<FJsonValue>>* ArrayValue;
		if (Pair.Value->TryGetArray(ArrayValue)) {
			for (TSharedPtr<FJsonValue> Value : *ArrayValue) {
				if (Value->TryGetObject(ExpressionValue)) {
					ModifyOffsetsForNewHookOffset(Script, *ExpressionValue, HookOffset);
				}
			}
		}
	}
}

void FFunctionHookInfo::InvokeBlueprintHook(FFrame& Frame, int32 HookOffset) {
	FBlueprintHookHelper HookHelper{Frame, ReturnStatementOffset};
	const TArray<TFunction<HookFunctionSignature>>& Hooks = this->CodeOffsetByHookList.FindChecked(HookOffset);
	for (const TFunction<HookFunctionSignature>& Hook : Hooks) {
		Hook(HookHelper);
	}
}

void FFunctionHookInfo::RecalculateReturnStatementOffset(UFunction* Function) {
	FSMLKismetBytecodeDisassembler Disassembler;
	ReturnStatementOffset = Disassembler.GetReturnStatementOffset(Function);
}

void UBlueprintHookManager::HookBlueprintFunction(UFunction* Function, const TFunction<HookFunctionSignature>& Hook, const int32 HookOffset) {
#if !WITH_EDITOR
	fgcheckf(Function, TEXT("HookBPFunction: Function provided is null"));
	fgcheckf(Function->Script.Num(), TEXT("HookBPFunction: Function provided is not implemented in BP"));

	//Make sure to add outer UClass to root set to avoid it being Garbage Collected
	//Because otherwise after GC script byte code will be reloaded, without our hooks applied
	UClass* OuterUClass = Function->GetTypedOuter<UClass>();
	fgcheck(OuterUClass);
	HookedClasses.AddUnique(OuterUClass);

#if UE_BLUEPRINT_EVENTGRAPH_FASTCALLS
	if (Function->EventGraphFunction != nullptr) {
		UE_LOG(LogBlueprintHookManager, Warning, TEXT("Attempt to hook event graph call stub function with fast-call enabled, disabling fast call for that function"));
		UE_LOG(LogBlueprintHookManager, Warning, TEXT("It may result in performance regression for called function, if you need highest performance possible, consider hooking event graph function"));
		UE_LOG(LogBlueprintHookManager, Warning, TEXT("Event graph function: %s, From Offset: %d"), *Function->EventGraphFunction->GetPathName(), Function->EventGraphCallOffset);
		Function->EventGraphFunction = nullptr;
	}
#endif

	FSMLKismetBytecodeDisassembler Disassembler;
	bool IsFirstTimeFunctionEverHooked = !HookedFunctions.Contains(Function);
	FFunctionHookInfo& FunctionHookInfo = HookedFunctions.FindOrAdd(Function);
	if (IsFirstTimeFunctionEverHooked)
	{
		FunctionHookInfo.OriginalReturnStatementOffset = Disassembler.GetReturnStatementOffset(Function);
	}

	//Each new offset modifies the code but we need to keep track by original offsets because callers cannot know how the code has been modified by other hooks.
	int32 StoredHookOffset = HookOffset == EPredefinedHookOffset::Return ? FunctionHookInfo.OriginalReturnStatementOffset : HookOffset;
	TArray<TFunction<HookFunctionSignature>>& InstalledHooks = FunctionHookInfo.CodeOffsetByHookList.FindOrAdd(StoredHookOffset);

	if (InstalledHooks.Num() == 0) {
		//First time function is hooked at this requested offset. We need to resolve what the offset actually is.

		int32 ResolvedHookOffset = HookOffset;
		if (ResolvedHookOffset == EPredefinedHookOffset::Return) {
			//Special case for hooking the return, which has an absolute location that we can directly find.
			//For now Kismet Compiler will always generate only one Return node, so all
			//execution paths will end up either with executing it directly or jumping to it
			//So we need to hook only in one place to handle all possible execution paths
			ResolvedHookOffset = Disassembler.GetReturnStatementOffset(Function);
		} else {
			//Each new offset moves the subsequent code by UBlueprintHookManager::JumpBytesRequired to make room for the hook jump.
			//So the resolved offset must be increased by JumpBytesRequired for every hook installed earlier than it in the instruction list.
			TArray<int32> HookOffsetKeys;
			FunctionHookInfo.CodeOffsetByHookList.GetKeys(HookOffsetKeys);
			for (int32 ExistingHookedOffset : HookOffsetKeys) {
				if (ExistingHookedOffset < HookOffset) {
					ResolvedHookOffset += UBlueprintHookManager::JumpBytesRequired;
				}
			}
		}

		InstallBlueprintHook(Function, StoredHookOffset, ResolvedHookOffset);

		//Update cached return instruction offset because we've edited the function and moved instructions around
		FunctionHookInfo.RecalculateReturnStatementOffset(Function);
	}
	//Add provided hook into the array
	InstalledHooks.Add(Hook);

#endif
}

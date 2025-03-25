#include "Patching/BlueprintHookManager.h"
#include "SatisfactoryModLoader.h"
#include "Patching/BlueprintHookingTypes.h"
#include "Toolkit/ScriptExprAssembler.h"
#include "UObject/ObjectSaveContext.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/GameInstance.h"
#include "Misc/CommandLine.h"
#include "Toolkit/HookingCodeGeneration.h"
#include "Toolkit/ScriptExprHelper.h"
#include "Patching/BlueprintHookBlueprint.h"

DEFINE_LOG_CATEGORY_STATIC(LogBlueprintHookManager, All, All);

bool UBlueprintHookManager::GetOriginalScriptCodeFromFunction(const UFunction* InFunction, TArray<uint8>& OutOriginalScriptCode) {
	constexpr int32 HookedFunctionFooterSizeBytes = 6;
	const int32 NumScriptBytes = InFunction->Script.Num();
	OutOriginalScriptCode.Empty(NumScriptBytes);

	// We can tell that the function is hooked if it's last instruction is EX_DeprecatedOp4A. Normal non-hooked functions will have EX_EndOfScript as the last instruction instead
	if (NumScriptBytes >= HookedFunctionFooterSizeBytes && InFunction->Script[NumScriptBytes - 1] == EX_DeprecatedOp4A) {

		// Hooked functions will contain EX_NothingInt32 before EX_DeprecatedOp4A, with int32 argument being the size of the original function code starting right before this instruction
		if (InFunction->Script[NumScriptBytes - HookedFunctionFooterSizeBytes] == EX_NothingInt32) {
			const int32 OriginalFunctionScriptSize = FPlatformMemory::ReadUnaligned<int32>(&InFunction->Script[NumScriptBytes - HookedFunctionFooterSizeBytes + 1]);
			const int32 OriginalFunctionScriptOffset = NumScriptBytes - HookedFunctionFooterSizeBytes - OriginalFunctionScriptSize;

			if (OriginalFunctionScriptSize > 0 && OriginalFunctionScriptOffset > 0) {
				OutOriginalScriptCode.Append(&InFunction->Script[OriginalFunctionScriptOffset], OriginalFunctionScriptSize);
				return true;
			}
		}
	}
	// This function has not been hooked otherwise and does not need any patch-ups
	OutOriginalScriptCode.Append(InFunction->Script);
	return false;
}

void UBlueprintHookManager::UpdateFunctionScriptCode(UFunction* InFunction, const TArray<uint8>& NewScriptCode, const TArray<uint8>& OriginalScriptCode) {
	check(IsInGameThread());

	TArray<uint8> ResultFunctionScriptCode;
	ResultFunctionScriptCode.Append(NewScriptCode);

	// Append original code after the current code
	ResultFunctionScriptCode.Append(OriginalScriptCode);
	
	// Append instruction with original code size
	ResultFunctionScriptCode.Add(EX_NothingInt32);
	const int32 OriginalScriptCodeSize = OriginalScriptCode.Num();
	const int32 OriginalScriptCodeSizeOffset = ResultFunctionScriptCode.AddZeroed(sizeof(OriginalScriptCodeSize));
	FPlatformMemory::WriteUnaligned(&ResultFunctionScriptCode[OriginalScriptCodeSizeOffset], OriginalScriptCodeSize);

	// Write EX_DeprecatedOp4A as a marker that there is an original code attachment to this function script
	ResultFunctionScriptCode.Add(EX_DeprecatedOp4A);

	// Replace the code of the function
	InFunction->Script = MoveTemp(ResultFunctionScriptCode);
}

static TAutoConsoleVariable<bool> CVarDumpBlueprintPatchingResults(
	TEXT("SML.DumpBlueprintPatchingResults"),
	false,
	TEXT("1 = Dump function code to log after blueprint hook application; 0 = only dump on errors"),
	ECVF_Default);

void UBlueprintHookManager::ApplyBlueprintHooksToBlueprintClass(UBlueprintGeneratedClass* BlueprintGeneratedClass) const {
	TArray<FBlueprintHookDefinition> BlueprintHooks;
	
	// Collect all active hook registrations for this class
	if (const TArray<TSoftObjectPtr<UHookBlueprintGeneratedClass>>* RegisteredHooks = InstalledHooksPerBlueprintGeneratedClass.Find(BlueprintGeneratedClass->GetClassPathName())) {
		for (const TSoftObjectPtr<UHookBlueprintGeneratedClass>& HookBlueprintClass : *RegisteredHooks) {
			// Attempt to load the hook class. If the asset has been deleted in the editor this might fail.
			if (UHookBlueprintGeneratedClass* LoadedHookClass = HookBlueprintClass.LoadSynchronous()) {
				for (const FBlueprintHookDefinition& HookDefinition : LoadedHookClass->HookDescriptors) {
					// Check that hook definition has valid data and targets this class
					if (HookDefinition.HookFunction && HookDefinition.TargetFunction && HookDefinition.TargetSpecifier && HookDefinition.TargetFunction->GetOuterUClass() == BlueprintGeneratedClass) {
						BlueprintHooks.Add(HookDefinition);
					}
				}
			}
		}
	}
	
	// Disassemble all blueprint functions in the class
	TMap<UFunction*, TArray<TSharedPtr<FScriptExpr>>> FunctionToFunctionScript;
	TMap<UFunction*, TArray<uint8>> FunctionToOriginalScript;
	UFunction* ExecuteUbergraphFunction{};
	bool bHasCurrentlyHookedFunctions = false;
	bool bIsBlueprintCurrentlyUnsafeToModify = false;

	for (TFieldIterator<UFunction> FunctionIt(BlueprintGeneratedClass, EFieldIterationFlags::IncludeDeprecated); FunctionIt; ++FunctionIt) {
		UFunction* BlueprintFunction = *FunctionIt;
		if (!BlueprintFunction->HasAnyFunctionFlags(FUNC_Native) && !BlueprintFunction->Script.IsEmpty()) {
			// Check that the function is currently safe to modify. If any of the BP functions are not safe to modify, hooking is cancelled
			if (!FHookCodeGenFunctionContext::CheckCanModifyFunctionScriptAndLocals(BlueprintFunction, false)) {
				UE_LOG(LogBlueprintHookManager, Warning, TEXT("Refusing to apply hooks to Blueprint %s because function %s is not safe to modify (call to the function is on the script stack)"),
					*BlueprintGeneratedClass->GetFullName(), *BlueprintFunction->GetFullName());
				bIsBlueprintCurrentlyUnsafeToModify = true;
				continue;
			}

			// Retrieve the original script code in case we have already applied hooks previously
			TArray<uint8> OriginalFunctionScript;
			bHasCurrentlyHookedFunctions |= GetOriginalScriptCodeFromFunction(BlueprintFunction, OriginalFunctionScript);
			FunctionToOriginalScript.Add(BlueprintFunction, OriginalFunctionScript);

			// Run the disassembler on the function code and save the results
			TArray<TSharedPtr<FScriptExpr>> LinearExecutionSequence;
			FScriptExprAssembler::DisassembleFunction(OriginalFunctionScript, LinearExecutionSequence);
			FunctionToFunctionScript.Add(BlueprintFunction, LinearExecutionSequence);

			// If this function is a merged ubergraph function, mark it separately as well
			if (BlueprintFunction->GetName().StartsWith(TEXT("ExecuteUbergraph")) || BlueprintFunction->HasAnyFunctionFlags(FUNC_UbergraphFunction)) {
				ExecuteUbergraphFunction = BlueprintFunction;
			}
		}
	}

	// If we have no functions currently hooked and no active hooks for this class, or the blueprint is not safe to modify, stop now
	if (bIsBlueprintCurrentlyUnsafeToModify || (!bHasCurrentlyHookedFunctions && BlueprintHooks.IsEmpty())) {
		return;
	}

	// Build a map from the event function to its entry point in the ubergraph function
	TMap<UFunction*, TSharedPtr<FScriptExpr>> EventFunctionToUberGraphEntryPoint;
	if (ExecuteUbergraphFunction != nullptr) {
		const TArray<TSharedPtr<FScriptExpr>> UberGraphFunctionScript = FunctionToFunctionScript.FindChecked(ExecuteUbergraphFunction);

		// Process functions to spot any calls into the ubergraph so that we can patch them up later
		for (const TPair<UFunction*, TArray<TSharedPtr<FScriptExpr>>>& FunctionToScriptPair : FunctionToFunctionScript) {
			for (const TSharedPtr<FScriptExpr>& FunctionStatement : FunctionToScriptPair.Value) {
				// If we have a local final function call into the ubergraph function, this is an event function stub
				if (FunctionStatement->Opcode == EX_LocalFinalFunction && FunctionStatement->RequireOperand(0, FScriptExprOperand::TypeObject).Object == ExecuteUbergraphFunction) {
					// Resolve to which specific statement this event points
					const TSharedPtr<FScriptExpr> OffsetWithinUbergraphConst = FunctionStatement->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;
					check(OffsetWithinUbergraphConst.IsValid() && OffsetWithinUbergraphConst->Opcode == EX_IntConst);
					const int32 OffsetWithinUbergraph = OffsetWithinUbergraphConst->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer;
					const TSharedPtr<FScriptExpr> UberGraphEntryPoint = FScriptExprHelper::FindStatementByScriptOffset(UberGraphFunctionScript, OffsetWithinUbergraph);
					EventFunctionToUberGraphEntryPoint.Add(FunctionToScriptPair.Key, UberGraphEntryPoint);
				}
			}
		}
	}

	// Build a mapping for each hook to the target function that it should be applied to
	TMap<UFunction*, TArray<FBlueprintHookDefinition>> FunctionToHookMapping;
	for (const FBlueprintHookDefinition& HookDefinition : BlueprintHooks) {
		// Make sure that this hook definition even has a valid target in this blueprint class
		if (FunctionToFunctionScript.Contains(HookDefinition.TargetFunction)) {
			// If this hook definition attempts to hook the event function stub, add the hook to the ubergraph function instead
			if (EventFunctionToUberGraphEntryPoint.Contains(HookDefinition.TargetFunction)) {
				FunctionToHookMapping.FindOrAdd(ExecuteUbergraphFunction).Add(HookDefinition);
			} else if (HookDefinition.TargetFunction != ExecuteUbergraphFunction) {
				// Add the hook to the target function normally otherwise
				FunctionToHookMapping.FindOrAdd(HookDefinition.TargetFunction).Add(HookDefinition);
			} else {
				// Print a warning if we are attempting to hook the ubergraph function directly - it can only be hooked by hooking a particular event
				UE_LOG(LogBlueprintHookManager, Error, TEXT("Failed to apply hook %s because hooks cannot target ubergraph function directly. Hook one of the events instead."), *GetFullNameSafe(HookDefinition.HookFunction));
			}	
		} else {
			// Print a warning if we failed to apply the hook because the function target is not valid
			UE_LOG(LogBlueprintHookManager, Error, TEXT("Failed to apply hook %s to function %s because the function has no script code or is not located in the target class"),
				*GetFullNameSafe(HookDefinition.HookFunction), *GetFullNameSafe(HookDefinition.TargetFunction));
		}
	}

	// Generate new code for all the functions that have hooks registered
	TMap<UFunction*, TArray<TSharedPtr<FScriptExpr>>> FunctionToGeneratedCode;
	TMap<UFunction*, TSharedPtr<FScriptExpr>> EventFunctionToGeneratedEntryPoint;
	TSet<UFunction*> FunctionsWithFailedHooks;
	
	for (const TPair<UFunction*, TArray<FBlueprintHookDefinition>>& Pair : FunctionToHookMapping) {
		// Create the function context for this function
		const TArray<TSharedPtr<FScriptExpr>> OriginalFunctionScript = FunctionToFunctionScript.FindChecked(Pair.Key);
		FHookCodeGenFunctionContext FunctionContext{Pair.Key, OriginalFunctionScript};

		// If this is an ubergraph function, initialize it with the data for each event function contained in it
		if (Pair.Key == ExecuteUbergraphFunction) {
			FunctionContext.InitializeUbergraphFunction(EventFunctionToUberGraphEntryPoint);
		}

		// Resolve hook targets and then generate the function code after the hook application
		FunctionContext.ResolveHookTargets(Pair.Value);
		TArray<TSharedPtr<FScriptExpr>> FunctionGeneratedCode;
		const bool bInstalledAllHooksSuccessfully = FunctionContext.GenerateFunctionCode(FunctionGeneratedCode, EventFunctionToGeneratedEntryPoint);

		if (!bInstalledAllHooksSuccessfully) {
			FunctionsWithFailedHooks.Add(Pair.Key);
		}
		FunctionToGeneratedCode.Add(Pair.Key, FunctionGeneratedCode);
	}

	// If we have ended up rewriting the event graph function, we need to make sure that we will patch up all the events that call into it
	if (ExecuteUbergraphFunction && FunctionToGeneratedCode.Contains(ExecuteUbergraphFunction)) {
		for (const TPair<UFunction*, TSharedPtr<FScriptExpr>>& Pair : EventFunctionToUberGraphEntryPoint) {

			// If we have not generated any code for this function, use the original code
			if (!FunctionToGeneratedCode.Contains(Pair.Key)) {
				const TArray<TSharedPtr<FScriptExpr>> OriginalFunctionScript = FunctionToFunctionScript.FindChecked(Pair.Key);
				TArray<TSharedPtr<FScriptExpr>> GeneratedFunctionScript;
				for (const TSharedPtr<FScriptExpr>& FunctionStatement : OriginalFunctionScript) {
					GeneratedFunctionScript.Add(FunctionStatement->DeepCopy());
				}
				FunctionToGeneratedCode.Add(Pair.Key, GeneratedFunctionScript);
			}
		}
	}
	
#if WITH_EDITORONLY_DATA
	// If we are re-assembling any of the functions in this blueprint, we need to thrash the debug data. Script offsets contained inside are no longer valid after functions are re-assembled
	// TODO: We could patch-up debug data as well, but that would require some extra work. We could look into it if debugging support for hooked Blueprints is important. Debug data for them can still be regenerated by recompile.
	BlueprintGeneratedClass->DebugData = FBlueprintDebugData{};
#endif

	// Utility function to split a single giant string into separate lines to avoid log being trimmed
	const auto DumpStringWithSplitLines = [](const TCHAR* InLongMessageString) {
		TArray<FString> SplitLogLines;
		FString(InLongMessageString).ParseIntoArrayLines(SplitLogLines);
		for (int32 i = 0; i < SplitLogLines.Num(); i++) {
			UE_LOG(LogBlueprintHookManager, Display, TEXT("%s"), *SplitLogLines[i]);
		}
	};

	// Utility to dump the code of the function in the log if requested, or if some hooks failed application
	const auto DumpFunctionCodeToLog = [&](const UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& GeneratedFunctionCode) {
		const bool bFailedToInstallFunctionHooks = FunctionsWithFailedHooks.Contains(TargetFunction);
		const bool bDumpAllFunctionsCode = FParse::Param(FCommandLine::Get(), TEXT("DumpBlueprintPatchingResults")) || CVarDumpBlueprintPatchingResults.GetValueOnGameThread();

		// Log original function script if we failed to install some hooks, or we are asked to dump all functions code
		if (bFailedToInstallFunctionHooks || bDumpAllFunctionsCode) {
			if (bFailedToInstallFunctionHooks) {
				UE_LOG(LogBlueprintHookManager, Warning, TEXT("Function %s failed to install some of the hooks. Function dumps for debugging are provided below:"), *TargetFunction->GetPathName());
			}
			TStringBuilder<256> OriginalCodeStringBuffer;
			FScriptExprHelper::DumpFunctionToString(TargetFunction, FunctionToFunctionScript.FindChecked(TargetFunction), 0, OriginalCodeStringBuffer);
			UE_LOG(LogBlueprintHookManager, Display, TEXT("Original function code %s"), *TargetFunction->GetPathName());
			DumpStringWithSplitLines(OriginalCodeStringBuffer.ToString());
		}

		// Log generated code and re-assembled code only if dumping all functions code
		if (bDumpAllFunctionsCode) {
			// Log generated function code
			TStringBuilder<256> GeneratedCodeStringBuffer;
			FScriptExprHelper::DumpFunctionToString(TargetFunction, GeneratedFunctionCode, 0, GeneratedCodeStringBuffer);
			UE_LOG(LogBlueprintHookManager, Display, TEXT("Generated function code %s"), *TargetFunction->GetPathName());
			DumpStringWithSplitLines(GeneratedCodeStringBuffer.ToString());

			// Log function code after it has been re-assembled
			TArray<TSharedPtr<FScriptExpr>> UpdatedFunctionScript;
			FScriptExprAssembler::DisassembleFunction(TargetFunction->Script, UpdatedFunctionScript);
			TStringBuilder<256> UpdatedFunctionCodeStringBuffer;
			FScriptExprHelper::DumpFunctionToString(TargetFunction, UpdatedFunctionScript, 0, UpdatedFunctionCodeStringBuffer);
			UE_LOG(LogBlueprintHookManager, Display, TEXT("Final re-assembled function code %s"), *TargetFunction->GetPathName());
			DumpStringWithSplitLines(UpdatedFunctionCodeStringBuffer.ToString());
		}
	};

	// Generate code for the ubergraph function first - event function stubs need to know the script offsets inside the ubergraph before they can be generated
	if (ExecuteUbergraphFunction && FunctionToGeneratedCode.Contains(ExecuteUbergraphFunction)) {
		const TArray<TSharedPtr<FScriptExpr>> GeneratedFunctionCode = FunctionToGeneratedCode.FindAndRemoveChecked(ExecuteUbergraphFunction);
		const TArray<uint8> OriginalScript = FunctionToOriginalScript.FindChecked(ExecuteUbergraphFunction);

		// Assemble the bytecode stream and apply it to the function
		TArray<uint8> UpdatedScript;
		FScriptExprAssembler::AssembleFunction(GeneratedFunctionCode, UpdatedScript);
		UpdateFunctionScriptCode(ExecuteUbergraphFunction, UpdatedScript, OriginalScript);

		// Iterate over all event function stubs and update the generated call into the ubergraph with the code offsets of the functions entry points
		for (const TPair<UFunction*, TSharedPtr<FScriptExpr>>& Pair : EventFunctionToGeneratedEntryPoint) {
			const TSharedPtr<FScriptExpr> NewEntryPoint = Pair.Value;
			const TArray<TSharedPtr<FScriptExpr>> FunctionGeneratedCode = FunctionToGeneratedCode.FindChecked(Pair.Key);

			for (const TSharedPtr<FScriptExpr>& FunctionStatement : FunctionGeneratedCode) {
				// Local final function call into the ubergraph has the event entry point offset as the first argument
				if (FunctionStatement->Opcode == EX_LocalFinalFunction && FunctionStatement->RequireOperand(0, FScriptExprOperand::TypeObject).Object == ExecuteUbergraphFunction) {
					const TSharedPtr<FScriptExpr> UberGraphEntryPointConstant = FunctionStatement->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;
					check(UberGraphEntryPointConstant.IsValid() && UberGraphEntryPointConstant->Opcode == EX_IntConst);
					UberGraphEntryPointConstant->Operands[0].Integer = NewEntryPoint->ScriptOffset;
				}
			}
		}
		// Dump re-assembled function bytecode for debugging if necessary
		DumpFunctionCodeToLog(ExecuteUbergraphFunction, GeneratedFunctionCode);
	}

	// Assemble code for the rest of the functions now
	for (const TPair<UFunction*, TArray<TSharedPtr<FScriptExpr>>>& Pair : FunctionToGeneratedCode) {
		const TArray<TSharedPtr<FScriptExpr>> GeneratedFunctionCode = Pair.Value;
		const TArray<uint8> OriginalScript = FunctionToOriginalScript.FindChecked(Pair.Key);
		
		// Assemble the bytecode stream and apply it to the function
		TArray<uint8> UpdatedScript;
		FScriptExprAssembler::AssembleFunction(GeneratedFunctionCode, UpdatedScript);
		UpdateFunctionScriptCode(Pair.Key, UpdatedScript, OriginalScript);

		// Dump re-assembled function bytecode for debugging if necessary
		DumpFunctionCodeToLog(Pair.Key, GeneratedFunctionCode);
	}
}


// Names of owner classes for hooked blueprint functions, used to avoid relatively expensive sanitization pass on functions on classes that are not hooked
static TSet<FName> HookedBlueprintFunctionClassFNameSet;

void UBlueprintHookManager::RegisterStaticHooks() {
#if WITH_EDITOR
	// When we are running in the uncooked environment with asset hooking allowed, we need to register a hook to ensure that when assets are saved, they do not contain
	// transient script code modified by the blueprint hooking. This is relevant in editor when saving hooked assets after running PIE, in all other cases this hook does not modify the assets
	if (FSatisfactoryModLoader::IsAssetHookingAllowed()) {
		FCoreUObjectDelegates::OnObjectPreSave.AddStatic([](UObject* InObject, FObjectPreSaveContext) {
			UFunction* Function = Cast<UFunction>(InObject);
			if (Function && !Function->Script.IsEmpty() && HookedBlueprintFunctionClassFNameSet.Contains(Function->GetOuterUClass()->GetFName())) {
				SanitizeFunctionScriptCodeBeforeSave(Function);
			}
		});
		// TODO: Add OnAssetDeleted callback here and to all other systems to delete stale hooks
	}
#endif
}

void UBlueprintHookManager::SanitizeFunctionScriptCodeBeforeSave(UFunction* InFunction) {
	// Replace the function script with the original code if it has been hooked
	TArray<uint8> OriginalFunctionScript;
	if (GetOriginalScriptCodeFromFunction(InFunction, OriginalFunctionScript)) {
		InFunction->Script = OriginalFunctionScript;
	}
}

void UBlueprintHookManager::RegisterBlueprintHook(UGameInstance* OwnerGameInstance, UHookBlueprintGeneratedClass* HookBlueprintGeneratedClass) {
	// Silently ignore all hook requests if asset hooking is not allowed in this environment
	if (!FSatisfactoryModLoader::IsAssetHookingAllowed()) {
		return;
	}
	
	// Check that hook class is valid
	if (HookBlueprintGeneratedClass == nullptr) {
		UE_LOG(LogBlueprintHookManager, Error, TEXT("NULL hook blueprint class passed to register hook"));
		return;
	}
	
	// Check that game instance is valid
	if (OwnerGameInstance == nullptr) {
		UE_LOG(LogBlueprintHookManager, Error, TEXT("Failed to register blueprint hook %s because game instance was null"), *GetFullNameSafe(HookBlueprintGeneratedClass));
		return;
	}

	// Resolve list of classes to which hooks need to be applied and register them
	TSet<UBlueprintGeneratedClass*> ClassesToReapplyHooks;
	for (const FBlueprintHookDefinition& HookDefinition : HookBlueprintGeneratedClass->HookDescriptors) {

		// Make sure the hook target function in question is actually valid
		if (HookDefinition.TargetFunction == nullptr || HookDefinition.HookFunction == nullptr || HookDefinition.TargetSpecifier == nullptr) {
			UE_LOG(LogBlueprintHookManager, Error, TEXT("Blueprint hook %s has invalid data, blueprint might need to be recompiled."), *HookBlueprintGeneratedClass->GetFullName());
			continue;
		}

		// Make sure the function is actually defined by a blueprint class
		UBlueprintGeneratedClass* TargetBlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(HookDefinition.TargetFunction->GetOuterUClass());
		if (TargetBlueprintGeneratedClass == nullptr) {
			UE_LOG(LogBlueprintHookManager, Error, TEXT("Failed to apply blueprint hook %s because its target function %s is not defined in Blueprint"),
				*GetFullNameSafe(HookDefinition.TargetFunction), *HookDefinition.TargetFunction->GetFullName());
			continue;
		}

		// Add the class to the hook re-application list and to the list of hooks for the target blueprint generated class
		ClassesToReapplyHooks.Add(TargetBlueprintGeneratedClass);
		TArray<TSoftObjectPtr<UHookBlueprintGeneratedClass>>& InstalledHooksForBlueprintClass = InstalledHooksPerBlueprintGeneratedClass.FindOrAdd(TargetBlueprintGeneratedClass->GetClassPathName());
		InstalledHooksForBlueprintClass.AddUnique(TSoftObjectPtr<UHookBlueprintGeneratedClass>(HookBlueprintGeneratedClass));
	}

	// Keep the hook object itself from being garbage collected
	OwnerGameInstance->RegisterReferencedObject(HookBlueprintGeneratedClass);

	// Re-apply blueprint hooks to all the blueprint classes
	for (UBlueprintGeneratedClass* BlueprintGeneratedClass : ClassesToReapplyHooks) {
		// Make sure the blueprint is kept in memory until the game instance runs out of scope
		OwnerGameInstance->RegisterReferencedObject(BlueprintGeneratedClass);

		// Apply blueprint hooks to that class
		ApplyBlueprintHooksToBlueprintClass(BlueprintGeneratedClass);
	}
}

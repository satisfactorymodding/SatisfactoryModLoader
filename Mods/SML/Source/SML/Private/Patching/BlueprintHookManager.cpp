#include "Patching/BlueprintHookManager.h"
#include "SatisfactoryModLoader.h"
#include "Patching/BlueprintHookingTypes.h"
#include "Toolkit/ScriptExprAssembler.h"
#include "UObject/ObjectSaveContext.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/GameInstance.h"
#include "Engine/Level.h"
#include "Misc/CommandLine.h"
#include "Toolkit/HookingCodeGeneration.h"
#include "Toolkit/ScriptExprHelper.h"
#include "Patching/BlueprintHookBlueprint.h"

DEFINE_LOG_CATEGORY_STATIC(LogBlueprintHookManager, All, All);

UBlueprintMixinHostComponent::UBlueprintMixinHostComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = true;	
}

void UBlueprintMixinHostComponent::OnComponentCreated() {
	Super::OnComponentCreated();

	const UWorld* OwnerWorld = GetWorld();
	AActor* OwnerActor = GetOwner();

	// Do not create mixin instances for non-game world actors. We do not want to modify editor worlds
	// since they will be saved, and we only want active mixins to be saved in game and not within the editor assets.
	if (OwnerActor && OwnerWorld && OwnerWorld->IsGameWorld()) {

		// Check which mixins we might already have to avoid creating them multiple times
		TSet<UHookBlueprintGeneratedClass*> ExistingMixinInstanceClasses;
		for (const UBlueprintActorMixin* ActorMixin : MixinInstances) {
			if (ActorMixin) {
				ExistingMixinInstanceClasses.Add(Cast<UHookBlueprintGeneratedClass>(ActorMixin->GetClass()));
			}
		}
		
		// Create mixin instances or find existing ones. Skip nulls since editor can null out references to deleted assets
		for (UHookBlueprintGeneratedClass* MixinClass : MixinClasses) {
			if (MixinClass && !ExistingMixinInstanceClasses.Contains(MixinClass) && MixinClass->IsChildOf<UBlueprintActorMixin>() && !MixinClass->HasAnyClassFlags(CLASS_Deprecated | CLASS_Abstract)) {

				// Attempt to find an existing mixin object. If we failed, create a new one
				const FName MixinInstanceName = *FString::Printf(TEXT("Mixin_%s"), *MixinClass->GetName());
				UBlueprintActorMixin* ActorMixinObject = Cast<UBlueprintActorMixin>(StaticFindObjectFast(MixinClass, OwnerActor, MixinInstanceName, true));
				if (ActorMixinObject == nullptr) {
					ActorMixinObject = NewObject<UBlueprintActorMixin>(OwnerActor, MixinClass, MixinInstanceName);
					check(ActorMixinObject);
				}

				// Add mixin object to the list
				MixinInstances.Add(ActorMixinObject);
			}
		}
	}

	// Evaluate overlay component tree for each mixin
	for (UBlueprintActorMixin* ActorMixin : MixinInstances) {
		if (ActorMixin) {
			const UHookBlueprintGeneratedClass* MixinGeneratedClass = Cast<UHookBlueprintGeneratedClass>(ActorMixin->GetClass());
			if (MixinGeneratedClass && MixinGeneratedClass->OverlayComponentTree) {
				MixinGeneratedClass->OverlayComponentTree->ExecuteOnActor(OwnerActor, ActorMixin);
			}
		}
	}

	// Dispatch OnMixinCreated to all the mixins now that we have created components for all of them
	bool bAnyMixinsRequireComponentTick = false;
	for (UBlueprintActorMixin* ActorMixin : MixinInstances) {
		if (ActorMixin) {
			ActorMixin->DispatchMixinCreated();
			bAnyMixinsRequireComponentTick |= ActorMixin->bEnableMixinTick;
		}
	}

	// If any of our mixins require Tick to be dispatched, set bCanEverTick to true
	if (bAnyMixinsRequireComponentTick) {
		PrimaryComponentTick.bCanEverTick = true;
	}
}

void UBlueprintMixinHostComponent::BeginPlay() {
	Super::BeginPlay();

	// Dispatch BeginPlay to mixins
	for (UBlueprintActorMixin* ActorMixin : MixinInstances) {
		if (ActorMixin) {
			ActorMixin->DispatchBeginPlay();
		}
	}
}

void UBlueprintMixinHostComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Tick mixins only if we are ticking actors, or if we are paused. Mixin actor tick mimics Actor tick, which runs even if the game is paused
	if (TickType == LEVELTICK_All || TickType == LEVELTICK_PauseTick) {
		// Dispatch Tick to mixins
		for (UBlueprintActorMixin* ActorMixin : MixinInstances) {
			if (ActorMixin && ActorMixin->bEnableMixinTick) {
				ActorMixin->DispatchTick(DeltaTime);
			}
		}
	}
}

void UBlueprintMixinHostComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	// Dispatch EndPlay to mixins
	for (UBlueprintActorMixin* ActorMixin : MixinInstances) {
		if (ActorMixin) {
			ActorMixin->DispatchEndPlay(EndPlayReason);	
		}
	}
	Super::EndPlay(EndPlayReason);
}

UBlueprintActorMixin* UBlueprintMixinHostComponent::FindMixinByClass(TSubclassOf<UBlueprintActorMixin> MixinClass) const {
	for (UBlueprintActorMixin* ActorMixin : MixinInstances) {
		if (ActorMixin && ActorMixin->GetClass() == MixinClass) {
			return ActorMixin;
		}
	}
	return nullptr;
}

void UMixinInputDelegateBinding::BindToInputComponent(UInputComponent* InputComponent, UObject* ObjectToBindTo) const {
	if (AActor* Actor = Cast<AActor>(ObjectToBindTo)) {
		UBlueprintMixinHostComponent* MixinHostComponent = Actor->GetComponentByClass<UBlueprintMixinHostComponent>();
		if (MixinHostComponent) {
			for (UBlueprintActorMixin* ActorMixin : MixinHostComponent->MixinInstances) {
				UInputDelegateBinding::BindInputDelegates(ActorMixin->GetClass(), InputComponent, ActorMixin);
			}
		}
	}
}

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

void UBlueprintHookManager::ApplyRegisteredHooksToBlueprintClass(UBlueprintGeneratedClass* BlueprintGeneratedClass) const {
	TArray<FBlueprintHookDefinition> BlueprintHooks;
	TArray<UHookBlueprintGeneratedClass*> ActorMixins;
	
	// Collect all active hook registrations for this class
	if (const TArray<TSoftObjectPtr<UHookBlueprintGeneratedClass>>* RegisteredHooks = InstalledHooksPerBlueprintGeneratedClass.Find(BlueprintGeneratedClass->GetClassPathName())) {
		for (const TSoftObjectPtr<UHookBlueprintGeneratedClass>& HookBlueprintClass : *RegisteredHooks) {
			// Attempt to load the hook class. If the asset has been deleted in the editor this might fail.
			if (UHookBlueprintGeneratedClass* LoadedHookClass = HookBlueprintClass.LoadSynchronous()) {

				// Get hook descriptors from the class
				for (const FBlueprintHookDefinition& HookDefinition : LoadedHookClass->HookDescriptors) {
					// Check that hook definition has valid data and targets this class
					if (HookDefinition.HookFunction && HookDefinition.TargetFunction && HookDefinition.TargetSpecifier && HookDefinition.TargetFunction->GetOuterUClass() == BlueprintGeneratedClass) {
						BlueprintHooks.Add(HookDefinition);
					}
				}
				// Add this class as a mixin if provided class is the target and this class is a mixin hook
				if (LoadedHookClass->MixinTargetClass && LoadedHookClass->MixinTargetClass == BlueprintGeneratedClass && LoadedHookClass->IsChildOf<UBlueprintActorMixin>()) {
					ActorMixins.Add(LoadedHookClass);
				}
			}
		}
	}

	// We have to apply hooks even if we have no active hooks, because we might want to reset currently applied hooks
	ApplyBlueprintHooksToBlueprintClass(BlueprintGeneratedClass, BlueprintHooks);
	// Apply actor mixins if this is an actor class as well
	if (BlueprintGeneratedClass->IsChildOf<AActor>() && BlueprintGeneratedClass->SimpleConstructionScript) {
		ApplyActorMixinsToBlueprintClass(BlueprintGeneratedClass, ActorMixins);
	}
}

void UBlueprintHookManager::ApplyBlueprintHooksToBlueprintClass(UBlueprintGeneratedClass* BlueprintGeneratedClass, const TArray<FBlueprintHookDefinition>& BlueprintHooks) const {
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
			FunctionContext.InitializeUbergraphFunction(EventFunctionToUberGraphEntryPoint, FunctionToFunctionScript);
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

void UBlueprintHookManager::ApplyActorMixinsToBlueprintClass(UBlueprintGeneratedClass* BlueprintGeneratedClass, TArray<UHookBlueprintGeneratedClass*>& BlueprintMixins) const {
	// Find an existing mixin host component node on the actor
	USCS_Node* MixinComponentHostNode = nullptr;
	for (USCS_Node* RootNode : BlueprintGeneratedClass->SimpleConstructionScript->GetRootNodes()) {
		if (RootNode && RootNode->ComponentClass == UBlueprintMixinHostComponent::StaticClass()) {
			MixinComponentHostNode = RootNode;
			break;
		}
	}

	// If we have no node and no blueprint mixins to install, we can exit early
	if (MixinComponentHostNode == nullptr && BlueprintMixins.IsEmpty()) {
		return;
	}
	
	// Create a new SCS node that will hold the mixin host component if we do not have one
	if (MixinComponentHostNode == nullptr) {
		MixinComponentHostNode = NewObject<USCS_Node>(BlueprintGeneratedClass->SimpleConstructionScript, TEXT("TRANSIENT_NODE_MixinHostComponent"), RF_Transient);
		MixinComponentHostNode->ComponentClass = UBlueprintMixinHostComponent::StaticClass();
		
		MixinComponentHostNode->ComponentTemplate = NewObject<UActorComponent>(BlueprintGeneratedClass, UBlueprintMixinHostComponent::StaticClass(),
			*FString::Printf(TEXT("TRANSIENT_MixinHostComponent%s"), *USimpleConstructionScript::ComponentTemplateNameSuffix), RF_ArchetypeObject | RF_Transient);
		
		// Add the node as a root node. It does not need to be attached to any other nodes.
		// We cannot use AddNode here because it would mark the package dirty, which we do not want because the original blueprint must appear unchanged from the user perspective,
		// and we will purge that extra node that we have added before the asset is actually saved on disk
		const_cast<TArray<USCS_Node*>&>(BlueprintGeneratedClass->SimpleConstructionScript->GetRootNodes()).Add(MixinComponentHostNode);
		const_cast<TArray<USCS_Node*>&>(BlueprintGeneratedClass->SimpleConstructionScript->GetAllNodes()).Add(MixinComponentHostNode);

		UMixinInputDelegateBinding* InputDelegateBindingWrapper = NewObject<UMixinInputDelegateBinding>(BlueprintGeneratedClass, UMixinInputDelegateBinding::StaticClass(), TEXT("TRANSIENT_MixinInputDelegateBindingWrapper"), RF_Transient);
		BlueprintGeneratedClass->DynamicBindingObjects.Add(InputDelegateBindingWrapper);
	}

	// Replace the mixin classes on the component template. All new actors created from the template will have the provided mixins initialized.
	UBlueprintMixinHostComponent* MixinHostComponentTemplate = CastChecked<UBlueprintMixinHostComponent>(MixinComponentHostNode->ComponentTemplate);
	MixinHostComponentTemplate->MixinClasses = BlueprintMixins;
}

void UBlueprintHookManager::ApplyMixinsToLevelActors(ULevel* Level) {
	for (auto& [ClassPath, Hooks] : InstalledHooksPerBlueprintGeneratedClass) {
		UClass* MixinTargetClass = Cast<UClass>(FSoftObjectPath(ClassPath).TryLoad());
		TArray<UHookBlueprintGeneratedClass*> MixinClasses;
		for (auto& Hook : Hooks) {
			if (UHookBlueprintGeneratedClass* LoadedHookClass = Hook.LoadSynchronous()) {
				// Sanity check, mixins should not ever be installed on other classes, but doesn't hurt to check
				if (LoadedHookClass->MixinTargetClass == MixinTargetClass) {
					MixinClasses.Add(LoadedHookClass);
				}
			}
		}
		if (MixinClasses.IsEmpty()) {
			continue;
		}
		TArray<UClass*> AllClassesArray;
		GetDerivedClasses(MixinTargetClass, AllClassesArray);
		TSet<UClass*> AllClasses(AllClassesArray);
		AllClasses.Add(MixinTargetClass);
		for (AActor* Actor : Level->Actors) {
			if (AllClasses.Contains(Actor->GetClass())) {
				if (Actor->GetComponentByClass(UBlueprintMixinHostComponent::StaticClass()) != nullptr) {
					continue;
				}
				UBlueprintMixinHostComponent* MixinHostComponent = NewObject<UBlueprintMixinHostComponent>(Actor, UBlueprintMixinHostComponent::StaticClass(), TEXT("TRANSIENT_MixinHostComponent"), RF_Transient);
				if(!MixinHostComponent) {
					UE_LOG(LogBlueprintHookManager, Error, TEXT("Failed to create mixin host component for level actor %s"), *GetFullNameSafe(Actor));
					continue;
				}
				MixinHostComponent->MixinClasses = MixinClasses;
				MixinHostComponent->RegisterComponent();
			}
		}
	}
}

// Names of owner classes for hooked blueprint functions/SCS hooks, used to avoid relatively expensive sanitization pass on functions and SCS on classes that are not hooked
static TSet<FName> HookedBlueprintGeneratedClassNames;

void UBlueprintHookManager::RegisterStaticHooks() {
#if WITH_EDITOR
	// When we are running in the uncooked environment with asset hooking allowed, we need to register a hook to ensure that when assets are saved, they do not contain
	// transient script code modified by the blueprint hooking. This is relevant in editor when saving hooked assets after running PIE, in all other cases this hook does not modify the assets
	if (FSatisfactoryModLoader::IsAssetHookingAllowed()) {
		FCoreUObjectDelegates::OnObjectPreSave.AddStatic([](UObject* InObject, FObjectPreSaveContext) {
			UFunction* Function = Cast<UFunction>(InObject);
			if (Function && !Function->Script.IsEmpty() && HookedBlueprintGeneratedClassNames.Contains(Function->GetOuterUClass()->GetFName())) {
				SanitizeFunctionScriptCodeBeforeSave(Function);
			}
			USimpleConstructionScript* SimpleConstructionScript = Cast<USimpleConstructionScript>(InObject);
			if (SimpleConstructionScript && HookedBlueprintGeneratedClassNames.Contains(SimpleConstructionScript->GetOwnerClass()->GetFName())) {
				SanitizeSimpleConstructionScript(SimpleConstructionScript);
			}
			UBlueprintGeneratedClass* BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(InObject);
			if (BlueprintGeneratedClass) {
				SanitizeBlueprintGeneratedClass(BlueprintGeneratedClass);
			}
		});
		// TODO: Add OnAssetDeleted callback here and to all other systems to delete stale hooks
	}
#endif
	// The construction script is not invoked on level actors as they are simply loaded from the cooked asset, or duplicated for PIE
	// So we need to manually add the mixin host component to such actors
	if (FSatisfactoryModLoader::IsAssetHookingAllowed()) {
		// TODO: This delegate is called after all save data for the actors in this level is loaded
		// so mixins on these actors cannot have components with SaveGame properties
		// Could not find any good delegate or hook that would fix this, maybe it can be addressed in the future 
		FWorldDelegates::LevelAddedToWorld.AddLambda([](ULevel* Level, UWorld*) {
			UBlueprintHookManager* HookManager = GEngine->GetEngineSubsystem<UBlueprintHookManager>();
			HookManager->ApplyMixinsToLevelActors(Level);
		});
	}
}

void UBlueprintHookManager::SanitizeFunctionScriptCodeBeforeSave(UFunction* InFunction) {
	// Replace the function script with the original code if it has been hooked
	TArray<uint8> OriginalFunctionScript;
	if (GetOriginalScriptCodeFromFunction(InFunction, OriginalFunctionScript)) {
		InFunction->Script = OriginalFunctionScript;
	}
}

void UBlueprintHookManager::SanitizeSimpleConstructionScript(USimpleConstructionScript* InSimpleConstructionScript) {
	TArray<USCS_Node*> TemporaryRootNodesToPurge;
	for (USCS_Node* RootNode : InSimpleConstructionScript->GetRootNodes()) {
		if (RootNode->HasAnyFlags(RF_Transient) && RootNode->ComponentClass == UBlueprintMixinHostComponent::StaticClass()) {
			TemporaryRootNodesToPurge.Add(RootNode);
		}
	}
	if (!TemporaryRootNodesToPurge.IsEmpty()) {
		for (USCS_Node* TemporaryRootNode : TemporaryRootNodesToPurge) {
			InSimpleConstructionScript->RemoveNode(TemporaryRootNode, false);
		}
	}
}

void UBlueprintHookManager::SanitizeBlueprintGeneratedClass(UBlueprintGeneratedClass* BlueprintGeneratedClass) {
	BlueprintGeneratedClass->DynamicBindingObjects.RemoveAll([](TObjectPtr<UDynamicBlueprintBinding> Binding) {
		return Binding->IsA<UMixinInputDelegateBinding>();
	});
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
		// It could be invalid due to broken data, removal of the target class/function, or being on a dedicated server (ex. widget blueprints not on servers)
		if (HookDefinition.TargetFunction == nullptr) {
			if (HookDefinition.HookFunction == nullptr) {
				// If the hook function is also invalid, we probably have invalid data
				UE_LOG(LogBlueprintHookManager, Error, TEXT("Blueprint hook asset %s has invalid data and one of its hooks can't be applied. Target structure may have changed or blueprint might need to be recompiled."), *HookBlueprintGeneratedClass->GetFullName());
			} else {
				// If the hook function is still valid, we are probably on a dedicated server where the target blueprint doesn't exist
				// Short form HookFunction name since the function must be defined in the hook blueprint
				UE_LOG(LogBlueprintHookManager, Warning, TEXT("Blueprint hook asset %s hook which would call hook implementation '%s' has invalid Target Function and can't be applied. Either the target structure has changed, or we're running on a dedicated server where the target doesn't exist (for example, widgets) in which case this isn't a problem."), *HookBlueprintGeneratedClass->GetFullName(), *HookDefinition.HookFunction->GetName());
			}
			continue;
		}

		// Verify other hook required data
		if (HookDefinition.HookFunction == nullptr || HookDefinition.TargetSpecifier == nullptr) {
			UE_LOG(LogBlueprintHookManager, Error, TEXT("Blueprint hook asset %s for target function %s has invalid data and can't be applied. Blueprint might need to be recompiled."), *HookBlueprintGeneratedClass->GetFullName(), *HookDefinition.TargetFunction->GetFullName());
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

	// If we have a mixin target class, we have to apply hooks to it as well, even if we have traditional hook definitions registered
	if (HookBlueprintGeneratedClass->MixinTargetClass) {
		ClassesToReapplyHooks.Add(HookBlueprintGeneratedClass->MixinTargetClass);
		TArray<TSoftObjectPtr<UHookBlueprintGeneratedClass>>& InstalledHooksForBlueprintClass = InstalledHooksPerBlueprintGeneratedClass.FindOrAdd(HookBlueprintGeneratedClass->MixinTargetClass->GetClassPathName());
		InstalledHooksForBlueprintClass.AddUnique(TSoftObjectPtr<UHookBlueprintGeneratedClass>(HookBlueprintGeneratedClass));
	}

	// Keep the hook object itself from being garbage collected
	OwnerGameInstance->RegisterReferencedObject(HookBlueprintGeneratedClass);

	// Re-apply blueprint hooks to all the blueprint classes
	for (UBlueprintGeneratedClass* BlueprintGeneratedClass : ClassesToReapplyHooks) {
		// Make sure the blueprint is kept in memory until the game instance runs out of scope
		OwnerGameInstance->RegisterReferencedObject(BlueprintGeneratedClass);
		// Mark the class as needing the sanitization before it can be saved on disk in the editor
		HookedBlueprintGeneratedClassNames.Add(BlueprintGeneratedClass->GetFName());

		// Apply blueprint hooks to that class
		ApplyRegisteredHooksToBlueprintClass(BlueprintGeneratedClass);
	}
}

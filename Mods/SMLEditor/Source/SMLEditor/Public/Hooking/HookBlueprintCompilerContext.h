#pragma once

#include "CoreMinimal.h"
#include "KismetCompiler.h"

class UHookBlueprint;

struct FInstanceHookStubGenerationData {
	FName InstanceFunctionName;
	class UK2Node_FunctionEntry* FunctionEntry{};
	class UK2Node_FunctionResult* FunctionResult{};
};

class SMLEDITOR_API FHookBlueprintCompilerContext : public FKismetCompilerContext {
private:
	UEdGraph* SourceHookTargetGraph{};
public:
	FHookBlueprintCompilerContext(UHookBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions);

	// Begin FKismetCompilerContext interface
	virtual void PreCompile() override;
	virtual void CreateFunctionList() override;
	virtual void CreateClassVariablesFromBlueprint() override;
	virtual void CleanAndSanitizeClass(UBlueprintGeneratedClass* ClassToClean, UObject*& OldCDO) override;
	virtual void SaveSubObjectsFromCleanAndSanitizeClass(FSubobjectCollection& SubObjectsToSave, UBlueprintGeneratedClass* ClassToClean) override;
	virtual void FinishCompilingClass(UClass* Class) override;
	virtual void SpawnNewClass(const FString& NewClassName) override;
	// End FKismetCompilerContext interface
protected:
	/** Creates a static function from the instance hook function. Static function handles context retrieval and failsafe if instance is not present */
	virtual void CreateStaticFunctionStubForInstanceHookFunction(const FInstanceHookStubGenerationData& StubGenerationData);
	/** Compiles hook target graph into a list of hook definitions */
	virtual void CompileHookTargetGraph();

	TMap<FName, FKismetFunctionContext*> InstanceHookFunctionToSyntheticStaticFunctionContext;
};

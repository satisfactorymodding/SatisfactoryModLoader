#pragma once

#include "CoreMinimal.h"
#include "KismetCompiler.h"

class UHookBlueprint;

class SMLEDITOR_API FHookBlueprintCompilerContext : public FKismetCompilerContext {
private:
	UEdGraph* SourceHookTargetGraph{};
public:
	FHookBlueprintCompilerContext(UHookBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions);

	// Begin FKismetCompilerContext interface
	virtual void PreCompile() override;
	virtual void CreateFunctionList() override;
	virtual void CleanAndSanitizeClass(UBlueprintGeneratedClass* ClassToClean, UObject*& OldCDO) override;
	virtual void FinishCompilingClass(UClass* Class) override;
	virtual void SpawnNewClass(const FString& NewClassName) override;
	// End FKismetCompilerContext interface
protected:
	virtual void CompileHookTargetGraph();
};

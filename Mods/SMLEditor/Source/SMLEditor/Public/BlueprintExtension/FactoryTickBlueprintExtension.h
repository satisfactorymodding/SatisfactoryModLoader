#pragma once

#include "BlueprintCompilerExtension.h"
#include "FactoryTickBlueprintExtension.generated.h"

UCLASS()
class SMLEDITOR_API UFactoryTickBlueprintExtension : public UBlueprintCompilerExtension
{
	GENERATED_BODY()
public:
	virtual void ProcessBlueprintCompiled(const FKismetCompilerContext& CompilationContext, const FBlueprintCompiledData& Data) override;
};
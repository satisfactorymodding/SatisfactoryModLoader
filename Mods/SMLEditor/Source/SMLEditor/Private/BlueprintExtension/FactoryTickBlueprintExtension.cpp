#include "BlueprintExtension/FactoryTickBlueprintExtension.h"
#include "Buildables/FGBuildable.h"

#define LOCTEXT_NAMESPACE "KismetCompiler"

void UFactoryTickBlueprintExtension::ProcessBlueprintCompiled(const FKismetCompilerContext& CompilationContext,
                                                              const FBlueprintCompiledData& Data)
{
	Super::ProcessBlueprintCompiled(CompilationContext, Data);

	// Code below is based on FKismetCompilerContext::SetCanEverTick
	FTickFunction* TickFunction = nullptr;
	FTickFunction* ParentTickFunction = nullptr;

	// Using OldClass here instead of NewClass because BlueprintCompilationExtensions are called before the new CDO is created
	// and the old CDO will be copied over
	if (!CompilationContext.OldClass) return;
	
	if (AFGBuildable* CDBuildable = Cast<AFGBuildable>(CompilationContext.OldClass->GetDefaultObject()))
	{
		TickFunction = &CDBuildable->mFactoryTickFunction;
		ParentTickFunction = &CompilationContext.OldClass->GetSuperClass()->GetDefaultObject<AFGBuildable>()->mFactoryTickFunction;
	}

	if (TickFunction == nullptr)
	{
		return;
	}

	const bool bOldFlag = TickFunction->bCanEverTick;
	// RESET FLAG 
	TickFunction->bCanEverTick = ParentTickFunction->bCanEverTick;
	
	// RECEIVE TICK
	if (!TickFunction->bCanEverTick)
	{
		// Make sure that both AActor and UActorComponent have the same name for their tick method
		static FName ReceiveTickName(GET_FUNCTION_NAME_CHECKED(AFGBuildable, Factory_ReceiveTick));

		if (FKismetCompilerUtilities::FindOverriddenImplementableEvent(ReceiveTickName, CompilationContext.OldClass))
		{
			// We have a tick node
			TickFunction->bCanEverTick = true;
		}
	}

	if (TickFunction->bCanEverTick != bOldFlag)
	{
		const FCoreTexts& CoreTexts = FCoreTexts::Get();

		UE_LOG(LogK2Compiler, Verbose, TEXT("Overridden flag for class '%s': CanEverTick %s "), *CompilationContext.NewClass->GetName(),
			TickFunction->bCanEverTick ? *(CoreTexts.True.ToString()) : *(CoreTexts.False.ToString()) );
	}
}

#undef LOCTEXT_NAMESPACE
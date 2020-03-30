#pragma once

#include "CoreMinimal.h"
#include "Json.h"

namespace SML {
	/**
	 * Parses the BP script of the given function into a Array of Json Code Instructions
	 */
	TArray<TSharedPtr<FJsonValue>> CreateFunctionCode(UFunction* function);
}
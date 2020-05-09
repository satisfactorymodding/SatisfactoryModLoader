#pragma once

#include "CoreMinimal.h"
#include "Json.h"

namespace SML {
	/**
	 * Parses the BP script of the given function into a Array of Json Code Instructions
	 */
	TArray<TSharedPtr<FJsonValue>> CreateFunctionCode(UFunction* Function);

	TArray<TSharedPtr<FJsonValue>> DumpByteCode(TArray<uint8>& Code, UFunction* Outer);
	
	/**
	 * Parses BP script byte code and returns offset to the start of first statement
	 * Before which it is possible to insert N bytes of code
	 * @return amount of bytes to skip (>= BytesRequired), or negative number specifying how much bytes are missing to fill up BytesRequired
	 */
	int32 GetMinInstructionReplaceLength(UFunction* Function, uint32 BytesRequired, uint32 StartOffset = 0);

	int32 FindReturnStatementOffset(UFunction* Function);
}
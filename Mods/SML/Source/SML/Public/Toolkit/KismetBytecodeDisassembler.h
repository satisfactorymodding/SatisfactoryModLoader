#pragma once
#include "CoreMinimal.h"
#include "UObject/Script.h"
#include "Dom/JsonObject.h"

class SML_API FSMLKismetBytecodeDisassembler {
public:
	/** Parses a block of statements until it hits return */
	TArray<TSharedPtr<FJsonValue>> SerializeFunction(UStruct* Function);

	/** Computes length of the statement in bytes and returns it. Returns false if given index does not correspond to any statement (e.g if it is inside of some statement) */
	bool GetStatementLength(UStruct* Function, int32 StatementIndex, int32& OutStatementLength);

	/** Gets the offset of the return statement. For now Kismet Compiler will always generate only one Return node, so there's always exactly one. Will assert if no return statement is found. */
	int32 GetReturnStatementOffset(UFunction* Function);

	/** Returns index of the first statement using given opcode */
	bool FindFirstStatementOfType(UStruct* Function, int32 StartIndex, uint8 StatementOpcode, int32& OutStatementIndex);

private:
	TWeakObjectPtr<UClass> SelfScope;
	TArray<uint8> Script;

	/** Internal utility function to convert a single statement into json object, provided Script and SelfScope have been set. Will include a StatementIndex in the returned json */
	TSharedPtr<FJsonObject> SerializeStatement(int32& StatementIndex);

	/** Converts a single expression into json object, provided Script and SelfScope have been set */
	TSharedPtr<FJsonObject> SerializeExpression(int32& ScriptIndex);

	//Begin script bytecode parsing methods
	int32 ReadInt(int32& ScriptIndex);
	uint64 ReadQword(int32& ScriptIndex);
	uint8 ReadByte(int32& ScriptIndex);
	FString ReadName(int32& ScriptIndex);
	uint16 ReadWord(int32& ScriptIndex);
	float ReadFloat(int32& ScriptIndex);
	double ReadDouble(int32& ScriptIndex);
	CodeSkipSizeType ReadSkipCount(int32& ScriptIndex);
	FString ReadString8(int32& ScriptIndex);
	FString ReadString16(int32& ScriptIndex);
	FString ReadString(int32& ScriptIndex);
	
	template <typename T>
    T* ReadPointer(int32& ScriptIndex) {
		return (T*)ReadQword(ScriptIndex);
	}
	//End script bytecode parsing methods
};

#pragma once
#include "CoreMinimal.h"
#include "UObject/Script.h"
#include "Dom/JsonObject.h"

class SML_API FSMLKismetBytecodeDisassembler {
public:
	/** Parses a block of statements until it hits return */
	TArray<TSharedPtr<FJsonValue>> SerializeFunction(UStruct* Function);

	/** Converts a single statement at the given index into json object. Will throw an error if the statement index does not correspond to the start of a statement.*/
	TSharedPtr<FJsonObject> SerializeStatement(UStruct* Function, int32 StatementIndex);

	/** Returns index of the first statement using given opcode */
	bool FindFirstStatementOfType(UStruct* Function, int32 StartIndex, uint8 StatementOpcode, int32& OutStatementIndex);

private:
	TWeakObjectPtr<UClass> SelfScope;
	TArray<uint8> Script;

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

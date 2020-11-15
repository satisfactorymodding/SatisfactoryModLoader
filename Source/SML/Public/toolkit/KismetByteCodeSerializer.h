#pragma once
#include "CoreMinimal.h"
#include "Json.h"
#include "Engine/EngineTypes.h"

class FParseFrame {
public:
	FFrame* Frame;
	void* ParametersFrame;
	FlowStackType FlowStack;

	FParseFrame(UObject* Context, UFunction* Function);
	~FParseFrame();

	FORCEINLINE FName ReadName() const {
		return Frame->ReadName();
	}

	FORCEINLINE float ReadFloat() const {
		return Frame->ReadFloat();
	}

	FORCEINLINE int32 ReadWord() const {
		return Frame->ReadWord();
	}

	template<typename T>
	FORCEINLINE T ReadInt() const {
		return Frame->ReadInt<T>();
	}

	FORCEINLINE UObject* ReadObject() const {
		return Frame->ReadObject();
	}

	FORCEINLINE CodeSkipSizeType ReadCodeSkipCount() const {
		return Frame->ReadCodeSkipCount();
	}

	FORCEINLINE UProperty* ReadProperty() const {
		return Frame->ReadProperty();
	}

	FORCEINLINE UProperty* ReadPropertyUnchecked() const {
		return Frame->ReadPropertyUnchecked();
	}

	FORCEINLINE VariableSizeType ReadVariableSize(UProperty** Property) const {
		return Frame->ReadVariableSize(Property);
	}

	FORCEINLINE CodeSkipSizeType GetOffsetFromPtr(uint8* OffsetCode) const {
		return (uint64) OffsetCode - (uint64) Frame->Node->Script.GetData();
	}

	TSharedPtr<FJsonObject> Step(void* ReturnValue);
};

class SML_API FKismetByteCodeSerializer {
public:
	/**
	 * Parses the BP script of the given function into a Array of Json Code Instructions
	 */
	static TArray<TSharedPtr<FJsonValue>> CreateFunctionCode(UFunction* Function);

	static TArray<TSharedPtr<FJsonValue>> DumpByteCode(TArray<uint8>& Code, UFunction* Outer);
	
	/**
	 * Parses BP script byte code and returns offset to the start of first statement
	 * Before which it is possible to insert N bytes of code
	 * @return amount of bytes to skip (>= BytesRequired), or negative number specifying how much bytes are missing to fill up BytesRequired
	 */
	static int32 GetMinInstructionReplaceLength(UFunction* Function, uint32 BytesRequired, uint32 StartOffset = 0);

	static int32 FindReturnStatementOffset(UFunction* Function);
};
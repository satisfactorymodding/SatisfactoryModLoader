#include "Toolkit/ScriptExprAssembler.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"

template<typename T> static T* ReadPointer(const uint8* ScriptData, int32& ScriptOffset) {
	const uint64 RawPointer = FPlatformMemory::ReadUnaligned<uint64>(&ScriptData[ScriptOffset]);
	ScriptOffset += sizeof(uint64);
	return reinterpret_cast<T*>(RawPointer);
}

template<typename T> static T ReadRawData(const uint8* ScriptData, int32& ScriptOffset) {
	const T Value = FPlatformMemory::ReadUnaligned<T>(&ScriptData[ScriptOffset]);
	ScriptOffset += sizeof(T);
	return Value;
}

static FString ReadString8(const uint8* ScriptData, int32& ScriptOffset) {
	FString ResultString;
	do {
		ResultString += static_cast<ANSICHAR>(ReadRawData<uint8>(ScriptData, ScriptOffset));
	} while (ScriptData[ScriptOffset - 1] != 0);
	return ResultString;
}

static FString ReadString16(const uint8* ScriptData, int32& ScriptOffset) {
	FString ResultString;
	do {
		ResultString += static_cast<TCHAR>(ReadRawData<uint16>(ScriptData, ScriptOffset));
	} while (ScriptData[ScriptOffset - 1] != 0 || ScriptData[ScriptOffset - 2] != 0);
	StringConv::InlineCombineSurrogates(ResultString);
	return ResultString;
}

static int32 GetOperandCountForBlueprintTextType(const EBlueprintTextLiteralType LiteralType) {
	switch(LiteralType) {
		case EBlueprintTextLiteralType::LocalizedText: return 3;
		case EBlueprintTextLiteralType::StringTableEntry: return 2;
		case EBlueprintTextLiteralType::InvariantText:
		case EBlueprintTextLiteralType::LiteralString: return 1;
		default: return 0;
	}
}

template<typename T> static void WritePointer(TArray<uint8>& OutScriptData, int32& ScriptOffset, T* Pointer) {
	if (OutScriptData.Num() < ScriptOffset + sizeof(uint64)) {
		OutScriptData.AddZeroed(sizeof(uint64));
	}
	const uint64 RawPointer = reinterpret_cast<uint64>(Pointer);
	FPlatformMemory::WriteUnaligned<uint64>(&OutScriptData[ScriptOffset], RawPointer);
	ScriptOffset += sizeof(uint64);
}

template<typename T> static T WriteRawData(TArray<uint8>& OutScriptData, int32& ScriptOffset, const T& Value) {
	if (OutScriptData.Num() < ScriptOffset + sizeof(T)) {
		OutScriptData.AddZeroed(sizeof(T));
	}
	FPlatformMemory::WriteUnaligned<T>(&OutScriptData[ScriptOffset], Value);
	ScriptOffset += sizeof(T);
	return Value;
}

static void WriteString8(TArray<uint8>& OutScriptData, int32& ScriptOffset, const FString& Value) {
	if (OutScriptData.Num() < ScriptOffset + (Value.Len() + 1)) {
		OutScriptData.AddZeroed(sizeof(Value.Len() + 1));
	}
	for (int32 i = 0; i < Value.Len(); i++) {
		WriteRawData<uint8>(OutScriptData, ScriptOffset, static_cast<ANSICHAR>(Value[i]));
	}
	WriteRawData<uint8>(OutScriptData, ScriptOffset, 0);
}

static void WriteString16(TArray<uint8>& OutScriptData, int32& ScriptOffset, const FString& Value) {
	if (OutScriptData.Num() < ScriptOffset + (Value.Len() * sizeof(uint16) + sizeof(uint16))) {
		OutScriptData.AddZeroed(sizeof(Value.Len() * sizeof(uint16) + sizeof(uint16)));
	}
	for (int32 i = 0; i < Value.Len(); i++) {
		WriteRawData<uint16>(OutScriptData, ScriptOffset, Value[i]);
	}
	WriteRawData<uint16>(OutScriptData, ScriptOffset, 0);
}

void FScriptExprOperand::PrintOperand(FStringBuilderBase& StringBuilder) const {
	switch (Type) {
		case TypeNull: StringBuilder.Append(TEXT("<Invalid>")); break;
		case TypeExpr: if (Expr) { Expr->PrintExpression(StringBuilder); } else { StringBuilder.Append(TEXT("<Invalid Expression>")); } break;
		case TypeScriptName: StringBuilder.Append(TEXT("Name(\"")).Append(ScriptNameToName(ScriptName).ToString().ReplaceCharWithEscapedChar()).Append(TEXT("\")")); break;
		case TypeLabel: StringBuilder.Append(TEXT("Label(")).Appendf(TEXT("0x%x"), TargetLabelCodeOffset).AppendChar(TEXT(')')); break;
		case TypeProperty: if (Property) { StringBuilder.Append(TEXT("Property(\"")).Append(Property->GetPathName()).Append(TEXT("\")")); } else { StringBuilder.Append(TEXT("Property(\"None\")")); } break;
		case TypeObject: StringBuilder.Append(TEXT("Object(\"")).Append(GetPathNameSafe(Object)).Append(TEXT("\")")); break;
		case TypeInteger: StringBuilder.Appendf(TEXT("%lld"), static_cast<int64>(Integer)); break;
		case TypeFloat: StringBuilder.Appendf(TEXT("%.3f"), Float); break;
		case TypeString: StringBuilder.AppendChar(TEXT('"')).Append(String.ReplaceCharWithEscapedChar()).AppendChar(TEXT('"')); break;
		default: StringBuilder.Append(TEXT("<Unknown Operand>")); break;
	}
}

const FScriptExprOperand& FScriptExpr::RequireOperand(int32 InOperandIndex, FScriptExprOperand::EScriptExprOperand InOperandType) {
	if (Operands.IsValidIndex(InOperandIndex) && Operands[InOperandIndex].Type == InOperandType) {
		return Operands[InOperandIndex];
	}
	static const FScriptExprOperand FallbackEmptyOperand{};
	return FallbackEmptyOperand;
}

TSharedPtr<FScriptExpr> FScriptExpr::GetStatement() {
	TSharedPtr<FScriptExpr> CurrentExpression = AsShared();
	while (CurrentExpression && CurrentExpression->OuterExpression.IsValid()) {
		CurrentExpression = CurrentExpression->OuterExpression.Pin();
	}
	return CurrentExpression;
}

TSharedPtr<FScriptExpr> FScriptExpr::DeepCopy() const {
	TSharedPtr<FScriptExpr> NewExpression = MakeShared<FScriptExpr>();
	NewExpression->Opcode = Opcode;
	NewExpression->OuterExpression = OuterExpression;
	NewExpression->Operands = Operands;

	// Copy expression operands for the new expression
	for (FScriptExprOperand& ExprOperand : NewExpression->Operands) {
		if (ExprOperand.Type == FScriptExprOperand::TypeExpr && ExprOperand.Expr) {
			ExprOperand.Expr = ExprOperand.Expr->DeepCopy();
		}
	}
	return NewExpression;
}

void FScriptExpr::PrintExpression(FStringBuilderBase& StringBuilder) const {
	StringBuilder.Append(FScriptExprAssembler::GetInstructionName(Opcode));
	if (!Operands.IsEmpty()) {
		StringBuilder.AppendChar(TEXT('('));
		for (int32 OperandIndex = 0; OperandIndex < Operands.Num(); OperandIndex++) {
			if (OperandIndex != 0) {
				StringBuilder.Append(TEXT(", "));
			}
			Operands[OperandIndex].PrintOperand(StringBuilder);
		}
		StringBuilder.AppendChar(TEXT(')'));
	}
}

FString FScriptExpr::ToString() const {
	TStringBuilder<256> StringBuilder;
	PrintExpression(StringBuilder);
	return StringBuilder.ToString();
}

bool operator==(const FScriptExprOperand& A, const FScriptExprOperand& B) {
	return A.Type == B.Type &&
		A.ScriptName == B.ScriptName &&
		A.TargetLabel == B.TargetLabel &&
		A.Property == B.Property && A.Object == B.Object &&
		A.Integer == B.Integer && A.Float == B.Float &&
		A.String == B.String;
}

TSharedPtr<FScriptExpr> FScriptExprAssembler::DisassembleScriptExpr(const uint8* ScriptData, int32& ScriptOffset, const TSharedPtr<FScriptExpr> OuterExpression) {
	TSharedPtr<FScriptExpr> Result = MakeShared<FScriptExpr>();
	Result->ScriptOffset = ScriptOffset;
	Result->OuterExpression = OuterExpression;
	Result->Opcode = ScriptData[ScriptOffset++];

	const auto ReadExpressionsUntilTerminator = [&](uint8 TerminatorOpcode) {
		while (ScriptData[ScriptOffset] != TerminatorOpcode) {
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
		}
		ScriptOffset++;
	};
	const auto ReadSetContainerOpcode = [&](uint8 TerminatorOpcode, bool bHasExplicitContainerLength = true) {
		Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
		if (bHasExplicitContainerLength) {
			Result->Operands.Add(ReadRawData<int32>(ScriptData, ScriptOffset));
		}
		ReadExpressionsUntilTerminator(TerminatorOpcode);
	};
	const auto ReadContainerConstOpcode = [&](uint8 TerminatorOpcode, int32 NumProperties) {
		for (int32 i = 0; i < NumProperties; i++) {
			Result->Operands.Add(ReadPointer<FProperty>(ScriptData, ScriptOffset));
		}
		Result->Operands.Add(ReadRawData<int32>(ScriptData, ScriptOffset));
		ReadExpressionsUntilTerminator(TerminatorOpcode);
	};

	switch (Result->Opcode) {
		case EX_Cast: {
			Result->Operands.Add(ReadRawData<uint8>(ScriptData, ScriptOffset));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}
		case EX_SetSet: { ReadSetContainerOpcode(EX_EndSet); return Result; }
		case EX_SetMap: { ReadSetContainerOpcode(EX_EndMap); return Result; }
		case EX_SetArray: { ReadSetContainerOpcode(EX_EndArray, false); return Result; }
		case EX_SetConst: { ReadContainerConstOpcode(EX_EndSetConst, 1); return Result; }
		case EX_MapConst: { ReadContainerConstOpcode(EX_EndMapConst, 2); return Result; }
		case EX_ArrayConst: { ReadContainerConstOpcode(EX_EndArrayConst, 1); return Result; }
		case EX_ObjToInterfaceCast:
		case EX_CrossInterfaceCast:
		case EX_InterfaceToObjCast:
		case EX_MetaCast:
		case EX_DynamicCast: {
			Result->Operands.Add(ReadPointer<UClass>(ScriptData, ScriptOffset));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}
		case EX_Let: {
			Result->Operands.Add(ReadPointer<FProperty>(ScriptData, ScriptOffset));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}
		case EX_LetObj:
		case EX_LetWeakObjPtr:
		case EX_LetDelegate:
		case EX_LetMulticastDelegate:
		case EX_LetBool:
		case EX_ArrayGetByRef:
		case EX_AddMulticastDelegate:
		case EX_RemoveMulticastDelegate: {
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}
		case EX_LetValueOnPersistentFrame:
		case EX_StructMemberContext: {
			Result->Operands.Add(ReadPointer<FProperty>(ScriptData, ScriptOffset));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}
		case EX_ComputedJump:
		case EX_InterfaceContext:
		case EX_Return:
		case EX_SoftObjectConst:
		case EX_FieldPathConst:
		case EX_ClearMulticastDelegate:
		case EX_PopExecutionFlowIfNot:
		case EX_AutoRtfmAbortIfNot: {
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}
		case EX_LocalVirtualFunction:
		case EX_VirtualFunction: {
			Result->Operands.Add(ReadRawData<FScriptName>(ScriptData, ScriptOffset));
			ReadExpressionsUntilTerminator(EX_EndFunctionParms);
			return Result;
		}
		case EX_LocalFinalFunction:
		case EX_FinalFunction:
		case EX_CallMath: {
			Result->Operands.Add(ReadPointer<UStruct>(ScriptData, ScriptOffset));
			ReadExpressionsUntilTerminator(EX_EndFunctionParms);
			return Result;
		}
		case EX_Jump:
		case EX_PushExecutionFlow: {
			const CodeSkipSizeType TargetAbsoluteCodeOffset = ReadRawData<CodeSkipSizeType>(ScriptData, ScriptOffset);
			Result->Operands.Add(FScriptExprOperand::CreateResolvedLabel(TargetAbsoluteCodeOffset));
			return Result;
		}
		case EX_LocalVariable:
		case EX_DefaultVariable:
		case EX_InstanceVariable:
		case EX_LocalOutVariable:
		case EX_ClassSparseDataVariable:
		case EX_PropertyConst: {
			Result->Operands.Add(ReadPointer<FProperty>(ScriptData, ScriptOffset));
			return Result;
		}
		case EX_CallMulticastDelegate: {
			Result->Operands.Add(ReadPointer<UStruct>(ScriptData, ScriptOffset));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			ReadExpressionsUntilTerminator(EX_EndFunctionParms);
			return Result;
		}
		case EX_ClassContext:
		case EX_Context:
		case EX_Context_FailSilent: {
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));

			// The jump offset is relative to offset of Expression (4th operand) 
			const CodeSkipSizeType TargetRelativeCodeOffset = ReadRawData<CodeSkipSizeType>(ScriptData, ScriptOffset);
			Result->Operands.Add(FScriptExprOperand::CreateResolvedLabel(INDEX_NONE));

			Result->Operands.Add(ReadPointer<FProperty>(ScriptData, ScriptOffset));

			// Compute the absolute code offset from the serialized relative offset
			const CodeSkipSizeType RelativeCodeOffsetBase = ScriptOffset;
			Result->Operands[1] = FScriptExprOperand::CreateResolvedLabel(RelativeCodeOffsetBase + TargetRelativeCodeOffset);

			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}
		case EX_IntConst: { Result->Operands.Add(ReadRawData<int32>(ScriptData, ScriptOffset)); return Result; }
		case EX_Int64Const: { Result->Operands.Add(ReadRawData<int64>(ScriptData, ScriptOffset)); return Result; }
		case EX_UInt64Const: { Result->Operands.Add(ReadRawData<uint64>(ScriptData, ScriptOffset)); return Result; }
		case EX_FloatConst: { Result->Operands.Add(ReadRawData<float>(ScriptData, ScriptOffset)); return Result; }
		case EX_DoubleConst: { Result->Operands.Add(ReadRawData<double>(ScriptData, ScriptOffset)); return Result; }
		case EX_StringConst: { Result->Operands.Add(ReadString8(ScriptData, ScriptOffset)); return Result; }
		case EX_UnicodeStringConst: { Result->Operands.Add(ReadString16(ScriptData, ScriptOffset)); return Result; }
		case EX_ObjectConst: { Result->Operands.Add(ReadPointer<UObject>(ScriptData, ScriptOffset)); return Result; }
		case EX_SkipOffsetConst: {
			const CodeSkipSizeType TargetAbsoluteCodeOffset = ReadRawData<CodeSkipSizeType>(ScriptData, ScriptOffset);
			Result->Operands.Add(FScriptExprOperand::CreateResolvedLabel(TargetAbsoluteCodeOffset));
			return Result;
		}
		case EX_InstrumentationEvent:
		case EX_IntConstByte:
		case EX_ByteConst: { Result->Operands.Add(ReadRawData<uint8>(ScriptData, ScriptOffset)); return Result; }
		case EX_TextConst: {
			Result->Operands.Add(ReadRawData<uint8>(ScriptData, ScriptOffset));
			const EBlueprintTextLiteralType LiteralType = static_cast<EBlueprintTextLiteralType>(Result->Operands[0].Integer);
			// String tables prefix their arguments with object const pointing to the string table object if present
			if (LiteralType == EBlueprintTextLiteralType::StringTableEntry) {
				Result->Operands.Add(ReadPointer<UObject>(ScriptData, ScriptOffset));
			}
			// Read the rest of the arguments as expressions
			const int32 OperandCount = GetOperandCountForBlueprintTextType(LiteralType);
			for (int32 i = 0; i < OperandCount; i++) {
				Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			}
			return Result;
		}
		case EX_InstanceDelegate:
		case EX_NameConst: { Result->Operands.Add(ReadRawData<FScriptName>(ScriptData, ScriptOffset)); return Result; }
		case EX_BitFieldConst: {
			Result->Operands.Add(ReadPointer<FProperty>(ScriptData, ScriptOffset));
			Result->Operands.Add(ReadRawData<uint8>(ScriptData, ScriptOffset));
			return Result;
		}
		case EX_Skip: {
			// Unknown whenever CodeSkipSizeType here is relative or absolute, since opcode does not currently have a handler registered
			const CodeSkipSizeType TargetAbsoluteCodeOffset = ReadRawData<CodeSkipSizeType>(ScriptData, ScriptOffset);
			Result->Operands.Add(FScriptExprOperand::CreateResolvedLabel(TargetAbsoluteCodeOffset));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}
		case EX_JumpIfNot: {
			const CodeSkipSizeType TargetAbsoluteCodeOffset = ReadRawData<CodeSkipSizeType>(ScriptData, ScriptOffset);
            Result->Operands.Add(FScriptExprOperand::CreateResolvedLabel(TargetAbsoluteCodeOffset));
            Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
            return Result;
        }
		case EX_Assert: {
			Result->Operands.Add(ReadRawData<uint16>(ScriptData, ScriptOffset));
			Result->Operands.Add(ReadRawData<uint8>(ScriptData, ScriptOffset));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}	
		case EX_BindDelegate: {
			Result->Operands.Add(ReadRawData<FScriptName>(ScriptData, ScriptOffset));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}
		case EX_RotationConst:
		case EX_VectorConst:
		case EX_Vector3fConst: {
			Result->Operands.Add(ReadRawData<double>(ScriptData, ScriptOffset));
			Result->Operands.Add(ReadRawData<double>(ScriptData, ScriptOffset));
			Result->Operands.Add(ReadRawData<double>(ScriptData, ScriptOffset));
			return Result;
		}
		case EX_TransformConst: {
			constexpr int32 TotalComponentCount = 4 + 3 + 3;
			for (int32 i = 0; i < TotalComponentCount; i++) {
				Result->Operands.Add(ReadRawData<double>(ScriptData, ScriptOffset));
			}
			return Result;
		}
		case EX_StructConst: {
			Result->Operands.Add(ReadPointer<UScriptStruct>(ScriptData, ScriptOffset));
			Result->Operands.Add(ReadRawData<int32>(ScriptData, ScriptOffset));
			ReadExpressionsUntilTerminator(EX_EndStructConst);
			return Result;
		}
		case EX_SwitchValue: {
			const uint16 NumCases = ReadRawData<uint16>(ScriptData, ScriptOffset);
			Result->Operands.Add(NumCases);
			// Skip absolute code offset to the end of the switch expression, this is not a real jump target as it does not point to a statement
			ReadRawData<CodeSkipSizeType>(ScriptData, ScriptOffset);
		
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));

			for (int32 CaseIndex = 0; CaseIndex < NumCases; CaseIndex++) {
				Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
				// Skip absolute code offset to the next switch case, this is not a real jump target as it does not point to a statement
				ReadRawData<CodeSkipSizeType>(ScriptData, ScriptOffset);
				Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			}
			Result->Operands.Add(DisassembleScriptExpr(ScriptData, ScriptOffset, Result));
			return Result;
		}
		case EX_AutoRtfmTransact: {
			Result->Operands.Add(ReadRawData<int32>(ScriptData, ScriptOffset));
			const CodeSkipSizeType TargetAbsoluteCodeOffset = ReadRawData<CodeSkipSizeType>(ScriptData, ScriptOffset);
			Result->Operands.Add(FScriptExprOperand::CreateResolvedLabel(TargetAbsoluteCodeOffset));
			return Result;
		}
		case EX_AutoRtfmStopTransact: {
			Result->Operands.Add(ReadRawData<int32>(ScriptData, ScriptOffset));
			Result->Operands.Add(ReadRawData<uint8>(ScriptData, ScriptOffset));
			return Result;
		}
		default: { return Result; }
	}
}

void FScriptExprAssembler::AssembleScriptExpr(TArray<uint8>& OutScriptData, int32& ScriptOffset, const TSharedPtr<FScriptExpr>& Expr) {
	WriteRawData<uint8>(OutScriptData, ScriptOffset, Expr->Opcode);
	
	const auto WriteTrailingExpressions = [&](int32 StartIndex, uint8 TerminatorOpcode) {
		for (int32 i = StartIndex; i < Expr->Operands.Num(); i++) {
			AssembleScriptExpr(OutScriptData, ScriptOffset, Expr->RequireOperand(i, FScriptExprOperand::TypeExpr).Expr);
		}
		WriteRawData<uint8>(OutScriptData, ScriptOffset, TerminatorOpcode);
	};
	const auto WriteSetContainerOpcode = [&](uint8 TerminatorOpcode, bool bHasExplicitContainerLength = true) {
		const TSharedPtr<FScriptExpr>& Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
		AssembleScriptExpr(OutScriptData, ScriptOffset, Operand0);
		if (bHasExplicitContainerLength) {
			const int32 Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeInteger).Integer;
			WriteRawData<int32>(OutScriptData, ScriptOffset, Operand1);
		}
		WriteTrailingExpressions(bHasExplicitContainerLength ? 2 : 1, TerminatorOpcode);
	};
	const auto WriteContainerConstOpcode = [&](uint8 TerminatorOpcode, int32 NumProperties) {
		for (int32 i = 0; i < NumProperties; i++) {
			WritePointer<FProperty>(OutScriptData, ScriptOffset, Expr->RequireOperand(i, FScriptExprOperand::TypeProperty).Property);
		}
		const int32 OperandN = Expr->RequireOperand(NumProperties, FScriptExprOperand::TypeInteger).Integer;
		WriteRawData<int32>(OutScriptData, ScriptOffset, OperandN);
		WriteTrailingExpressions(NumProperties + 1, TerminatorOpcode);
	};

	switch (Expr->Opcode) {
		case EX_Cast: {
			const uint8 Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer;
			const TSharedPtr<FScriptExpr>& Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;
			
			WriteRawData<uint8>(OutScriptData, ScriptOffset, Operand0);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand1);
			break;
		}
		case EX_SetSet: { WriteSetContainerOpcode(EX_EndSet); break; }
		case EX_SetMap: { WriteSetContainerOpcode(EX_EndMap); break; }
		case EX_SetArray: { WriteSetContainerOpcode(EX_EndArray, false); break; }
		case EX_SetConst: { WriteContainerConstOpcode(EX_EndSetConst, 1); break; }
		case EX_MapConst: { WriteContainerConstOpcode(EX_EndMapConst, 2); break; }
		case EX_ArrayConst: { WriteContainerConstOpcode(EX_EndArrayConst, 1); break; }
		case EX_ObjToInterfaceCast:
		case EX_CrossInterfaceCast:
		case EX_InterfaceToObjCast:
		case EX_MetaCast:
		case EX_DynamicCast: {
			UClass* Operand0 = Cast<UClass>(Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			const TSharedPtr<FScriptExpr>& Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;

			WritePointer<UClass>(OutScriptData, ScriptOffset, Operand0);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand1);
			break;
		}
		case EX_Let: {
			FProperty* Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
			const TSharedPtr<FScriptExpr>& Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;
			const TSharedPtr<FScriptExpr>& Operand2 = Expr->RequireOperand(2, FScriptExprOperand::TypeExpr).Expr;

			WritePointer<FProperty>(OutScriptData, ScriptOffset, Operand0);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand1);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand2);
			break;
		}
		case EX_LetObj:
		case EX_LetWeakObjPtr:
		case EX_LetDelegate:
		case EX_LetMulticastDelegate:
		case EX_LetBool:
		case EX_ArrayGetByRef:
		case EX_AddMulticastDelegate:
		case EX_RemoveMulticastDelegate: {
			const TSharedPtr<FScriptExpr>& Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
			const TSharedPtr<FScriptExpr>& Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;
			
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand0);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand1);
			break;
		}
		case EX_LetValueOnPersistentFrame: 
		case EX_StructMemberContext: {
			FProperty* Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
			const TSharedPtr<FScriptExpr>& Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;

			WritePointer<FProperty>(OutScriptData, ScriptOffset, Operand0);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand1);
			break;
		}
		case EX_ComputedJump:
		case EX_InterfaceContext:
		case EX_Return:
		case EX_SoftObjectConst:
		case EX_FieldPathConst:
		case EX_ClearMulticastDelegate:
		case EX_PopExecutionFlowIfNot:
		case EX_AutoRtfmAbortIfNot: {
			const TSharedPtr<FScriptExpr>& Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand0);
			break;
		}
		case EX_LocalVirtualFunction:
		case EX_VirtualFunction: {
			const FScriptName& Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeScriptName).ScriptName;
			WriteRawData<FScriptName>(OutScriptData, ScriptOffset, Operand0);
			WriteTrailingExpressions(1, EX_EndFunctionParms);
			break;
		}
		case EX_LocalFinalFunction:
		case EX_FinalFunction:
		case EX_CallMath: {
			UStruct* Operand0 = Cast<UStruct>(Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			WritePointer<UStruct>(OutScriptData, ScriptOffset, Operand0);
			WriteTrailingExpressions(1, EX_EndFunctionParms);
			break;
		}
		case EX_Jump:
		case EX_PushExecutionFlow: {
			const CodeSkipSizeType Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeLabel).TargetLabelCodeOffset;
			WriteRawData<CodeSkipSizeType>(OutScriptData, ScriptOffset, Operand0);
			break;
		}
		case EX_LocalVariable:
		case EX_DefaultVariable:
		case EX_InstanceVariable:
		case EX_LocalOutVariable:
		case EX_ClassSparseDataVariable:
		case EX_PropertyConst: {
			FProperty* Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
			WritePointer<FProperty>(OutScriptData, ScriptOffset, Operand0);
			break;
		}
		case EX_CallMulticastDelegate: {
			UStruct* Operand0 = Cast<UStruct>(Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			const TSharedPtr<FScriptExpr>& Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;

			WritePointer<UStruct>(OutScriptData, ScriptOffset, Operand0);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand1);
			WriteTrailingExpressions(2, EX_EndFunctionParms);
			break;
		}
		case EX_ClassContext:
		case EX_Context:
		case EX_Context_FailSilent: {
			const TSharedPtr<FScriptExpr>& Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand0);

			// Code offset here is relative to the end of first operand
			const CodeSkipSizeType Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeLabel).TargetLabelCodeOffset;
			FProperty* Operand2 = Expr->RequireOperand(2, FScriptExprOperand::TypeProperty).Property;
			const TSharedPtr<FScriptExpr>& Operand3 = Expr->RequireOperand(3, FScriptExprOperand::TypeExpr).Expr;

			// The jump offset is relative to offset of Expression (4th operand)
			// Write a placeholder value, we will come back to patch it later
			int32 ContextNullSkipOffset = ScriptOffset;
			CodeSkipSizeType ContextNullSkip = -1;
			WriteRawData<CodeSkipSizeType>(OutScriptData, ScriptOffset, ContextNullSkip);

			WritePointer<FProperty>(OutScriptData, ScriptOffset, Operand2);

			// Compute the relative code offset from the serialized absolute offset and patch the placeholder
			ContextNullSkip = Operand1 - ScriptOffset;
			WriteRawData<CodeSkipSizeType>(OutScriptData, ContextNullSkipOffset, ContextNullSkip);

			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand3);
			break;
		}
		case EX_IntConst: { WriteRawData<int32>(OutScriptData, ScriptOffset, Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer); break; }
		case EX_Int64Const: { WriteRawData<int64>(OutScriptData, ScriptOffset, Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer); break; }
		case EX_UInt64Const: { WriteRawData<uint64>(OutScriptData, ScriptOffset, Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer); break; }
		case EX_FloatConst: { WriteRawData<float>(OutScriptData, ScriptOffset, Expr->RequireOperand(0, FScriptExprOperand::TypeFloat).Float); break; }
		case EX_DoubleConst: { WriteRawData<double>(OutScriptData, ScriptOffset, Expr->RequireOperand(0, FScriptExprOperand::TypeFloat).Float); break; }
		case EX_StringConst: { WriteString8(OutScriptData, ScriptOffset, Expr->RequireOperand(0, FScriptExprOperand::TypeString).String); break; }
		case EX_UnicodeStringConst: { WriteString16(OutScriptData, ScriptOffset, Expr->RequireOperand(0, FScriptExprOperand::TypeString).String); break; }
		case EX_ObjectConst: { WritePointer<UObject>(OutScriptData, ScriptOffset, Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object); break; }
		case EX_SkipOffsetConst: {
			const CodeSkipSizeType Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeLabel).TargetLabelCodeOffset;
			WriteRawData<CodeSkipSizeType>(OutScriptData, ScriptOffset, Operand0);
			break;
		}
		case EX_InstrumentationEvent:
		case EX_IntConstByte:
		case EX_ByteConst: { WriteRawData<uint8>(OutScriptData, ScriptOffset, Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer); break; }
		case EX_TextConst: {
			const uint8 Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer;
			WriteRawData<uint8>(OutScriptData, ScriptOffset, Operand0);
			const EBlueprintTextLiteralType LiteralType = static_cast<EBlueprintTextLiteralType>(Operand0);

			// String tables prefix their arguments with object const pointing to the string table object if present
			int32 TextOperandOffset = 1;
			if (LiteralType == EBlueprintTextLiteralType::StringTableEntry) {
				WritePointer<UObject>(OutScriptData, ScriptOffset, Expr->RequireOperand(1, FScriptExprOperand::TypeObject).Object);
				TextOperandOffset++;
			}
			// Read the rest of the arguments as expressions
			const int32 OperandCount = GetOperandCountForBlueprintTextType(LiteralType);
			for (int32 i = 0; i < OperandCount; i++) {
				AssembleScriptExpr(OutScriptData, ScriptOffset, Expr->RequireOperand(TextOperandOffset + i, FScriptExprOperand::TypeExpr).Expr);
			}
			break;
		}
		case EX_InstanceDelegate:
		case EX_NameConst: { WriteRawData<FScriptName>(OutScriptData, ScriptOffset, Expr->RequireOperand(0, FScriptExprOperand::TypeScriptName).ScriptName); break; }
		case EX_BitFieldConst: {
			FProperty* Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
			const uint8 Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeInteger).Integer;

			WritePointer<FProperty>(OutScriptData, ScriptOffset, Operand0);
			WriteRawData<uint8>(OutScriptData, ScriptOffset, Operand1);
			break;
		}
		case EX_Skip: {
			// Unknown whenever CodeSkipSizeType here is relative or absolute, since opcode does not currently have a handler registered
			const CodeSkipSizeType Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeLabel).TargetLabelCodeOffset;
			const TSharedPtr<FScriptExpr>& Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;

			WriteRawData<CodeSkipSizeType>(OutScriptData, ScriptOffset, Operand0);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand1);
			break;
		}
		case EX_JumpIfNot: {
			const CodeSkipSizeType Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeLabel).TargetLabelCodeOffset;
			const TSharedPtr<FScriptExpr>& Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;

			WriteRawData<CodeSkipSizeType>(OutScriptData, ScriptOffset, Operand0);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand1);
            break;
        }
		case EX_Assert: {
			const uint16 Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer;
			const uint8 Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeInteger).Integer;
			const TSharedPtr<FScriptExpr>& Operand2 = Expr->RequireOperand(2, FScriptExprOperand::TypeExpr).Expr;

			WriteRawData<uint16>(OutScriptData, ScriptOffset, Operand0);
			WriteRawData<uint8>(OutScriptData, ScriptOffset, Operand1);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand2);
			break;
		}	
		case EX_BindDelegate: {
			const FScriptName& Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeScriptName).ScriptName;
			const TSharedPtr<FScriptExpr>& Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;
			const TSharedPtr<FScriptExpr>& Operand2 = Expr->RequireOperand(2, FScriptExprOperand::TypeExpr).Expr;

			WriteRawData<FScriptName>(OutScriptData,	ScriptOffset, Operand0);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand1);
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand2);
			break;
		}
		case EX_RotationConst:
		case EX_VectorConst:
		case EX_Vector3fConst: {
			const double Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeFloat).Float;
			const double Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeFloat).Float;
			const double Operand2 = Expr->RequireOperand(2, FScriptExprOperand::TypeFloat).Float;

			WriteRawData<double>(OutScriptData, ScriptOffset, Operand0);
			WriteRawData<double>(OutScriptData, ScriptOffset, Operand1);
			WriteRawData<double>(OutScriptData, ScriptOffset, Operand2);
			break;
		}
		case EX_TransformConst: {
			constexpr int32 TotalComponentCount = 4 + 3 + 3;
			for (int32 i = 0; i < TotalComponentCount; i++) {
				WriteRawData<double>(OutScriptData, ScriptOffset, Expr->RequireOperand(i, FScriptExprOperand::TypeFloat).Float);
			}
			break;
		}
		case EX_StructConst: {
			UScriptStruct* Operand0 = Cast<UScriptStruct>(Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			const int32 Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeInteger).Integer;

			WritePointer<UScriptStruct>(OutScriptData, ScriptOffset, Operand0);
			WriteRawData<int32>(OutScriptData, ScriptOffset, Operand1);
			WriteTrailingExpressions(2, EX_EndStructConst);
			break;
		}
		case EX_SwitchValue: {
			const uint16 Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer;
			const TSharedPtr<FScriptExpr>& Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;

			WriteRawData<uint16>(OutScriptData, ScriptOffset, Operand0);
			
			// Write placeholder absolute code skip offset to the end of switch expression, we will come back to it to patch it up once we finish serializing the current instruction
			int32 SwitchExpressionEndSkipOffsetOffset = ScriptOffset;
			CodeSkipSizeType SwitchExpressionEndSkipOffset = -1;
			WriteRawData<CodeSkipSizeType>(OutScriptData, ScriptOffset, SwitchExpressionEndSkipOffset);
			
			AssembleScriptExpr(OutScriptData, ScriptOffset, Operand1);

			for (int32 CaseIndex = 0; CaseIndex < Operand0; CaseIndex++) {
				const TSharedPtr<FScriptExpr>& CaseSelectorExpression = Expr->RequireOperand(2 + CaseIndex * 2 + 0, FScriptExprOperand::TypeExpr).Expr;
				const TSharedPtr<FScriptExpr>& CaseValueExpression = Expr->RequireOperand(2 + CaseIndex * 2 + 1, FScriptExprOperand::TypeExpr).Expr;
				
				AssembleScriptExpr(OutScriptData, ScriptOffset, CaseSelectorExpression);

				// Write placeholder absolute code skip offset to the next case statement, we will come back to it to patch it up once we write the value expression for this case
				int32 SwitchCaseEndSkipOffsetOffset = ScriptOffset;
				CodeSkipSizeType SwitchCaseEndSkipOffset = -1;
				WriteRawData<CodeSkipSizeType>(OutScriptData, ScriptOffset, SwitchCaseEndSkipOffset);
				
				AssembleScriptExpr(OutScriptData, ScriptOffset, CaseValueExpression);

				// Patcj up placeholder absolute code skip offset that we have written above
				SwitchCaseEndSkipOffset = ScriptOffset;
				WriteRawData<CodeSkipSizeType>(OutScriptData, SwitchCaseEndSkipOffsetOffset, SwitchCaseEndSkipOffset);
			}
			const TSharedPtr<FScriptExpr>& OperandN = Expr->RequireOperand(2 + Operand0 * 2, FScriptExprOperand::TypeExpr).Expr;
			AssembleScriptExpr(OutScriptData, ScriptOffset, OperandN);

			// Patch up placeholder absolute code skip offset that we have written earlier
			SwitchExpressionEndSkipOffset = ScriptOffset;
			WriteRawData<CodeSkipSizeType>(OutScriptData, SwitchExpressionEndSkipOffsetOffset, SwitchExpressionEndSkipOffset);
			break;
		}
		case EX_AutoRtfmTransact: {
			const int32 Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer;
			const CodeSkipSizeType Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeLabel).TargetLabelCodeOffset;

			WriteRawData<int32>(OutScriptData, ScriptOffset, Operand0);
			WriteRawData<CodeSkipSizeType>(OutScriptData, ScriptOffset, Operand1);
			break;
		}
		case EX_AutoRtfmStopTransact: {
			const int32 Operand0 = Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer;
			const uint8 Operand1 = Expr->RequireOperand(1, FScriptExprOperand::TypeInteger).Integer;

			WriteRawData<int32>(OutScriptData, ScriptOffset, Operand0);
			WriteRawData<uint8>(OutScriptData, ScriptOffset, Operand1);
			break;
		}
		default: {
			break;
		}
	}
}

const TCHAR* FScriptExprAssembler::GetInstructionName(uint8 InOpcode) {
	switch (InOpcode) {
		case EX_LocalVariable: return TEXT("EX_LocalVariable");
		case EX_InstanceVariable: return TEXT("EX_InstanceVariable");
		case EX_DefaultVariable: return TEXT("EX_InstanceVariable");
		case EX_Return: return TEXT("EX_Return");
		case EX_Jump: return TEXT("EX_Jump");
		case EX_JumpIfNot: return TEXT("EX_JumpIfNot");
		case EX_Assert: return TEXT("EX_Assert");
		case EX_Nothing: return TEXT("EX_Nothing");
		case EX_NothingInt32: return TEXT("EX_NothingInt32"); // unused
		case EX_Let: return TEXT("EX_Let");
		case EX_BitFieldConst: return TEXT("EX_BitfieldConst");
		case EX_ClassContext: return TEXT("EX_ClassContext");
		case EX_MetaCast: return TEXT("EX_MetaCast");
		case EX_LetBool: return TEXT("EX_LetBool");
		case EX_EndParmValue: return TEXT("EX_EndParmValue"); // unused
		case EX_EndFunctionParms: return TEXT("EX_EndFunctionParms");
		case EX_Self: return TEXT("EX_Self");
		case EX_Skip: return TEXT("EX_Skip"); // unused
		case EX_Context: return TEXT("EX_Context");
		case EX_Context_FailSilent: return TEXT("EX_Context_FailSilent");
		case EX_VirtualFunction: return TEXT("EX_VirtualFunction");
		case EX_FinalFunction: return TEXT("EX_FinalFunction");
		case EX_IntConst: return TEXT("EX_IntConst");
		case EX_FloatConst: return TEXT("EX_FloatConst");
		case EX_StringConst: return TEXT("EX_StringConst");
		case EX_ObjectConst: return TEXT("EX_ObjectConst");
		case EX_NameConst: return TEXT("EX_NameConst");
		case EX_RotationConst: return TEXT("EX_RotationConst");
		case EX_VectorConst: return TEXT("EX_VectorConst");
		case EX_ByteConst: return TEXT("EX_ByteConst");
		case EX_IntZero: return TEXT("EX_IntZero"); // unused
		case EX_IntOne: return TEXT("EX_IntOne"); // unused
		case EX_True: return TEXT("EX_True");
		case EX_False: return TEXT("EX_False");
		case EX_TextConst: return TEXT("EX_TextConst");
		case EX_NoObject: return TEXT("EX_NoObject");
		case EX_TransformConst: return TEXT("EX_TransformConst");
		case EX_IntConstByte: return TEXT("EX_IntConstByte"); // unused
		case EX_NoInterface: return TEXT("EX_NoInterface");
		case EX_DynamicCast: return TEXT("EX_DynamicCast");
		case EX_StructConst: return TEXT("EX_StructConst");
		case EX_EndStructConst: return TEXT("EX_EndStructConst");
		case EX_SetArray: return TEXT("EX_SetArray");
		case EX_EndArray: return TEXT("EX_EndArray");
		case EX_PropertyConst: return TEXT("EX_PropertyConst"); // unused
		case EX_UnicodeStringConst: return TEXT("EX_UnicodeStringConst");
		case EX_Int64Const: return TEXT("EX_Int64Const");
		case EX_UInt64Const: return TEXT("EX_UInt64Const");
		case EX_DoubleConst: return TEXT("EX_DoubleConst");
		case EX_Cast: return TEXT("EX_Cast");
		case EX_SetSet: return TEXT("EX_SetSet");
		case EX_EndSet: return TEXT("EX_EndSet");
		case EX_SetMap: return TEXT("EX_SetMap");
		case EX_EndMap: return TEXT("EX_EndMap");
		case EX_SetConst: return TEXT("EX_SetConst");
		case EX_EndSetConst: return TEXT("EX_EndSetConst");
		case EX_MapConst: return TEXT("EX_MapConst");
		case EX_EndMapConst: return TEXT("EX_EndMapConst");
		case EX_Vector3fConst: return TEXT("EX_Vector3fConst");
		case EX_StructMemberContext: return TEXT("EX_StructMemberContext");
		case EX_LetMulticastDelegate: return TEXT("EX_LetMulticastDelegate");
		case EX_LetDelegate: return TEXT("EX_LetDelegate");
		case EX_LocalVirtualFunction: return TEXT("EX_LocalVirtualFunction");
		case EX_LocalFinalFunction: return TEXT("EX_LocalFinalFunction");
		case EX_LocalOutVariable: return TEXT("EX_LocalOutVariable");
		case EX_DeprecatedOp4A: return TEXT("EX_DeprecatedOp4A");
		case EX_InstanceDelegate: return TEXT("EX_InstanceDelegate");
		case EX_PushExecutionFlow: return TEXT("EX_PushExecutionFlow");
		case EX_PopExecutionFlow: return TEXT("EX_PopExecutionFlow");
		case EX_ComputedJump: return TEXT("EX_ComputedJump");
		case EX_PopExecutionFlowIfNot: return TEXT("EX_PopExecutionFlowIfNot");
		case EX_Breakpoint: return TEXT("EX_Breakpoint");
		case EX_InterfaceContext: return TEXT("EX_InterfaceContext");
		case EX_ObjToInterfaceCast: return TEXT("EX_ObjToInterfaceCast");
		case EX_EndOfScript: return TEXT("EX_EndOfScript");
		case EX_CrossInterfaceCast: return TEXT("EX_CrossInterfaceCast");
		case EX_InterfaceToObjCast: return TEXT("EX_InterfaceToObjCast");
		case EX_WireTracepoint: return TEXT("EX_WireTracepoint");
		case EX_SkipOffsetConst: return TEXT("EX_SkipOffsetConst");
		case EX_AddMulticastDelegate: return TEXT("EX_AddMulticastDelegate");
		case EX_ClearMulticastDelegate: return TEXT("EX_ClearMulticastDelegate");
		case EX_Tracepoint: return TEXT("EX_Tracepoint");
		case EX_LetObj: return TEXT("EX_LetObj");
		case EX_LetWeakObjPtr: return TEXT("EX_LetWeakObjPtr");
		case EX_BindDelegate: return TEXT("EX_BindDelegate");
		case EX_RemoveMulticastDelegate: return TEXT("EX_RemoveMulticastDelegate");
		case EX_CallMulticastDelegate: return TEXT("EX_CallMulticastDelegate");
		case EX_LetValueOnPersistentFrame: return TEXT("EX_LetValueOnPersistentFrame");
		case EX_ArrayConst: return TEXT("EX_ArrayConst");
		case EX_EndArrayConst: return TEXT("EX_EndArrayConst");
		case EX_SoftObjectConst: return TEXT("EX_SoftObjectConst");
		case EX_CallMath: return TEXT("EX_CallMath");
		case EX_SwitchValue: return TEXT("EX_SwitchValue");
		case EX_InstrumentationEvent: return TEXT("EX_InstrumentationEvent");
		case EX_ArrayGetByRef: return TEXT("EX_ArrayGetByRef");
		case EX_ClassSparseDataVariable: return TEXT("EX_ClassSparseDataVariable");
		case EX_FieldPathConst: return TEXT("EX_FieldPathConst");
		case EX_AutoRtfmTransact: return TEXT("EX_AutoRtfmTransact");
		case EX_AutoRtfmStopTransact: return TEXT("EX_AutoRtfmStopTransact");
		case EX_AutoRtfmAbortIfNot: return TEXT("EX_AutoRtfmAbortIfNot");
		default: return TEXT("Unknown");
	}
}

void FScriptExprAssembler::DisassembleFunction(const TArray<uint8>& ScriptBytecode, TArray<TSharedPtr<FScriptExpr>>& OutLinearExecutionSequence) {
	OutLinearExecutionSequence.Empty();
	TMap<int32, TSharedPtr<FScriptExpr>> StatementToScriptOffsetLookup;

	// Diassemble instructions until we reach the end of the stream
	int32 CurrentScriptOffset = 0;
	while (CurrentScriptOffset < ScriptBytecode.Num()) {
		const TSharedPtr<FScriptExpr> DisassembledStatement = DisassembleScriptExpr(ScriptBytecode.GetData(), CurrentScriptOffset);

		// Add the statement to the mapping if we have parsed one
		if (DisassembledStatement) {
			StatementToScriptOffsetLookup.Add(DisassembledStatement->ScriptOffset, DisassembledStatement);
			OutLinearExecutionSequence.Add(DisassembledStatement);
		}
		// Stop after we failed to parse a statement or the statement was end of script
		if (DisassembledStatement == nullptr || DisassembledStatement->Opcode == EX_EndOfScript) {
			break;
		}
	}

	// Resolve labels on the statements that we have disassembled
	for (const TSharedPtr<FScriptExpr>& Statement : OutLinearExecutionSequence) {
		Statement->ForEachOperandRecursive([&](FScriptExprOperand& Operand) {
			if (Operand.Type == FScriptExprOperand::TypeLabel) {
				Operand.TargetLabel = nullptr;
				if (Operand.TargetLabelCodeOffset >= 0) {
					if (const TSharedPtr<FScriptExpr>* ResolvedLabelStatement = StatementToScriptOffsetLookup.Find(Operand.TargetLabelCodeOffset)) {
						Operand.TargetLabel = *ResolvedLabelStatement;
					}
				}
			}
		});
	}
}

void FScriptExprAssembler::AssembleFunction(const TArray<TSharedPtr<FScriptExpr>>& LinearExecutionSequence, TArray<uint8>& OutScriptBytecode) {
	OutScriptBytecode.Empty();
	TSet<TSharedPtr<FScriptExpr>> ValidJumpTargetStatementLabels;

	// Write statements without valid jump label offsets first and collect their locations
	int32 CurrentScriptOffset = 0;
	for (const TSharedPtr<FScriptExpr>& Statement : LinearExecutionSequence) {
		Statement->ScriptOffset = CurrentScriptOffset;
		AssembleScriptExpr(OutScriptBytecode, CurrentScriptOffset, Statement);
		ValidJumpTargetStatementLabels.Add(Statement);
	}

	// Resolve labels on the statements now that we have script offsets
	for (const TSharedPtr<FScriptExpr>& Statement : LinearExecutionSequence) {
		Statement->ForEachOperandRecursive([&](FScriptExprOperand& Operand) {
			if (Operand.Type == FScriptExprOperand::TypeLabel) {
				Operand.TargetLabelCodeOffset = INDEX_NONE;
				if (ValidJumpTargetStatementLabels.Contains(Operand.TargetLabel)) {
					Operand.TargetLabelCodeOffset = Operand.TargetLabel->ScriptOffset;
				}
			}
		});
	}

	// Re-write statements on their original offsets to apply new label offsets
	for (const TSharedPtr<FScriptExpr>& Statement : LinearExecutionSequence) {
		int32 CurrentStatementScriptOffset = Statement->ScriptOffset;
		AssembleScriptExpr(OutScriptBytecode, CurrentStatementScriptOffset, Statement);
	}
}

#include "Toolkit/KismetByteCodeSerializer.h"
#include "Toolkit/PropertyTypeHandler.h"

typedef bool InstructionHandler(FParseFrame&, TSharedPtr<FJsonObject>&, uint8*);
typedef InstructionHandler PrimitiveCastHandler;

TMap<uint8, InstructionHandler*> InstructionHandlers;
TMap<uint8, PrimitiveCastHandler*> PrimitiveCasts;

struct InstructionHandlerRegisterer {
	InstructionHandlerRegisterer(InstructionHandler handler, uint8 instruction) {
		InstructionHandlers.Add(instruction, handler);
	}
};

struct PrimitiveCastHandlerRegisterer {
	PrimitiveCastHandlerRegisterer(PrimitiveCastHandler handler, uint8 primitiveCast) {
		PrimitiveCasts.Add(primitiveCast, handler);
	}
};

FParseFrame::FParseFrame(UObject* Context, UFunction* Function) {
	ParametersFrame = FMemory::Malloc(Function->ParmsSize);
	Frame = new FFrame(Context, Function, ParametersFrame, NULL, NULL);
}

FParseFrame::~FParseFrame() {
	FMemory::Free(ParametersFrame);
	delete Frame;
}

TSharedPtr<FJsonObject> FParseFrame::Step(void* ReturnValue) {
	TSharedPtr<FJsonObject> Instruction = MakeShareable(new FJsonObject());
	int32 NextInstruction = *Frame->Code++;
	InstructionHandler* const* InstructionHandler = InstructionHandlers.Find(NextInstruction);
	checkf(InstructionHandler, TEXT("Handler not found for instruction %X"), NextInstruction);
	(*InstructionHandler)(*this, Instruction, (uint8*) ReturnValue);
	return Instruction;
}

#define INSTRUCTION(Inst) InstructionHandlerRegisterer Register##Inst(&Handle##Inst, Inst);
#define INSTRUCTION_HANDLER(Inst) \
	bool Handle##Inst(FParseFrame& Stack, TSharedPtr<FJsonObject>& Result, uint8* ReturnValue) { \
		Result->SetStringField("Instruction", #Inst); \
		Result->SetNumberField("InstOffsetFromTop", Stack.GetOffsetFromPtr(Stack.Frame->Code - 1));

#define PRIMITIVE_CAST(Cast) PrimitiveCastHandlerRegisterer Register##Cast(&Handle##Cast, Cast);
#define PRIMITIVE_CAST_HANDLER(Cast) \
	bool Handle##Cast(FParseFrame& Stack, TSharedPtr<FJsonObject>& Result, uint8* ReturnValue) {

TArray<TSharedPtr<FJsonValue>> ParseClosure(FParseFrame& Stack, uint8* ReturnValue) {
	TArray<TSharedPtr<FJsonValue>> Result;
	while (*Stack.Frame->Code != EX_Return) {
		TSharedPtr<FJsonObject> Inst = Stack.Step(ReturnValue);
		if (Inst.IsValid()) Result.Add(MakeShareable(new FJsonValueObject(Inst)));
	}
	return Result;
}

void SetDefaultRetVal(uint8* ReturnValue, UProperty* Prop) {
	if (!ReturnValue) return;
	if (UObjectProperty* objProp = Cast<UObjectProperty>(Prop)) {
		*(UObject**)ReturnValue = objProp->PropertyClass->GetDefaultObject();
	} else if (UInterfaceProperty* objProp = Cast<UInterfaceProperty>(Prop)) {
		*(UObject**)ReturnValue = objProp->InterfaceClass->GetDefaultObject();
	}
}

INSTRUCTION_HANDLER(EX_LocalVariable)
	UProperty* Prop = Stack.ReadProperty();
	Result->SetStringField("VarName", Prop->GetName());
	FEdGraphPinType PropertyPinType;
	FPropertyTypeHelper::ConvertPropertyToPinType(Prop, PropertyPinType);
	Result->SetObjectField("VarType", FPropertyTypeHelper::SerializeGraphPinType(PropertyPinType));
	SetDefaultRetVal(ReturnValue, Prop);
	return true;
}
INSTRUCTION(EX_LocalVariable)

INSTRUCTION_HANDLER(EX_InstanceVariable)
	UProperty* Prop = (UProperty*)Stack.ReadObject();
	Result->SetStringField("VarName", Prop->GetName());
	SetDefaultRetVal(ReturnValue, Prop);
	return true;
}
INSTRUCTION(EX_InstanceVariable)

INSTRUCTION_HANDLER(EX_DefaultVariable)
	UProperty* Prop = (UProperty*)Stack.ReadObject();
	Result->SetStringField("VarName", Prop->GetName());
	SetDefaultRetVal(ReturnValue, Prop);
	return true;
}
INSTRUCTION(EX_DefaultVariable)

INSTRUCTION_HANDLER(EX_Return)
	return true;
}
INSTRUCTION(EX_Return)

INSTRUCTION_HANDLER(EX_Jump)
	const CodeSkipSizeType Offset = Stack.ReadCodeSkipCount();
	Result->SetNumberField("Offset", Offset);
	return true;
}
INSTRUCTION(EX_Jump)

INSTRUCTION_HANDLER(EX_JumpIfNot)
	Result->SetNumberField("Offset", Stack.ReadCodeSkipCount());
	Result->SetObjectField("Condition", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_JumpIfNot)

INSTRUCTION_HANDLER(EX_Assert)
	Result->SetNumberField("Line", Stack.ReadWord());
	Result->SetBoolField("Debug", (bool) *Stack.Frame->Code++);
	Result->SetObjectField("Condition", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_Assert)

INSTRUCTION_HANDLER(EX_Nothing)
	return false;
}
INSTRUCTION(EX_Nothing)

INSTRUCTION_HANDLER(EX_Let)
	UProperty* LocalProp = Stack.ReadPropertyUnchecked();
	if (LocalProp) {
		Result->SetStringField("LocalProp", LocalProp->GetName());
	}
	Result->SetObjectField("EvaluateProp", Stack.Step(nullptr));
	Result->SetObjectField("EvaluateExp", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_Let)

INSTRUCTION_HANDLER(EX_ClassContext)
	UObject* OldContext = Stack.Frame->Object;
	UObject* NewContext = nullptr;
	Result->SetObjectField("Context", Stack.Step(&NewContext));
	Result->SetNumberField("Skip", Stack.ReadCodeSkipCount());
	UProperty* RValueProperty = nullptr;
	const VariableSizeType bSize = Stack.ReadVariableSize(&RValueProperty);
	Result->SetStringField("ValProp", RValueProperty->GetFullName());
	Result->SetNumberField("ValSize", bSize);
	Stack.Frame->Object = NewContext;
	Result->SetObjectField("Code", Stack.Step(ReturnValue));
	Stack.Frame->Object = OldContext;
	return true;
}
INSTRUCTION(EX_ClassContext)

INSTRUCTION_HANDLER(EX_MetaCast)
	UClass* MetaClass = (UClass*)Stack.ReadObject();
	Result->SetStringField("MetaClass", MetaClass->GetFullName());
	UObject* OldContext = Stack.Frame->Object;
	Stack.Frame->Object = MetaClass->GetDefaultObject();
	Result->SetObjectField("Castee", Stack.Step(nullptr));
	Stack.Frame->Object = OldContext;
	return true;
}
INSTRUCTION(EX_MetaCast)

INSTRUCTION_HANDLER(EX_LetBool)
	Result->SetObjectField("EvaluateProp", Stack.Step(nullptr));
	Result->SetObjectField("EvaluateExp", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_LetBool)

INSTRUCTION_HANDLER(EX_Self)
	if (ReturnValue)
		*(UObject**)ReturnValue = Stack.Frame->Object;
	return true;
}
INSTRUCTION(EX_Self)

INSTRUCTION_HANDLER(EX_EndFunctionParms)
	Stack.Frame->Code--;
	return false;
}
INSTRUCTION(EX_EndFunctionParms)

void ParseContextInstruction(FParseFrame& Stack, TSharedPtr<FJsonObject>& Result, uint8* ReturnValue) {
	UObject* OldContext = Stack.Frame->Object;
	UObject* NewContext = nullptr;
	Result->SetObjectField("Context", Stack.Step(&NewContext));
	Result->SetNumberField("Skip", Stack.ReadCodeSkipCount());
	UProperty* RValueProperty = nullptr;
	const VariableSizeType bSize = Stack.ReadVariableSize(&RValueProperty);
	Result->SetStringField("ValProp", RValueProperty->GetFullName());
	Result->SetNumberField("ValSize", bSize);
	Stack.Frame->Object = NewContext;
	Result->SetObjectField("Code", Stack.Step(ReturnValue));
	Stack.Frame->Object = OldContext;
}

INSTRUCTION_HANDLER(EX_Context)
	ParseContextInstruction(Stack, Result, ReturnValue);
	return true;
}
INSTRUCTION(EX_Context)

INSTRUCTION_HANDLER(EX_Context_FailSilent)
	ParseContextInstruction(Stack, Result, ReturnValue);
	return true;
}
INSTRUCTION(EX_Context_FailSilent)

void ParseFunctionInstruction(UFunction* function, FParseFrame& Stack, TSharedPtr<FJsonObject>& Result, uint8* ReturnValue) {
	TArray<TSharedPtr<FJsonValue>> params;
	for (UProperty* Property = (UProperty*) function->Children; *Stack.Frame->Code != EX_EndFunctionParms; Property = (UProperty*)Property->Next) {
		if (Property->PropertyFlags & CPF_ReturnParm) {
			if (UObjectProperty* objProp = Cast<UObjectProperty>(Property)) {
				if (ReturnValue) *(UObject**)ReturnValue = objProp->PropertyClass->GetDefaultObject();
			}
		} else if (Property->PropertyFlags & CPF_OutParm) {
			TSharedPtr<FJsonObject> param = Stack.Step(nullptr);
			param->SetBoolField("FunctionParamOut", true);
			param->SetStringField("FunctionParamName", Property->GetName());
			params.Add(MakeShareable(new FJsonValueObject(param)));
		} else {
			TSharedPtr<FJsonObject> param = Stack.Step(nullptr);
			param->SetBoolField("FunctionParamOut", false);
			param->SetStringField("FunctionParamName", Property->GetName());
			params.Add(MakeShareable(new FJsonValueObject(param)));
		}
	}
	Result->SetArrayField("Params", params);
	Stack.Frame->Code += !!Stack.Frame->Code; // EX_EndFunctionParms
}

INSTRUCTION_HANDLER(EX_VirtualFunction)
	FName funcName = Stack.ReadName();
	Result->SetStringField("Function", funcName.ToString());
	ParseFunctionInstruction(Stack.Frame->Object->FindFunctionChecked(funcName), Stack, Result, ReturnValue);
	return true;
}
INSTRUCTION(EX_VirtualFunction)

INSTRUCTION_HANDLER(EX_FinalFunction)
	UFunction* func = (UFunction*) Stack.ReadObject();
	Result->SetStringField("Function", func->GetFullName());
	ParseFunctionInstruction(func, Stack, Result, ReturnValue);
	return true;
}
INSTRUCTION(EX_FinalFunction)

INSTRUCTION_HANDLER(EX_IntConst)
	Result->SetNumberField("Value", Stack.ReadInt<int32>());
	return true;
}
INSTRUCTION(EX_IntConst)

INSTRUCTION_HANDLER(EX_FloatConst)
	Result->SetNumberField("Value", Stack.ReadFloat());
	return true;
}
INSTRUCTION(EX_FloatConst)

INSTRUCTION_HANDLER(EX_StringConst)
	FString Str = (ANSICHAR*)Stack.Frame->Code;
	while (*Stack.Frame->Code)
		Stack.Frame->Code++;
	Stack.Frame->Code++;

	Result->SetStringField("Value", Str);
	return true;
}
INSTRUCTION(EX_StringConst)

INSTRUCTION_HANDLER(EX_ObjectConst)
	UObject* obj = Stack.ReadObject();
	Result->SetStringField("Value", obj->GetFullName());
	if (ReturnValue) *((UObject**)ReturnValue) = obj;
	return true;
}
INSTRUCTION(EX_ObjectConst)

INSTRUCTION_HANDLER(EX_NameConst)
	Result->SetStringField("Value", Stack.ReadName().ToString());
	return true;
}
INSTRUCTION(EX_NameConst)

INSTRUCTION_HANDLER(EX_RotationConst)
	Result->SetNumberField("Pitch", Stack.ReadFloat());
	Result->SetNumberField("Yaw", Stack.ReadFloat());
	Result->SetNumberField("Roll", Stack.ReadFloat());
	return true;
}
INSTRUCTION(EX_RotationConst)

INSTRUCTION_HANDLER(EX_VectorConst)
	Result->SetNumberField("X", Stack.ReadFloat());
	Result->SetNumberField("Y", Stack.ReadFloat());
	Result->SetNumberField("Z", Stack.ReadFloat());
	return true;
}
INSTRUCTION(EX_VectorConst)

INSTRUCTION_HANDLER(EX_ByteConst)
	Result->SetNumberField("Value", (uint8)*Stack.Frame->Code++);
	return true;
}
INSTRUCTION(EX_ByteConst)

INSTRUCTION_HANDLER(EX_IntZero)
	return true;
}
INSTRUCTION(EX_IntZero)

INSTRUCTION_HANDLER(EX_IntOne)
	return true;
}
INSTRUCTION(EX_IntOne)

INSTRUCTION_HANDLER(EX_True)
	return true;
}
INSTRUCTION(EX_True)

INSTRUCTION_HANDLER(EX_False)
	return true;
}
INSTRUCTION(EX_False)

INSTRUCTION_HANDLER(EX_TextConst)
	const EBlueprintTextLiteralType TextLiteralType = (EBlueprintTextLiteralType)*Stack.Frame->Code++;
	Result->SetNumberField("Type", (uint32) TextLiteralType);
	
	switch (TextLiteralType) {
		case EBlueprintTextLiteralType::Empty: {
			break;
		}
		case EBlueprintTextLiteralType::LocalizedText: {
			Result->SetObjectField("SrcStr", Stack.Step(nullptr));
			Result->SetObjectField("Key", Stack.Step(nullptr));
			Result->SetObjectField("Namespace", Stack.Step(nullptr));
			break;
		}
		case EBlueprintTextLiteralType::InvariantText: {
			Result->SetObjectField("SrcStr", Stack.Step(nullptr));
			break;
		}
		case EBlueprintTextLiteralType::LiteralString: {
			Result->SetObjectField("SrcStr", Stack.Step(nullptr));
			break;
		}

		case EBlueprintTextLiteralType::StringTableEntry: {
			Result->SetStringField("StringTable", Stack.ReadObject()->GetFullName());
			Result->SetObjectField("TableIDStr", Stack.Step(nullptr));
			Result->SetObjectField("KeyStr", Stack.Step(nullptr));
			break;
		}
		default:
			checkf(false, TEXT("Unknown EBlueprintTextLiteralType! Please update UObject::execTextConst to handle this type of text."));
			break;
		}
	return true;
}
INSTRUCTION(EX_TextConst)

INSTRUCTION_HANDLER(EX_NoObject)
	if (ReturnValue) *(UObject**)ReturnValue = nullptr;
	return true;
}
INSTRUCTION(EX_NoObject)

INSTRUCTION_HANDLER(EX_TransformConst)
	Result->SetNumberField("RotX", Stack.ReadFloat());
	Result->SetNumberField("RotY", Stack.ReadFloat());
	Result->SetNumberField("RotZ", Stack.ReadFloat());
	Result->SetNumberField("RotW", Stack.ReadFloat());

	Result->SetNumberField("TransX", Stack.ReadFloat());
	Result->SetNumberField("TransY", Stack.ReadFloat());
	Result->SetNumberField("TransZ", Stack.ReadFloat());

	Result->SetNumberField("ScaleX", Stack.ReadFloat());
	Result->SetNumberField("ScaleY", Stack.ReadFloat());
	Result->SetNumberField("ScaleZ", Stack.ReadFloat());
	return true;
}
INSTRUCTION(EX_TransformConst)

INSTRUCTION_HANDLER(EX_IntConstByte)
	Result->SetNumberField("Value", (int32)*Stack.Frame->Code++);
	return true;
}
INSTRUCTION(EX_IntConstByte)

INSTRUCTION_HANDLER(EX_NoInterface)
	if (ReturnValue) *(UObject**)ReturnValue = nullptr;
	return true;
}
INSTRUCTION(EX_NoInterface)

INSTRUCTION_HANDLER(EX_DynamicCast)
	UClass* Type = (UClass*)Stack.ReadObject();
	Result->SetStringField("Type", Type->GetFullName());
	Result->SetObjectField("Code", Stack.Step(ReturnValue));
	if (ReturnValue) *((UObject**)ReturnValue) = Type->GetDefaultObject();
	return true;
}
INSTRUCTION(EX_DynamicCast)

INSTRUCTION_HANDLER(EX_StructConst)
	UScriptStruct* ScriptStruct = CastChecked<UScriptStruct>(Stack.ReadObject());
	Result->SetStringField("Struct", ScriptStruct->GetFullName());
	
	int32 SerializedSize = Stack.ReadInt<int32>();
	Result->SetNumberField("Size", SerializedSize);

	TArray<TSharedPtr<FJsonValue>> attributes;
	bool bIsEditorOnlyStruct = false;
	for (UProperty* StructProp = ScriptStruct->PropertyLink; StructProp; StructProp = StructProp->PropertyLinkNext) {
		if (StructProp->PropertyFlags & CPF_Transient || (!bIsEditorOnlyStruct && StructProp->PropertyFlags & CPF_EditorOnly)) {
			continue;
		}

		for (int32 ArrayIter = 0; ArrayIter < StructProp->ArrayDim; ++ArrayIter) {
			TSharedPtr<FJsonObject> prop = Stack.Step(nullptr);
			prop->SetStringField("StructPropName", StructProp->GetName());
			attributes.Add(MakeShareable(new FJsonValueObject(prop)));
		}
	}
	Result->SetArrayField("Value", attributes);
	Stack.Frame->Code += !!Stack.Frame->Code;;
	return true;
}
INSTRUCTION(EX_StructConst)

INSTRUCTION_HANDLER(EX_SetArray)
	Result->SetObjectField("Array", Stack.Step(nullptr));
	TArray<TSharedPtr<FJsonValue>> values;
	while (*Stack.Frame->Code != EX_EndArray) {
		values.Add(MakeShareable(new FJsonValueObject(Stack.Step(nullptr))));
	}
	Result->SetArrayField("Values", values);
	Stack.Frame->Code += !!Stack.Frame->Code; // EX_EndArray
	return true;
}
INSTRUCTION(EX_SetArray)

INSTRUCTION_HANDLER(EX_UnicodeStringConst)
	Result->SetStringField("Value", FString((UCS2CHAR*)Stack.Frame->Code));

	while (*(uint16*)Stack.Frame->Code) {
		Stack.Frame->Code += sizeof(uint16);
	}
	Stack.Frame->Code += sizeof(uint16);
	return true;
}
INSTRUCTION(EX_UnicodeStringConst)

INSTRUCTION_HANDLER(EX_Int64Const)
	Result->SetNumberField("Value", Stack.ReadInt<int64>());

	return true;
}
INSTRUCTION(EX_Int64Const)

INSTRUCTION_HANDLER(EX_UInt64Const)
	Result->SetNumberField("Value", Stack.ReadInt<uint64>());

	return true;
}
INSTRUCTION(EX_UInt64Const)

INSTRUCTION_HANDLER(EX_PrimitiveCast)
	int32 B = *(Stack.Frame->Code)++;
	Result->SetNumberField("Cast", B);
	(PrimitiveCasts[B])(Stack, Result, ReturnValue);
	
	return true;
}
INSTRUCTION(EX_PrimitiveCast)

INSTRUCTION_HANDLER(EX_SetSet)
	Result->SetObjectField("Set", Stack.Step(nullptr));
	const int32 Num = Stack.ReadInt<int32>();
	TArray<TSharedPtr<FJsonValue>> values;
	if (Num > 0) {
		while (*Stack.Frame->Code != EX_EndSet) {
			values.Add(MakeShareable(new FJsonValueObject(Stack.Step(nullptr))));
		}
	}
	Result->SetArrayField("Values", values);

	Stack.Frame->Code += !!Stack.Frame->Code; // EX_EndSet
	
	return true;
}
INSTRUCTION(EX_SetSet)

INSTRUCTION_HANDLER(EX_SetMap)
	Result->SetObjectField("Map", Stack.Step(nullptr));
	const int32 Num = Stack.ReadInt<int32>();
	TArray<TSharedPtr<FJsonValue>> values;
	if (Num > 0) {
		while (*Stack.Frame->Code != EX_EndMap) {
			TSharedRef<FJsonObject> value = MakeShareable(new FJsonObject());
			value->SetObjectField("Value", Stack.Step(nullptr));
			value->SetObjectField("Key", Stack.Step(nullptr));
			values.Add(MakeShareable(new FJsonValueObject(value)));
		}
	}
	Result->SetArrayField("Values", values);

	Stack.Frame->Code += !!Stack.Frame->Code; // EX_EndMap

	return true;
}
INSTRUCTION(EX_SetMap)

INSTRUCTION_HANDLER(EX_SetConst)
	UProperty* InnerProperty = CastChecked<UProperty>(Stack.ReadObject());
	Result->SetStringField("Type", InnerProperty->GetFullName());
	
	int32 Num = Stack.ReadInt<int32>();
	Result->SetNumberField("Num", Num);

	TArray<TSharedPtr<FJsonValue>> values;
	while (*Stack.Frame->Code != EX_EndSetConst) {
		values.Add(MakeShareable(new FJsonValueObject(Stack.Step(nullptr))));
	}
	Result->SetArrayField("Values", values);

	Stack.Frame->Code += !!Stack.Frame->Code; // EX_EndSetConst

	return true;
}
INSTRUCTION(EX_SetConst)

INSTRUCTION_HANDLER(EX_MapConst)
	UProperty* KeyProperty = CastChecked<UProperty>(Stack.ReadObject());
	Result->SetStringField("KeyType", KeyProperty->GetFullName());
	UProperty* ValProperty = CastChecked<UProperty>(Stack.ReadObject());
	Result->SetStringField("ValueType", ValProperty->GetFullName());
	int32 Num = Stack.ReadInt<int32>();
	Result->SetNumberField("Num", Num);

	TArray<TSharedPtr<FJsonValue>> values;
	while (*Stack.Frame->Code != EX_EndMapConst) {
		TSharedRef<FJsonObject> value = MakeShareable(new FJsonObject());
		value->SetObjectField("Value", Stack.Step(nullptr));
		value->SetObjectField("Key", Stack.Step(nullptr));
		values.Add(MakeShareable(new FJsonValueObject(value)));
	}
	Result->SetArrayField("Values", values);

	Stack.Frame->Code += !!Stack.Frame->Code; // EX_EndMapConst

	return true;
}
INSTRUCTION(EX_MapConst)

INSTRUCTION_HANDLER(EX_StructMemberContext)
	UProperty* StructProperty = Stack.ReadProperty();
	Result->SetStringField("Context", StructProperty->GetName());
	Result->SetObjectField("Code", Stack.Step(ReturnValue));
	SetDefaultRetVal(ReturnValue, StructProperty);
	return true;
}
INSTRUCTION(EX_StructMemberContext)

INSTRUCTION_HANDLER(EX_LetMulticastDelegate)
	Result->SetObjectField("EvaluateProp", Stack.Step(nullptr));
	Result->SetObjectField("EvaluateExp", Stack.Step(nullptr));

	return true;
}
INSTRUCTION(EX_LetMulticastDelegate)

INSTRUCTION_HANDLER(EX_LetDelegate)
	Result->SetObjectField("EvaluateProp", Stack.Step(nullptr));
	Result->SetObjectField("EvaluateExp", Stack.Step(nullptr));

	return true;
}
INSTRUCTION(EX_LetDelegate)

INSTRUCTION_HANDLER(EX_LocalVirtualFunction)
	FName funcName = Stack.ReadName();
	Result->SetStringField("Function", funcName.ToString());
	ParseFunctionInstruction(Stack.Frame->Object->FindFunctionChecked(funcName), Stack, Result, ReturnValue);

	return true;
}
INSTRUCTION(EX_LocalVirtualFunction)

INSTRUCTION_HANDLER(EX_LocalFinalFunction)
	UFunction* func = (UFunction*)Stack.ReadObject();
	Result->SetStringField("Function", func->GetFullName());
	ParseFunctionInstruction(func, Stack, Result, ReturnValue);

	// Ubergraph execute parse
	if (Result->GetStringField("Instruction") == "EX_LocalFinalFunction") {
		FString ubergraphFunc = Result->GetStringField("Function");
		FString ubergraph;
		ubergraphFunc.Split(":", NULL, &ubergraph);
		if (ubergraph.Contains("ExecuteUbergraph")) {
			TSharedPtr<FJsonObject> newInstruction = MakeShareable(new FJsonObject());
			newInstruction->SetStringField("Instruction", "CallUbergraph");
			newInstruction->SetNumberField("InstOffsetFromTop", Result->GetNumberField("InstOffsetFromTop"));
			TArray<TSharedPtr<FJsonValue>> params = Result->GetArrayField("Params");
			newInstruction->SetNumberField("UbergraphOffset", params[0]->AsObject()->GetNumberField("Value"));
			newInstruction->SetStringField("Ubergraph", ubergraph);
			Result = newInstruction;
		}
	}

	return true;
}
INSTRUCTION(EX_LocalFinalFunction)

INSTRUCTION_HANDLER(EX_LocalOutVariable)
	UProperty* VarProperty = Stack.ReadProperty();
	Result->SetStringField("VarName", VarProperty->GetName());
	FEdGraphPinType PropertyPinType;
	FPropertyTypeHelper::ConvertPropertyToPinType(VarProperty, PropertyPinType);
	Result->SetObjectField("VarType", FPropertyTypeHelper::SerializeGraphPinType(PropertyPinType));
	SetDefaultRetVal(ReturnValue, VarProperty);
	return true;
}
INSTRUCTION(EX_LocalOutVariable)

INSTRUCTION_HANDLER(EX_DeprecatedOp4A)
	return false;
}
INSTRUCTION(EX_DeprecatedOp4A)

INSTRUCTION_HANDLER(EX_InstanceDelegate)
	Result->SetStringField("FunctionName", Stack.ReadName().ToString());
	return true;
}
INSTRUCTION(EX_InstanceDelegate)

INSTRUCTION_HANDLER(EX_PushExecutionFlow)
	CodeSkipSizeType offset = Stack.ReadCodeSkipCount();
	Result->SetNumberField("Offset", offset);
	return true;
}
INSTRUCTION(EX_PushExecutionFlow)

INSTRUCTION_HANDLER(EX_PopExecutionFlow)
	return true;
}
INSTRUCTION(EX_PopExecutionFlow)

INSTRUCTION_HANDLER(EX_ComputedJump)
	Result->SetObjectField("Offset", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_ComputedJump)

INSTRUCTION_HANDLER(EX_PopExecutionFlowIfNot)
	Result->SetObjectField("Condition", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_PopExecutionFlowIfNot)

INSTRUCTION_HANDLER(EX_Breakpoint)
	return false;
}
INSTRUCTION(EX_Breakpoint)

INSTRUCTION_HANDLER(EX_InterfaceContext)
	Result->SetObjectField("Interface", Stack.Step(ReturnValue));
	return true;
}
INSTRUCTION(EX_InterfaceContext)

INSTRUCTION_HANDLER(EX_ObjToInterfaceCast)
	return (PrimitiveCasts[CST_ObjectToInterface])(Stack, Result, ReturnValue);
}
INSTRUCTION(EX_ObjToInterfaceCast)

INSTRUCTION_HANDLER(EX_CrossInterfaceCast)
	UClass* CastTo = dynamic_cast<UClass*>(Stack.ReadObject());
	Result->SetStringField("Type", CastTo->GetFullName());
	Result->SetObjectField("Value", Stack.Step(nullptr));
	if (ReturnValue) *(UObject**)ReturnValue = CastTo->GetDefaultObject();
	return true;
}
INSTRUCTION(EX_CrossInterfaceCast)

INSTRUCTION_HANDLER(EX_InterfaceToObjCast)
	UClass* CastTo = dynamic_cast<UClass*>(Stack.ReadObject());
	Result->SetStringField("Type", CastTo->GetFullName());
	Result->SetObjectField("Value", Stack.Step(nullptr));
	if (ReturnValue) *(UObject**)ReturnValue = CastTo->GetDefaultObject();
	return true;
}
INSTRUCTION(EX_InterfaceToObjCast)

INSTRUCTION_HANDLER(EX_WireTracepoint)
	return false;
}
INSTRUCTION(EX_WireTracepoint)

INSTRUCTION_HANDLER(EX_SkipOffsetConst)
	Result->SetNumberField("Value", Stack.ReadCodeSkipCount());
	return true;
}
INSTRUCTION(EX_SkipOffsetConst)

INSTRUCTION_HANDLER(EX_AddMulticastDelegate)
	Result->SetObjectField("Variable", Stack.Step(nullptr));
	Result->SetObjectField("Delegate", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_AddMulticastDelegate)

INSTRUCTION_HANDLER(EX_ClearMulticastDelegate)
	Result->SetObjectField("Variable", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_ClearMulticastDelegate)

INSTRUCTION_HANDLER(EX_Tracepoint)
	return false;
}
INSTRUCTION(EX_Tracepoint)

INSTRUCTION_HANDLER(EX_LetObj)
	Result->SetObjectField("EvaluateProp", Stack.Step(nullptr));
	Result->SetObjectField("EvaluateExp", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_LetObj)

INSTRUCTION_HANDLER(EX_LetWeakObjPtr)
	Result->SetObjectField("EvaluateProp", Stack.Step(nullptr));
	Result->SetObjectField("EvaluateExp", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_LetWeakObjPtr)

INSTRUCTION_HANDLER(EX_BindDelegate)
	Result->SetStringField("FunctionName", Stack.ReadName().ToString());
	Result->SetObjectField("Variable", Stack.Step(nullptr));
	Result->SetObjectField("Object", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_BindDelegate)

INSTRUCTION_HANDLER(EX_RemoveMulticastDelegate)
	Result->SetObjectField("Variable", Stack.Step(nullptr));
	Result->SetObjectField("Delegate", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_RemoveMulticastDelegate)

INSTRUCTION_HANDLER(EX_CallMulticastDelegate)
	UFunction* Signature = CastChecked<UFunction>(Stack.ReadObject());
	Result->SetStringField("Signature", Signature->GetFullName());
	Result->SetObjectField("Variable", Stack.Step(nullptr));
	ParseFunctionInstruction(Signature, Stack, Result, ReturnValue);
	return true;
}
INSTRUCTION(EX_CallMulticastDelegate)

INSTRUCTION_HANDLER(EX_LetValueOnPersistentFrame)
#if USE_UBER_GRAPH_PERSISTENT_FRAME
	UProperty* DestProperty = Stack.ReadProperty();
	Result->SetStringField("Dest", DestProperty->GetFullName());
	Result->SetObjectField("Value", Stack.Step(nullptr));
#endif
	return true;
}
INSTRUCTION(EX_LetValueOnPersistentFrame)

INSTRUCTION_HANDLER(EX_ArrayConst)
	UProperty* InnerProperty = CastChecked<UProperty>(Stack.ReadObject());
	Result->SetStringField("Type", InnerProperty->GetFullName());
	int32 Num = Stack.ReadInt<int32>();
	Result->SetNumberField("Num", Num);
	
	TArray<TSharedPtr<FJsonValue>> values;
	while (*Stack.Frame->Code != EX_EndArrayConst) {
		values.Add(MakeShareable(new FJsonValueObject(Stack.Step(nullptr))));
	}
	Result->SetArrayField("Values", values);

	Stack.Frame->Code += !!Stack.Frame->Code; // EX_EndArrayConst

	return true;
}
INSTRUCTION(EX_ArrayConst)

INSTRUCTION_HANDLER(EX_SoftObjectConst)
	Result->SetObjectField("Value", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_SoftObjectConst)

INSTRUCTION_HANDLER(EX_CallMath)
	UFunction* Function = (UFunction*)Stack.ReadObject();
	Result->SetStringField("Function", Function->GetFullName());
	ParseFunctionInstruction(Function, Stack, Result, ReturnValue);
	return true;
}
INSTRUCTION(EX_CallMath)

INSTRUCTION_HANDLER(EX_SwitchValue)
	const int32 NumCases = Stack.ReadWord();
	const CodeSkipSizeType OffsetToEnd = Stack.ReadCodeSkipCount();
	Result->SetNumberField("Offset", OffsetToEnd);
	Result->SetObjectField("Input", Stack.Step(nullptr));
	
	TArray<TSharedPtr<FJsonValue>> cases;
	for (int32 CaseIndex = 0; CaseIndex < NumCases; ++CaseIndex) {
		TSharedPtr<FJsonObject> CaseObject = MakeShareable(new FJsonObject());
		CaseObject->SetObjectField("Match", Stack.Step(nullptr));
		const CodeSkipSizeType OffsetToNextCase = Stack.ReadCodeSkipCount();
		CaseObject->SetObjectField("Result", Stack.Step(ReturnValue));
		CaseObject->SetNumberField("OffsetToNextCase", OffsetToNextCase);
		cases.Add(MakeShareable(new FJsonValueObject(CaseObject)));
	}
	Result->SetArrayField("Cases", cases);
	Result->SetObjectField("Default", Stack.Step(ReturnValue));
	Stack.Frame->Code = &Stack.Frame->Node->Script[OffsetToEnd];
	return true;
}
INSTRUCTION(EX_SwitchValue)

INSTRUCTION_HANDLER(EX_InstrumentationEvent)
#if !UE_BUILD_SHIPPING
	const EScriptInstrumentation::Type EventType = static_cast<EScriptInstrumentation::Type>(*Stack.Frame->Code);
	Result->SetNumberField(TEXT("InstrumentationType"), EventType);

	if (EventType == EScriptInstrumentation::InlineEvent) {
		const FName& EventName = *reinterpret_cast<FName*>(&Stack.Frame->Code[1]);
		Result->SetStringField(TEXT("EventName"), EventName.ToString());
		Stack.Frame->Code += sizeof(FName);
	}
	Stack.Frame->Code++;
#endif
	return true;
}
INSTRUCTION(EX_InstrumentationEvent)

INSTRUCTION_HANDLER(EX_ArrayGetByRef)
	Result->SetObjectField("Variable", Stack.Step(nullptr));
	Result->SetObjectField("Index", Stack.Step(nullptr));
	return true;
}
INSTRUCTION(EX_ArrayGetByRef)

PRIMITIVE_CAST_HANDLER(CST_ObjectToBool)
	Result->SetObjectField("Value", Stack.Step(nullptr));
	return true;
}
PRIMITIVE_CAST(CST_ObjectToBool);

PRIMITIVE_CAST_HANDLER(CST_InterfaceToBool)
	Result->SetObjectField("Value", Stack.Step(nullptr));
	return true;
}
PRIMITIVE_CAST(CST_InterfaceToBool);

PRIMITIVE_CAST_HANDLER(CST_ObjectToInterface)
	UClass* InterfaceClass = dynamic_cast<UClass*>(Stack.ReadObject());
	Result->SetStringField("Type", InterfaceClass->GetFullName());
	Result->SetObjectField("Value", Stack.Step(nullptr));
	return true;
}
PRIMITIVE_CAST(CST_ObjectToInterface);

TArray<TSharedPtr<FJsonValue>> FKismetByteCodeSerializer::CreateFunctionCode(UFunction* Function) {
	TArray<TSharedPtr<FJsonValue>> result;
	if (Function->Script.Num() > 0) {
		UObject* Context = Function->GetTypedOuter<UClass>()->GetDefaultObject();
		FParseFrame Frame = FParseFrame(Context, Function);
		const bool bHasReturnParam = Function->ReturnValueOffset != MAX_uint16;
		void* ReturnValue = bHasReturnParam ? ((uint8*)Frame.ParametersFrame + Function->ReturnValueOffset) : nullptr;
		result = ParseClosure(Frame, (uint8*)ReturnValue);
	}
	return result;
}

TArray<TSharedPtr<FJsonValue>> FKismetByteCodeSerializer::DumpByteCode(TArray<uint8>& Code, UFunction* Function) {
	TArray<TSharedPtr<FJsonValue>> result;
	if (Function->Script.Num() > 0) {
		UObject* Context = Function->GetTypedOuter<UClass>()->GetDefaultObject();
		FParseFrame Frame = FParseFrame(Context, Function);
		Frame.Frame->Code = Code.GetData();
		const bool bHasReturnParam = Function->ReturnValueOffset != MAX_uint16;
		void* ReturnValue = bHasReturnParam ? ((uint8*)Frame.ParametersFrame + Function->ReturnValueOffset) : nullptr;
		result = ParseClosure(Frame, (uint8*)ReturnValue);
	}
	return result;
}

int32 FKismetByteCodeSerializer::GetMinInstructionReplaceLength(UFunction* Function, uint32 BytesRequired, uint32 StartOffset) {
	if (Function->Script.Num() > 0) {
		UObject* Context = Function->GetTypedOuter<UClass>()->GetDefaultObject();
		FParseFrame Frame = FParseFrame(Context, Function);
		Frame.Frame->Code += StartOffset;
		const bool bHasReturnParam = Function->ReturnValueOffset != MAX_uint16;
		void* ReturnValue = bHasReturnParam ? ((uint8*)Frame.ParametersFrame + Function->ReturnValueOffset) : nullptr;
		const uint64 CodePointerBase = reinterpret_cast<uint64>(Frame.Frame->Code);
		
		while (*Frame.Frame->Code != EX_Return) {
			Frame.Step(ReturnValue);
			const uint64 CodePointer = reinterpret_cast<uint64>(Frame.Frame->Code);
			const uint64 Offset = CodePointer - CodePointerBase;
			if (Offset >= BytesRequired)
				return Offset;
		}
		//Not enough bytes before return to actually fit MinBytes before return
		//return after it will also have EX_Nothing or EX_LocalOutVariable and then EX_Nothing
		//so if we can't fit we should before we replace entire remaining part
		const uint32 BytesRemaining = Function->Script.Num() - StartOffset;
		if (BytesRemaining >= BytesRequired)
			return BytesRemaining; //return full bytes remaining, because after return we have 2 more instructions generated
		const int32 BytesLacking = BytesRequired - BytesRemaining;
		return -BytesLacking; //Otherwise return how much bytes we lack
	}
	return -((int32) BytesRequired);
}

int32 FKismetByteCodeSerializer::FindReturnStatementOffset(UFunction* Function) {
	if (Function->Script.Num() > 0) {
		UObject* Context = Function->GetTypedOuter<UClass>()->GetDefaultObject();
		FParseFrame Frame = FParseFrame(Context, Function);
		const bool bHasReturnParam = Function->ReturnValueOffset != MAX_uint16;
		void* ReturnValue = bHasReturnParam ? ((uint8*)Frame.ParametersFrame + Function->ReturnValueOffset) : nullptr;
		const uint64 CodePointerBase = (uint64)Frame.Frame->Code;
		while (*Frame.Frame->Code != EX_Return) {
			Frame.Step(ReturnValue);
		}
		//Will always point to EX_Return at that point, so just compute offset
		const uint64 CodePointer = (uint64)Frame.Frame->Code;
		return CodePointer - CodePointerBase;
	}
	return -1;
}



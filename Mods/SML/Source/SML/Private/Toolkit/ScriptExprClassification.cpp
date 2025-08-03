#include "Toolkit/ScriptExprClassification.h"
#include "UObject/Script.h"

bool FScriptExprClassification::IsSingleAssignmentOpcode(uint8 Opcode) {
	return Opcode == EX_Let || Opcode == EX_LetBool || Opcode == EX_LetDelegate || Opcode == EX_LetObj || Opcode == EX_LetMulticastDelegate || Opcode == EX_LetWeakObjPtr || Opcode == EX_LetValueOnPersistentFrame;
}

bool FScriptExprClassification::IsMultiAssignmentOpcode(uint8 Opcode) {
	return Opcode == EX_SetSet || Opcode == EX_SetMap || Opcode == EX_SetArray ||
		Opcode == EX_BindDelegate || Opcode == EX_AddMulticastDelegate || Opcode == EX_RemoveMulticastDelegate || Opcode == EX_ClearMulticastDelegate;
}

bool FScriptExprClassification::IsAssignmentOpcode(uint8 Opcode) {
	return IsSingleAssignmentOpcode(Opcode) || IsMultiAssignmentOpcode(Opcode);
}

bool FScriptExprClassification::IsControlFlowOpcode(uint8 Opcode) {
	return Opcode == EX_Jump || Opcode == EX_JumpIfNot || Opcode == EX_ComputedJump ||
		Opcode == EX_PushExecutionFlow || Opcode == EX_PopExecutionFlow || Opcode == EX_PopExecutionFlowIfNot ||
		Opcode == EX_AutoRtfmTransact || Opcode == EX_AutoRtfmStopTransact || Opcode == EX_AutoRtfmAbortIfNot ||
		Opcode == EX_Return || Opcode == EX_EndOfScript;
}

bool FScriptExprClassification::IsDebugOpcode(uint8 Opcode) {
	return Opcode == EX_Breakpoint || Opcode == EX_Tracepoint || Opcode == EX_WireTracepoint || Opcode == EX_InstrumentationEvent || Opcode == EX_Assert;
}

bool FScriptExprClassification::IsUnconditionalControlFlowStop(uint8 Opcode) {
	return Opcode == EX_Jump || Opcode == EX_ComputedJump || Opcode == EX_PopExecutionFlow || Opcode == EX_Return || Opcode == EX_EndOfScript;
}

bool FScriptExprClassification::IsFunctionCallOpcode(uint8 Opcode) {
	return Opcode == EX_FinalFunction || Opcode == EX_LocalFinalFunction || Opcode == EX_VirtualFunction || Opcode == EX_LocalVirtualFunction || Opcode == EX_CallMath || Opcode == EX_CallMulticastDelegate;
}

bool FScriptExprClassification::IsPureTransformationOpcode(uint8 Opcode) {
	return Opcode == EX_InterfaceContext || Opcode == EX_StructMemberContext || Opcode == EX_ArrayGetByRef || Opcode == EX_SwitchValue || Opcode == EX_CallMath || Opcode == EX_Self;
}

bool FScriptExprClassification::IsPropertyOpcode(uint8 Opcode) {
	return Opcode == EX_LocalVariable || Opcode == EX_LocalOutVariable || Opcode == EX_InstanceVariable || Opcode == EX_DefaultVariable || Opcode == EX_ClassSparseDataVariable;
}

bool FScriptExprClassification::IsCastOpcode(uint8 Opcode) {
	return Opcode == EX_Cast || Opcode == EX_DynamicCast || Opcode == EX_MetaCast || Opcode == EX_InterfaceToObjCast || Opcode == EX_CrossInterfaceCast || Opcode == EX_ObjToInterfaceCast;
}

bool FScriptExprClassification::IsContextOpcode(uint8 Opcode) {
	return Opcode == EX_Context || Opcode == EX_Context_FailSilent || Opcode == EX_ClassContext;
}

bool FScriptExprClassification::IsIntConstantOpcode(uint8 Opcode) {
	return Opcode == EX_ByteConst || Opcode == EX_IntConst || Opcode == EX_Int64Const || Opcode == EX_UInt64Const || Opcode == EX_IntConstByte || Opcode == EX_IntZero || Opcode == EX_IntOne;
}

bool FScriptExprClassification::IsNumericConstantOpcode(uint8 Opcode) {
	return IsIntConstantOpcode(Opcode) || Opcode == EX_FloatConst || Opcode == EX_DoubleConst;
}

bool FScriptExprClassification::IsSimpleConstantOpcode(uint8 Opcode) {
	return IsNumericConstantOpcode(Opcode) ||
		Opcode == EX_True || Opcode == EX_False || Opcode == EX_BitFieldConst ||
		Opcode == EX_RotationConst || Opcode == EX_VectorConst || Opcode == EX_Vector3fConst || Opcode == EX_TransformConst ||
		Opcode == EX_StringConst || Opcode == EX_UnicodeStringConst || Opcode == EX_NameConst ||
		Opcode == EX_PropertyConst || Opcode == EX_ObjectConst || Opcode == EX_NoInterface || Opcode == EX_NoObject ||
		Opcode == EX_InstanceDelegate ||
		// EX_Nothing can appear as a part of a struct literal, so it has to be a constant. By the same logic, nothing32 and 4A are also constants
		Opcode == EX_Nothing || Opcode == EX_NothingInt32 || Opcode == EX_DeprecatedOp4A;
}

bool FScriptExprClassification::IsComplexConstantOpcode(uint8 Opcode) {
	return Opcode == EX_StructConst || Opcode == EX_TextConst || Opcode == EX_SoftObjectConst || Opcode == EX_FieldPathConst || Opcode == EX_ArrayConst || Opcode == EX_SetConst || Opcode == EX_MapConst;
}

bool FScriptExprClassification::IsConstantOpcode(uint8 Opcode) {
	return IsSimpleConstantOpcode(Opcode) || IsComplexConstantOpcode(Opcode);
}

bool FScriptExprClassification::IsStructConstantOpcode(uint8 Opcode) {
	return Opcode == EX_StructConst || Opcode == EX_TextConst || Opcode == EX_RotationConst || Opcode == EX_VectorConst || Opcode == EX_Vector3fConst || Opcode == EX_TransformConst;
}

bool FScriptExprClassification::IsPureOpcode(uint8 Opcode) {
	return IsConstantOpcode(Opcode) || IsPureTransformationOpcode(Opcode) || IsCastOpcode(Opcode) || IsContextOpcode(Opcode) || IsPropertyOpcode(Opcode);
}

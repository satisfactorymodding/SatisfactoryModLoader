#include "Toolkit/ScriptExprTypeResolver.h"
#include "Toolkit/ScriptExprAssembler.h"
#include "Toolkit/ScriptExprHelper.h"
#include "UObject/Class.h"
#include "UObject/EnumProperty.h"
#include "UObject/Interface.h"
#include "UObject/PropertyOptional.h"
#include "UObject/Script.h"
#include "UObject/UnrealType.h"

bool operator==(const FScriptExprTypeOperand& A, const FScriptExprTypeOperand& B) {
	return A.Type == B.Type && A.Object == B.Object &&
		A.ExprType.IsValid() == B.ExprType.IsValid() &&
		(!A.ExprType.IsValid() || A.ExprType->Identical(B.ExprType));
}

void FScriptExprTypeOperand::PrintExpressionTypeOperand(FStringBuilderBase& StringBuilder) const {
	switch (Type) {
		case TypeNull: StringBuilder.Append(TEXT("<Invalid Type Operand>")); break;
		case TypeObject: StringBuilder.Append(TEXT("Object(\"")).Append(GetPathNameSafe(Object)).Append(TEXT("\")")); break;
		case TypeExprType: if (ExprType) { ExprType->PrintExpressionType(StringBuilder); } else { StringBuilder.Append(TEXT("<Invalid Expr Type Operand>")); }; break;
		default: StringBuilder.Append(TEXT("<Unknown Type Operand>")); break;
	}
}

bool FScriptExprType::IsA(const FFieldClass* InPropertyClass) const {
	return InPropertyClass && PropertyType && PropertyType->IsChildOf(InPropertyClass);
}

const FScriptExprTypeOperand& FScriptExprType::RequireOperand(int32 InOperandIndex, FScriptExprTypeOperand::EScriptExprTypeOperand InOperandType, const FFieldClass* InPropertyClass) const {
	// Check that the type matches the provided property (if one was provided), and check that the operand is actually valid
	if (InPropertyClass == nullptr || IsA(InPropertyClass)) {
		if (Operands.IsValidIndex(InOperandIndex) && Operands[InOperandIndex].Type == InOperandType) {
			return Operands[InOperandIndex];
		}
	}
	// Return a dummy null operand otherwise
	static const FScriptExprTypeOperand StaticNullOperand;
	return StaticNullOperand;
}

UFunction* FScriptExprType::FindFunctionInObjectPropertyClass(const FName& FunctionName) const {
	// Check property class for the object property
	if (const UClass* PropertyClass = Cast<UClass>(RequireOperand<FObjectProperty>(0, FScriptExprTypeOperand::TypeObject).Object)) {
		if (UFunction* ClassFunction = PropertyClass->FindFunctionByName(FunctionName)) {
			return ClassFunction;
		}
	}
	// We might also have an interface class this object conforms to, so check
	if (const UClass* InterfaceClass = Cast<UClass>(RequireOperand<FObjectProperty>(1, FScriptExprTypeOperand::TypeObject).Object)) {
		if (UFunction* InterfaceFunction = InterfaceClass->FindFunctionByName(FunctionName)) {
			return InterfaceFunction;
		}
	}
	// We did not find a function in the object class or in the interface class
	return nullptr;
}

bool FScriptExprType::Identical(const TSharedPtr<FScriptExprType>& Other) const {
	return Other && PropertyType == Other->PropertyType && Operands == Other->Operands;
}

void FScriptExprType::PrintExpressionType(FStringBuilderBase& StringBuilder) const {
	StringBuilder.Append(PropertyType ? PropertyType->GetName() : TEXT("Null"));
	if (PropertyType && !Operands.IsEmpty()) {
		StringBuilder.AppendChar(TEXT('('));
		for (int32 OperandIndex = 0; OperandIndex < Operands.Num(); OperandIndex++) {
			if (OperandIndex != 0) {
				StringBuilder.Append(TEXT(", "));
			}
			Operands[OperandIndex].PrintExpressionTypeOperand(StringBuilder);
		}
		StringBuilder.AppendChar(TEXT(')'));
	}
}

FString FScriptExprType::ToString() const {
	TStringBuilder<256> StringBuilder;
	PrintExpressionType(StringBuilder);
	return StringBuilder.ToString();
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateObjectProperty(UClass* PropertyClass, UClass* ImplementedInterface) {
	const TSharedPtr<FScriptExprType> ObjectProperty = CreateProperty<FObjectProperty>();
	ObjectProperty->Operands.Add(PropertyClass ? PropertyClass : UObject::StaticClass());
	ObjectProperty->Operands.Add(ImplementedInterface);
	return ObjectProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateInterfaceProperty(UClass* InterfaceClass) {
	const TSharedPtr<FScriptExprType> InterfaceProperty = CreateProperty<FInterfaceProperty>();
	InterfaceProperty->Operands.Add(InterfaceClass ? InterfaceClass : UInterface::StaticClass());
	return InterfaceProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateClassProperty(UClass* MetaClass, UClass* PropertyClass) {
	const TSharedPtr<FScriptExprType> ClassProperty = CreateProperty<FClassProperty>();
	ClassProperty->Operands.Add(PropertyClass ? PropertyClass : (MetaClass ? MetaClass->GetClass() : UClass::StaticClass()));
	ClassProperty->Operands.Add(FScriptExprTypeOperand()); // class properties do not have attached implemented interface
	ClassProperty->Operands.Add(MetaClass ? MetaClass : UObject::StaticClass());
	return ClassProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateStructProperty(UScriptStruct* ScriptStruct) {
	const TSharedPtr<FScriptExprType> StructProperty = CreateProperty<FStructProperty>();
	StructProperty->Operands.Add(ScriptStruct);
	return StructProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateDelegateProperty(UFunction* DelegateSignatureFunction) {
	const TSharedPtr<FScriptExprType> DelegateProperty = CreateProperty<FDelegateProperty>();
	DelegateProperty->Operands.Add(DelegateSignatureFunction);
	return DelegateProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateMulticastDelegateProperty(FFieldClass* DelegatePropertyClass, UFunction* DelegateSignatureFunction) {
	const TSharedPtr<FScriptExprType> MulticastDelegateProperty = CreateProperty(DelegatePropertyClass);
	MulticastDelegateProperty->Operands.Add(DelegateSignatureFunction);
	return MulticastDelegateProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateArrayProperty(const TSharedPtr<FScriptExprType>& ElementProperty) {
	const TSharedPtr<FScriptExprType> ArrayProperty = CreateProperty<FArrayProperty>();
	ArrayProperty->Operands.Add(ElementProperty);
	return ArrayProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateSetProperty(const TSharedPtr<FScriptExprType>& ElementProperty) {
	const TSharedPtr<FScriptExprType> SetProperty = CreateProperty<FSetProperty>();
	SetProperty->Operands.Add(ElementProperty);
	return SetProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateMapProperty(const TSharedPtr<FScriptExprType>& KeyProperty, const TSharedPtr<FScriptExprType>& ValueProperty) {
	const TSharedPtr<FScriptExprType> MapProperty = CreateProperty<FMapProperty>();
	MapProperty->Operands.Add(KeyProperty);
	MapProperty->Operands.Add(ValueProperty);
	return MapProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateOptionalProperty(const TSharedPtr<FScriptExprType>& ValueProperty) {
	const TSharedPtr<FScriptExprType> OptionalProperty = CreateProperty<FOptionalProperty>();
	OptionalProperty->Operands.Add(ValueProperty);
	return OptionalProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateByteProperty(UEnum* InEnum) {
	const TSharedPtr<FScriptExprType> ByteProperty = CreateProperty<FByteProperty>();
	ByteProperty->Operands.Add(InEnum);
	return ByteProperty;
}

TSharedPtr<FScriptExprType> FScriptExprType::CreateEnumProperty(UEnum* InEnum, const TSharedPtr<FScriptExprType>& UnderlyingProp) {
	const TSharedPtr<FScriptExprType> EnumProperty = CreateProperty<FEnumProperty>();
	EnumProperty->Operands.Add(InEnum);
	EnumProperty->Operands.Add(UnderlyingProp);
	return EnumProperty;
}

TSharedPtr<FScriptExprType> FScriptExprTypeResolver::ResolveExpressionType(const TSharedPtr<FScriptExpr>& Expr, UClass* OwnerFunctionOuterClass) {
	// If we have no outer context switch expression, this expression runs in the context of the function class
	const TSharedPtr<FScriptExpr> OuterContextSwitchExpression = FScriptExprHelper::GetOuterContextSwitchExpression(Expr);
	if (OuterContextSwitchExpression == nullptr) {
		return ResolveExpressionTypeWithExplicitContext(Expr, FScriptExprType::CreateObjectProperty(OwnerFunctionOuterClass));
	}

	// Evaluate the context of the context switch expression and then evaluate the evaluated expression with that context
	const TSharedPtr<FScriptExpr> ContextExpression = OuterContextSwitchExpression->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;

	const TSharedPtr<FScriptExprType> ContextExpressionType = ResolveExpressionType(ContextExpression, OwnerFunctionOuterClass);
	return ResolveExpressionTypeWithExplicitContext(Expr, ContextExpressionType);
}

TSharedPtr<FScriptExprType> FScriptExprTypeResolver::ResolveExpressionTypeWithExplicitContext(const TSharedPtr<FScriptExpr>& Expr, const TSharedPtr<FScriptExprType>& ContextType) {
	// Switch based on the expression type
	switch (Expr ? Expr->Opcode : EX_Nothing) {
		case EX_Cast: {
			const uint8 CastType = Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer;
			switch(CastType) {
				case CST_InterfaceToBool:
				case CST_ObjectToBool: return FScriptExprType::CreateProperty<FBoolProperty>();
				case CST_DoubleToFloat: return FScriptExprType::CreateProperty<FFloatProperty>();
				case CST_FloatToDouble: return FScriptExprType::CreateProperty<FDoubleProperty>();
				default: return FScriptExprType::CreateNothing();
			}
		}
		case EX_SetConst: {
			const FProperty* SetElementProperty = Expr->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
			return FScriptExprType::CreateSetProperty(ResolvePropertyType(SetElementProperty));
		}
		case EX_MapConst: {
			const FProperty* KeyType = Expr->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
			const FProperty* ValueType = Expr->RequireOperand(1, FScriptExprOperand::TypeProperty).Property;
			return FScriptExprType::CreateMapProperty(ResolvePropertyType(KeyType), ResolvePropertyType(ValueType));
		}
		case EX_ArrayConst: {
			const FProperty* ArrayInnerProperty = Expr->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
			return FScriptExprType::CreateArrayProperty(ResolvePropertyType(ArrayInnerProperty));
		}
		case EX_ObjToInterfaceCast:
		case EX_CrossInterfaceCast: {
			UClass* InterfaceClass = Cast<UClass>(Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			return FScriptExprType::CreateInterfaceProperty(InterfaceClass);
		}
		case EX_InterfaceToObjCast: {
			UClass* ObjectClass = Cast<UClass>(Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			return FScriptExprType::CreateObjectProperty(ObjectClass);
		}
		case EX_MetaCast: {
			UClass* MetaClass = Cast<UClass>(Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			return FScriptExprType::CreateClassProperty(MetaClass);
		}
		case EX_DynamicCast: {
			UClass* ObjectClassOrInterfaceClass = Cast<UClass>(Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			const TSharedPtr<FScriptExpr>& CastedExpression = Expr->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;

			// If this is not an interface conformation cast, return the cast class type
			if (ObjectClassOrInterfaceClass && !ObjectClassOrInterfaceClass->HasAnyClassFlags(CLASS_Interface)) {
				return FScriptExprType::CreateObjectProperty(ObjectClassOrInterfaceClass);
			}

			// If this is an interface conformation cast, take property type from parent property, but mark this interface as implemented
			const TSharedPtr<FScriptExprType> CastedExpressionType = ResolveExpressionTypeWithExplicitContext(CastedExpression, ContextType);
			UClass* CastedPropertyClass = Cast<UClass>(CastedExpressionType->RequireOperand<FObjectProperty>(0, FScriptExprTypeOperand::TypeObject).Object);
			return FScriptExprType::CreateObjectProperty(CastedPropertyClass ? CastedPropertyClass : UObject::StaticClass(), ObjectClassOrInterfaceClass);
		}
		case EX_ArrayGetByRef: {
			const TSharedPtr<FScriptExpr>& TargetArrayExpression = Expr->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
			const TSharedPtr<FScriptExprType> TargetArrayType = ResolveExpressionTypeWithExplicitContext(TargetArrayExpression, ContextType);

			const TSharedPtr<FScriptExprType> ArrayInnerProperty = TargetArrayType->RequireOperand<FArrayProperty>(0, FScriptExprTypeOperand::TypeExprType).ExprType;
			return ArrayInnerProperty ? ArrayInnerProperty : FScriptExprType::CreateNothing();
		}
		case EX_StructMemberContext: {
			const FProperty* MemberPropertyType = Expr->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
			return ResolvePropertyType(MemberPropertyType);
		}
		case EX_InterfaceContext: { return FScriptExprType::CreateObjectProperty(UObject::StaticClass()); }
		case EX_LocalVirtualFunction:
		case EX_VirtualFunction: {
			const FName VirtualFunctionName = ScriptNameToName(Expr->RequireOperand(0, FScriptExprOperand::TypeScriptName).ScriptName);
			const UFunction* CallTargetFunction = ContextType ? ContextType->FindFunctionInObjectPropertyClass(VirtualFunctionName) : nullptr;
			const FProperty* ReturnProperty = CallTargetFunction ? CallTargetFunction->GetReturnProperty() : nullptr;
			return ReturnProperty ? ResolvePropertyType(ReturnProperty) : FScriptExprType::CreateNothing();
		}
		case EX_LocalFinalFunction:
		case EX_FinalFunction:
		case EX_CallMath: {
			const UFunction* TargetFunction = Cast<UFunction>(Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			const FProperty* ReturnProperty = TargetFunction ? TargetFunction->GetReturnProperty() : nullptr;
			return ReturnProperty ? ResolvePropertyType(ReturnProperty) : FScriptExprType::CreateNothing();
		}
		case EX_LocalVariable:
		case EX_DefaultVariable:
		case EX_InstanceVariable:
		case EX_LocalOutVariable:
		case EX_ClassSparseDataVariable: {
			const FProperty* PropertyAccessed = Expr->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
			return PropertyAccessed ? ResolvePropertyType(PropertyAccessed) : FScriptExprType::CreateNothing();
		}
		case EX_ClassContext: {
			const TSharedPtr<FScriptExpr>& NewContextExpression = Expr->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
			const TSharedPtr<FScriptExpr>& EvaluatedExpression = Expr->RequireOperand(3, FScriptExprOperand::TypeExpr).Expr;
			const TSharedPtr<FScriptExprType> NewContextExpressionType = ResolveExpressionTypeWithExplicitContext(NewContextExpression, ContextType);
			
			UClass* NewContextMetaClass = Cast<UClass>(NewContextExpressionType->RequireOperand<FClassProperty>(2, FScriptExprTypeOperand::TypeObject).Object);
			return ResolveExpressionTypeWithExplicitContext(EvaluatedExpression, FScriptExprType::CreateObjectProperty(
				NewContextMetaClass ? NewContextMetaClass : UObject::StaticClass()));
		}
		case EX_Context:
		case EX_Context_FailSilent: {
			const TSharedPtr<FScriptExpr>& NewContextExpression = Expr->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
			const TSharedPtr<FScriptExpr>& EvaluatedExpression = Expr->RequireOperand(3, FScriptExprOperand::TypeExpr).Expr;
			return ResolveExpressionTypeWithExplicitContext(EvaluatedExpression, ResolveExpressionTypeWithExplicitContext(NewContextExpression, ContextType));
		}
		case EX_InstanceDelegate: {
			const FName DelegateFunctionName = ScriptNameToName(Expr->RequireOperand(0, FScriptExprOperand::TypeScriptName).ScriptName);
			UFunction* DelegateSignatureFunction = ContextType ? ContextType->FindFunctionInObjectPropertyClass(DelegateFunctionName) : nullptr;
			return DelegateSignatureFunction ? FScriptExprType::CreateDelegateProperty(DelegateSignatureFunction) : FScriptExprType::CreateNothing();
		}
		case EX_ObjectConst: {
			UObject* ObjectConstant = Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object;
			UClass* ClassConstant = Cast<UClass>(ObjectConstant);
			return ClassConstant ? FScriptExprType::CreateClassProperty(ClassConstant) : FScriptExprType::CreateObjectProperty(ObjectConstant ? ObjectConstant->GetClass() : UObject::StaticClass());
		}
		case EX_Self: {
			return ContextType ? ContextType : FScriptExprType::CreateNothing();
		}
		case EX_IntConst:
		case EX_SkipOffsetConst:
		case EX_IntConstByte:
		case EX_IntZero:
		case EX_IntOne: { return FScriptExprType::CreateProperty<FIntProperty>(); }
		case EX_Int64Const: { return FScriptExprType::CreateProperty<FInt64Property>(); }
		case EX_UInt64Const: { return FScriptExprType::CreateProperty<FUInt64Property>(); }
		case EX_FloatConst: { return FScriptExprType::CreateProperty<FFloatProperty>(); }
		case EX_DoubleConst: { return FScriptExprType::CreateProperty<FDoubleProperty>(); }
		case EX_StringConst:
		case EX_UnicodeStringConst: { return FScriptExprType::CreateProperty<FStrProperty>(); }
		case EX_ByteConst: { return FScriptExprType::CreateProperty<FByteProperty>(); }
		case EX_TextConst: { return FScriptExprType::CreateProperty<FTextProperty>(); }
		case EX_NameConst: { return FScriptExprType::CreateProperty<FNameProperty>(); }
		case EX_SoftObjectConst: { return FScriptExprType::CreateProperty<FSoftObjectProperty>(); }
		case EX_FieldPathConst: { return FScriptExprType::CreateProperty<FFieldPathProperty>(); }
		case EX_RotationConst: { return FScriptExprType::CreateStructProperty(TBaseStructure<FRotator>::Get()); }
		case EX_VectorConst: { return FScriptExprType::CreateStructProperty(TBaseStructure<FVector>::Get()); }
		case EX_Vector3fConst: { return FScriptExprType::CreateStructProperty(TVariantStructure<FVector3f>::Get()); }
		case EX_TransformConst: { return FScriptExprType::CreateStructProperty(TBaseStructure<FTransform>::Get()); }
		case EX_False:
		case EX_True:
		case EX_BitFieldConst: { return FScriptExprType::CreateProperty<FBoolProperty>(); }
		case EX_StructConst: {
			UScriptStruct* ScriptStruct = Cast<UScriptStruct>(Expr->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			return FScriptExprType::CreateStructProperty(ScriptStruct);
		}
		case EX_NoObject: { return FScriptExprType::CreateObjectProperty(UObject::StaticClass()); }
		case EX_NoInterface: { return FScriptExprType::CreateInterfaceProperty(UInterface::StaticClass()); }
		case EX_SwitchValue: {
			const uint16 NumCases = Expr->RequireOperand(0, FScriptExprOperand::TypeInteger).Integer;
			const TSharedPtr<FScriptExpr>& DefaultCaseValue = Expr->RequireOperand(2 + NumCases * 2, FScriptExprOperand::TypeExpr).Expr;
			return ResolveExpressionTypeWithExplicitContext(DefaultCaseValue, ContextType);
		}
		default: { return FScriptExprType::CreateNothing(); }
	}
}

TSharedPtr<FScriptExprType> FScriptExprTypeResolver::ResolvePropertyType(const FProperty* Property) {
	if (const FClassProperty* ClassProperty = CastField<FClassProperty>(Property)) {
		return FScriptExprType::CreateClassProperty(ClassProperty->MetaClass, ClassProperty->PropertyClass);
	}
	if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property)) {
		return FScriptExprType::CreateObjectProperty(ObjectProperty->PropertyClass);
	}
	if (const FInterfaceProperty* InterfaceProperty = CastField<FInterfaceProperty>(Property)) {
		return FScriptExprType::CreateInterfaceProperty(InterfaceProperty->InterfaceClass);
	}
	if (const FStructProperty* StructProperty = CastField<FStructProperty>(Property)) {
		return FScriptExprType::CreateStructProperty(StructProperty->Struct);
	}
	if (const FDelegateProperty* DelegateProperty = CastField<FDelegateProperty>(Property)) {
		return FScriptExprType::CreateDelegateProperty(DelegateProperty->SignatureFunction);
	}
	if (const FMulticastDelegateProperty* MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(Property)) {
		return FScriptExprType::CreateMulticastDelegateProperty(MulticastDelegateProperty->GetClass(), MulticastDelegateProperty->SignatureFunction);
	}
	if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property)) {
		return FScriptExprType::CreateArrayProperty(ResolvePropertyType(ArrayProperty->Inner));
	}
	if (const FSetProperty* SetProperty = CastField<FSetProperty>(Property)) {
		return FScriptExprType::CreateSetProperty(ResolvePropertyType(SetProperty->ElementProp));
	}
	if (const FMapProperty* MapProperty = CastField<FMapProperty>(Property)) {
		return FScriptExprType::CreateMapProperty(ResolvePropertyType(MapProperty->KeyProp), ResolvePropertyType(MapProperty->ValueProp));
	}
	if (const FOptionalProperty* OptionalProperty = CastField<FOptionalProperty>(Property)) {
		return FScriptExprType::CreateOptionalProperty(ResolvePropertyType(OptionalProperty->GetValueProperty()));
	}
	if (const FByteProperty* ByteProperty = CastField<FByteProperty>(Property)) {
		return FScriptExprType::CreateByteProperty(ByteProperty->Enum);
	}
	if (const FEnumProperty* EnumProperty = CastField<FEnumProperty>(Property)) {
		return FScriptExprType::CreateEnumProperty(EnumProperty->GetEnum(), ResolvePropertyType(EnumProperty->GetUnderlyingProperty()));
	}
	return FScriptExprType::CreateProperty(Property->GetClass());
}

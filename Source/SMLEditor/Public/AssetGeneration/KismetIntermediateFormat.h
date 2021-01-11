#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphPin.h"

/** Basically mimics EKismetCompiledStatementType in KismetCompiler module */
enum ECompiledStatementType {
	KCST_Nop,
	// [wiring =] TargetObject->FunctionToCall(wiring)
	KCST_CallFunction,
	// TargetObject->TargetProperty = [wiring]
	KCST_Assignment,
	// goto TargetLabel
	KCST_UnconditionalGoto,
	// FlowStack.Push(TargetLabel)
	KCST_PushState,
	// [if (!TargetObject->TargetProperty)] goto TargetLabel
	KCST_GotoIfNot,
	// return TargetObject->TargetProperty
	KCST_Return,
	// if (FlowStack.Num()) { NextState = FlowStack.Pop; } else { return; }
	KCST_EndOfThread,
	// NextState = LHS;
	KCST_ComputedGoto,
	// [if (!TargetObject->TargetProperty)] { same as KCST_EndOfThread; }
	KCST_EndOfThreadIfNot,
	// TargetInterface(TargetObject)
	KCST_CastObjToInterface,
	// Cast<TargetClass>(TargetObject)
	KCST_DynamicCast,
	// (TargetObject != None)
	KCST_ObjectToBool,
	// TargetDelegate->Add(EventDelegate)
	KCST_AddMulticastDelegate,
	// TargetDelegate->Clear()
	KCST_ClearMulticastDelegate,
	// Creates simple delegate
	KCST_BindDelegate,
	// TargetDelegate->Remove(EventDelegate)
	KCST_RemoveMulticastDelegate,
	// TargetDelegate->Broadcast(...)
	KCST_CallDelegate,
	// Creates and sets an array literal term
	KCST_CreateArray,
	// TargetInterface(Interface)
	KCST_CrossInterfaceCast,
	// Cast<TargetClass>(TargetObject)
	KCST_MetaCast,
	KCST_AssignmentOnPersistentFrame,
	// Cast<TargetClass>(TargetInterface)
	KCST_CastInterfaceToObj,
	// goto ReturnLabel
	KCST_GotoReturn,
	// [if (!TargetObject->TargetProperty)] goto TargetLabel
	KCST_GotoReturnIfNot,
	KCST_SwitchValue,
	KCST_ArrayGetByRef,
	KCST_CreateSet,
	KCST_CreateMap,
};

struct FKismetCompiledStatement {
	
	FORCEINLINE FKismetCompiledStatement()
        : Type(KCST_Nop)
        , FunctionContext(NULL)
        , FunctionToCall(NULL)
        , TargetLabel(NULL)
        , UbergraphCallIndex(-1)
        , LHS(NULL)
        , bIsInterfaceContext(false)
        , bIsParentContext(false)
	{}

	ECompiledStatementType Type;

	// Object that the function should be called on, or NULL to indicate self (KCST_CallFunction)
	TSharedPtr<struct FKismetTerminal> FunctionContext;

	// Function that executes the statement (KCST_CallFunction)
	UFunction* FunctionToCall;

	// Target label (KCST_Goto, or KCST_CallFunction that requires an ubergraph reference)
	TSharedPtr<FKismetCompiledStatement> TargetLabel;

	// The index of the argument to replace (only used when KCST_CallFunction has a non-NULL TargetLabel)
	int32 UbergraphCallIndex;

	// Destination of assignment statement or result from function call
	TSharedPtr<struct FKismetTerminal> LHS;

	// Argument list of function call or source of assignment statement
	TArray<TSharedPtr<struct FKismetTerminal>> RHS;

	// Is this node an interface context? (KCST_CallFunction)
	bool bIsInterfaceContext;

	// Is this function called on a parent class (super, etc)?  (KCST_CallFunction)
	bool bIsParentContext;
};

/** A terminal in the graph (literal or variable reference) */
struct FKismetTerminal {

	FEdGraphPinType Type;
	bool bIsLiteral; 
	
	// Context->
	TSharedPtr<FKismetTerminal> Context;

	/** Literal value represented as the string */
	FString StringLiteral;

	// For non-literal terms, this is the UProperty being referenced (in the stack if bIsLocal set, or on the context otherwise)
	//TODO not UProperty because local properties are not reconstructed as UProperty objects, but rather as simple FEdGraphPinTypes
	FString AssociatedVarProperty;

	/** Pointer to an object literal */
	UObject* ObjectLiteral;

	/** The FText literal */
	FText TextLiteral;

	/**
	 * Reference to the statement passed inline as the function parameter
	 * Basically it allows statement execution in the context where only expressions are allowed
	 * Currently it is only utilised by GetArrayItem, Select and MathExpression nodes,
	 * neither of which are really usable as statements, because they just return values and don't perform any actions themselves
	 */
	TSharedPtr<FKismetCompiledStatement> InlineGeneratedParameter;

	FORCEINLINE FKismetTerminal()
		: bIsLiteral(false)
		, Context(nullptr)
		, AssociatedVarProperty(TEXT(""))
		, ObjectLiteral(nullptr)
		, VarType(EVarType_Instanced)
		, ContextType(EContextType_Object)
	{}

	enum EVarType {
		EVarType_Local,
        EVarType_Default,
        EVarType_Instanced
    };

	// For non-literal terms, this is set to the type of variable reference
	EVarType VarType;

	// Context types (mutually-exclusive)
	enum EContextType {
		EContextType_Class,
        EContextType_Struct,
        EContextType_Object,
    };

	// Variable reference types (mutually-exclusive)
	// If this term is also a context, this indicates which type of context it is
	EContextType ContextType;
};
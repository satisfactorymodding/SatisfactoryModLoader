#include "AssetGeneration/KismetBytecodeTransformer.h"

#include "BPTerminal.h"
#include "Engine/LatentActionManager.h"

FKismetBytecodeTransformer::FKismetBytecodeTransformer() {
}

void FKismetBytecodeTransformer::SetSourceStatements(const TArray<TSharedPtr<FJsonObject>>& Statements) {
    
}

void FKismetBytecodeTransformer::FinishGeneration() {
    //Apply patch-ups to jump statements
    for (const TPair<TSharedPtr<FKismetCompiledStatement>, int32>& Pair : JumpPatchUpTable) {
        const TSharedPtr<FKismetCompiledStatement> JumpStatement = Pair.Key;
        const TSharedPtr<FKismetCompiledStatement> JumpTarget = StatementsByOffset.FindChecked(Pair.Value);
        JumpStatement->TargetLabel = JumpTarget;

        //Replace jump statement type if we are jumping to the return statement
        if (JumpTarget->Type == EKismetCompiledStatementType::KCST_Return) {
            //Replace KCST_UnconditionalGoto with KCST_GotoReturn
            if (JumpStatement->Type == EKismetCompiledStatementType::KCST_UnconditionalGoto) {
                JumpStatement->Type = EKismetCompiledStatementType::KCST_GotoReturn;
            }
            //Replace KCST_GotoIfNot with KCST_GotoReturnIfNot
            if (JumpStatement->Type == EKismetCompiledStatementType::KCST_GotoIfNot) {
                JumpStatement->Type = EKismetCompiledStatementType::KCST_GotoReturnIfNot;
            }
        }
    }
}

//Warning! EX_InterfaceContext is NOT actually a context expression
//It's behavior is mostly similar to EX_InterfaceToObjCast, except that it doesn't check for interface type,
//It just retrieves UObject* pointer from FScriptInterface object
bool FKismetBytecodeTransformer::IsContextExpression(const FString& InstructionName) {
    return InstructionName == TEXT("Context") ||
        InstructionName == TEXT("Context_FailSilent") ||
        InstructionName == TEXT("ClassContext");
}

bool FKismetBytecodeTransformer::IsCallFunctionInstruction(const FString& InstructionName) {
    return InstructionName == TEXT("CallMath") ||
        InstructionName == TEXT("LocalFinalFunction") ||
        InstructionName == TEXT("FinalFunction") ||
        InstructionName == TEXT("LocalVirtualFunction") ||
        InstructionName == TEXT("VirtualFunction");
}

bool FKismetBytecodeTransformer::IsCallFunctionInstruction(TSharedPtr<FJsonObject> Expression) {
    const FString InstructionName = Expression->GetStringField(TEXT("Inst"));

    if (IsContextExpression(InstructionName)) {
        const TSharedPtr<FJsonObject> ExpressionInner = Expression->GetObjectField(TEXT("Expression"));
        return IsCallFunctionInstruction(ExpressionInner);
    }

    IsCallFunctionInstruction(InstructionName);
}

TSharedPtr<FKismetCompiledStatement> FKismetBytecodeTransformer::ProcessStatement(TSharedPtr<FJsonObject> Statement) {
    const int32 StatementIndex = Statement->GetIntegerField(TEXT("StatementIndex"));
    const FString InstructionName = Statement->GetStringField(TEXT("Inst"));

    if (InstructionName == TEXT("Nothing")) {
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_Nop;
        return Result;
    }
    
    if (InstructionName == TEXT("SetSet")) {
        TArray<TSharedPtr<FJsonValue>> Values = Statement->GetArrayField(TEXT("Values"));
        const TSharedPtr<FJsonObject> LeftSideExpression = Statement->GetObjectField(TEXT("LeftSideExpression"));

        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_CreateSet;
        Result->LHS = ProcessExpression(LeftSideExpression);

        for (const TSharedPtr<FJsonValue>& Value : Values) {
            Result->RHS.Add(ProcessExpression(Value->AsObject()));
        }
        return Result;
    }

    if (InstructionName == TEXT("SetArray")) {
        TArray<TSharedPtr<FJsonValue>> Values = Statement->GetArrayField(TEXT("Values"));
        const TSharedPtr<FJsonObject> LeftSideExpression = Statement->GetObjectField(TEXT("LeftSideExpression"));

        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_CreateArray;
        Result->LHS = ProcessExpression(LeftSideExpression);

        for (const TSharedPtr<FJsonValue>& Value : Values) {
            Result->RHS.Add(ProcessExpression(Value->AsObject()));
        }
        return Result;
    }

    if (InstructionName == TEXT("SetMap")) {
        TArray<TSharedPtr<FJsonValue>> Values = Statement->GetArrayField(TEXT("Values"));
        const TSharedPtr<FJsonObject> LeftSideExpression = Statement->GetObjectField(TEXT("LeftSideExpression"));

        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_CreateMap;
        Result->LHS = ProcessExpression(LeftSideExpression);

        //Maps are represented by (key, value) terms being followed by each other
        for (const TSharedPtr<FJsonValue>& Value : Values) {
            const TSharedPtr<FJsonObject> PairObject = Value->AsObject();
            Result->RHS.Add(ProcessExpression(PairObject->GetObjectField(TEXT("Key"))));
            Result->RHS.Add(ProcessExpression(PairObject->GetObjectField(TEXT("Value"))));
        }
        return Result;
    }

    //All of the assignment instructions are similar, it's just that they are type-specific for runtime to have easier time handling them
    if (InstructionName == TEXT("Let") || InstructionName == TEXT("LetObj") ||
        InstructionName == TEXT("LetWeakObjPtr") || InstructionName == TEXT("LetBool") ||
        InstructionName == TEXT("LetMulticastDelegate") || InstructionName == TEXT("LetDelegate")) {

        const TSharedPtr<FJsonObject> Variable = Statement->GetObjectField(TEXT("Variable"));
        const TSharedPtr<FJsonObject> Expression = Statement->GetObjectField(TEXT("Expression"));
        
        //Function calls cannot be expressions in compiled statement representation, so we need to handle case of RHS being CallFunction here
        if (IsCallFunctionInstruction(Expression)) {
            TSharedPtr<FKismetCompiledStatement> FunctionCall = ProcessFunctionCallStatement(Expression);
            
            //Set LHS so that function call result will be saved into the variable
            FunctionCall->LHS = ProcessExpression(Variable);
            return FunctionCall;
        }

        
        
        //Otherwise it is a normal assignment operation, so right side should be a simple expression
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_Assignment;
        Result->LHS = ProcessExpression(Variable);
        Result->RHS.Add(ProcessExpression(Expression));
        return Result;
    }

    if (InstructionName == TEXT("LetValueOnPersistentFrame")) {
        //It is variable assignment on a persistent frame, just like a normal assignment, but dest property is a bit special
        const TSharedPtr<FJsonObject> Expression = Statement->GetObjectField(TEXT("Expression"));
        
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_AssignmentOnPersistentFrame;
        Result->LHS = MakeShareable(new FKismetTerminal());
        Result->LHS->AssociatedVarProperty = Statement->GetStringField(TEXT("PropertyName"));
        Result->RHS.Add(ProcessExpression(Expression));
        return Result;
    }

    if (IsCallFunctionInstruction(Statement)) {
        //This is a function call statement, possibly prefixed with context expressions
        //Just call process function call, it will handle the case when actual statement passed
        //is a context and not the function call node itself gracefully
        return ProcessFunctionCallStatement(Statement);
    }

    //This is a computed jump statement, offset expression should be stored in the LHS
    if (InstructionName == TEXT("ComputedJump")) {
        const TSharedPtr<FJsonObject> Expression = Statement->GetObjectField(TEXT("Expression"));
        
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_ComputedGoto;
        Result->LHS = ProcessExpression(Expression);
        return Result;
    }

    //This is an unconditional jump, offset is stored in the TargetLabel
    //But we cannot really resolve it until we finished processing all statements, so store it in the patch-up map
    if (InstructionName == TEXT("Jump")) {
        const int32 JumpOffset = Statement->GetIntegerField(TEXT("Offset"));
        
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_UnconditionalGoto;
        JumpPatchUpTable.Add(Result, JumpOffset);
        return Result;
    }

    if (InstructionName == TEXT("JumpIfNot")) {
        const TSharedPtr<FJsonObject> Condition = Statement->GetObjectField(TEXT("Condition"));
        const int32 JumpOffset = Statement->GetIntegerField(TEXT("Offset"));
        
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_GotoIfNot;
        Result->LHS = ProcessExpression(Condition);
        JumpPatchUpTable.Add(Result, JumpOffset);
        return Result;
    }

    //Adds the location at which code will jump once PopExecutionFlow is encountered
    if (InstructionName == TEXT("PushExecutionFlow")) {
        const int32 JumpOffset = Statement->GetIntegerField(TEXT("Offset"));
        
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_PushState;
        JumpPatchUpTable.Add(Result, JumpOffset);
        return Result;
    }

    //Pops execution flow to the last stored location (or to return statement) if condition is zero
    if (InstructionName == TEXT("PopExecutionFlowIfNot")) {
        const TSharedPtr<FJsonObject> Condition = Statement->GetObjectField(TEXT("Condition"));
        
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_EndOfThreadIfNot;
        Result->LHS = ProcessExpression(Condition);
        return Result;
    }

    //Pops execution flow to the last stored location (or to return statement) unconditionally
    if (InstructionName == TEXT("PopExecutionFlow")) {
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_EndOfThread;
        return Result;
    }

    //Registers a delegate object into the multicast delegate subscription list
    if (InstructionName == TEXT("AddMulticastDelegate")) {
        const TSharedPtr<FJsonObject> MulticastDelegate = Statement->GetObjectField(TEXT("MulticastDelegate"));
        const TSharedPtr<FJsonObject> Delegate = Statement->GetObjectField(TEXT("Delegate"));

        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_AddMulticastDelegate;
        Result->LHS = ProcessExpression(MulticastDelegate);
        Result->RHS.Add(ProcessExpression(Delegate));
        return Result;
    }

    //Removes a single delegate object out of multicast delegate subscription list
    if (InstructionName == TEXT("RemoveMulticastDelegate")) {
        const TSharedPtr<FJsonObject> MulticastDelegate = Statement->GetObjectField(TEXT("MulticastDelegate"));
        const TSharedPtr<FJsonObject> Delegate = Statement->GetObjectField(TEXT("Delegate"));

        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_RemoveMulticastDelegate;
        Result->LHS = ProcessExpression(MulticastDelegate);
        Result->RHS.Add(ProcessExpression(Delegate));
        return Result;
    }

    //Clears a multicast delegate subscription list
    if (InstructionName == TEXT("RemoveMulticastDelegate")) {
        const TSharedPtr<FJsonObject> MulticastDelegate = Statement->GetObjectField(TEXT("MulticastDelegate"));
        
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_ClearMulticastDelegate;
        Result->LHS = ProcessExpression(MulticastDelegate);
        return Result;
    }

    //Populates delegate object expression with a reference to the function of the object passed
    if (InstructionName == TEXT("BindDelegate")) {
        const TSharedPtr<FJsonObject> Delegate = Statement->GetObjectField(TEXT("Delegate"));
        const TSharedPtr<FJsonObject> Object = Statement->GetObjectField(TEXT("Object"));
        const FString FunctionName = Statement->GetStringField(TEXT("FunctionName"));

        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_BindDelegate;
        Result->LHS = ProcessExpression(Delegate);

        //Create string literal with function name and add it as the first argument
        TSharedPtr<FKismetTerminal> FunctionNameTerminal = MakeShareable(new FKismetTerminal());
        FunctionNameTerminal->bIsLiteral = true;
        FunctionNameTerminal->StringLiteral = FunctionName;
        Result->RHS.Add(FunctionNameTerminal);
        
        Result->RHS.Add(ProcessExpression(Object));
        return Result;
    }

    //Returns from the currently running function, optionally passing back returned value (or nothing)
    if (InstructionName == TEXT("Return")) {
        TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
        Result->Type = EKismetCompiledStatementType::KCST_Return;
        return Result;
    }

    checkf(0, TEXT("Cannot transform instruction into compiled statement: %s"), *InstructionName);
    return NULL;
}

TSharedPtr<FKismetCompiledStatement> FKismetBytecodeTransformer::ProcessFunctionCallStatement(TSharedPtr<FJsonObject> Statement) {
    TSharedPtr<FKismetTerminal> Context;
    bool bIsInterfaceContext = false;

    //If expression we got is actually a context expression and not a direct function call, resolve context and record it
    if (IsContextExpression(Statement->GetStringField(TEXT("Inst")))) {
        TSharedPtr<FJsonObject> ResultExpression;
        Context = ResolveContext(Statement, ResultExpression, bIsInterfaceContext);
        Statement = ResultExpression;
    }
    
    const FString InstructionName = Statement->GetStringField(TEXT("Inst"));
        
    //At this point we should always end up with one of function call instructions
    check(IsCallFunctionInstruction(InstructionName));

    TSharedPtr<FKismetCompiledStatement> Result = MakeShareable(new FKismetCompiledStatement());
    Result->Type = EKismetCompiledStatementType::KCST_CallFunction;
    Result->FunctionContext = Context;
    Result->bIsInterfaceContext = bIsInterfaceContext;

    if (InstructionName == TEXT("LocalVirtualFunction") || InstructionName == TEXT("VirtualFunction")) {
        //This is a virtual function call, we have just a function name that needs to be resolved
        const FString FunctionName = Statement->GetStringField(TEXT("FunctionName"));
        UFunction* ResolvedFunction = ResolveFunctionByNameFromContext(Context, FunctionName);
        check(ResolvedFunction);

        //Obviously it is not a parent context for a virtual function
        Result->FunctionToCall = ResolvedFunction;
        Result->bIsParentContext = false;
    }
    else if (InstructionName == TEXT("CallMath")) {
        //CallMath functions should never have any context, so check this
        check(!Context.IsValid());

        const FString FunctionObjectPath = Statement->GetStringField(TEXT("Function"));
        UFunction* Function = LoadObject<UFunction>(NULL, *FunctionObjectPath);
        check(Function);
        
        Result->FunctionToCall = Function;
        Result->bIsParentContext = false;
    }
    else if (InstructionName == TEXT("LocalFinalFunction") || InstructionName == TEXT("FinalFunction")) {
        //Final function call, possibly in the parent context
        //We set parent context flag if function in question is not final, but is called with FinalFunction opcode
        const FString FunctionObjectPath = Statement->GetStringField(TEXT("Function"));
        UFunction* Function = LoadObject<UFunction>(NULL, *FunctionObjectPath);
        check(Function);

        Result->FunctionToCall = Function;
        Result->bIsParentContext = !Function->HasAnyFunctionFlags(EFunctionFlags::FUNC_Final);
    }
    else {
        checkf(0, TEXT("Unhandled function call opcode: %s"), *InstructionName);
    }

    //Do argument processing that is common for all function call instructions
    TArray<TSharedPtr<FJsonValue>> Parameters = Statement->GetArrayField(TEXT("Parameters"));

    int32 NumParams = 0;
    for (TFieldIterator<UProperty> PropIt(Result->FunctionToCall); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt) {
        UProperty* FuncParamProperty = *PropIt;

        //Skip return values because they are handled in a special way when we happened to be an expression in EX_Let statement
        if (!FuncParamProperty->HasAnyPropertyFlags(CPF_ReturnParm)) {
            TSharedPtr<FJsonObject> ParameterExpression = Parameters[NumParams++]->AsObject();
            const FString ParameterInstructionName = ParameterExpression->GetStringField(TEXT("Inst"));

            TSharedPtr<FKismetTerminal> ParameterTerminal;

            //Functions can have statements passed as parameters inline sometimes,
            //so we need to handle this gracefully here, because ProcessExpression has no idea how to deal with statements
            
            //GetArrayItem is one of the only 3 statements that can appear as function arguments. Noticeably, ArrayGetByRef
            //will actually never appear as a dedicated statement outside of inlined generated parameter context
            if (ParameterInstructionName == TEXT("ArrayGetByRef")) {
                TSharedPtr<FKismetCompiledStatement> ArrayItemStatement = MakeShareable(new FKismetCompiledStatement());
                ArrayItemStatement->Type = EKismetCompiledStatementType::KCST_ArrayGetByRef;
                ArrayItemStatement->RHS.Add(ProcessExpression(ParameterExpression->GetObjectField(TEXT("ArrayExpression"))));
                ArrayItemStatement->RHS.Add(ProcessExpression(ParameterExpression->GetObjectField(TEXT("IndexExpression"))));
                
                ParameterTerminal = MakeShareable(new FKismetTerminal());
                ParameterTerminal->InlineGeneratedParameter = ArrayItemStatement;
            }

            //Select is also the other node that will never appear on it's own as a dedicated statement,
            //because actually it is a perfectly pure node just returning value depending on the inputs
            else if (ParameterInstructionName == TEXT("SwitchValue")) {
                TSharedPtr<FKismetCompiledStatement> SwitchValue = MakeShareable(new FKismetCompiledStatement());
                SwitchValue->Type = EKismetCompiledStatementType::KCST_SwitchValue;
                //First RHS terminal is an index
                SwitchValue->RHS.Add(ProcessExpression(ParameterExpression->GetObjectField(TEXT("Expression"))));

                //Append pairs of (case value, case result) cases in order
                TArray<TSharedPtr<FJsonValue>> Cases = ParameterExpression->GetArrayField(TEXT("Cases"));
                for (const TSharedPtr<FJsonValue>& CaseValue : Cases) {
                    TSharedPtr<FJsonObject> CasePairObject = CaseValue->AsObject();
                    TSharedPtr<FKismetTerminal> CaseTestValue = ProcessExpression(CasePairObject->GetObjectField(TEXT("CaseValue")));
                    TSharedPtr<FKismetTerminal> CaseResult = ProcessExpression(CasePairObject->GetObjectField(TEXT("CaseResult")));
                    
                    //Case test values should *always* be literals, because so far only node currently generating KCST_SwitchValue is Select,
                    //and select allows selecting between literals by passed value only
                    check(CaseTestValue->bIsLiteral);
                    
                    SwitchValue->RHS.Add(CaseTestValue);
                    SwitchValue->RHS.Add(CaseResult);
                }

                //Default value is appended at the end
                SwitchValue->RHS.Add(ProcessExpression(ParameterExpression->GetObjectField(TEXT("DefaultResult"))));

                ParameterTerminal = MakeShareable(new FKismetTerminal());
                ParameterTerminal->InlineGeneratedParameter = SwitchValue;
            }

            //Function calls can be inlined too, but as far as I am aware, this is only used for MathExpression node
            //I must admit though, that these are MUCH more powerful than most users think -
            //they can not only use standard mathematical operators and functions, but also ANY
            //static, pure, native final functions exposed by blueprint libraries
            //These functions, obviously, cannot have any context though.
            //They, in fact, will be called with a context object that is logically wrong,
            //but it still works, because native static functions don't use context object at all.
            else if (IsCallFunctionInstruction(ParameterInstructionName)) {
                TSharedPtr<FKismetCompiledStatement> InlineFunctionCall = ProcessFunctionCallStatement(ParameterExpression);
                check(InlineFunctionCall->FunctionContext.IsValid() == false);
                check(InlineFunctionCall->FunctionToCall->HasAllFunctionFlags(FUNC_Final | FUNC_Static | FUNC_Native));

                ParameterTerminal = MakeShareable(new FKismetTerminal());
                ParameterTerminal->InlineGeneratedParameter = InlineFunctionCall;
            }
            else {
                //Otherwise it is a simple expression that we need to parse
                ParameterTerminal = ProcessExpression(ParameterExpression);
            }

            check(ParameterTerminal.IsValid());
            Result->RHS.Add(ParameterTerminal);
        }
    }
    return Result;
}

TSharedPtr<FKismetTerminal> FKismetBytecodeTransformer::ResolveContext(TSharedPtr<FJsonObject> Expression, TSharedPtr<FJsonObject>& OutResultExpression, bool& bOutIsInterfaceContext) {
    const FString InstructionName = Expression->GetStringField(TEXT("Inst"));

    //Deserialize context expression and set context type conforming to the instruction used
    TSharedPtr<FJsonObject> Context = Expression->GetObjectField(TEXT("Context"));
    const TSharedPtr<FJsonObject> ContextualExpression = Expression->GetObjectField(TEXT("Expression"));

    bOutIsInterfaceContext = false;
    
    //EX_InterfaceContext can happen only and only in one place
    //When function requires a context and received context is a FScriptInterface
    //It will never be nested, so we need to check it only on first level
    if (Context->GetStringField(TEXT("Inst")) == TEXT("InterfaceContext")) {
        bOutIsInterfaceContext = true;
        Context = Context->GetObjectField(TEXT("Expression"));
    }

    //Now that we know whenever context represented interface or not, transform it into the expression
    TSharedPtr<FKismetTerminal> ContextTerminal = ProcessExpression(Context);

    //Set context type on the acquired terminal according to the instruction used
    if (InstructionName == TEXT("Context") || InstructionName == TEXT("Context_FailSilent")) {
        ContextTerminal->ContextType = FKismetTerminal::EContextType_Object;
    } else if (InstructionName == TEXT("ClassContext")) {
        ContextTerminal->ContextType = FKismetTerminal::EContextType_Class;
    } else {
        checkf(0, TEXT("Unhandled context instruction: %s"), *InstructionName);
    }

    //If contextual expression is the context expression on it's own,
    //We should return it's term instead and set ourselves as it's context object
    if (IsContextExpression(ContextualExpression->GetStringField(TEXT("Inst")))) {
        //Never used, InterfaceContext can be encountered on top level only
        bool bDummyBoolean = false;
        TSharedPtr<FKismetTerminal> ChildContext = ResolveContext(ContextualExpression, OutResultExpression, bDummyBoolean);
        
        //Set ourselves as the parent context of the children context expression
        ChildContext->Context = ContextTerminal;
        
        //Return children context, not parent's one!
        return ChildContext;
    }
    
    //It is not the context expression on the right side, so set result expression and just return ourselves
    OutResultExpression = ContextualExpression;
    return ContextTerminal;
}
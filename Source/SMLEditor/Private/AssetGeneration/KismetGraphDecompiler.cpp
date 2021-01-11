#include "AssetGeneration/KismetGraphDecompiler.h"


#include "EdGraphSchema_K2_Actions.h"
#include "K2Node_DynamicCast.h"
#include "K2Node_FunctionEntry.h"
#include "K2Node_MakeArray.h"
#include "K2Node_MakeMap.h"
#include "K2Node_MakeSet.h"

FKismetGraphDecompiler::FKismetGraphDecompiler(UFunction* Function, UEdGraph* Graph) {
    this->Function = Function;
    this->EditorGraph = Graph;
}

void FKismetGraphDecompiler::Initialize(const TArray<TSharedPtr<FKismetCompiledStatement>>& Statements) {
    this->CompiledStatements = Statements;
}

UEdGraphNode* FKismetGraphDecompiler::CreateMakeMapNode(TSharedPtr<FKismetCompiledStatement> Statement) {
    const FString DestinationVariableName = ConvertTerminalToQualifiedName(Statement->LHS);
    const FVector2D NodePosition = EditorGraph->GetGoodPlaceForNewNode();
    
    //Spawn node in question and links it's terms with children nodes
    UK2Node_MakeMap* MakeMapNode = FEdGraphSchemaAction_K2NewNode::SpawnNode<UK2Node_MakeMap>(EditorGraph, NodePosition, EK2NewNodeFlags::None,
        [&Statement](UK2Node_MakeMap* MakeMapNode) {
        //Setup number of outputs so AllocateDefaultPins will create correct amount of pins
        //We divide number of right hand inputs by two because NumInputs is actually a number of (key, value) pairs
        MakeMapNode->NumInputs = Statement->RHS.Num() / 2;
    });

    //Connect inputs terminals and generate nodes for them
    //First input pin is offset by one because first pin allocated by MakeMap is an output
    for (int32 i = 0; i < Statement->RHS.Num(); i++) {
        UEdGraphPin* MakeMapInputPin = MakeMapNode->Pins[1 + i];
        check(MakeMapInputPin->Direction == EEdGraphPinDirection::EGPD_Input);
                
        const TSharedPtr<FKismetTerminal> InputTerminalValue = Statement->RHS[i];
        GenerateCodeForTerminalAndConnectItToPin(MakeMapInputPin, InputTerminalValue);
    }

    //Link output pin with intermediate variable value for replacement
    UEdGraphPin* OutputMakeMapPin = MakeMapNode->Pins[0];
    this->IntermediateVariableHandles.Add(DestinationVariableName, OutputMakeMapPin);
    return MakeMapNode;
}

UEdGraphNode* FKismetGraphDecompiler::CreateMakeSetNode(TSharedPtr<FKismetCompiledStatement> Statement) {
    const FString DestinationVariableName = ConvertTerminalToQualifiedName(Statement->LHS);
    const FVector2D NodePosition = EditorGraph->GetGoodPlaceForNewNode();
    
    //Spawn node in question and links it's terms with children nodes
    UK2Node_MakeSet* MakeSetNode = FEdGraphSchemaAction_K2NewNode::SpawnNode<UK2Node_MakeSet>(EditorGraph, NodePosition, EK2NewNodeFlags::None,
        [&Statement](UK2Node_MakeSet* MakeSetNode) {
        //Setup number of outputs so AllocateDefaultPins will create correct amount of pins
        MakeSetNode->NumInputs = Statement->RHS.Num();
    });

    //Connect inputs terminals and generate nodes for them
    //First input pin is offset by one because first pin allocated by MakeMap is an output
    for (int32 i = 0; i < Statement->RHS.Num(); i++) {
        UEdGraphPin* MakeSetInputPin = MakeSetNode->Pins[1 + i];
        check(MakeSetInputPin->Direction == EEdGraphPinDirection::EGPD_Input);
                
        const TSharedPtr<FKismetTerminal> InputTerminalValue = Statement->RHS[i];
        GenerateCodeForTerminalAndConnectItToPin(MakeSetInputPin, InputTerminalValue);
    }

    //Link output pin with intermediate variable value for replacement
    UEdGraphPin* OutputMakeSetPin = MakeSetNode->Pins[0];
    this->IntermediateVariableHandles.Add(DestinationVariableName, OutputMakeSetPin);
    return MakeSetNode;
}

UEdGraphNode* FKismetGraphDecompiler::CreateMakeArrayNode(TSharedPtr<FKismetCompiledStatement> Statement) {
    const FString DestinationVariableName = ConvertTerminalToQualifiedName(Statement->LHS);
    const FVector2D NodePosition = EditorGraph->GetGoodPlaceForNewNode();
    
    //Spawn node in question and links it's terms with children nodes
    UK2Node_MakeArray* MakeArrayNode = FEdGraphSchemaAction_K2NewNode::SpawnNode<UK2Node_MakeArray>(EditorGraph, NodePosition, EK2NewNodeFlags::None,
        [&Statement](UK2Node_MakeArray* MakeArrayNode) {
        //Setup number of outputs so AllocateDefaultPins will create correct amount of pins
        MakeArrayNode->NumInputs = Statement->RHS.Num();
    });

    //Connect inputs terminals and generate nodes for them
    //First input pin is offset by one because first pin allocated by MakeMap is an output
    for (int32 i = 0; i < Statement->RHS.Num(); i++) {
        UEdGraphPin* MakeArrayInputPin = MakeArrayNode->Pins[1 + i];
        check(MakeArrayInputPin->Direction == EEdGraphPinDirection::EGPD_Input);
                
        const TSharedPtr<FKismetTerminal> InputTerminalValue = Statement->RHS[i];
        GenerateCodeForTerminalAndConnectItToPin(MakeArrayInputPin, InputTerminalValue);
    }

    //Link output pin with intermediate variable value for replacement
    UEdGraphPin* OutputMakeArrayPin = MakeArrayNode->Pins[0];
    this->IntermediateVariableHandles.Add(DestinationVariableName, OutputMakeArrayPin);
    return MakeArrayNode;
}

UEdGraphNode* FKismetGraphDecompiler::CreateDynamicCastNode(TSharedPtr<FKismetCompiledStatement> Statement, UEdGraphPin* PreviousNodeExecOutput, int32& NextStatementIndex) {
    //First RHS terminal will always be a class constant specifying type of class to cast to
    const TSharedPtr<FKismetTerminal> ClassToCastTerminal = Statement->RHS[0];
    check(ClassToCastTerminal->bIsLiteral);
    UClass* ClassObjectToCast = CastChecked<UClass>(ClassToCastTerminal->ObjectLiteral);
    check(ClassObjectToCast);

    const TSharedPtr<FKismetTerminal> InputObjectTerminal = Statement->RHS[1];
    const FString CastedObjectOutVariableName = ConvertTerminalToQualifiedName(Statement->LHS);
    const FVector2D NodePosition = EditorGraph->GetGoodPlaceForNewNode();

    //K2Node_DynamicCast will always emit KCST_ObjectToBool as the next statement
    //Variable name generated by it should be wired up with DynamicCast bSuccess pin output instead
    const TSharedPtr<FKismetCompiledStatement> ObjectToBool = CompiledStatements[NextStatementIndex++];
    check(ObjectToBool->Type == ECompiledStatementType::KCST_ObjectToBool);
    const FString CastSucceedOutVariableName = ConvertTerminalToQualifiedName(ObjectToBool->LHS);

    //Next statement decides whenever cast is pure or not
    //When cast is not pure, next statements will be KCST_GotoIfNot followed by KCST_UnconditionalGoto
    //with GotoIfNot LHS being equal to CastSucceedOutVariableName
    const TSharedPtr<FKismetCompiledStatement> GotoIfNot = CompiledStatements[NextStatementIndex];

    bool bIsCastCompletelyPure = true;
    TSharedPtr<FKismetCompiledStatement> StatementToJumpOnFailure;
    TSharedPtr<FKismetCompiledStatement> StatementToJumpOnSuccess;
    
    if (GotoIfNot->Type == ECompiledStatementType::KCST_GotoIfNot && ConvertTerminalToQualifiedName(GotoIfNot->LHS) == CastSucceedOutVariableName) {
        //This is an impure cast, next statement checks if bSuccess is false and then jumps to false execution statements!
        bIsCastCompletelyPure = false;
        
        const TSharedPtr<FKismetCompiledStatement> UnconditionalGoto = CompiledStatements[NextStatementIndex + 1];
        check(UnconditionalGoto->Type == ECompiledStatementType::KCST_UnconditionalGoto);
        
        StatementToJumpOnSuccess = UnconditionalGoto->TargetLabel;
        StatementToJumpOnFailure = GotoIfNot->TargetLabel;
        
        //Skip two next statements because we just handled them
        NextStatementIndex += 2;
    }
    
    UK2Node_DynamicCast* DynamicCastNode = FEdGraphSchemaAction_K2NewNode::SpawnNode<UK2Node_DynamicCast>(EditorGraph, NodePosition, EK2NewNodeFlags::None,
        [bIsCastCompletelyPure, ClassObjectToCast](UK2Node_DynamicCast* DynamicCastNode) {
        //We know at this point whenever cast is going to be pure or impure
        DynamicCastNode->TargetType = ClassObjectToCast;
        DynamicCastNode->SetPurity(bIsCastCompletelyPure);
    });

    //Connect input object pin with the terminal type passed at RHS
    UEdGraphPin* InputObject = DynamicCastNode->GetCastSourcePin();
    GenerateCodeForTerminalAndConnectItToPin(InputObject, InputObjectTerminal);

    //Add output object pin into the variable map so it will be connected later
    UEdGraphPin* OutputObjectPin = DynamicCastNode->GetCastResultPin();
    this->IntermediateVariableHandles.Add(CastedObjectOutVariableName, OutputObjectPin);

    //Future actions depend on whenever we are working with pure or an impure cast
    if (bIsCastCompletelyPure) {
        //For pure casts, we also need to add bSuccess pin into the intermediate variable map
        UEdGraphPin* CastSucceedOutputPin = DynamicCastNode->GetBoolSuccessPin();
        this->IntermediateVariableHandles.Add(CastSucceedOutVariableName, CastSucceedOutputPin);
    } else {
        //For impure casts, we need to connect input pin and add output pins to fixup map
        UEdGraphPin* InputExecPin = DynamicCastNode->FindPinChecked(UEdGraphSchema_K2::PN_Execute, EEdGraphPinDirection::EGPD_Input);
        ConnectGraphPins(PreviousNodeExecOutput, InputExecPin);

        //Automatically connect success and failure execution pins later
        UEdGraphPin* OutputSuccessExecPin = DynamicCastNode->GetValidCastPin();
        UEdGraphPin* OutputFailureExecPin = DynamicCastNode->GetInvalidCastPin();

        this->ExecPinPatchUpMap.Add(OutputSuccessExecPin, StatementToJumpOnSuccess);
        this->ExecPinPatchUpMap.Add(OutputFailureExecPin, StatementToJumpOnFailure);
    }
    
    return DynamicCastNode;
}

UEdGraphNode* FKismetGraphDecompiler::CreateAssignmentNode(TSharedPtr<FKismetCompiledStatement> Statement, UEdGraphPin* PreviousNodeExecOutput, int32& NextStatementIndex) {
    //KCST_Assignment can be generated when:
    // 1) through FKismetCompilerUtilities::CreateObjectAssignmentStatement call
    //     (which can also generate KCST_CastObjToInterface/KCST_CastInterfaceToObj instead, but they both will end up here too)
    //     Can be also called by:
    //         a) by K2Node_MakeStruct for actually filling struct fields X
    //         b) by K2Node_VariableSet for setting user defined variable value
    //         c) by K2Node_Copy for copying provided value into the local generated variable X
    // 2) by K2Node_MakeStruct for doing very awkward stuff with EditCondition properties X
    // 3) by K2Node_VariableSetRef to assign external variable passed by reference to the given value 
    // 4) by K2Node_SetFieldsInStruct if input struct is not passed by reference to copy it to the returned variable X
    // 5) by K2Node_MultiGate for implementing god knows what N
    // 6) by K2Node_DelegateSet for initializing delegate object with InstanceDelegate on self with provided function name
    // And we need to handle all of these cases... oh well...

    const TSharedPtr<FKismetTerminal> VariableAssigned = Statement->LHS;

    //Only and only K2Node_SetFieldsAndStruct and K2Node_MakeStruct can set struct variables directly
    //there is no way to modify them around these nodes in blueprints through assignment
    if (VariableAssigned->Context && VariableAssigned->Context->ContextType == FKismetTerminal::EContextType_Struct) {
        check(VariableAssigned->Context->Type.PinCategory == UEdGraphSchema_K2::PC_Struct);
        const FString ContextPropertyName = VariableAssigned->Context->AssociatedVarProperty;

        //We are dealing with MakeStruct node - run dedicated routine that will handle it
        if (ContextPropertyName.StartsWith(TEXT("K2Node_MakeStruct"))) {
            //Struct variable in MakeStruct will always be a local variable, unlike in SetFieldsInStruct
            check(IsLocalVariable(VariableAssigned->Context));
            //Also variable in question will never be user defined, only generated implicitly
            check(!IsUserCreatedLocalVariable(VariableAssigned->Context));
        
            //Decrement NextStatementIndex by one so CreateMakeStruct node will start with first assignment
            NextStatementIndex--;
            return CreateMakeStructNode(VariableAssigned, NextStatementIndex);
        }
        //We are dealing with something that does struct assignments directly by reference,
        //and currently only node capable of doing that is K2Node_SetFieldsInStruct. So we assume we are dealing with it here
        //This node will not generate local variables by itself except when it's input is connected to non-const value
        //So we cannot really use variable names to identify access. This behavior is very similar to K2Node_VariableSetRef

        //Decrement NextStatementIndex by one so CreateMakeStruct node will start with first assignment
        NextStatementIndex--;
        return CreateSetFieldsInStructNode(VariableAssigned, PreviousNodeExecOutput, NextStatementIndex);
    }

    //If we are working with a local variable with copy name, we are definitely working with a K2Node_Copy
    if (IsLocalVariable(VariableAssigned) && VariableAssigned->AssociatedVarProperty.StartsWith(TEXT("K2Node_Copy"))) {
        return CreateCopyNode(Statement);
    }

    //K2Node_DelegateSet will result in a local variable with a recognisable name too
    if (IsLocalVariable(VariableAssigned) && VariableAssigned->AssociatedVarProperty.StartsWith(TEXT("K2Node_DelegateSet"))) {
        return CreateDelegateSetNode(Statement, PreviousNodeExecOutput, NextStatementIndex);
    }

    //Only remaining nodes are K2Node_VariableSet and K2Node_VariableSetRef
    //Difference between them is very simple: VariableSet sets "static" variable predefined earlier,
    //while VariableSetRef can set any unknown value passed by reference to the provided value
    //Solution here would be using VariableSet when possible, while falling back to
    //VariableSetRef when variable expression in question cannot be represented as a static variable reference
    
}

UEdGraphNode* FKismetGraphDecompiler::GenerateNodeForStatement(int32& StatementIndex, UEdGraphPin* PreviousNodeExecOutput) {
    const TSharedPtr<FKismetCompiledStatement> Statement = CompiledStatements[StatementIndex++];

    //KCST_CreateMap statement can be generated only in two cases: either by user-created K2Node_MakeMap,
    //or by compiler generated K2Node_MakeVariable, generated to create a map value to be then used by K2Node_VariableSet
    //apparently both nodes have roughly identical functionality, but K2Node_VariableSet is capable of
    //"automatically initializing" itself from property types, but it's not really important during decompilation,
    //so we basically just treat every KCST_CreateMap opcode as K2Node_MakeMap
    //Later, if it can be reduced into default local variable value assignment, it will be removed and set as default value,
    //which will cause the generation of K2Node_MakeVariable by function entry again, resulting in the equal graph
    if (Statement->Type == ECompiledStatementType::KCST_CreateMap) {
        return CreateMakeMapNode(Statement);
    }

    //Exactly the same thing for KCST_CreateSet instruction - we treat all of them as K2Node_MakeSet
    if (Statement->Type == ECompiledStatementType::KCST_CreateSet) {
        return CreateMakeSetNode(Statement);
    }

    //Exactly the same thing with KCST_CreateArray instruction - we treat all of them as K2Node_MakeArray
    if (Statement->Type == ECompiledStatementType::KCST_CreateArray) {
        return CreateMakeArrayNode(Statement);
    }

    //These two instructions are only ever emitted to K2Node_DynamicCast, so it is completely safe to convert them directly
    if (Statement->Type == ECompiledStatementType::KCST_DynamicCast ||
        Statement->Type == ECompiledStatementType::KCST_CrossInterfaceCast) {
        return CreateDynamicCastNode(Statement, PreviousNodeExecOutput, StatementIndex);
    }

    //These statements can appear in multiple cases:
    //1) As the part of K2Node_DynamicCast
    //2) Instead of KCST_Assignment when trying to assign interface value to object property or vice versa
    //3) When interface is passed to a function call node where object argument is expected, or vise versa
    if (Statement->Type == ECompiledStatementType::KCST_CastInterfaceToObj ||
        Statement->Type == ECompiledStatementType::KCST_CastObjToInterface) {
        
        //User-defined variables can only happen as the part of KCST_Assignment instructions
        if (IsUserCreatedLocalVariable(Statement->LHS)) {
            return CreateAssignmentNode(Statement, PreviousNodeExecOutput, StatementIndex);
        }
        //Otherwise it is a generated variable, and we can use a name to differentiate between 3 cases
        const FString VariableName = Statement->LHS->AssociatedVarProperty;
        
        if (VariableName.StartsWith(TEXT("K2Node_DynamicCast"))) {
            //Dynamic cast node, handle the same way as KCST_DynamicCast
            CreateDynamicCastNode(Statement, PreviousNodeExecOutput, StatementIndex);
        }
        else if (VariableName.StartsWith(TEXT("CallFunc_")) && VariableName.EndsWith(TEXT("_CastInput"))) {
            //Function call node with parameter converter in-place from interface to object or vice versa
            //Correct handling for it would be just skipping the cast altogether,
            //while mapping output variable to the same pin as input one
            const TSharedPtr<FKismetTerminal> InputObjectTerminal = Statement->RHS[1];
            UEdGraphPin* CorrespondingInputPin = this->IntermediateVariableHandles.FindChecked(ConvertTerminalToQualifiedName(InputObjectTerminal));
  
            const TSharedPtr<FKismetTerminal> OutputObjectTerminal = Statement->LHS;
            this->IntermediateVariableHandles.Add(ConvertTerminalToQualifiedName(OutputObjectTerminal), CorrespondingInputPin);
            return NULL;
        }
        else {
            //Otherwise it should be assignment node with generated variable name, which can happen for various node types
            return CreateAssignmentNode(Statement, PreviousNodeExecOutput, StatementIndex);
        }
    }

    //Assignment statements can be a part of multiple nodes, exact handling will be decided in CreateAssignmentNode
    if (Statement->Type == ECompiledStatementType::KCST_Assignment) {
        return CreateAssignmentNode(Statement, PreviousNodeExecOutput, StatementIndex);
    }

    
    

    
    
}

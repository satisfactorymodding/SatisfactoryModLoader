// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_PlayerState_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_PlayerState.BP_PlayerState_C.ClearShoppingList
// ()

void ABP_PlayerState_C::ClearShoppingList()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.ClearShoppingList");

	ABP_PlayerState_C_ClearShoppingList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.ShoppingListUpdated
// ()

void ABP_PlayerState_C::ShoppingListUpdated()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.ShoppingListUpdated");

	ABP_PlayerState_C_ShoppingListUpdated_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.OnRep_mShoppingList
// ()

void ABP_PlayerState_C::OnRep_mShoppingList()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.OnRep_mShoppingList");

	ABP_PlayerState_C_OnRep_mShoppingList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.GetShoppingListSortIndex
// ()
// Parameters:
// struct FRecipeAmountStruct     RecipeAmountStruct             (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int ABP_PlayerState_C::GetShoppingListSortIndex(struct FRecipeAmountStruct* RecipeAmountStruct)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.GetShoppingListSortIndex");

	ABP_PlayerState_C_GetShoppingListSortIndex_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (RecipeAmountStruct != nullptr)
		*RecipeAmountStruct = params.RecipeAmountStruct;

	return params.ReturnValue;
}


// Function BP_PlayerState.BP_PlayerState_C.SortShoppingList
// ()

void ABP_PlayerState_C::SortShoppingList()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.SortShoppingList");

	ABP_PlayerState_C_SortShoppingList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.SetNumRecipeInShoppingList
// ()
// Parameters:
// class UClass*                  Recipe                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            NumRecipes                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PlayerState_C::SetNumRecipeInShoppingList(class UClass* Recipe, int NumRecipes)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.SetNumRecipeInShoppingList");

	ABP_PlayerState_C_SetNumRecipeInShoppingList_Params params;
	params.Recipe = Recipe;
	params.NumRecipes = NumRecipes;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.PonderUpdatingShoppingList
// ()
// Parameters:
// class UClass*                  InputPin                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PlayerState_C::PonderUpdatingShoppingList(class UClass* InputPin)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.PonderUpdatingShoppingList");

	ABP_PlayerState_C_PonderUpdatingShoppingList_Params params;
	params.InputPin = InputPin;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.AddRecipeToShoppingList
// ()
// Parameters:
// class UClass*                  Recipe                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            NumRecipes                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PlayerState_C::AddRecipeToShoppingList(class UClass* Recipe, int NumRecipes)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.AddRecipeToShoppingList");

	ABP_PlayerState_C_AddRecipeToShoppingList_Params params;
	params.Recipe = Recipe;
	params.NumRecipes = NumRecipes;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.RemoveRecipeFromShoppingList
// ()
// Parameters:
// class UClass*                  Recipe                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            NumRecipes                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PlayerState_C::RemoveRecipeFromShoppingList(class UClass* Recipe, int NumRecipes)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.RemoveRecipeFromShoppingList");

	ABP_PlayerState_C_RemoveRecipeFromShoppingList_Params params;
	params.Recipe = Recipe;
	params.NumRecipes = NumRecipes;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.UserConstructionScript
// ()

void ABP_PlayerState_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.UserConstructionScript");

	ABP_PlayerState_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.ReceiveBeginPlay
// ()

void ABP_PlayerState_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.ReceiveBeginPlay");

	ABP_PlayerState_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.BroadcastChatMessage
// ()
// Parameters:
// struct FText                   ChatMessageIn                  (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_PlayerState_C::BroadcastChatMessage(const struct FText& ChatMessageIn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.BroadcastChatMessage");

	ABP_PlayerState_C_BroadcastChatMessage_Params params;
	params.ChatMessageIn = ChatMessageIn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.ReceiveChatMessage
// ()
// Parameters:
// struct FText                   ChatMessageIn                  (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FText                   ChatSender                     (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_PlayerState_C::ReceiveChatMessage(const struct FText& ChatMessageIn, const struct FText& ChatSender)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.ReceiveChatMessage");

	ABP_PlayerState_C_ReceiveChatMessage_Params params;
	params.ChatMessageIn = ChatMessageIn;
	params.ChatSender = ChatSender;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.OnBuildableConstructed
// ()
// Parameters:
// class UClass*                  itemDescriptor                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PlayerState_C::OnBuildableConstructed(class UClass* itemDescriptor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.OnBuildableConstructed");

	ABP_PlayerState_C_OnBuildableConstructed_Params params;
	params.itemDescriptor = itemDescriptor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.Server_AddRecipeToShoppingList
// ()
// Parameters:
// class UClass*                  Recipe                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            NumRecipes                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PlayerState_C::Server_AddRecipeToShoppingList(class UClass* Recipe, int NumRecipes)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.Server_AddRecipeToShoppingList");

	ABP_PlayerState_C_Server_AddRecipeToShoppingList_Params params;
	params.Recipe = Recipe;
	params.NumRecipes = NumRecipes;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.Server_SetNumRecipesInShoppingList
// ()
// Parameters:
// class UClass*                  Recipe                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            NumRecipes                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PlayerState_C::Server_SetNumRecipesInShoppingList(class UClass* Recipe, int NumRecipes)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.Server_SetNumRecipesInShoppingList");

	ABP_PlayerState_C_Server_SetNumRecipesInShoppingList_Params params;
	params.Recipe = Recipe;
	params.NumRecipes = NumRecipes;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.Server_RemoveRecupeFromShoppingList
// ()
// Parameters:
// class UClass*                  Recipe                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            NumRecipes                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PlayerState_C::Server_RemoveRecupeFromShoppingList(class UClass* Recipe, int NumRecipes)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.Server_RemoveRecupeFromShoppingList");

	ABP_PlayerState_C_Server_RemoveRecupeFromShoppingList_Params params;
	params.Recipe = Recipe;
	params.NumRecipes = NumRecipes;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PlayerState_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.ReceiveTick");

	ABP_PlayerState_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.Server_ClearShoppingList
// ()

void ABP_PlayerState_C::Server_ClearShoppingList()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.Server_ClearShoppingList");

	ABP_PlayerState_C_Server_ClearShoppingList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.ExecuteUbergraph_BP_PlayerState
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PlayerState_C::ExecuteUbergraph_BP_PlayerState(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.ExecuteUbergraph_BP_PlayerState");

	ABP_PlayerState_C_ExecuteUbergraph_BP_PlayerState_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.OnShoppingListUpdated__DelegateSignature
// ()

void ABP_PlayerState_C::OnShoppingListUpdated__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.OnShoppingListUpdated__DelegateSignature");

	ABP_PlayerState_C_OnShoppingListUpdated__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PlayerState.BP_PlayerState_C.ReceivedChatMessage__DelegateSignature
// ()
// Parameters:
// struct FText                   ChatSender                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FText                   ChatMessage                    (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_PlayerState_C::ReceivedChatMessage__DelegateSignature(const struct FText& ChatSender, const struct FText& ChatMessage)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PlayerState.BP_PlayerState_C.ReceivedChatMessage__DelegateSignature");

	ABP_PlayerState_C_ReceivedChatMessage__DelegateSignature_Params params;
	params.ChatSender = ChatSender;
	params.ChatMessage = ChatMessage;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

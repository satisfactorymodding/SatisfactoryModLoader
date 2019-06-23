#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_PlayerState_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_PlayerState.BP_PlayerState_C.ClearShoppingList
struct ABP_PlayerState_C_ClearShoppingList_Params
{
};

// Function BP_PlayerState.BP_PlayerState_C.ShoppingListUpdated
struct ABP_PlayerState_C_ShoppingListUpdated_Params
{
};

// Function BP_PlayerState.BP_PlayerState_C.OnRep_mShoppingList
struct ABP_PlayerState_C_OnRep_mShoppingList_Params
{
};

// Function BP_PlayerState.BP_PlayerState_C.GetShoppingListSortIndex
struct ABP_PlayerState_C_GetShoppingListSortIndex_Params
{
	struct FRecipeAmountStruct                         RecipeAmountStruct;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.SortShoppingList
struct ABP_PlayerState_C_SortShoppingList_Params
{
};

// Function BP_PlayerState.BP_PlayerState_C.SetNumRecipeInShoppingList
struct ABP_PlayerState_C_SetNumRecipeInShoppingList_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumRecipes;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.PonderUpdatingShoppingList
struct ABP_PlayerState_C_PonderUpdatingShoppingList_Params
{
	class UClass*                                      InputPin;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.AddRecipeToShoppingList
struct ABP_PlayerState_C_AddRecipeToShoppingList_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumRecipes;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.RemoveRecipeFromShoppingList
struct ABP_PlayerState_C_RemoveRecipeFromShoppingList_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumRecipes;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.UserConstructionScript
struct ABP_PlayerState_C_UserConstructionScript_Params
{
};

// Function BP_PlayerState.BP_PlayerState_C.ReceiveBeginPlay
struct ABP_PlayerState_C_ReceiveBeginPlay_Params
{
};

// Function BP_PlayerState.BP_PlayerState_C.BroadcastChatMessage
struct ABP_PlayerState_C_BroadcastChatMessage_Params
{
	struct FText                                       ChatMessageIn;                                            // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_PlayerState.BP_PlayerState_C.ReceiveChatMessage
struct ABP_PlayerState_C_ReceiveChatMessage_Params
{
	struct FText                                       ChatMessageIn;                                            // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FText                                       ChatSender;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_PlayerState.BP_PlayerState_C.OnBuildableConstructed
struct ABP_PlayerState_C_OnBuildableConstructed_Params
{
	class UClass*                                      itemDescriptor;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.Server_AddRecipeToShoppingList
struct ABP_PlayerState_C_Server_AddRecipeToShoppingList_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumRecipes;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.Server_SetNumRecipesInShoppingList
struct ABP_PlayerState_C_Server_SetNumRecipesInShoppingList_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumRecipes;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.Server_RemoveRecupeFromShoppingList
struct ABP_PlayerState_C_Server_RemoveRecupeFromShoppingList_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumRecipes;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.ReceiveTick
struct ABP_PlayerState_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.Server_ClearShoppingList
struct ABP_PlayerState_C_Server_ClearShoppingList_Params
{
};

// Function BP_PlayerState.BP_PlayerState_C.ExecuteUbergraph_BP_PlayerState
struct ABP_PlayerState_C_ExecuteUbergraph_BP_PlayerState_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PlayerState.BP_PlayerState_C.OnShoppingListUpdated__DelegateSignature
struct ABP_PlayerState_C_OnShoppingListUpdated__DelegateSignature_Params
{
};

// Function BP_PlayerState.BP_PlayerState_C.ReceivedChatMessage__DelegateSignature
struct ABP_PlayerState_C_ReceivedChatMessage__DelegateSignature_Params
{
	struct FText                                       ChatSender;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FText                                       ChatMessage;                                              // (BlueprintVisible, BlueprintReadOnly, Parm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

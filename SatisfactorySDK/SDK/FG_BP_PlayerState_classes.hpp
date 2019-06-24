#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_PlayerState_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_PlayerState.BP_PlayerState_C
// 0x0054 (0x04FC - 0x04A8)
class ABP_PlayerState_C : public AFGPlayerState
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x04A8(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x04B0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FScriptMulticastDelegate                    ReceivedChatMessage;                                      // 0x04B8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	TArray<struct FLinearColor>                        mSavedColorPickerColors;                                  // 0x04C8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, SaveGame)
	TArray<struct FRecipeAmountStruct>                 mShoppingList;                                            // 0x04D8(0x0010) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, SaveGame)
	struct FScriptMulticastDelegate                    OnShoppingListUpdated;                                    // 0x04E8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	int                                                mLastSchematicTierInUI;                                   // 0x04F8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_PlayerState.BP_PlayerState_C");
		return ptr;
	}


	void ClearShoppingList();
	void ShoppingListUpdated();
	void OnRep_mShoppingList();
	int GetShoppingListSortIndex(struct FRecipeAmountStruct* RecipeAmountStruct);
	void SortShoppingList();
	void SetNumRecipeInShoppingList(class UClass* Recipe, int NumRecipes);
	void PonderUpdatingShoppingList(class UClass* InputPin);
	void AddRecipeToShoppingList(class UClass* Recipe, int NumRecipes);
	void RemoveRecipeFromShoppingList(class UClass* Recipe, int NumRecipes);
	void UserConstructionScript();
	void ReceiveBeginPlay();
	void BroadcastChatMessage(const struct FText& ChatMessageIn);
	void ReceiveChatMessage(const struct FText& ChatMessageIn, const struct FText& ChatSender);
	void OnBuildableConstructed(class UClass* itemDescriptor);
	void Server_AddRecipeToShoppingList(class UClass* Recipe, int NumRecipes);
	void Server_SetNumRecipesInShoppingList(class UClass* Recipe, int NumRecipes);
	void Server_RemoveRecupeFromShoppingList(class UClass* Recipe, int NumRecipes);
	void ReceiveTick(float* DeltaSeconds);
	void Server_ClearShoppingList();
	void ExecuteUbergraph_BP_PlayerState(int EntryPoint);
	void OnShoppingListUpdated__DelegateSignature();
	void ReceivedChatMessage__DelegateSignature(const struct FText& ChatSender, const struct FText& ChatMessage);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

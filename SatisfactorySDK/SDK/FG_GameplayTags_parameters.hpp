#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_GameplayTags_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function GameplayTags.BlueprintGameplayTagLibrary.RemoveGameplayTag
struct UBlueprintGameplayTagLibrary_RemoveGameplayTag_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (Parm, OutParm, ReferenceParm)
	struct FGameplayTag                                Tag;                                                      // (Parm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.NotEqual_TagTag
struct UBlueprintGameplayTagLibrary_NotEqual_TagTag_Params
{
	struct FGameplayTag                                A;                                                        // (Parm)
	class FString                                      B;                                                        // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.NotEqual_TagContainerTagContainer
struct UBlueprintGameplayTagLibrary_NotEqual_TagContainerTagContainer_Params
{
	struct FGameplayTagContainer                       A;                                                        // (Parm)
	class FString                                      B;                                                        // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.NotEqual_GameplayTagContainer
struct UBlueprintGameplayTagLibrary_NotEqual_GameplayTagContainer_Params
{
	struct FGameplayTagContainer                       A;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FGameplayTagContainer                       B;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.NotEqual_GameplayTag
struct UBlueprintGameplayTagLibrary_NotEqual_GameplayTag_Params
{
	struct FGameplayTag                                A;                                                        // (Parm)
	struct FGameplayTag                                B;                                                        // (Parm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.MatchesTag
struct UBlueprintGameplayTagLibrary_MatchesTag_Params
{
	struct FGameplayTag                                TagOne;                                                   // (Parm)
	struct FGameplayTag                                TagTwo;                                                   // (Parm)
	bool                                               bExactMatch;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.MatchesAnyTags
struct UBlueprintGameplayTagLibrary_MatchesAnyTags_Params
{
	struct FGameplayTag                                TagOne;                                                   // (Parm)
	struct FGameplayTagContainer                       OtherContainer;                                           // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               bExactMatch;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.MakeLiteralGameplayTagContainer
struct UBlueprintGameplayTagLibrary_MakeLiteralGameplayTagContainer_Params
{
	struct FGameplayTagContainer                       Value;                                                    // (Parm)
	struct FGameplayTagContainer                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.MakeLiteralGameplayTag
struct UBlueprintGameplayTagLibrary_MakeLiteralGameplayTag_Params
{
	struct FGameplayTag                                Value;                                                    // (Parm)
	struct FGameplayTag                                ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.MakeGameplayTagQuery
struct UBlueprintGameplayTagLibrary_MakeGameplayTagQuery_Params
{
	struct FGameplayTagQuery                           TagQuery;                                                 // (Parm)
	struct FGameplayTagQuery                           ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.MakeGameplayTagContainerFromTag
struct UBlueprintGameplayTagLibrary_MakeGameplayTagContainerFromTag_Params
{
	struct FGameplayTag                                SingleTag;                                                // (Parm)
	struct FGameplayTagContainer                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.MakeGameplayTagContainerFromArray
struct UBlueprintGameplayTagLibrary_MakeGameplayTagContainerFromArray_Params
{
	TArray<struct FGameplayTag>                        GameplayTags;                                             // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	struct FGameplayTagContainer                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.IsGameplayTagValid
struct UBlueprintGameplayTagLibrary_IsGameplayTagValid_Params
{
	struct FGameplayTag                                GameplayTag;                                              // (Parm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.HasTag
struct UBlueprintGameplayTagLibrary_HasTag_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FGameplayTag                                Tag;                                                      // (Parm)
	bool                                               bExactMatch;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.HasAnyTags
struct UBlueprintGameplayTagLibrary_HasAnyTags_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FGameplayTagContainer                       OtherContainer;                                           // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               bExactMatch;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.HasAllTags
struct UBlueprintGameplayTagLibrary_HasAllTags_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FGameplayTagContainer                       OtherContainer;                                           // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               bExactMatch;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.HasAllMatchingGameplayTags
struct UBlueprintGameplayTagLibrary_HasAllMatchingGameplayTags_Params
{
	TScriptInterface<class UGameplayTagAssetInterface> TagContainerInterface;                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FGameplayTagContainer                       OtherContainer;                                           // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.GetTagName
struct UBlueprintGameplayTagLibrary_GetTagName_Params
{
	struct FGameplayTag                                GameplayTag;                                              // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FName                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.GetNumGameplayTagsInContainer
struct UBlueprintGameplayTagLibrary_GetNumGameplayTagsInContainer_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.GetDebugStringFromGameplayTagContainer
struct UBlueprintGameplayTagLibrary_GetDebugStringFromGameplayTagContainer_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.GetDebugStringFromGameplayTag
struct UBlueprintGameplayTagLibrary_GetDebugStringFromGameplayTag_Params
{
	struct FGameplayTag                                GameplayTag;                                              // (Parm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.GetAllActorsOfClassMatchingTagQuery
struct UBlueprintGameplayTagLibrary_GetAllActorsOfClassMatchingTagQuery_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ActorClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FGameplayTagQuery                           GameplayTagQuery;                                         // (ConstParm, Parm, OutParm, ReferenceParm)
	TArray<class AActor*>                              OutActors;                                                // (Parm, OutParm, ZeroConstructor)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.EqualEqual_GameplayTagContainer
struct UBlueprintGameplayTagLibrary_EqualEqual_GameplayTagContainer_Params
{
	struct FGameplayTagContainer                       A;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FGameplayTagContainer                       B;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.EqualEqual_GameplayTag
struct UBlueprintGameplayTagLibrary_EqualEqual_GameplayTag_Params
{
	struct FGameplayTag                                A;                                                        // (Parm)
	struct FGameplayTag                                B;                                                        // (Parm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.DoesTagAssetInterfaceHaveTag
struct UBlueprintGameplayTagLibrary_DoesTagAssetInterfaceHaveTag_Params
{
	TScriptInterface<class UGameplayTagAssetInterface> TagContainerInterface;                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FGameplayTag                                Tag;                                                      // (Parm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.DoesContainerMatchTagQuery
struct UBlueprintGameplayTagLibrary_DoesContainerMatchTagQuery_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FGameplayTagQuery                           TagQuery;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.BreakGameplayTagContainer
struct UBlueprintGameplayTagLibrary_BreakGameplayTagContainer_Params
{
	struct FGameplayTagContainer                       GameplayTagContainer;                                     // (ConstParm, Parm, OutParm, ReferenceParm)
	TArray<struct FGameplayTag>                        GameplayTags;                                             // (Parm, OutParm, ZeroConstructor)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.AppendGameplayTagContainers
struct UBlueprintGameplayTagLibrary_AppendGameplayTagContainers_Params
{
	struct FGameplayTagContainer                       InOutTagContainer;                                        // (Parm, OutParm, ReferenceParm)
	struct FGameplayTagContainer                       InTagContainer;                                           // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function GameplayTags.BlueprintGameplayTagLibrary.AddGameplayTag
struct UBlueprintGameplayTagLibrary_AddGameplayTag_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (Parm, OutParm, ReferenceParm)
	struct FGameplayTag                                Tag;                                                      // (Parm)
};

// Function GameplayTags.GameplayTagAssetInterface.HasMatchingGameplayTag
struct UGameplayTagAssetInterface_HasMatchingGameplayTag_Params
{
	struct FGameplayTag                                TagToCheck;                                               // (Parm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.GameplayTagAssetInterface.HasAnyMatchingGameplayTags
struct UGameplayTagAssetInterface_HasAnyMatchingGameplayTags_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.GameplayTagAssetInterface.HasAllMatchingGameplayTags
struct UGameplayTagAssetInterface_HasAllMatchingGameplayTags_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GameplayTags.GameplayTagAssetInterface.GetOwnedGameplayTags
struct UGameplayTagAssetInterface_GetOwnedGameplayTags_Params
{
	struct FGameplayTagContainer                       TagContainer;                                             // (Parm, OutParm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

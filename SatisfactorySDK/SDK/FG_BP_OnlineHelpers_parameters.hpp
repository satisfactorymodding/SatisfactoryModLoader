#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_OnlineHelpers_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.InsertionAddButton
struct UBP_OnlineHelpers_C_InsertionAddButton_Params
{
	class UPanelWidget*                                NewParam;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetSessionFromFriendNetId
struct UBP_OnlineHelpers_C_GetSessionFromFriendNetId_Params
{
	class UObject*                                     WorldContext;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUniqueNetIdRepl                            friendNetId;                                              // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FBlueprintSessionResult                     session;                                                  // (Parm, OutParm)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.IsHost
struct UBP_OnlineHelpers_C_IsHost_Params
{
	class APlayerState*                                PlayerState;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APlayerController*                           OwningPlayer;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isOurself;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.CanJoinInvite
struct UBP_OnlineHelpers_C_CanJoinInvite_Params
{
	class UObject*                                     WorldContext;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FPendingInvite                              invite;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ECanJoinInviteResult>                  Result;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.IsInThisGame
struct UBP_OnlineHelpers_C_IsInThisGame_Params
{
	struct FFGOnlineFriend                             onlineFriend;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	class UObject*                                     WorldContext;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               inThisGame;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.CanSendInvite
struct UBP_OnlineHelpers_C_CanSendInvite_Params
{
	class UObject*                                     WorldContext;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FFGOnlineFriend                             _friend;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ECantInviteResult>                     canSend;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.IsFriendInOnlineSession
struct UBP_OnlineHelpers_C_IsFriendInOnlineSession_Params
{
	class UObject*                                     WorldContext;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FFGOnlineFriend                             frriend;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               inSession;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetCompactPresence
struct UBP_OnlineHelpers_C_GetCompactPresence_Params
{
	struct FOnlinePresence                             presence;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FFCompactPresence                           compactPresence;                                          // (Parm, OutParm, ZeroConstructor)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetFriendSession
struct UBP_OnlineHelpers_C_GetFriendSession_Params
{
	struct FFGOnlineFriend                             _friend;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UObject*                                     WorldContext;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FBlueprintSessionResult                     session;                                                  // (Parm, OutParm)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetInvitePresence
struct UBP_OnlineHelpers_C_GetInvitePresence_Params
{
	class UObject*                                     WorldContext;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FPendingInvite                              invite;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FOnlinePresence                             presence;                                                 // (Parm, OutParm)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetFriendPresence
struct UBP_OnlineHelpers_C_GetFriendPresence_Params
{
	struct FFGOnlineFriend                             onlineFriend;                                             // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	class UObject*                                     WorldContext;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FOnlinePresence                             ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.SessionVisibilityStringToEnum
struct UBP_OnlineHelpers_C_SessionVisibilityStringToEnum_Params
{
	class FString                                      String;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ESessionVisibility>                    Enum;                                                     // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

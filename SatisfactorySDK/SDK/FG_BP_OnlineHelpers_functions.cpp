// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_OnlineHelpers_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_OnlineHelpers.BP_OnlineHelpers_C.InsertionAddButton
// ()
// Parameters:
// class UPanelWidget*            NewParam                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_OnlineHelpers_C::InsertionAddButton(class UPanelWidget* NewParam, class UObject* __WorldContext)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.InsertionAddButton");

	UBP_OnlineHelpers_C_InsertionAddButton_Params params;
	params.NewParam = NewParam;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetSessionFromFriendNetId
// ()
// Parameters:
// class UObject*                 WorldContext                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUniqueNetIdRepl        friendNetId                    (BlueprintVisible, BlueprintReadOnly, Parm)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FBlueprintSessionResult session                        (Parm, OutParm)

void UBP_OnlineHelpers_C::GetSessionFromFriendNetId(class UObject* WorldContext, const struct FUniqueNetIdRepl& friendNetId, class UObject* __WorldContext, struct FBlueprintSessionResult* session)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetSessionFromFriendNetId");

	UBP_OnlineHelpers_C_GetSessionFromFriendNetId_Params params;
	params.WorldContext = WorldContext;
	params.friendNetId = friendNetId;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (session != nullptr)
		*session = params.session;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.IsHost
// ()
// Parameters:
// class APlayerState*            PlayerState                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APlayerController*       OwningPlayer                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           isOurself                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_OnlineHelpers_C::IsHost(class APlayerState* PlayerState, class APlayerController* OwningPlayer, class UObject* __WorldContext, bool* isOurself)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.IsHost");

	UBP_OnlineHelpers_C_IsHost_Params params;
	params.PlayerState = PlayerState;
	params.OwningPlayer = OwningPlayer;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (isOurself != nullptr)
		*isOurself = params.isOurself;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.CanJoinInvite
// ()
// Parameters:
// class UObject*                 WorldContext                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FPendingInvite          invite                         (BlueprintVisible, BlueprintReadOnly, Parm)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<ECanJoinInviteResult> Result                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_OnlineHelpers_C::CanJoinInvite(class UObject* WorldContext, const struct FPendingInvite& invite, class UObject* __WorldContext, TEnumAsByte<ECanJoinInviteResult>* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.CanJoinInvite");

	UBP_OnlineHelpers_C_CanJoinInvite_Params params;
	params.WorldContext = WorldContext;
	params.invite = invite;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.IsInThisGame
// ()
// Parameters:
// struct FFGOnlineFriend         onlineFriend                   (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// class UObject*                 WorldContext                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           inThisGame                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_OnlineHelpers_C::IsInThisGame(class UObject* WorldContext, class UObject* __WorldContext, struct FFGOnlineFriend* onlineFriend, bool* inThisGame)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.IsInThisGame");

	UBP_OnlineHelpers_C_IsInThisGame_Params params;
	params.WorldContext = WorldContext;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (onlineFriend != nullptr)
		*onlineFriend = params.onlineFriend;
	if (inThisGame != nullptr)
		*inThisGame = params.inThisGame;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.CanSendInvite
// ()
// Parameters:
// class UObject*                 WorldContext                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FFGOnlineFriend         _friend                        (BlueprintVisible, BlueprintReadOnly, Parm)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<ECantInviteResult> canSend                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_OnlineHelpers_C::CanSendInvite(class UObject* WorldContext, const struct FFGOnlineFriend& _friend, class UObject* __WorldContext, TEnumAsByte<ECantInviteResult>* canSend)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.CanSendInvite");

	UBP_OnlineHelpers_C_CanSendInvite_Params params;
	params.WorldContext = WorldContext;
	params._friend = _friend;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (canSend != nullptr)
		*canSend = params.canSend;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.IsFriendInOnlineSession
// ()
// Parameters:
// class UObject*                 WorldContext                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FFGOnlineFriend         frriend                        (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           inSession                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_OnlineHelpers_C::IsFriendInOnlineSession(class UObject* WorldContext, class UObject* __WorldContext, struct FFGOnlineFriend* frriend, bool* inSession)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.IsFriendInOnlineSession");

	UBP_OnlineHelpers_C_IsFriendInOnlineSession_Params params;
	params.WorldContext = WorldContext;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (frriend != nullptr)
		*frriend = params.frriend;
	if (inSession != nullptr)
		*inSession = params.inSession;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetCompactPresence
// ()
// Parameters:
// struct FOnlinePresence         presence                       (BlueprintVisible, BlueprintReadOnly, Parm)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FFCompactPresence       compactPresence                (Parm, OutParm, ZeroConstructor)

void UBP_OnlineHelpers_C::GetCompactPresence(const struct FOnlinePresence& presence, class UObject* __WorldContext, struct FFCompactPresence* compactPresence)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetCompactPresence");

	UBP_OnlineHelpers_C_GetCompactPresence_Params params;
	params.presence = presence;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (compactPresence != nullptr)
		*compactPresence = params.compactPresence;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetFriendSession
// ()
// Parameters:
// struct FFGOnlineFriend         _friend                        (BlueprintVisible, BlueprintReadOnly, Parm)
// class UObject*                 WorldContext                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FBlueprintSessionResult session                        (Parm, OutParm)

void UBP_OnlineHelpers_C::GetFriendSession(const struct FFGOnlineFriend& _friend, class UObject* WorldContext, class UObject* __WorldContext, struct FBlueprintSessionResult* session)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetFriendSession");

	UBP_OnlineHelpers_C_GetFriendSession_Params params;
	params._friend = _friend;
	params.WorldContext = WorldContext;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (session != nullptr)
		*session = params.session;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetInvitePresence
// ()
// Parameters:
// class UObject*                 WorldContext                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FPendingInvite          invite                         (BlueprintVisible, BlueprintReadOnly, Parm)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FOnlinePresence         presence                       (Parm, OutParm)

void UBP_OnlineHelpers_C::GetInvitePresence(class UObject* WorldContext, const struct FPendingInvite& invite, class UObject* __WorldContext, struct FOnlinePresence* presence)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetInvitePresence");

	UBP_OnlineHelpers_C_GetInvitePresence_Params params;
	params.WorldContext = WorldContext;
	params.invite = invite;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (presence != nullptr)
		*presence = params.presence;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetFriendPresence
// ()
// Parameters:
// struct FFGOnlineFriend         onlineFriend                   (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// class UObject*                 WorldContext                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FOnlinePresence         ReturnValue                    (Parm, OutParm, ReturnParm)

struct FOnlinePresence UBP_OnlineHelpers_C::GetFriendPresence(const struct FFGOnlineFriend& onlineFriend, class UObject* WorldContext, class UObject* __WorldContext)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.GetFriendPresence");

	UBP_OnlineHelpers_C_GetFriendPresence_Params params;
	params.onlineFriend = onlineFriend;
	params.WorldContext = WorldContext;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_OnlineHelpers.BP_OnlineHelpers_C.SessionVisibilityStringToEnum
// ()
// Parameters:
// class FString                  String                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<ESessionVisibility> Enum                           (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_OnlineHelpers_C::SessionVisibilityStringToEnum(const class FString& String, class UObject* __WorldContext, TEnumAsByte<ESessionVisibility>* Enum)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_OnlineHelpers.BP_OnlineHelpers_C.SessionVisibilityStringToEnum");

	UBP_OnlineHelpers_C_SessionVisibilityStringToEnum_Params params;
	params.String = String;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Enum != nullptr)
		*Enum = params.Enum;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

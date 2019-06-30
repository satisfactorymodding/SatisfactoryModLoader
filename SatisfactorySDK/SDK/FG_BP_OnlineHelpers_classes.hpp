#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_OnlineHelpers_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_OnlineHelpers.BP_OnlineHelpers_C
// 0x0000 (0x0028 - 0x0028)
class UBP_OnlineHelpers_C : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_OnlineHelpers.BP_OnlineHelpers_C");
		return ptr;
	}


	void InsertionAddButton(class UPanelWidget* NewParam, class UObject* __WorldContext);
	void GetSessionFromFriendNetId(class UObject* WorldContext, const struct FUniqueNetIdRepl& friendNetId, class UObject* __WorldContext, struct FBlueprintSessionResult* session);
	void IsHost(class APlayerState* PlayerState, class APlayerController* OwningPlayer, class UObject* __WorldContext, bool* isOurself);
	void CanJoinInvite(class UObject* WorldContext, const struct FPendingInvite& invite, class UObject* __WorldContext, TEnumAsByte<ECanJoinInviteResult>* Result);
	void IsInThisGame(class UObject* WorldContext, class UObject* __WorldContext, struct FFGOnlineFriend* onlineFriend, bool* inThisGame);
	void CanSendInvite(class UObject* WorldContext, const struct FFGOnlineFriend& _friend, class UObject* __WorldContext, TEnumAsByte<ECantInviteResult>* canSend);
	void IsFriendInOnlineSession(class UObject* WorldContext, class UObject* __WorldContext, struct FFGOnlineFriend* frriend, bool* inSession);
	void GetCompactPresence(const struct FOnlinePresence& presence, class UObject* __WorldContext, struct FFCompactPresence* compactPresence);
	void GetFriendSession(const struct FFGOnlineFriend& _friend, class UObject* WorldContext, class UObject* __WorldContext, struct FBlueprintSessionResult* session);
	void GetInvitePresence(class UObject* WorldContext, const struct FPendingInvite& invite, class UObject* __WorldContext, struct FOnlinePresence* presence);
	struct FOnlinePresence GetFriendPresence(const struct FFGOnlineFriend& onlineFriend, class UObject* WorldContext, class UObject* __WorldContext);
	void SessionVisibilityStringToEnum(const class FString& String, class UObject* __WorldContext, TEnumAsByte<ESessionVisibility>* Enum);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

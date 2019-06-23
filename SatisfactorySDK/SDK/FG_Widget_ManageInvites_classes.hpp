#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManageInvites_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_ManageInvites.Widget_ManageInvites_C
// 0x0197 (0x03E8 - 0x0251)
class UWidget_ManageInvites_C : public UBP_MenuBase_C
{
public:
	unsigned char                                      UnknownData00[0x7];                                       // 0x0251(0x0007) MISSED OFFSET
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0258(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UFGMultiplayerVerticalBox*                   InvitePlayers;                                            // 0x0260(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UFGMultiplayerVerticalBox*                   ManageInvites;                                            // 0x0268(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_FrontEnd_Button_C*                   mInvitePlayers;                                           // 0x0270(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_SubMenuBackground_C*                 mNavigation;                                              // 0x0278(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_FrontEnd_Button_C*                   mReceivedInvites;                                         // 0x0280(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_SubMenuBackground_C*                 mSettings;                                                // 0x0288(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UFGWidgetSwitcher*                           mSwitcher;                                                // 0x0290(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UVerticalBox*                                OptionsList;                                              // 0x0298(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	struct FTimerHandle                                UpdateManageListTimer;                                    // 0x02A0(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	TMap<class UWidget_Multiplayer_ListButton_C*, struct FFGOnlineFriend> mButtonToFriend;                                          // 0x02A8(0x0050) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TMap<class UWidget_Multiplayer_ListButton_C*, struct FPendingInvite> mButtonToInvite;                                          // 0x02F8(0x0050) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TMap<struct FUniqueNetIdRepl, class UWidget_Multiplayer_ListButton_C*> mFriendToButton;                                          // 0x0348(0x0050) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TMap<struct FPendingInvite, class UWidget_Multiplayer_ListButton_C*> mInviteToButton;                                          // 0x0398(0x0050) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_ManageInvites.Widget_ManageInvites_C");
		return ptr;
	}


	void AddInviteToInviteList(struct FPendingInvite* invite);
	void UpdateFriendInviteButton(struct FUniqueNetIdRepl* netId);
	void SetupButtonForJoinInvite(class UWidget_Multiplayer_ListButton_C* Button, struct FPendingInvite* invite);
	void SetupButtonForSendInvite(class UWidget_Multiplayer_ListButton_C* Button, const struct FFGOnlineFriend& onlineFriend);
	void UpdateOrAddFriendsToInvite(TArray<struct FFGOnlineFriend>* UpdatedFriends);
	void UpdateInviteFriendButton(const struct FUniqueNetIdRepl& friendId);
	void PopulateInviteList();
	void ClearInviteList();
	void ClearInvitePlayerList();
	void PopulateFriendsToInvite();
	void OnEscape();
	void Construct();
	void OnJoinInvite(class UWidget_Multiplayer_ListButton_C* Button);
	void AddInvitePlayersDelegates();
	void FriendListUpdated_InvitePlayerss(const struct FUpdatedFriends& UpdatedFriends);
	void PresenceUpdated_InvitePlayers(const struct FUniqueNetIdRepl& updatedId);
	void RemoveInvitePlayersDelegates();
	void AddManageInvitesDelegates();
	void FriendsPresenceUpdate_ManageInvites(const struct FUniqueNetIdRepl& updatedId);
	void RemoveManageInvitesDelegates();
	void InviteReceived_ManageInvites(const struct FPendingInvite& receivedInvite);
	void OnMenuExit(class UWidget** prevMenu, bool* noAnimation);
	void BndEvt__mSwitcher_K2Node_ComponentBoundEvent_0_OnActiveWidgetSet__DelegateSignature(class UWidget* oldWidget, class UWidget* newWidget);
	void OnMenuEnter(class UWidget** prevMenu);
	void Destruct();
	void OnInvite(class UWidget_Multiplayer_ListButton_C* ClickedButton);
	void ExecuteUbergraph_Widget_ManageInvites(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

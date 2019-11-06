#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_NetworkErrorPopup_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C
// 0x0038 (0x0240 - 0x0208)
class UWidget_NetworkErrorPopup_C : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0208(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UOverlay*                                    mContent;                                                 // 0x0210(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UFGGameInstance*                             FGGameInstance;                                           // 0x0218(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasPopupOpen;                                            // 0x0220(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0221(0x0007) MISSED OFFSET
	struct FFGGameNetworkErrorMsg                      LatestMessage;                                            // 0x0228(0x0018) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C");
		return ptr;
	}


	void CreatePopup(const struct FFGGameNetworkErrorMsg& FGGameNetworkErrorMsg);
	void Construct();
	void mOnNetworkErrorRecieved_Event_1(TEnumAsByte<ENetworkFailure> errorType, const class FString& errorMsg);
	void CheckErrors();
	void OnPopupClosed(bool NewParam);
	void ExecuteUbergraph_Widget_NetworkErrorPopup(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

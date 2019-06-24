#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_DebugCameraController_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_DebugCameraController.BP_DebugCameraController_C
// 0x0010 (0x06D0 - 0x06C0)
class ABP_DebugCameraController_C : public ADebugCameraController
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x06C0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class AFGHUD*                                      mOriginalHUD;                                             // 0x06C8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_DebugCameraController.BP_DebugCameraController_C");
		return ptr;
	}


	void UserConstructionScript();
	void InpActEvt_Shift_P_K2Node_InputKeyEvent_1(const struct FKey& Key);
	void ReceiveOnActivate(class APlayerController** OriginalPC);
	void ReceiveOnDeactivate(class APlayerController** RestoredPC);
	void ExecuteUbergraph_BP_DebugCameraController(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

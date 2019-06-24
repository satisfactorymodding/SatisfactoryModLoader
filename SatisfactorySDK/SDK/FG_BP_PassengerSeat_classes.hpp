#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_PassengerSeat_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_PassengerSeat.BP_PassengerSeat_C
// 0x0020 (0x03F0 - 0x03D0)
class ABP_PassengerSeat_C : public AFGPassengerSeat
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03D0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USpringArmComponent*                         SpringArm;                                                // 0x03D8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPostProcessComponent*                       PostProcess;                                              // 0x03E0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UCameraComponent*                            Camera;                                                   // 0x03E8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_PassengerSeat.BP_PassengerSeat_C");
		return ptr;
	}


	void UserConstructionScript();
	void InpActEvt_Use_K2Node_InputActionEvent_1(const struct FKey& Key);
	void UpdateCamera();
	void ReceivePossessed(class AController** NewController);
	void ReceiveUnpossessed(class AController** OldController);
	void Server_Leave();
	void ExecuteUbergraph_BP_PassengerSeat(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

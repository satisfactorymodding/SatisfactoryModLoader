#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_RailroadVehicleSoundComponent_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C
// 0x0008 (0x0278 - 0x0270)
class UBP_RailroadVehicleSoundComponent_C : public UFGRailroadVehicleSoundComponent
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0270(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C");
		return ptr;
	}


	void UpdateRTPCs();
	void ReceiveBeginPlay();
	void OnStartedMoving();
	void OnStoppedMoving();
	void ExecuteUbergraph_BP_RailroadVehicleSoundComponent(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

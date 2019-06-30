#pragma once

// Satisfactory SDK

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
// 0x0009 (0x0279 - 0x0270)
class UBP_RailroadVehicleSoundComponent_C : public UFGRailroadVehicleSoundComponent
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0270(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	bool                                               mIdleSoundWasNotValid;                                    // 0x0278(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C");
		return ptr;
	}


	void mSpeedKmH(float* Speed);
	void OnStoppedMoving();
	void OnStartedMoving();
	void UpdateRTPCs();
	void OnDynamicBrakesApplied();
	void OnAirBrakesApplied();
	void OnAirBrakesReleased();
	void OnDynamicBrakesReleased();
	void OnThrottleReleased();
	void OnThrottleApplied();
	void OnStoppedMovingRelay();
	void ReceiveBeginPlay();
	void ExecuteUbergraph_BP_RailroadVehicleSoundComponent(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

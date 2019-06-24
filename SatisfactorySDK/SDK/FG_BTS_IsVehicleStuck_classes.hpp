#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_IsVehicleStuck_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTS_IsVehicleStuck.BTS_IsVehicleStuck_C
// 0x0034 (0x00CC - 0x0098)
class UBTS_IsVehicleStuck_C : public UBTService_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0098(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      IsStuckKey;                                               // 0x00A0(0x0028) (Edit, BlueprintVisible)
	float                                              mTimeSpentStuck;                                          // 0x00C8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTS_IsVehicleStuck.BTS_IsVehicleStuck_C");
		return ptr;
	}


	void ReceiveTickAI(class AAIController** OwnerController, class APawn** ControlledPawn, float* DeltaSeconds);
	void ExecuteUbergraph_BTS_IsVehicleStuck(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_CheckNearbyThreats_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTS_CheckNearbyThreats.BTS_CheckNearbyThreats_C
// 0x0060 (0x00F8 - 0x0098)
class UBTS_CheckNearbyThreats_C : public UBTService_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0098(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      ThreatNearbyBBkey;                                        // 0x00A0(0x0028) (Edit, BlueprintVisible)
	struct FBlackboardKeySelector                      NearbyActorBBKey;                                         // 0x00C8(0x0028) (Edit, BlueprintVisible)
	class AChar_Hog_C*                                 localHogPawn;                                             // 0x00F0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTS_CheckNearbyThreats.BTS_CheckNearbyThreats_C");
		return ptr;
	}


	void ReceiveTickAI(class AAIController** OwnerController, class APawn** ControlledPawn, float* DeltaSeconds);
	void ExecuteUbergraph_BTS_CheckNearbyThreats(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

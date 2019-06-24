#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_EQSTestingPawn_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_EQSTestingPawn.BP_EQSTestingPawn_C
// 0x0008 (0x07D8 - 0x07D0)
class ABP_EQSTestingPawn_C : public AEQSTestingPawn
{
public:
	class UAIPerceptionComponent*                      AIPerception;                                             // 0x07D0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_EQSTestingPawn.BP_EQSTestingPawn_C");
		return ptr;
	}


	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

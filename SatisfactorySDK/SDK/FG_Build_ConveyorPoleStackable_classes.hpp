#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorPoleStackable_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_ConveyorPoleStackable.Build_ConveyorPoleStackable_C
// 0x0010 (0x05A8 - 0x0598)
class ABuild_ConveyorPoleStackable_C : public AFGConveyorPoleStackable
{
public:
	class UBP_LadderComponent_C*                       BP_LadderComponent1;                                      // 0x0598(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_LadderComponent_C*                       BP_LadderComponent;                                       // 0x05A0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_ConveyorPoleStackable.Build_ConveyorPoleStackable_C");
		return ptr;
	}


	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

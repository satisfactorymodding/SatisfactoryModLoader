#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ManufacturerMk2_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_ManufacturerMk2.Build_ManufacturerMk2_C
// 0x0008 (0x0710 - 0x0708)
class ABuild_ManufacturerMk2_C : public ABuild_ManufacturerMk1_C
{
public:
	class UBP_LadderComponent_C*                       BP_LadderComponent;                                       // 0x0708(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_ManufacturerMk2.Build_ManufacturerMk2_C");
		return ptr;
	}


	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_WaterPostProcess_Lake_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_WaterPostProcess_Lake.BP_WaterPostProcess_Lake_C
// 0x0000 (0x0520 - 0x0520)
class UBP_WaterPostProcess_Lake_C : public UFGSharedPostProcessSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_WaterPostProcess_Lake.BP_WaterPostProcess_Lake_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

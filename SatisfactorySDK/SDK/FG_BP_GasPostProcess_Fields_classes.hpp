#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_GasPostProcess_Fields_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_GasPostProcess_Fields.BP_GasPostProcess_Fields_C
// 0x0000 (0x0520 - 0x0520)
class UBP_GasPostProcess_Fields_C : public UFGSharedPostProcessSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_GasPostProcess_Fields.BP_GasPostProcess_Fields_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

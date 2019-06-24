#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_PowerPoleMk3_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_PowerPoleMk3.Build_PowerPoleMk3_C
// 0x0000 (0x0598 - 0x0598)
class ABuild_PowerPoleMk3_C : public ABuild_PowerPoleMk1_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_PowerPoleMk3.Build_PowerPoleMk3_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

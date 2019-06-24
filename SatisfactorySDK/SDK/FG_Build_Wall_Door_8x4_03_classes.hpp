#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_Wall_Door_8x4_03_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_Wall_Door_8x4_03.Build_Wall_Door_8x4_03_C
// 0x0000 (0x0578 - 0x0578)
class ABuild_Wall_Door_8x4_03_C : public AFGBuildableWall
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_Wall_Door_8x4_03.Build_Wall_Door_8x4_03_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

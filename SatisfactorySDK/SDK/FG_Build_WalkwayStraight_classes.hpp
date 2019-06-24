#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_WalkwayStraight_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_WalkwayStraight.Build_WalkwayStraight_C
// 0x0000 (0x0580 - 0x0580)
class ABuild_WalkwayStraight_C : public AFGBuildableWalkway
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_WalkwayStraight.Build_WalkwayStraight_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

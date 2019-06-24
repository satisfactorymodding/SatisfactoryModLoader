#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Area_SouthernForest_2_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Area_SouthernForest_2.Area_SouthernForest_1_C
// 0x0000 (0x0060 - 0x0060)
class UArea_SouthernForest_1_C : public UFGMapArea
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Area_SouthernForest_2.Area_SouthernForest_1_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

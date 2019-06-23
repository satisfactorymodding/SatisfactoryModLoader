#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AmbientSetting_MazeCanyons_Lake_Water_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass AmbientSetting_MazeCanyons_Lake_Water.AmbientSetting_MazeCanyons_Lake_Water_C
// 0x0000 (0x0050 - 0x0050)
class UAmbientSetting_MazeCanyons_Lake_Water_C : public UFGAmbientSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass AmbientSetting_MazeCanyons_Lake_Water.AmbientSetting_MazeCanyons_Lake_Water_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

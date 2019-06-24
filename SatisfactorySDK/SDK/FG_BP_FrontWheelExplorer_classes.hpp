#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_FrontWheelExplorer_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_FrontWheelExplorer.BP_FrontWheelExplorer_C
// 0x0000 (0x0128 - 0x0128)
class UBP_FrontWheelExplorer_C : public UFGVehicleWheel
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_FrontWheelExplorer.BP_FrontWheelExplorer_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

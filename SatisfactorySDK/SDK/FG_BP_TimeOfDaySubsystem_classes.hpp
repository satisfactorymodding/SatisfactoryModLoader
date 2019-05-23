#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_TimeOfDaySubsystem_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_TimeOfDaySubsystem.BP_TimeOfDaySubsystem_C
// 0x0000 (0x0378 - 0x0378)
class ABP_TimeOfDaySubsystem_C : public AFGTimeOfDaySubsystem
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_TimeOfDaySubsystem.BP_TimeOfDaySubsystem_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

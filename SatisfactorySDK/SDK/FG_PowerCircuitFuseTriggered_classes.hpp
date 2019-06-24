#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_PowerCircuitFuseTriggered_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass PowerCircuitFuseTriggered.PowerCircuitFuseTriggered_C
// 0x0000 (0x0280 - 0x0280)
class UPowerCircuitFuseTriggered_C : public UWidget_TextMessage_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass PowerCircuitFuseTriggered.PowerCircuitFuseTriggered_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_AmbientSettings_Caves_Medium_Rev10_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass AmbientSettings_Caves_Medium_Rev10.AmbientSettings_Caves_Medium_Rev10_C
// 0x0000 (0x0050 - 0x0050)
class UAmbientSettings_Caves_Medium_Rev10_C : public UFGAmbientSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass AmbientSettings_Caves_Medium_Rev10.AmbientSettings_Caves_Medium_Rev10_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

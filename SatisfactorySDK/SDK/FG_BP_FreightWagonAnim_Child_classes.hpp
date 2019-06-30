#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_FreightWagonAnim_Child_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass BP_FreightWagonAnim_Child.BP_FreightWagonAnim_Child_C
// 0x0000 (0x3278 - 0x3278)
class UBP_FreightWagonAnim_Child_C : public UBP_LocomotiveAnim_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass BP_FreightWagonAnim_Child.BP_FreightWagonAnim_Child_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

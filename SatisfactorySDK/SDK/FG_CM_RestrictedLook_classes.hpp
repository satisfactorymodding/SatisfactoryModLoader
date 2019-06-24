#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_CM_RestrictedLook_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass CM_RestrictedLook.CM_RestrictedLook_C
// 0x0000 (0x0060 - 0x0060)
class UCM_RestrictedLook_C : public UFGCameraModifierLimitLook
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass CM_RestrictedLook.CM_RestrictedLook_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

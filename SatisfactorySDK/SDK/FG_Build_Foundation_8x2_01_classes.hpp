#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_Foundation_8x2_01_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Build_Foundation_8x2_01.Build_Foundation_8x2_01_C
// 0x0008 (0x0588 - 0x0580)
class ABuild_Foundation_8x2_01_C : public AFGBuildableFoundation
{
public:
	class UBoxComponent*                               Clearance;                                                // 0x0580(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Build_Foundation_8x2_01.Build_Foundation_8x2_01_C");
		return ptr;
	}


	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

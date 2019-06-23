#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MinimapCaptureActor_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_MinimapCaptureActor.BP_MinimapCaptureActor_C
// 0x0008 (0x0348 - 0x0340)
class ABP_MinimapCaptureActor_C : public AFGMinimapCaptureActor
{
public:
	class UTexture2D*                                  mMapTexture;                                              // 0x0340(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_MinimapCaptureActor.BP_MinimapCaptureActor_C");
		return ptr;
	}


	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

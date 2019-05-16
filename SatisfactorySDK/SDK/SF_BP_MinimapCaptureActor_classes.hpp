#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_MinimapCaptureActor_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_MinimapCaptureActor.BP_MinimapCaptureActor_C
// 0x0008 (0x0350 - 0x0348)
class ABP_MinimapCaptureActor_C : public AFGMinimapCaptureActor
{
public:
	class UTexture2D*                                  mMapTexture;                                              // 0x0348(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

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

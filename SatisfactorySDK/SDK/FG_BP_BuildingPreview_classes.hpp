#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildingPreview_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_BuildingPreview.BP_BuildingPreview_C
// 0x001C (0x036C - 0x0350)
class ABP_BuildingPreview_C : public AFGRenderTargetStage
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0350(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UDirectionalLightComponent*                  DirectionalLight1;                                        // 0x0358(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UDirectionalLightComponent*                  DirectionalLight;                                         // 0x0360(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mRotationSpeed;                                           // 0x0368(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_BuildingPreview.BP_BuildingPreview_C");
		return ptr;
	}


	void UserConstructionScript();
	void ReceiveTick(float* DeltaSeconds);
	void ExecuteUbergraph_BP_BuildingPreview(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

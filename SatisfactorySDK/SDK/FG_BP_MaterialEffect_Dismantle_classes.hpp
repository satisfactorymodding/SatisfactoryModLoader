#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_Dismantle_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C
// 0x0088 (0x01E8 - 0x0160)
class UBP_MaterialEffect_Dismantle_C : public UFGMaterialEffect_Build
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0160(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	float                                              mElapsedTime;                                             // 0x0168(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaterializeDuration;                                     // 0x016C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRuntimeFloatCurve                          mMaterializeCurve;                                        // 0x0170(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C");
		return ptr;
	}


	void OnStarted();
	void OnUpdate(float* DeltaTime);
	void PreStarted();
	void ExecuteUbergraph_BP_MaterialEffect_Dismantle(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

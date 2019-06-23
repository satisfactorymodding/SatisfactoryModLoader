#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_ConveyorBuild_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_MaterialEffect_ConveyorBuild.BP_MaterialEffect_ConveyorBuild_C
// 0x0010 (0x0170 - 0x0160)
class UBP_MaterialEffect_ConveyorBuild_C : public UFGMaterialEffect_Build
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0160(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class ABP_BuildEffect_ConveyorBelt_C*              mBuildEffectActor;                                        // 0x0168(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_MaterialEffect_ConveyorBuild.BP_MaterialEffect_ConveyorBuild_C");
		return ptr;
	}


	void PreStarted();
	void OnStarted();
	void ExecuteUbergraph_BP_MaterialEffect_ConveyorBuild(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_ManufacturerMk2_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// AnimBlueprintGeneratedClass Anim_ManufacturerMk2.Anim_ManufacturerMk2_C
// 0x004F (0x0FD0 - 0x0F81)
class UAnim_ManufacturerMk2_C : public UAnim_ManufacturerMk1_C
{
public:
	unsigned char                                      UnknownData00[0x7];                                       // 0x0F81(0x0007) MISSED OFFSET
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0F88(0x0008) (Transient, DuplicateTransient)
	class UParticleSystemComponent*                    mExhaustVfx01;                                            // 0x0F90(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mExhaustVfx02;                                            // 0x0F98(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mExhaustVfx03;                                            // 0x0FA0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mExhaustVfx04;                                            // 0x0FA8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mExhaustVfx05;                                            // 0x0FB0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mExhaustVfx06;                                            // 0x0FB8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mHeatGridVfx01;                                           // 0x0FC0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mHeatGridVfx02;                                           // 0x0FC8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("AnimBlueprintGeneratedClass Anim_ManufacturerMk2.Anim_ManufacturerMk2_C");
		return ptr;
	}


	void AnimNotify_ConstructorComplexIndustrialLeftOfflineState();
	void AnimNotify_ConstructorComplexIndustrialEnteredProducingState();
	void AnimNotify_ConstructorComplexIndustrialLeftProducingState();
	void AnimNotify_ConstructorComplexIndustrialEnteredOfflineState();
	void ExecuteUbergraph_Anim_ManufacturerMk2(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_NutBush_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_NutBush.BP_NutBush_C
// 0x0020 (0x03D8 - 0x03B8)
class ABP_NutBush_C : public ABP_Edible_C
{
public:
	class UStaticMesh*                                 Nuts1;                                                    // 0x03B8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 Nuts2;                                                    // 0x03C0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 Bush1;                                                    // 0x03C8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 Bush2;                                                    // 0x03D0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_NutBush.BP_NutBush_C");
		return ptr;
	}


	class UAkAudioEvent* GetDestroyAudioEvent();
	class UParticleSystem* GetDestroyEffect();
	float GetForceThreshold();
	class UStaticMeshComponent* GetMeshComponent();
	bool IsChainsawable();
	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

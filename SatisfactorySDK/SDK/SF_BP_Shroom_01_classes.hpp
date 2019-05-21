#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_Shroom_01_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_Shroom_01.BP_Shroom_01_C
// 0x0010 (0x03C8 - 0x03B8)
class ABP_Shroom_01_C : public ABP_Edible_C
{
public:
	TArray<class UStaticMesh*>                         mMeshAlternatives;                                        // 0x03B8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_Shroom_01.BP_Shroom_01_C");
		return ptr;
	}


	class UAkAudioEvent* GetDestroyAudioEvent();
	class UParticleSystem* GetDestroyEffect();
	float GetForceThreshold();
	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

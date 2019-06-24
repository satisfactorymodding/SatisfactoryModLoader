#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BerryBush_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_BerryBush.BP_BerryBush_C
// 0x0011 (0x03C9 - 0x03B8)
class ABP_BerryBush_C : public ABP_Edible_C
{
public:
	TArray<struct FBerryAlternatives>                  mBerryVariation;                                          // 0x03B8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	bool                                               mLockVariation;                                           // 0x03C8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_BerryBush.BP_BerryBush_C");
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

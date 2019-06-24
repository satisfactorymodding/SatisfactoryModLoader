#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_EliteCaveStinger_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Char_EliteCaveStinger.Char_EliteCaveStinger_C
// 0x0036 (0x09EE - 0x09B8)
class AChar_EliteCaveStinger_C : public AChar_Stinger_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x09B8(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USceneComponent*                             Scene;                                                    // 0x09C0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    ParticleSystem3;                                          // 0x09C8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    ParticleSystem2;                                          // 0x09D0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    ParticleSystem1;                                          // 0x09D8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    ParticleSystem;                                           // 0x09E0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              GasOnHitChance;                                           // 0x09E8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               OffCooldown;                                              // 0x09EC(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bSpawnGas;                                                // 0x09ED(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Char_EliteCaveStinger.Char_EliteCaveStinger_C");
		return ptr;
	}


	void OnRep_bSpawnGass();
	void UserConstructionScript();
	void SpawnGas();
	void GasEffect();
	void ExecuteUbergraph_Char_EliteCaveStinger(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

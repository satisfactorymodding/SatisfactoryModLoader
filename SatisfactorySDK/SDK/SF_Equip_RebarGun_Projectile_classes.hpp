#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Equip_RebarGun_Projectile_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Equip_RebarGun_Projectile.Equip_RebarGun_Projectile_C
// 0x0024 (0x045C - 0x0438)
class AEquip_RebarGun_Projectile_C : public AFGWeaponProjectileFire
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0438(0x0008) (Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      RebarGun_skl;                                             // 0x0440(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0448(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mMuteDryFire;                                             // 0x0450(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0451(0x0003) MISSED OFFSET
	int                                                mRandomReloadAnim;                                        // 0x0454(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mRandomStingerAnim;                                       // 0x0458(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Equip_RebarGun_Projectile.Equip_RebarGun_Projectile_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayFireEffect();
	void PlayReloadEffects();
	void WasEquipped();
	void WasUnEquipped();
	void PlayFailedToFireEffects();
	void ExecuteUbergraph_Equip_RebarGun_Projectile(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

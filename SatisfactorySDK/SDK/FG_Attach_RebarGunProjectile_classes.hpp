#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_RebarGunProjectile_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attach_RebarGunProjectile.Attach_RebarGunProjectile_C
// 0x0018 (0x0388 - 0x0370)
class AAttach_RebarGunProjectile_C : public AFGWeaponAttachmentProjectile
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0370(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      RebarGun_skl;                                             // 0x0378(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0380(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attach_RebarGunProjectile.Attach_RebarGunProjectile_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayFireEffect(struct FVector* flashLocation);
	void ClientPlayReloadEffect();
	void PlayAttachEffects3P();
	void ExecuteUbergraph_Attach_RebarGunProjectile(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

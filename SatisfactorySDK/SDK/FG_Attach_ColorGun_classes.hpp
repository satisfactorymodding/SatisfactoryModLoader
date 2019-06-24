#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_ColorGun_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attach_ColorGun.Attach_ColorGun_C
// 0x0018 (0x0388 - 0x0370)
class AAttach_ColorGun_C : public AFGWeaponAttachment
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0370(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      Colorgun_skl;                                             // 0x0378(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0380(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attach_ColorGun.Attach_ColorGun_C");
		return ptr;
	}


	void UserConstructionScript();
	void ClientPlayReloadEffect();
	void PlayFireEffect(struct FVector* flashLocation);
	void PlayAttachEffects3P();
	void ExecuteUbergraph_Attach_ColorGun(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

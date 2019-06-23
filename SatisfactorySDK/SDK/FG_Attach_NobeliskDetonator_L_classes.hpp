#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_NobeliskDetonator_L_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C
// 0x0018 (0x0390 - 0x0378)
class AAttach_NobeliskDetonator_L_C : public AFGNobeliskDetonatorAttachment
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0378(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      Detonator_skel;                                           // 0x0380(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0388(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C");
		return ptr;
	}


	void UserConstructionScript();
	void ClientPlayReloadEffect();
	void PlayFireEffect(struct FVector* flashLocation);
	void PlayAttachEffects3P();
	void ExecuteUbergraph_Attach_NobeliskDetonator_L(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

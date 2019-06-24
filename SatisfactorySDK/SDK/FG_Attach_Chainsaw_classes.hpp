#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_Chainsaw_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attach_Chainsaw.Attach_Chainsaw_C
// 0x0030 (0x0390 - 0x0360)
class AAttach_Chainsaw_C : public AFGEquipmentAttachment
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0360(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      Chainsaw_skl;                                             // 0x0368(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0370(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               IsSawing;                                                 // 0x0378(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               IsSawEngaged;                                             // 0x0379(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x037A(0x0006) MISSED OFFSET
	class UParticleSystemComponent*                    mSawingVfx;                                               // 0x0380(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UAnimInstance*                               mAnim3pInstance;                                          // 0x0388(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attach_Chainsaw.Attach_Chainsaw_C");
		return ptr;
	}


	void UserConstructionScript();
	void OnAttachmentUseStateUpdated(int* newUseState);
	void PlayAttachEffects3P();
	void PlayDetachEffects3P();
	void ExecuteUbergraph_Attach_Chainsaw(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
